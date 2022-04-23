/**
     @file
    */

// Project headers
#include "treeitem.h"


namespace test {
namespace data {

TreeItem::TreeItem(const QList<QVariant>& data, TreeItem* parent)
{
    _Parent   = parent;
    _ItemData = data;
}

TreeItem::~TreeItem()
{ qDeleteAll(_Children); }

void TreeItem::AddChild(TreeItem* child)
{ _Children.append(child); }

TreeItem* TreeItem::GetChild(int rowIndex)
{ return _Children.value(rowIndex); }

int TreeItem::GetNumberOfChildren() const
{ return _Children.count(); }

int TreeItem::GetNumberOfColumns() const
{ return _ItemData.count(); }

QVariant TreeItem::GetData(int columnIndex) const
{ return _ItemData.value(columnIndex); }

TreeItem* TreeItem::GetParent()
{ return _Parent; }

int TreeItem::GetRowIndex() const
{

    if (_Parent)
        return _Parent->_Children.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

} // namespace data
} // namespace test
