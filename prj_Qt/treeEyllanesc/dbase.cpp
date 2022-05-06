#include "dbase.h"
#include <QSqlDatabase>
#include <QSqlError>

#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlTableModel>

dBase::dBase()
{
    qDebug() << "- create conn";
    createConnection();
    qDebug() << "-  conn created";
    qDebug() << "-- adding records *******";

        msqlmdl = new MySqlModel;
    addRecord ("ASSETS"                                       , 1, 0);
    addRecord ("FIXED ASSETS"                            , 101, 1 );
    addRecord ("TANGIBLE FIXED ASSETS"            , 10101, 101 );
    addRecord ("MACHINERY"               , 1010103, 10101 );
    addRecord ("LAND"                    , 1010101, 10101 );
    addRecord ("OFFICE EQUIPMENTS"       , 1010104, 10101 );
    addRecord ("MOTOR VEHICLES"          , 1010105, 10101 );
    addRecord ("INTANGIBLE FIXED ASSETS"          , 10102, 101 );
    addRecord ("COMPUTER SOFTWARE"       , 1010203, 10102 );
    addRecord ("GOODWILL"                , 10102001, 10102 );
    addRecord ("PATENTS & TRADE MARKS"   , 10102002, 10102 );
    addRecord ("ACC.DeP. FXD ASSETS"              , 10103, 101 );
    addRecord ("ACC.DP- MOTOR VHCLS"     , 10103004, 10103 );
    addRecord ("ACC.DP- OFF EQPMNTS"     , 10103003, 10103 );
    addRecord ("ACC.DP- MACHNRY"         , 10103001, 10103 );
    addRecord ("ACC.DP- COMPTRS"         , 10103002, 10103 );
    addRecord ("CURRENT ASSETS"                          , 102, 1 );
    addRecord ("dbtb_accounts RECEIVABLE"              , 10205, 102 );
    addRecord ("STOCK"                          , 1010105, 102 );
    addRecord ("DEPOSITS & PREPAYMENTS"           , 10212, 102 );
    addRecord ("LIABILITIES"                                  , 2, 0 );
    addRecord ("CAPITAL"                                      , 3, 0 );
    addRecord ("SALES"                                        , 4, 0 );
    addRecord ("EXPENSES"                                     , 5, 0 );
    qDebug() << "-- adding records ended      *******";
}



bool dBase::addRecord(QString  accNm, int accCd, int grpCd)
{
    // control the existence of the account name in the table


    msqlmdl->setQuery (QString("SELECT * "
                              "FROM dbtb_accounts "
                              "WHERE AcName = '%1' ")
                          .arg(accNm) );

    if ( msqlmdl->rowCount() > 0 )
    {
        qDebug ()<< msqlmdl->rowCount()<<" KAYIT VAR "  ;
        /// bu isimde ekayıt var
        /// UYARI YAP
        /// geri dön
        ///

        return false;
    }
    else
    {
        qDebug ()<<"--İlk kayıt ekleniyor... :"
                 << msqlmdl->rowCount() ;

        /// bu isimde kayıt yok yeni ekle
        ///
        /// ADD
        ///
        QString q= (QString( "insert into dbtb_accounts ("
                             "AcName, ActCod, GroupCode) "
                             "values( '%1' , %2 ,%3 ) ")
                         .arg(accNm)
                         .arg(accCd)
                         .arg(grpCd) );

        QSqlQuery qry;
        if ( qry.exec(q))
        {
            qDebug()<<"--Kayıt eklendi"<< qry.lastError ().text ();
        }
        else
        {
            qDebug()<<"--Kayıt eklen e m e d i " ;
        }
    }
    return true;
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
         contains( "dbtb_accounts" ))
    {
        QSqlQuery query;
        if(!query.exec("CREATE TABLE IF NOT EXISTS dbtb_accounts "
                        " ( AcName TEXT,"
                        "ActCod INTEGER,"
                        "GroupCode INTEGER ) "))
            qDebug()<<query.lastError().text();
        qDebug() << "query executed table created . . .";
    }
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
