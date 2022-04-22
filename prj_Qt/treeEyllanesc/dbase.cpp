#include "dbase.h"

dBase::dBase()
{
    createDb();
    dbName="db.db";
}

bool dBase::createDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (db.isValid())
    {
        qDebug () <<"--- db VALIDATED----" << db.driverName();
    }

    if( openDb() )
    {
        qDebug () <<"--- db OPENED for creating accounts table---";
        QSqlQuery query;
        QString qStr{};

        qStr =  "CREATE TABLE IF NOT EXISTS adm_ac "
                " ( "
                "AcName TEXT,"
                "ActCod INTEGER,"
                "GroupCode INTEGER "
                " ) ";

        if(!query.exec(qStr))
        {
            qDebug()<<query.lastError().text();
            qDebug() << QSqlDatabase::drivers();
            qDebug() <<  db.lastError().nativeErrorCode();
        }
        else
        {
            qDebug() << "query executed . . .";
        }
        if ( query.isActive())
        {
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
            return true;
        }
        else
        {
            qDebug () << "query is NOT active";
        }
    }
    qDebug () << "--- db CANNN NOTTT OPENED for creating accounts table---";
    db.close();
    db.removeDatabase(db.connectionName());

    return false;
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


