#ifndef TREESQLITEM_H
#define TREESQLITEM_H

#include <QVariant>
#include <QList>

//! [0]
class TreeSqlItem
{
public:
    explicit TreeSqlItem(const QList<QVariant> &data,
                         TreeSqlItem *parent = nullptr);
    ~TreeSqlItem();

    TreeSqlItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeSqlItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    TreeSqlItem *parentItem;
    QList<TreeSqlItem *> childItems;
    QList<QVariant> itemData;

};
//! [0]

#endif // TREESQLITEM_H
