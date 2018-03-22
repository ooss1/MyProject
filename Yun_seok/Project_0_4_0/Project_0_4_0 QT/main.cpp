#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    int pid;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    pid=fork();
    if(pid==0) execl("./device_manager",NULL);
    return a.exec();
}
