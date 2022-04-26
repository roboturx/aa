#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dBase db;
    db.openDb();
    MainWindow w;
    w.show();
    return a.exec();
}
