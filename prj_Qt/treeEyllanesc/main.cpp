#include "mainwindow.h"
#include "dbase.h"
#include <QSql>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QMessageBox>

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSqlDatabase>

enum RelationRoles{
    CodeRole = Qt::UserRole + 1000,
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QString qStr = "";

  //  dBase* dbase = new dBase;

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("dbName.db");
    if (!dbase.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE IF NOT EXISTS adm_ac "
                    " ( AcName TEXT,"
                    "ActCod INTEGER,"
                    "GroupCode INTEGER ) "))
    {
        qDebug() << "query NOT executed table NOT created . . .";
        qDebug()<<query.lastError().text();
        qDebug() << QSqlDatabase::drivers();
        qDebug() <<  dbase.lastError().nativeErrorCode();
    }
    else
    {
        qDebug() << "query executed table created . . .";
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"EXPENSES\", 5, 0)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"SALES\", 4, 0)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ASSETS\", 1, 0)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"CAPITAL\", 3, 0)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"LIAILITIES\", 2, 0)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"CURRENT ASSETS\", 102, 1)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"FIXED ASSETS\", 101, 1)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"INTANGIBLE FIXED ASSETS\", 10102, 101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACCUM.DEP. FIXED ASSETS\", 10103, 101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"TANGIBLE FIXED ASSETS\", 10101, 101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"MACHINERY\", 1010102, 10101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"COMPUTERS\", 1010103, 10101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"LAND\", 1010101, 10101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"OFFICE EQUIPMENTS\", 1010104, 10101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"MOTOR VEHICLES\", 1010105, 10101)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"COMPUTER SOFTWARE\", 1010203, 10102)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"GOODWILL\", 10102001, 10102)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"PATENTS & TRADE MARKS\", 10102002, 10102)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACC.DEP- MOTOR VEHICLES\", 10103004, 10103)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACC.DEP- OFFICE EQUIPMENTS\", 10103003, 10103)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACC.DEP- MACHINERY\", 10103001, 10103)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACC.DEP- COMPUTERS\", 10103002, 10103)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"ACCOUNTS RECEIVABLE\", 10205, 102)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"STOCK\", 1010105, 102)");
        query.exec("insert into adm_ac(AcName, ActCod, GroupCode) values(\"DEPOSITS & PREPAYMENTS\", 10212, 102)");

    }
        qDebug () <<"- QSQLITE available - main";

    qDebug() << "000----------------------------------";
    qDebug() << dbase.lastError().text();
    qDebug()<<"Dbdriver : "<<dbase.driverName();
    QStandardItemModel model;
 qDebug() <<"000";
    if(!dbase.open())
     qWarning() << "ERROR: " << dbase.lastError();
    if (dbase.isValid())
    {
        qDebug() <<"100";
        dbase.open();
        qDebug() <<"200";
        if (dbase.isOpen())
        {
            qDebug() <<"300";
            QSqlQuery query2;
            query2.prepare("SELECT GroupCode, AcName, ActCod from adm_ac");
            query2.exec();
            if ( query2.isActive())
            {
                qDebug() <<"400";
                //model->setQuery(query);
                qDebug() <<"query is active-----------------------";


                const QSqlRecord rec = query2.record();
                while (query2.next()) {
                    QString AcName = query2.value(rec.indexOf("AcName")).toString();
                    int GroupCode = query2.value(rec.indexOf("GroupCode")).toInt();
                    int ActCod = query2.value(rec.indexOf("ActCod")).toInt();
                    QStandardItem *it = new QStandardItem(AcName);
                    it->setData(ActCod, RelationRoles::CodeRole);
                    if(GroupCode == 0)
                        model.invisibleRootItem()->appendRow(it);
                    else{
                        QModelIndexList ixs = model.match(model.index(0, 0),
                                                          RelationRoles::CodeRole,
                                                          GroupCode,
                                                          1,
                                                          Qt::MatchExactly| Qt::MatchRecursive);
                        if(ixs.size() > 0){
                            QStandardItem *parent = model.itemFromIndex(ixs.first());
                            parent->appendRow(it);
                        }
                    }
                }


                dbase.close();
                qDebug() << "opened success\n";
            }
            else
            {
                qDebug() << "001 -----------------------------------------------------";
                qDebug() << "    query is not active：DB being occupied, close manually";
                qDebug() << dbase.lastError().text();
                qFatal("failed to connect.");
                dbase.lastError().text();
                qDebug()<<"Dbdriver : "<<dbase.driverName();
                dbase.close();
                dbase.removeDatabase(dbase.connectionName());
                qApp->exit(1) ;
                qDebug()<<"NOT SELECTED";

            }
        }
        else
        {
            qDebug() << "DB is not open";

        }
    }
    else
    {
        qDebug() << "002 ---------------------------------------------------";
        qDebug() << "    DB is not valid ";
        qDebug() << "    query is not active：DB being occupied, close manually";
        qDebug() << dbase.lastError().text();
        qFatal("       failed to connect.");
        qDebug()<<"       Dbdriver : "<<dbase.driverName();
        dbase.close();
        dbase.removeDatabase(dbase.connectionName());
        qApp->exit(1) ;
        qDebug()<<"       NOT SELECTED";

    }





    QTreeView w;
    w.setModel(&model);
    w.expandAll();
    w.show();
    // MainWindow w;
    //w.show();
    return a.exec();
}
