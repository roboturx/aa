#include "proxytreemodeltest.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>

#include <QDebug>

proxyTreeModelTest::proxyTreeModelTest(QObject *parent) : QAbstractProxyModel(parent) {}

QModelIndex proxyTreeModelTest::mapFromSource(const QModelIndex &sourceIndex) const {
    if(!sourceIndex.isValid())
        return QModelIndex();

    int id = (sourceIndex.column() == 0)
                    ? sourceIndex.data().toInt()
                    : sourceIndex.sibling(sourceIndex.row(),0).data().toInt();

    int row = -1;
    QSqlQuery* q = getChildren(getParentId(id));
    while(q->next()) {
        row++;
        if(q->value(0).toInt() == id)
            break;
    }
    delete q;
    return createIndex(row, sourceIndex.column(), id);
}

QModelIndex proxyTreeModelTest::mapToSource(const QModelIndex &proxyIndex) const
{
    if(!proxyIndex.isValid())
        return QModelIndex();

    int id = proxyIndex.internalId();

    QSqlQuery q;
    q.exec("SELECT id FROM test");
    int row = -1;
    while(q.next()) {
        row++;
        if(q.value(0).toInt() == id)
            break;
    }
    return sourceModel()->index(row, proxyIndex.column());
}

bool proxyTreeModelTest::hasChildren(const QModelIndex &parent) const {

    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM test WHERE parentId=?");
    q.addBindValue(parent.internalId());
    q.exec();
    q.first();
    return q.value(0).toInt() > 0;
}

QModelIndex proxyTreeModelTest::parent(const QModelIndex &childIndex) const {

    int childId  = childIndex.internalId();
    int parentId = getParentId(childId);
    if(parentId == 0)
        return QModelIndex();

    int parentRow = -1;
    QSqlQuery* q = getChildren(getParentId(parentId));
    while(q->next()) {
        parentRow++;
        if(q->value(0).toInt() == parentId)
            break;
    }
    delete q;
    return createIndex(parentRow, childIndex.row(), parentId);
}

QModelIndex proxyTreeModelTest::index(int row, int column, const QModelIndex &parent) const {

    if(row < 0 || column < 0)
        return QModelIndex();

    QSqlQuery* q = getChildren(parent.internalId());
    q->seek(row);
    int id = q->value(0).toInt();
    delete q;
    return createIndex(row, column, id);
}

int proxyTreeModelTest::rowCount(const QModelIndex &parent) const {

    QSqlQuery* q = getChildren(parent.internalId());

    //use last() and at() since SQLite does not support query size calls
    q->last();
    int size = q->at() + 1;
    delete q;
    return size;
}

int proxyTreeModelTest::getParentId(int childId) const {
    QSqlQuery q;
    q.prepare("SELECT parentId FROM test WHERE id=?");
    q.addBindValue(childId);
    q.exec();
    q.first();
    return q.value(0).toInt();
}

QSqlQuery* proxyTreeModelTest::getChildren(int parentId) const {
    QSqlQuery* q = new QSqlQuery;
    q->prepare("SELECT id FROM test WHERE parentId=?");
    q->addBindValue(parentId);
    q->exec();
    return q;
}
