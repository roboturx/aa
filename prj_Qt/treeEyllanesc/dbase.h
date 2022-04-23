#ifndef dBase_H
#define dBase_H
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSqlDatabase>

class dBase : public QSqlDatabase
{
public:

    dBase();
    static bool createConnection();
    bool openDb();

    QSqlDatabase db;


};

#endif // dBase_H
