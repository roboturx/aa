#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "begin dbase---------------------";
    dBase db;
 //   db.openDb();
    qDebug() << "end dbase--------------------------";
qDebug() << "begin w---------------------";
    MainWindow w;
qDebug() << "end w---------------------";
    w.show();
    return a.exec();
}
