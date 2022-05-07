
#include "treesqlmodel.h"
#include "treesqlitem.h"

#include <QtWidgets>

//! [0]
TreeSqlModel::TreeSqlModel(const QStringList &headers,
                           QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    for (const QString &header : headers)
        rootData << header;

    rootItem = new TreeSqlItem(rootData);
//    setupModelData(query, rootItem);
}
//! [0]

//! [1]
TreeSqlModel::~TreeSqlModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeSqlModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}
//! [2]

QVariant TreeSqlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeSqlItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeSqlModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
TreeSqlItem *TreeSqlModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeSqlItem *item = static_cast<TreeSqlItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeSqlModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex TreeSqlModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
//! [5]

//! [6]
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeSqlItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

bool TreeSqlModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeSqlModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeSqlModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeSqlItem *childItem = getItem(index);
    TreeSqlItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool TreeSqlModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeSqlModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int TreeSqlModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() > 0)
        return 0;

    const TreeSqlItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]

bool TreeSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeSqlItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeSqlModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

//void TreeSqlModel::setupModelData(const QSqlQuery &query,
//                                  TreeSqlItem *parent)
//{
//    QList<TreeSqlItem *> parents;
//    /// indentations levelları belirliyor
//    /// ilk girinti root item için
//  //  QList<int> indentations;
//    parents << parent; // içinde header olan ilk parent
//   // indentations << 0;

//    int number = 0;

//    while (number < query.count()) // record count
//    {
//        /// boşluk bulunca çık
//        int position = 0;
//        while (position < query[number].length()) {
//            if (query[number].at(position) != ' ')
//                break;
//            ++position;
//        }

//        const QString lineData = query[number].mid(position).trimmed();

//        if (!lineData.isEmpty()) {
//            // Read the column data from the rest of the line.
//            const QStringList columnStrings =
//                lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);

//            // sql deki fieldları columndatay ekle
//            QList<QVariant> columnData;
//            columnData.reserve(columnStrings.size());
//            for (const QString &columnString : columnStrings)
//                columnData << columnString;

//            if (position > indentations.last()) {
//                // The last child of the current parent is now the new parent
//                // unless the current parent has no children.

//                if (parents.last()->childCount() > 0) {
//                    parents << parents.last()->child(parents.last()->childCount()-1);
//                    indentations << position;
//                }
//            } else {
//                while (position < indentations.last() && parents.count() > 0) {
//                    parents.pop_back();
//                    indentations.pop_back();
//                }
//            }

//            // Append a new item to the current parent's list of children.
//            TreeSqlItem *parent = parents.last();
//            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
//            for (int column = 0; column < columnData.size(); ++column)
//                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
//        }
//        ++number;
//    }
//}
