#include "dbase.h"
#include <QSqlDatabase>
#include <QSqlError>

#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlTableModel>
#include "mysqlmodel.h"

dBase::dBase()
{
    qDebug() << "dBase";
    createConnection();
    msqlmdl = new QSqlQueryModel;

    addRecord (0,1,"VARLIKLAR");
    addRecord (  1,10,"DÖNEN VARLIKLAR");
    addRecord (    10,100,"KASA");
    addRecord (    10,101,"ALINAN ÇEKLER");
    addRecord (    10,102,"BANKALAR");
    addRecord (0,2,"DURAN VARLIKLAR" );
    addRecord (  2,22,"TİCARİ ALACAKLAR" );
    addRecord (    22,220,"ALICILAR" );
    addRecord (    22,221,"ALACAK SENETLERİ" );
    addRecord (0,3,"KISA VADELİ YABANCI KAYNAKLAR" );
    addRecord (0,4,"UZUN VADELİ YABANCI KAYNAKLAR" );
    addRecord (0,5,"SERMAYE" );

  // qDebug() << "-- adding records ended      *******";
}



bool dBase::addRecord(int prntCd,  int accCd,QString  accNm )
{
    // control the existence of the account name in the table
    msqlmdl->setQuery (QString("SELECT * "
                              "FROM dbtb_accounts "
                              "WHERE AcName = '%1' ")
                          .arg(accNm) );
    if ( msqlmdl->rowCount() > 0 )
    {
       // qDebug ()<< msqlmdl->rowCount()<<" KAYIT VAR "  ;
        /// bu isimde ekayıt var
        /// UYARI YAP
        /// geri dön
        ///

        return false;
    }
    else
    {
       // qDebug ()<<"--İlk kayıt ekleniyor... :"
       //          << msqlmdl->rowCount() ;

        /// bu isimde kayıt yok yeni ekle
        ///
        /// ADD
        ///
        QString q= (QString( "insert into dbtb_accounts ("
                             "parentCode,  ActCod, AcName ) "
                             "values( %1 , %2, '%3' ) ")
                         .arg(prntCd)
                         .arg(accCd)
                         .arg(accNm) );

        QSqlQuery qry;
        if ( qry.exec(q))
        {
            qDebug()<<"--Kayıt eklendi";
        }
        else
        {
            qDebug()<<"--Kayıt e k l e n e m e d i "<< qry.lastError ().text () ;
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
                        " ( parentCode INTEGER,"
                        " ActCod INTEGER,"
                        " AcName TEXT) "))
            qDebug()<<query.lastError().text();
        qDebug() << "query executed table created . . .";
    }
    if (!db.open() )
    {
        qDebug()<<  "dBase NOT opened." ;
    }
    else return true;
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
