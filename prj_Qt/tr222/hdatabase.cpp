#include "hdatabase.h"
#define DATABASE_NAME       "DataBase.db"

HDataBase::HDataBase(QObject *parent) : QObject(parent)
{

}

HDataBase::~HDataBase()
{

}

void HDataBase::connectToDataBase()
{
    /* см. статью про QSqlTableModel */
    // hakkındaki makaleye bakın
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool HDataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if((!this->createMainTable()) || (!this->createDeviceTable())){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Veritabanı geri yüklenemedi";
        return false;
    }
    return false;
}

bool HDataBase::openDataBase()
{
    /* cm. article QSqlTableModel */
    // hakkındaki makaleye bakın
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName( DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void HDataBase::closeDataBase()
{
    db.close();
}

bool HDataBase::createMainTable()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE Tb_Hsp("
                    "h_snf INTEGER,"
                    "h_grp INTEGER,"
                    "h_dft INTEGER,"
                    "h_alt INTEGER,"
                    "h_kod TEXT,"
                    "h_name TEXT,"
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
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " DEVICE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    DEVICE_HOSTNAME  " VARCHAR(255)    NOT NULL,"
                    DEVICE_IP        " VARCHAR(16)     NOT NULL"
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
