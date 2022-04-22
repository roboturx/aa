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
    bool createDb();
    bool openDb();

    QSqlDatabase db;
    QString dbName;

};

#endif // dBase_H
