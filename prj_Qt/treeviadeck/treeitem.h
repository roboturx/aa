#ifndef TREEITEM_H
#define TREEITEM_H


/**
 @file
*/

// Qt headers
#include <QtCore/QList>
#include <QtCore/QVariant>


namespace test{
namespace data {

class TreeItem
{
public:
    TreeItem(const QList<QVariant>& data, TreeItem* parent = 0);
    ~TreeItem();

    void AddChild(TreeItem* child);
    TreeItem* GetChild(int rowIndex);
    int GetNumberOfChildren() const;
    int GetNumberOfColumns() const;
    QVariant GetData(int columnIndex) const;
    int GetRowIndex() const;


    TreeItem* GetParent();

private:
    QList<TreeItem*> _Children;
    QList<QVariant>  _ItemData;
    TreeItem*        _Parent;
};

} // namespace data
} // namespace test

#endif // TREEITEM_H
