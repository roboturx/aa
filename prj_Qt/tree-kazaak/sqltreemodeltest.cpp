#include "sqltreemodeltest.h"

sqlTreeModelTest::sqlTreeModelTest(QObject *parent) : QSqlTableModel(parent) {}

Qt::ItemFlags sqlTreeModelTest::flags(const QModelIndex &index) const {
    //QSqlTableModel doesn't allow children so use these flags
    if(index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
    else
        return Qt::ItemIsEnabled;
}
