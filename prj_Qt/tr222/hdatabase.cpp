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
    if((!this->createMainTable()) || (!this->createDeviceTable()))
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

bool HDataBase::createMainTable()
{
    qDebug() << "   Creating Tablee 1";
    QSqlQuery query;
    if(!query.exec("CREATE TABLE Tb_Hsp("
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
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool HDataBase::createDeviceTable()
{
    qDebug() << "   Creating Tablee 2";
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
                    )){
        qDebug() << "DataBase: error of create " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool HDataBase::inserIntoMainTable(const QVariantList &data)
{

    QSqlQuery query;
    ////
    query.exec("insert into Tb_Hsp(Hsp_name, Hsp_kodu, Hsp_parentkod) "
               "values(\"1 DÖNEN VARLIKLAR \", 1, 0)");

    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                  TABLE_TIME ", "
                  TABLE_HOSTNAME ", "
                  TABLE_IP " ) "
                  "VALUES (:Date, :Time, :Hostname, :IP )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Hostname",    data[2].toInt());
    query.bindValue(":IP",          data[3].toInt());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool HDataBase::inserIntoDeviceTable(const QVariantList &data)
{

    QSqlQuery query;
    query.prepare("INSERT INTO " DEVICE " ( " DEVICE_HOSTNAME ", "
                  DEVICE_IP " ) "
                  "VALUES (:Hostname, :IP )");
    query.bindValue(":Hostname",    data[0].toString());
    query.bindValue(":IP",          data[1].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
