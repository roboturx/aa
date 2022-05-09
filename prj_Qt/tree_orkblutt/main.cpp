#include "hc_tree.h"

#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include "../dbase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "--------------------- begin dbase ------------";
    dBase db;
    qDebug() << "----------------------- end dbase ------------";

    hC_Tree w;
    w.show();
    return a.exec();

}


