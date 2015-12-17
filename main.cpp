#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(
        "QPushButton{font-family:""Consolas"";font-size: 20px;color: #fff;background-color: #5cb85c;border-color: #4cae4c;height:35px;width:80px;border-radius: 5px 5px 0 0;}"
        "QPushButton:hover{color: #fff;background-color: #449d44; border-color: #398439;}"

        "QLabel{font-family:""Consolas"";font-size: 30px;text-align: center;border-radius: 5px 5px 0px 0px;}"

        "QLineEdit{font-family:""微软雅黑"";font-size: 30px;text-align: center;width: 100%;height:35px; padding: 6px 12px;line-height: 1.42857143;color: #555;background-color: #fff;border: 1px solid #ccc;border-radius: 4px;}"
                );
    MainWindow w;
    w.show();

    return a.exec();
}
