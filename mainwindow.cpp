#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDateTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>               // 添加 QTimer 头文件
#include <QStringListModel>     // 添加 QStringListModel 头文件
#include <QListView>            // 添加 QListView 头文件
#include <QDialog>              // 添加 QDialog 头文件
#include <QVBoxLayout>          // 添加 QVBoxLayout 头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings("PasswordGenerator", "Settings")
{
    ui->setupUi(this);
    setWindowTitle("密码生成器");
    
    // 加载历史记录
    passwordHistory = settings.value("history", QStringList()).toStringList();
    
    // 初始化UI
    ui->lengthSlider->setRange(8, 32);
    ui->lengthSlider->setValue(settings.value("length", 12).toInt());
    ui->lettersCheck->setChecked(settings.value("useLetters", true).toBool());
    ui->numbersCheck->setChecked(settings.value("useNumbers", true).toBool());
    ui->symbolsCheck->setChecked(settings.value("useSymbols", true).toBool());
    
    // 连接信号槽 - 使用 checkStateChanged 替代弃用的 stateChanged
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generatePassword);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyToClipboard);
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::showHistory);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::savePassword);
    connect(ui->lengthSlider, &QSlider::valueChanged, this, &MainWindow::updateLength);
    connect(ui->lettersCheck, &QCheckBox::checkStateChanged, this, &MainWindow::updateStrength);
    connect(ui->numbersCheck, &QCheckBox::checkStateChanged, this, &MainWindow::updateStrength);
    connect(ui->symbolsCheck, &QCheckBox::checkStateChanged, this, &MainWindow::updateStrength);
    
    // 初始生成密码
    generatePassword();
}

MainWindow::~MainWindow()
{
    // 保存设置
    settings.setValue("length", ui->lengthSlider->value());
    settings.setValue("useLetters", ui->lettersCheck->isChecked());
    settings.setValue("useNumbers", ui->numbersCheck->isChecked());
    settings.setValue("useSymbols", ui->symbolsCheck->isChecked());
    settings.setValue("history", passwordHistory);
    
    delete ui;
}

void MainWindow::generatePassword()
{
    const int length = ui->lengthSlider->value();
    const bool useLetters = ui->lettersCheck->isChecked();
    const bool useNumbers = ui->numbersCheck->isChecked();
    const bool useSymbols = ui->symbolsCheck->isChecked();
    
    QString password = generateRandomPassword(length, useLetters, useNumbers, useSymbols);
    ui->passwordDisplay->setText(password);
    updateStrength();
    saveToHistory(password);
}

QString MainWindow::generateRandomPassword(int length, 
                                          bool useLetters, 
                                          bool useNumbers, 
                                          bool useSymbols) const
{
    const QString letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString numbers = "0123456789";
    const QString symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    QString validChars;
    if (useLetters) validChars += letters;
    if (useNumbers) validChars += numbers;
    if (useSymbols) validChars += symbols;
    
    if (validChars.isEmpty()) {
        return "请至少选择一种字符类型";
    }
    
    QString password;
    // 正确使用 QRandomGenerator - 移除指针声明
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    
    for (int i = 0; i < length; ++i) {
        const int index = generator.bounded(validChars.length());
        password.append(validChars.at(index));
    }
    
    return password;
}

void MainWindow::copyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->passwordDisplay->text());
    
    // 提供视觉反馈
    ui->copyButton->setText("✓ 已复制");
    QTimer::singleShot(2000, this, [this]() {
        ui->copyButton->setText("复制密码");
    });
}

void MainWindow::updateLength(int value)
{
    ui->lengthLabel->setText(QString("密码长度: %1").arg(value));
    updateStrength();
}

void MainWindow::updateStrength()
{
    const QString password = ui->passwordDisplay->text();
    int strength = calculateStrength(password);
    
    // 更新强度指示器
    ui->strengthBar->setValue(strength);
    
    // 设置颜色
    QString color;
    if (strength < 30) color = "red";
    else if (strength < 70) color = "orange";
    else color = "green";
    
    ui->strengthBar->setStyleSheet(QString(
        "QProgressBar::chunk { background-color: %1; }"
    ).arg(color));
}

int MainWindow::calculateStrength(const QString &password) const
{
    if (password.isEmpty() || password == "请至少选择一种字符类型") return 0;
    
    int strength = 0;
    const int length = password.length();
    
    // 长度评分
    strength += qMin(length * 4, 40);
    
    // 字符种类评分
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;
    for (const QChar &c : password) {
        if (c.isLower()) hasLower = true;
        else if (c.isUpper()) hasUpper = true;
        else if (c.isDigit()) hasDigit = true;
        else hasSymbol = true;
    }
    
    int charTypes = (hasLower ? 1 : 0) + (hasUpper ? 1 : 0) + 
                   (hasDigit ? 1 : 0) + (hasSymbol ? 1 : 0);
    
    strength += (charTypes - 1) * 15;
    
    return qMin(strength, 100);
}

void MainWindow::showHistory()
{
    if (passwordHistory.isEmpty()) {
        QMessageBox::information(this, "历史记录", "没有历史记录");
        return;
    }
    
    QStringListModel model;
    model.setStringList(passwordHistory);
    
    QDialog dialog(this);
    dialog.setWindowTitle("密码历史记录");
    dialog.resize(400, 300);
    
    QVBoxLayout layout(&dialog);
    QListView listView;
    listView.setModel(&model);
    
    QPushButton closeButton("关闭", &dialog);
    connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    
    layout.addWidget(&listView);
    layout.addWidget(&closeButton);
    
    dialog.exec();
}

void MainWindow::savePassword()
{
    QString password = ui->passwordDisplay->text();
    if (password.isEmpty() || password == "请至少选择一种字符类型") {
        QMessageBox::warning(this, "保存失败", "没有有效的密码可保存");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "保存密码",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/passwords.txt",
        "文本文件 (*.txt)"
    );
    
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") 
               << ": " << password << "\n";
        file.close();
        QMessageBox::information(this, "保存成功", "密码已保存到文件");
    } else {
        QMessageBox::warning(this, "保存失败", "无法打开文件进行写入");
    }
}

void MainWindow::saveToHistory(const QString &password)
{
    if (passwordHistory.size() >= 20) {
        passwordHistory.removeFirst();
    }
    passwordHistory.append(QDateTime::currentDateTime().toString("hh:mm") + ": " + password);
}
