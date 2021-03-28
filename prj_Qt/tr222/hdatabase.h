#ifndef HDATABASE_H
#define HDATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QMessageBox>

#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE                   "MainTable"
#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_IP                "IP"
#define TABLE_HOSTNAME          "Hostname"

#define DEVICE                  "DeviceTable"
#define DEVICE_IP               "IP"
#define DEVICE_HOSTNAME         "Hostname"

class HDataBase : public QObject
{
    Q_OBJECT
public:
    explicit HDataBase(QObject *parent = 0);
    ~HDataBase();
    /* Methods to work directly with the class.
         * Connect to the database and insert records into the table
         * */
    bool controlDriver();
    bool connectToDataBase();
    bool inserIntoMainTable(const QVariantList &data);
    bool inserIntoDeviceTable(const QVariantList &data);

    QMessageBox *msgBox;

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createMainTable();
    bool createDeviceTable();


};

#endif // HDATABASE_H
