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

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Methods to work directly with the class.
         * Connect to the database and insert records into the table
         * */
    void connectToDataBase();
    bool inserIntoMainTable(const QVariantList &data);
    bool inserIntoDeviceTable(const QVariantList &data);

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createMainTable();
    bool createDeviceTable();
};

#endif // DATABASE_H
