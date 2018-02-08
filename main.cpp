#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /*
    QPixmap pixmap(":/images/images/welcome_4.png");
    QSplashScreen screen(pixmap);

    a.processEvents();
    screen.show();
    screen.showMessage("Init driver service...",Qt::AlignRight | Qt::AlignBaseline,Qt::black);
    QThread::sleep(1);
    screen.showMessage("Load GUI Program...",Qt::AlignRight | Qt::AlignBaseline,Qt::black);

    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        a.processEvents();
    } while (n.secsTo(now)<=1);
    //screen.close();
    */
    qDebug() <<"Create windows";
    w.show();

    //

    return a.exec();
}
