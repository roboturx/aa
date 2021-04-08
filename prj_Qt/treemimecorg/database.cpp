#include <QDebug>
#include <QEventLoop>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

#include "database.h"

#define DATABASE_NAME "___hesap.dbase"

DataBase::DataBase() //: QObject(parent()) , QSqlDatabase("QSQLITE")
{
    qDebug() << "   Database constructor";
    msgBox = new QMessageBox;

    if (!controlDriver()) {
        msgBox->setText("       DRIVER ERROR...");
        qDebug() << "       DRIVER ERROR...";
    }
    if (!connectToDataBase()) {
        msgBox->setText("       DATABASE ERROR...");
        qDebug() << "       DATABASE ERROR...";
    }
    //  connectToDataBase();
}

DataBase::~DataBase() {}

bool DataBase::controlDriver()
{
    // if qt has driver
    qDebug() << "   Controlling driver...";
    const QString DRIVER("QSQLITE");

    if (!QSqlDatabase::isDriverAvailable(DRIVER)) {
        // not has driver !!!
        qDebug() << "       Database driver error...";
        return false;
    }
    // qt has driver
    qDebug() << "       Database driver OK";
    db = QSqlDatabase::addDatabase(DRIVER);
    // create database
    qDebug() << "       Database added";
    db.setDatabaseName(DATABASE_NAME);
    qDebug() << "       Database name : " << DATABASE_NAME;
    return true;
}

bool DataBase::connectToDataBase()
{
    qDebug() << "   Searching Database file on disk...";
    if (!QFile(DATABASE_NAME).exists()) {
        qDebug() << "       NO FİLE - Database file creating....";
        if (!restoreDataBase()) {
            qDebug() << "       Database file NOT created.";
            return false;
        }
        qDebug() << "       Database file created.";
    } else {
        qDebug() << "       Database file on disk";
        openDataBase();
    }
    return true;
}

bool DataBase::restoreDataBase()
{
    if (!openDataBase()) {
        qDebug() << "   Database CONNECTION ERROR...";
        return false;
    }

    //after opening before creating
    db.exec("PRAGMA encoding = \"UTF-16\"");

    qDebug() << "   Database tables creating...";
    if ((!this->create_Table_h_snf()) || (!this->create_Table_h_grp())
        || (!this->create_Table_h_hsp())) {
        qDebug() << "       Database tables NOT created...";
        return false;
    }
    qDebug() << "       Database tables created...";
    return true;
}

bool DataBase::openDataBase()
{
    /* cm. article QSqlTableModel */
    // hakkındaki makaleye bakın
    // db = QSqlDatabase::addDatabase("QSQLITE");
    //  db.setHostName(DATABASE_HOSTNAME);

    if (db.open()) {
        qDebug() << "   Database opened.";
        return true;
    } else {
        qDebug() << "   Database OPEN ERROR.";
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
    qDebug() << "   Database closed.";
}

bool DataBase::create_Table_h_snf()
{
    qDebug() << "       Creating Tables ";

    //    h_tip (not null)      hesap türü
    //    h_kod (not null)      hesap kodu
    //    h_ad                  self-explanatory
    //    h_prnt (not null)     the parent account to which the account is attached.
    //                          All accounts but the root_account should have a parent account.
    //    h_acklm               self-explanatory
    //    h_prbrm (not null)    The commodity that is handled by the account
    //    h_prbrmx (not null)   The smallest currency/commodity unit is similar to the
    //                          fraction of a commodity. It is the smallest amount of
    //                          the commodity that is tracked in the account.
    //                          If it is different than the fraction of the commodity to
    //                          which the account is linked, the field non_std_scu is
    //                          set to 1 (otherwise the latter is set to 0).
    //    h_ana                 if True/1, the account cannot be involved in transactions
    //                            through splits (ie it can only be the parent of other
    //                            accounts). if False/0, the account can have Splits referring
    //                            to it (as well as be the parent of other accounts). This
    //                            field, if True, is also stored as a Slot under the key
    //                            “placeholder” as a string “true”.
    //    h_gzli                if True/1, the account will not be displayed in the GnuCash
    //                            GUI Accounts tab and can be easily excluded from GnuCash GUI
    //                            Reports. if False/0, the account will be displayed in the
    //                            GnuCash GUI Accounts tab.

    // hesap sınıfları
    qDebug() << "           Creating Table hesap sınıfları ... ";
    qDebug() << "           -----------------------------------";
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS `h_snf` ("
                    "`h_kod`	INTEGER PRIMARY KEY, "
                    "`h_prnt`	INTEGER,"
                    "`h_ad`	TEXT,"
                    "`h_acklm`	TEXT )")) {
        qDebug() << "               NOT CREATED ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "               CREATED. ";
        qDebug() << "               inserting RECORDS ";

        //    insertIntoHesapTable();
        QList<QString> ekle;
        // sql statement
        ekle << "INSERT INTO h_snf (h_kod, h_prnt, h_ad, h_acklm ) "
                "VALUES (:A , :B , :C , :D )";
        // field sayısı
        ekle << "4";
        // bind values
        ekle << "1"
             << "0"
             << "DÖNEN VARLIKLAR"
             << "Nakit, ÇEK - SENET, banka, menkul değerler vs."
             << "Hesap Sınıfları";

        if (!addrecord(ekle))
            return false;
    }
    return true;
}

