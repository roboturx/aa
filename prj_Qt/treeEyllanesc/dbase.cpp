#include "dbase.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlDriver>
dBase::dBase()
{
    createConnection();

}


bool dBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "db.db"  );

    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                    "Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit.";
        return false;
    }


    if ( ! db.tables().
         contains( "adm_ac" ))
    {
        QSqlQuery query;
        if(!query.exec("CREATE TABLE IF NOT EXISTS adm_ac "
                        " ( AcName TEXT,"
                        "ActCod INTEGER,"
                        "GroupCode INTEGER ) "))
            qDebug()<<query.lastError().text();
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
    return true;
}


bool dBase::openDb()
{
    if (db.open() )
    {
        qDebug()<<  "dBase opened.";
        return true;

    }
    else
    {
        qDebug()<<  "dBase NOT opened.";
        return false;
    }
}


