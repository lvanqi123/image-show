#include "mainwindow.h"
#include <QApplication>
int x=5;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
