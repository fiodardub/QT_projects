#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Вычисление функций (qint64)");
    w.resize(500, 600);
    w.show();
    return a.exec();
}
