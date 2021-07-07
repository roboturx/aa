#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QMessageBox>

#define TABLE                   "MainTable"
#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_IP                "IP"
#define TABLE_HOSTNAME          "Hostname"

#define DEVICE                  "DeviceTable"
#define DEVICE_IP               "IP"
#define DEVICE_HOSTNAME         "Hostname"



class DataBase : public QObject, public QSqlDatabase
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    /* Methods to work directly with the class.
         * Connect to the database and insert records into the table
         * */
    bool controlDriver();
    bool connectToDataBase();
    bool insertIntoHesapTable();
    bool insertIntoYevmiyeTable();
    void ddd();
    QMessageBox *msgBox;

public:
    QSqlDatabase *   db;


private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();

    bool create_Table_konum();
    bool create_Table_isemri();
    bool create_Table_h_hsp();
    bool create_Table_h_mmbr();

    bool addrecord(QList<QString> ekle);

    bool createYevmiyeTable();

protected:
    void changeEvent(QEvent *e);

};

#endif // DATABASE_H