bool DataBase::create_Table_h_grp()
{
    // hesap grupları
    qDebug() << " ";
    qDebug() << "           Creating Table hesap grupları ";
    qDebug() << "           ------------------------------";

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS `h_grp` ("
                    "`h_kod`	INTEGER PRIMARY KEY, "
                    "`h_prnt`	INTEGER,"
                    "`h_ad`	TEXT,"
                    "`h_acklm`	TEXT )")) {
        qDebug() << "               NOT CREATED ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "               CREATED. ";
        qDebug() << "               inserting RECORDS ";

        //    bir kayıt ekleyelim
        QList<QString> ekle;
        // sql statement
        ekle << "INSERT INTO h_grp (h_kod, h_prnt, h_ad, h_acklm ) "
                "VALUES (:A , :B , :C , :D )";
        // field sayısı
        ekle << "4";
        // bind values
        ekle << "10"
             << "1"
             << "HAZIR DEĞERLER"
             << "Kasa, nakit, banka vs."
             << "Hesap Grupları";

        if (!addrecord(ekle))
            return false;
    }
    return true;
}



bool DataBase::create_Table_h_hsp()
{
    // hesaplar
    qDebug() << " ";
    qDebug() << "           Creating Table Hesaplar ";
    qDebug() << "           ------------------------";

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS `h_hsp` ("
                    "h_kod  INTEGER PRIMARY KEY,"
                    "h_prnt INTEGER,"
                    "h_ad       TEXT,"
                    "h_acklm    TEXT,"
                    "h_prbrm    TEXT,"
                    "h_prbrmx   TEXT,"
                    "h_ana      TEXT,"
                    "h_gzli     TEXT "
                    ")")) {
        qDebug() << "               NOT CREATED ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "               CREATED. ";
        qDebug() << "               inserting RECORDS ";

        //    bir kayıt ekleyelim
        QList<QString> ekle;
        // sql statement ekle[0]
        ekle << "INSERT INTO h_hsp (h_kod, h_prnt, h_ad, h_acklm,"
                "h_prbrm, h_prbrmx, h_ana, h_gzli ) "
                "VALUES (:A, :B, :C, :D, :E, :F, :G, :H )";
        // field sayısı   ekle [1]
        ekle << "8";
        // bind values    ekle [2] +
        ekle << "100"
             << "10"
             << "KASA "
             << "Kasa"
             << "para birimi"
             << "para birim x"
             << "ana hesap mı"
             << "gizli mi"
             << "Hesaplar";

        if (!addrecord(ekle))
            return false;
    }
    return true;
}


bool DataBase::addrecord(QList<QString> ekle)
{
    QSqlQuery query;
    // eklenin ilk elemanında query var
    query.prepare(ekle.first());
    // ekle nin 1. elemanında kaç field olduğu var - for için
    
qDebug() << ekle.count ();
qDebug() << ekle.last ();
qDebug() << ekle[1];

    for (int i = 0; i < ekle[1].toInt(); i++) {
        QString x = ":";
        // qchar 65 = A    -  bindvalue A: B: C: ... oluyor
        qDebug() << QChar(65 + i);
        query.bindValue(x.append(QChar(65 + i)), ekle[i + 2]);
        // ekle nin 2 ve sonraki elemanlarında değerler var
    }
    
    if (!query.exec()) {
        qDebug() << "               error insert into " << ekle.last();
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "               First record inserted into " << ekle.last();
        return true;
    }
    return false;
}


bool DataBase::createYevmiyeTable()
{
    qDebug() << "       Creating Table YEVMİYE";
    QSqlQuery query;
    if (!query.exec("CREATE TABLE yevmiye ("
                    "y_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "y_tarih TEXT NOT NULL,"
                    "y_brc_hsp TEXT NOT NULL,"
                    "y_alc_hsp TEXT NOT NULL,"
                    "y_acklm TEXT,"
                    "y_tutar TEXT,"
                    "y_belge_kod"
                    " )")) {
        qDebug() << "DataBase: error of create table YEVMİYE";
        qDebug() << query.lastError().text();
        return false;
    } else {
        insertIntoYevmiyeTable();
        return true;
    }
    return false;
}

bool DataBase::insertIntoHesapTable() //const QVariantList &data
{
    QSqlQuery query;
    query.prepare("INSERT INTO table11 "
                  "(level, id,sid,name ) "
                  "VALUES (:A, :B, :C, :D)");

    query.bindValue(":A", 1);
    query.bindValue(":B", 1);
    query.bindValue(":C", "SID1");
    query.bindValue(":D", "SID ! in adı");

    if (!query.exec()) {
        qDebug() << "           error insert into HESAP";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "            First record inserted to HESAP";
        return true;
    }
    return false;
}

bool DataBase::insertIntoYevmiyeTable()
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
    query.bindValue(":A", 1);
    query.bindValue(":B", "01-01-2021");
    query.bindValue(":C", "borçlu hesap");
    query.bindValue(":D", "alacaklı hesap");
    query.bindValue(":E", "acıklama");
    query.bindValue(":F", 10000);
    query.bindValue(":G", "BELGE KODU");

    // После чего выполняется запросом методом exec()
    if (!query.exec()) {
        qDebug() << "           error insert into YEVMİYE";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "             One record inserted to YEVMİYE";
        return true;
    }
    return false;
}
