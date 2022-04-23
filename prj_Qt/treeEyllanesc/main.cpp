#include "mainwindow.h"
#include "dbase.h"
#include <QSql>
#include <QSqlDriver>

#include <QSqlDatabase>
#include <QMessageBox>

#include <QApplication>
#include <QTreeView>

#include <QSqlDatabase>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
