#include "mytreemodel.h"

MyTreeModel::MyTreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    
    
    
}

/////////////////////////////////////////////////////////////////////
QVariant MyTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
/////////////////////////////////////////////////  rootitem
bool MyTreeModel::setHeaderData(int section,
                                Qt::Orientation orientation,
                                const QVariant &value,
                                int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        if (role != Qt::EditRole || orientation != Qt::Horizontal) {
            return false;
        }
        if (rootItem->setData(section, value)) {
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////
QModelIndex MyTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    MyTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    MyTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

/////////////////////////////////////////////////////////////////////
QModelIndex MyTreeModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    if (!index.isValid())
        return QModelIndex();

    MyTreeItem *childItem = getItem(index);
    MyTreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
/////////////////////////////////////////////////////////////////////
int MyTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
/////////////////////////////////////////////////////////////////////
int MyTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!

    Q_UNUSED(parent);
    return rootItem->columnCount();
}

bool MyTreeModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool MyTreeModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void MyTreeModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

/////////////////////////////////////////////////////////////////////
QVariant MyTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    MyTreeItem *item = getItem(index);

    return item->data(index.column());
}

/////////////////////////////////////////////////////////////////////
bool MyTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    if (data(index, role) != value) {
        // FIXME: Implement me!
        MyTreeItem *item = getItem(index);
        bool result = item->setData(index.column(), value);
        if (result)
            emit dataChanged(index, index, QVector<int>() << role);
        return result;
    }
    return false;
}
/////////////////////////////////////////////////////////////////////
Qt::ItemFlags MyTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    //return Qt::ItemIsEditable;
    // FIXME: Implement me!
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

/////////////////////////////////////////////////////////////////////
bool MyTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    MyTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    const bool success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

/////////////////////////////////////////////////////////////////////
bool MyTreeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    const bool success = rootItem->insertColumns(position, columns);

    endInsertColumns();

    return success;
}

/////////////////////////////////////////////////////////////////////
bool MyTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    MyTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

/////////////////////////////////////////////////////////////////////
bool MyTreeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    // const bool success = rootItem->removeColumns(position, column);
    const bool success = rootItem->removeColumns(count, column);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

/////////////////////////////////////////////////////////////////////
MyTreeItem *MyTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        MyTreeItem *item = static_cast<MyTreeItem *>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}