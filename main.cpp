#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用元数据
    app.setApplicationName("密码生成器");
    app.setApplicationVersion("1.1");
    app.setOrganizationName("SecureTools");
    
    // 设置样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
