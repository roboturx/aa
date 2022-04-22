#include "hc_treeitem.h"

#include <QStringList>


hC_TreeItem::hC_TreeItem(const QList<QVariant> &data,
                         unsigned int id,
                         hC_TreeItem *parent)
                    : m_itemData(data), m_parentItem(parent)
{
    qDebug() <<"------- treeitem constructor --------------";
    m_parentItem = parent;
    m_itemData = data;
    _id = id;
}

hC_TreeItem::~hC_TreeItem()
{
    qDeleteAll(m_childItems);
}


hC_TreeItem *hC_TreeItem::parent()
{
    return m_parentItem;
}
hC_TreeItem *hC_TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.value(row);
}

int hC_TreeItem::childCount() const
{
    return m_childItems.count();
}

int hC_TreeItem::childNumber() const///
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<hC_TreeItem*>(this));
    return 0;
}
int hC_TreeItem::columnCount() const
{
    return m_itemData.count();
}
QVariant hC_TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.value(column);
  //  return m_itemData.at(column);
}



int hC_TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<hC_TreeItem*>(this));


    return 0;
}

////editables

bool hC_TreeItem::setData(int column, const QVariant &value)///
{
    if (column < 0 || column >= m_itemData.size())
        return false;

    m_itemData[column] = value;
    return true;
}

void hC_TreeItem::appendChild(hC_TreeItem *item)
{
    m_childItems.append(item);
}
