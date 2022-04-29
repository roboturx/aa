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
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "editablesqlmodel.h"
class dBase : public QSqlDatabase
{
public:

    dBase();
    static bool createConnection();
    bool openDb();

    QSqlDatabase db;
  //  MySqlModel* msqlmdl;
    EditableSqlModel* mysqlmodel;
private:
    bool addRecord(QString accnm, int accCd, int grpCd);

};

#endif // dBase_H
