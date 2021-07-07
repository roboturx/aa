#ifndef MYTREEITEM_H
#define MYTREEITEM_H

#include <QtCore/qglobal.h>
#include <QVariant>
#include <QList>

class MyTreeItem
{
public:
    explicit MyTreeItem(const QList<QVariant> &data, MyTreeItem *parent = nullptr);
    ~MyTreeItem();

    MyTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);

    MyTreeItem *parent();
    bool removeChildren(int position, int count); //, int columns);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    
    
private:
    QList<MyTreeItem *> childItems;
     QList<QVariant> itemData;
    MyTreeItem *parentItem;
};

#endif // MYTREEITEM_H
