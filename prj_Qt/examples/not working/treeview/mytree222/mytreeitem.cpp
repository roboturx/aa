#include "mytreeitem.h"



MyTreeItem::MyTreeItem(const QList<QVariant> &data, MyTreeItem *parent)
    : itemData(data), parentItem(parent)
{
    
}

MyTreeItem::~MyTreeItem()
{
    qDeleteAll(childItems);
    
    
}


MyTreeItem *MyTreeItem::child(int number)
{
    if (number < 0 || number >= childItems.size())
        return nullptr;
    return childItems.at(number);
}

int MyTreeItem::childCount() const
{
    return childItems.count();
}

int MyTreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<MyTreeItem*>(this));
    return 0;
}

int MyTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant MyTreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

bool MyTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;
    
    for (int row = 0; row < count; ++row) {
        QList<QVariant> data(columns);
        MyTreeItem *item = new MyTreeItem(data, this);
        childItems.insert(position, item);
    }
    
    return true;
}

bool MyTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;
    
    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());
    
    for (TreeItem *child : qAsConst(childItems))
        child->insertColumns(position, columns);
    
    return true;
}

MyTreeItem *MyTreeItem::parent()
{
    return parentItem;
}

bool MyTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;
    
    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);
    
    return true;
}

bool MyTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;
    
    for (int column = 0; column < columns; ++column)
        itemData.remove(position);
    
    for (TreeItem *child : qAsConst(childItems))
        child->removeColumns(position, columns);
    
    return true;
}

bool MyTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;
    
    itemData[column] = value;
    return true;
}
