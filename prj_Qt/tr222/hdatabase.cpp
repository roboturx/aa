#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>


#include "hdatabase.h"
#define DATABASE_NAME       "DataBase.db"

HDataBase::HDataBase(QObject *parent) : QObject(parent)
{

    qDebug()<<"Database constructor";
    msgBox = new QMessageBox ;


    if (!controlDriver())
    {
        msgBox->setText("DRIVER ERROR...");
        qDebug()<<"DRIVER ERROR...";
    }
    if (!connectToDataBase())
    {
        msgBox->setText("DATABASE ERROR...");
        qDebug()<<"DATABASE ERROR...";
    }

}

HDataBase::~HDataBase()
{

}

bool HDataBase::controlDriver()
{
    // if qt has driver
    qDebug() << "Controlling driver...";
    const QString DRIVER("QSQLITE");

    if(!QSqlDatabase::isDriverAvailable(DRIVER))
    {
        // not has driver !!!
        qDebug() << "Database driver error...";
        return false;
    }
    // qt has driver
    qDebug() << "Database driver OK";
    db = QSqlDatabase::addDatabase(DRIVER);
    // create database
    qDebug() << "Database added";
    db.setDatabaseName( DATABASE_NAME);
    qDebug() << "Database name : " << DATABASE_NAME;
    return true;
}

bool HDataBase::connectToDataBase()
{
    qDebug() << "Searching Database file on disk...";
    if(!QFile(DATABASE_NAME).exists())
    {
        qDebug() << "   NO FİLE - Database file creating....";
        if (!restoreDataBase())
        {
            qDebug() << "   Database file NOT created.";
            return false;
        }
        qDebug() << "   Database file created.";
    }
    else
    {
        qDebug() << "Database file on disk";
        openDataBase();
    }
    return true;
}



bool HDataBase::restoreDataBase()
{
    if(!openDataBase())
    {
        qDebug() << "Database CONNECTION ERROR...";
        return false;
    }
    qDebug() << "   Database tables creating...";
    if((!this->createHesapTable()) ||
        (!this->createYevmiyeTable()))
    {
        qDebug() << "   Database tables NOT created...";
        return false;
    }
    qDebug() << "   Database tables created...";
    return true;
}

bool HDataBase::openDataBase()
{
    /* cm. article QSqlTableModel */
    // hakkındaki makaleye bakın
    // db = QSqlDatabase::addDatabase("QSQLITE");
    //  db.setHostName(DATABASE_HOSTNAME);

    if(db.open())
    {
        qDebug() << "Database opened.";
        return true;
    } else
    {
        qDebug() << "Database OPEN ERROR.";
        return false;
    }
}

void HDataBase::closeDataBase()
{
    db.close();
    qDebug() << "Database closed.";
}

bool HDataBase::createHesapTable()
{
    qDebug() << "   Creating Table HESAP";
    QSqlQuery query;
    if(!query.exec("CREATE TABLE tb_hsp("
                    "h_snf INTEGER,"
                    "h_grp INTEGER,"
                    "h_dft INTEGER,"
                    "h_alt INTEGER,"
                    "h_kod TEXT,"
                    "h_name TEXT,"
                   "h_tipi TEXT,"
                   //alacak, borç, ç,ft bakiyeli
                   "h_cinsi"
                   // stok  - alış iade, satış, satış iade
                   // cari - kamu, özel
                   // gider - kasa - kdv
                   // kesinti -diğer - masraf merkezi
                   // erişim seviyesi
                    "h_parentkod INTEGER"
                    ")"))
    {
        qDebug() << "DataBase: error of create table HESAP" ;
        qDebug() << query.lastError().text();
        return false;
    } else {
        insertIntoHesapTable ();
        return true;
    }
    return false;
}

bool HDataBase::createYevmiyeTable()
{
    qDebug() << "   Creating Table YEVMİYE";
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE yevmiye ("
                    "y_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "y_tarih TEXT NOT NULL,"
                    "y_brc_hsp TEXT NOT NULL,"
                    "y_alc_hsp TEXT NOT NULL,"
                    "y_acklm TEXT,"
                    "y_tutar TEXT,"
                    "y_belge_kod"
                    " )"
                    ))
    {
        qDebug() << "DataBase: error of create table YEVMİYE" ;
        qDebug() << query.lastError().text();
        return false;
    } else {
        insertIntoYevmiyeTable ();
        return true;
    }
    return false;
}

bool HDataBase::insertIntoHesapTable()  //const QVariantList &data
{
    //alacak, borç, ç,ft bakiyeli
    // stok  - alış iade, satış, satış iade
    // cari - kamu, özel
    // gider - kasa - kdv
    // kesinti -diğer - masraf merkezi
    // erişim seviyesi

    QSqlQuery query;              
    query.prepare( "INSERT INTO tb_hsp ("
                    "h_snf, h_grp, h_dft, "
                    "h_alt, h_kod, h_name, "
                   "h_tipi, h_cinsi, h_parentkod ) "
                    "VALUES (:A, :B, :C, :D, :E, :F, :G, :H, :I )");

                    query.bindValue(":A",1);
                    query.bindValue(":B",0);
                    query.bindValue(":C",0);
                    query.bindValue(":D","100");
                    query.bindValue(":E","KOD");
                    query.bindValue(":F","HESAP ADI");
                    query.bindValue(":G","HESAP TİPİ");
                    query.bindValue(":H","CİNSİ");
                    query.bindValue(":I",1);

    if(!query.exec()){
        qDebug() << "error insert into HESAP" ;
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "       One record inserted to HESAP";
        return true;
    }
    return false;
}

bool HDataBase::insertIntoYevmiyeTable()
{

    QSqlQuery query;
    query.prepare("INSERT INTO yevmiye ("
                  "y_id, "
                  "y_tarih,"
                  "y_brc_hsp,"
                  "y_alc_hsp,"
                  "y_acklm,"
                  "y_tutar,"
                  "y_belge_kod ) "
                  "VALUES (:A, :B, :C, :D, :E, :F, :G )");
    query.bindValue(":A",1);
    query.bindValue(":B","01-01-2021");
    query.bindValue(":C","borçlu hesap");
    query.bindValue(":D","alacaklı hesap");
    query.bindValue(":E","acıklama");
    query.bindValue(":F",10000);
    query.bindValue(":G","BELGE KODU");


    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into YEVMİYE";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "       One record inserted to YEVMİYE";
        return true;
    }
    return false;
}
