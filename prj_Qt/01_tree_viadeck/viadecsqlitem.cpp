#include "viadecsqlitem.h"


namespace test {
namespace data {

ViadeckSqlItem::ViadeckSqlItem(const QList<QVariant>& data, ViadeckSqlItem* parent)
{
    _Parent   = parent;
    _ItemData = data;
}

ViadeckSqlItem::~ViadeckSqlItem()
{ qDeleteAll(_Children); }

void ViadeckSqlItem::AddChild(ViadeckSqlItem* child)
{ _Children.append(child); }

ViadeckSqlItem* ViadeckSqlItem::GetChild(int rowIndex)
{ return _Children.value(rowIndex); }

int ViadeckSqlItem::GetNumberOfChildren() const
{ return _Children.count(); }

int ViadeckSqlItem::GetNumberOfColumns() const
{ return _ItemData.count(); }

QVariant ViadeckSqlItem::GetData(int columnIndex) const
{ return _ItemData.value(columnIndex); }

ViadeckSqlItem* ViadeckSqlItem::GetParent()
{ return _Parent; }

int ViadeckSqlItem::GetRowIndex() const
{

    if (_Parent)
        return _Parent->_Children.indexOf(const_cast<ViadeckSqlItem*>(this));

    return 0;
}

} // namespace data
} // namespace test
