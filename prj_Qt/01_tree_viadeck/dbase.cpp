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
   // msqlmdl = new MySqlModel;
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
  //  qDebug() << "-- adding records ended      *******";
}



bool dBase::addRecord(int grpCd, int accCd, QString  accNm )
{
    // control the existence of the account name in the table

    QSqlQueryModel query;
    query.setQuery (QString("SELECT * "
                              "FROM dbtb_accounts "
                              "WHERE f_AccountName = '%1' ")
                          .arg(accNm) );

    if ( query.rowCount() > 0 )
    {
       // qDebug ()<< query.rowCount()<<" KAYIT VAR "  ;
        /// bu isimde ekayıt var
        /// UYARI YAP
        /// geri dön
        ///

        return false;
    }
    else
    {
        qDebug ()<<"--İlk kayıt ekleniyor... :"
                 << query.rowCount() ;

        /// bu isimde kayıt yok yeni ekle
        ///
        /// ADD
        ///
        QString q= (QString( "insert into dbtb_accounts ("
                             "f_ParentCode, "
                             "f_AccountCode, "
                             "f_AccountName) "
                             "values( %1 , %2, '%3' ) ")
                         .arg(grpCd)
                         .arg(accCd)
                         .arg(accNm) );

        QSqlQuery qry;
        bool ok = qry.exec(q);

        if ( ! ok)
        {
            qDebug()<<"--Kayıt eklen e m e d i "
                     << qry.lastError ().text ();
        }

         Q_ASSERT_X(ok,"Kayıt eklenemedi",  "hata");
    }
    return true;
}



bool dBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "a_viadeck.db"  );

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
                        " ( f_ParentCode INTEGER ,"
                        " f_AccountCode INTEGER PRIMARY KEY,"
                        " f_AccountName TEXT) "))
            qDebug()<<query.lastError().text();
        qDebug() << "query executed table created . . .";
    }
    bool ok=db.open();
    Q_ASSERT_X(ok,"database open"," database can not open");
    return ok;
}

