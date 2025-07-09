#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generatePassword();
    void copyToClipboard();
    void showHistory();
    void savePassword();
    void updateLength(int value);
    void updateStrength();

private:
    Ui::MainWindow *ui;
    QSettings settings;
    QList<QString> passwordHistory;
    
    QString generateRandomPassword(int length, 
                                  bool useLetters, 
                                  bool useNumbers, 
                                  bool useSymbols) const;
    int calculateStrength(const QString &password) const;
    void saveToHistory(const QString &password);
};
#endif // MAINWINDOW_H
