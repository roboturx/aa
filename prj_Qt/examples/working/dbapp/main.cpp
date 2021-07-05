#include <QCoreApplication>
#include <QDebug>
#include <QtSql>

bool createDb();
static bool createConnection();
void listele();
void ekle();
void sil();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool x=createDb();
    bool y=createConnection();
    if ( (y == false) | (x == false) )
    {
        qDebug()<<"Veritabanı Bağlantısı - HATA";
        return a.exec();
    }
    else
    {
        qDebug() << "Veritabanı Bağlantısı - OK";

        listele();
        ekle();
        sil();

















        QSqlDatabase::removeDatabase ("QSQLITE");
        qDebug()<<"Veritabanı kapatılıyor...";
        //db.close ();
        qDebug()<<"Veritabanı kapatıldı.";
    }

    return a.exec();
}


void ekle()
{
    qDebug() << "ekleniyor";

    QString qstr ("INSERT INTO Tb_addr (firstname,lastname) "
                    "VALUES (:first, :last)");

    QSqlQuery query;
    query.prepare (qstr);

    query.bindValue (":first","ahmet");
    query.bindValue (":last","vural");

    if (query.exec ())
    {
        listele();
        qDebug() << "eklendi";
    }
    else
    {
        qDebug()<<query.lastError().text();
        qDebug() << "eklenemedi";
    }


}

void sil()
{

}

void listele()
{
    QSqlQuery query;
    if (query.exec ("SELECT * FROM Tb_Addr"))
    {
        while (query.next ())
        {
            qDebug() << "İsim : " << query.value (1).toString ();
        }

    }
    else
    {
        qDebug()<<query.lastError().text();
        qDebug() << "listelenemdi";
    }


}

static bool createConnection()
{
    QSqlDatabase db;

    // contains() default argument is initialized to default connection
    if (QSqlDatabase::contains())
    {
        db = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setDatabaseName("db.db");

    if (!db.isValid())
    {
        // Log error (last error: db.lastError().text()) and throw exception
    }

    if (!db.open())
    {
        // Log error (last error: db.lastError().text()) and throw exception
    }
    //QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    //dbase.setDatabaseName("db.db");
    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                    "Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit.";
        return false;
    }

    return true;
}
bool createDb(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(":memory:");
    qDebug()<<"Veritabanı dosyası kontrol ediliyor...";
    db.setDatabaseName("db.db");

    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                    "Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit.";
        return false;
    }
    else
    {
        qDebug()<<"Veritabanı BAĞLANDI...";
    }
    QSqlQuery query;
    if(!query.exec("CREATE TABLE Tb_Addr("
                    "ID INTE,"
                    "FirstName TEXT,"
                    "LastName TEXT"
                    ")"))
    {
        qDebug()<<"HATA - Veritabanı tablo OLUŞTURULAMADI";
        qDebug()<<query.lastError().text();
    }
    else
    {
        qDebug()<<"Veritabanı tablo OLUŞTURULDU";

    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 1, 'mustafa', 'balcı')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 2, 'hasibe', 'balcı')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 3, 'ismail', 'balcı')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 4, 'hasan', 'kayalar')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 6, 'hakan', 'balcı')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 7, 'dönüş', 'kışlalı')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 8, 'yaşar', 'kayalar')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 9, 'nesibe', 'kayalar')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 10, 'mustafa', 'ışıklıyurt')");
    query.exec("insert into Tb_Addr (ID, FirstName, LastName) VALUES ( 11, 'melahat', 'ışıklıyurt')");
    }

    QSqlDatabase::removeDatabase ("QSQLITE");
    qDebug()<<"Veritabanı kapatılıyor...";
    db.close ();
    qDebug()<<"Veritabanı kapatıldı.";
    return true;
}
