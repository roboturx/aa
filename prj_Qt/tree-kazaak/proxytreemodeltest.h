#ifndef PROXYTREEMODELTEST_H
#define PROXYTREEMODELTEST_H

#include <QDebug>
#include <QAbstractProxyModel>

class QSqlQuery;

class proxyTreeModelTest : public QAbstractProxyModel
{
    Q_OBJECT

public:
    proxyTreeModelTest(QObject *parent=0);
    virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    virtual QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const { return sourceModel()->columnCount(parent); }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const { return sourceModel()->headerData(section,orientation,role); }
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) { return sourceModel()->setHeaderData(section,orientation,value,role); }

    virtual bool hasChildren(const QModelIndex &parent) const;

private:

    int getParentId(int childId) const;
    QSqlQuery* getChildren(int parentId) const;
};

#endif // PROXYTREEMODELTEST_H
