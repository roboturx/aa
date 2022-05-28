#ifndef SQLTREEMODELTEST_H
#define SQLTREEMODELTEST_H

#include <QtSql/QSqlTableModel>

class sqlTreeModelTest : public QSqlTableModel
{
    Q_OBJECT

public:
    sqlTreeModelTest(QObject *parent=0);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // SQLTREEMODELTEST_H
