#include "hc_treeitem.h"

#include <QStringList>


hC_TreeItem::hC_TreeItem(const QList<QVariant> &data, hC_TreeItem *parent, unsigned int id)
{
    m_parentItem = parent;
    m_itemData = data;
    _id = id;
}

hC_TreeItem::~hC_TreeItem()
{
    qDeleteAll(m_childItems);
}

void hC_TreeItem::appendChild(hC_TreeItem *item)
{
    m_childItems.append(item);
}

hC_TreeItem *hC_TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int hC_TreeItem::childCount() const
{
    return m_childItems.count();
}

int hC_TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant hC_TreeItem::data(int column) const
{
    return m_itemData.value(column);
}

hC_TreeItem *hC_TreeItem::parentItem()
{
    return m_parentItem;
}

int hC_TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<hC_TreeItem*>(this));

    return 0;
}
