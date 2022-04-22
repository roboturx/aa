#include "hc_tree.h"

#include <QApplication>
#include <QtSql>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hC_Tree w;

    QSqlQuery query;
    QString qStr, mesaj;
    QString path = "db.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);


    if (db.open())
    {
        qDebug ()<< "base opened";
    } else
    {
        qDebug ()<< "base NOT opened";
    }


    qStr = "CREATE TABLE IF NOT EXISTS dbtb_knm "
           "( knm_id INTEGER PRIMARY KEY ,"
           "  knm_ad TEXT"
           " )";
    if ( ! query.exec (qStr))
    {
        mesaj = "HATA - Konum Dosyası Oluştur u l a m a d ı . . .  "
                "------------------------------------<br>"+
                query.lastError().text() +
                "------------------------------------";
    }
    else
    {
        qDebug ()<< "query executed";
        /*
         qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\1234\\bb\\cccc') ";
      if (query.exec(qStr))
      {
          qDebug () << "knm_ad added";
      }
      else
      {
          qDebug () << "knm_ad NOT added " + query.lastError().text();
      }
     qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\xxxx\\cccc') ";
      if (query.exec(qStr))
      {
          qDebug () << "knm_ad added";
      }
      else
      {
          qDebug () << "knm_ad NOT added " + query.lastError().text();
      }
      qStr="INSERT INTO dbtb_knm (knm_ad) values ('C:\\aaaa\\bbbb\\dddddddd') ";
      if (query.exec(qStr))
      {
          qDebug () << "knm_ad added";
      }
      else
      {
          qDebug () << "knm_ad NOT added " + query.lastError().text();
      }*/
    }

    w.show();
    return a.exec();
}
