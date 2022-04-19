#ifndef HC_TREEITEM_H
#define HC_TREEITEM_H

#include <QList>
#include <QVariant>

class hC_TreeItem
{
public:
    explicit hC_TreeItem(const QList<QVariant> &data, hC_TreeItem *parentItem = 0, unsigned int id = 0);
    ~hC_TreeItem();

    void appendChild(hC_TreeItem *child);

    hC_TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

    unsigned int getIndex(){return _id;};

    hC_TreeItem *parentItem();

private:

    QList<hC_TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    hC_TreeItem *m_parentItem;
    unsigned int _id;
};

#endif // HC_TREEITEM_H
