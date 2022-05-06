
/*
    treesqlitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include "treesqlitem.h"

//! [0]
TreeSqlItem::TreeSqlItem(const QList<QVariant> &data, TreeSqlItem *parent)
    : itemData(data), parentItem(parent)
{}
//! [0]

//! [1]
TreeSqlItem::~TreeSqlItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
TreeSqlItem *TreeSqlItem::child(int number)
{
    if (number < 0 || number >= childItems.size())
        return nullptr;
    return childItems.at(number);
}
//! [2]

//! [3]
int TreeSqlItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int TreeSqlItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeSqlItem*>(this));
    return 0;
}
//! [4]

//! [5]
int TreeSqlItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant TreeSqlItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}
//! [6]

//! [7]
bool TreeSqlItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QList<QVariant> data(columns);
        TreeSqlItem *item = new TreeSqlItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool TreeSqlItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    for (TreeSqlItem *child : qAsConst(childItems))
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
TreeSqlItem *TreeSqlItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool TreeSqlItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeSqlItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    for (TreeSqlItem *child : qAsConst(childItems))
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool TreeSqlItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]
