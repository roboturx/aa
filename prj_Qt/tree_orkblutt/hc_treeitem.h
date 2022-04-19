#ifndef HC_TREEITEM_H
#define HC_TREEITEM_H

#include <QList>
#include <QVariant>

class hC_TreeItem
{
public:
    explicit hC_TreeItem(const QList<QVariant> &data,
                         unsigned int id ,
                         hC_TreeItem *parent = 0);
    ~hC_TreeItem();

    void appendChild(hC_TreeItem *child);

    hC_TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    hC_TreeItem *parent(); // treemodel de çağrılır

    int row() const;

    int childNumber() const;///

    ///editables
    bool setData(int column, const QVariant &value);///
    unsigned int getIndex(){return _id;};
private:
    QList<hC_TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    hC_TreeItem *m_parentItem;
    unsigned int _id;
};

#endif // HC_TREEITEM_H
