#ifndef VIADECKSQLITEM_H
#define VIADECKSQLITEM_H

#include <QtCore/QList>
#include <QtCore/QVariant>

namespace test{
namespace data {

class ViadeckSqlItem
{
public:
    ViadeckSqlItem(const QList<QVariant>& data, ViadeckSqlItem* parent = 0);
    ~ViadeckSqlItem();

    void AddChild(ViadeckSqlItem* child);
    ViadeckSqlItem* GetChild(int rowIndex);
    int GetNumberOfChildren() const;
    int GetNumberOfColumns() const;
    QVariant GetData(int columnIndex) const;
    int GetRowIndex() const;


    ViadeckSqlItem* GetParent();

private:
    QList<ViadeckSqlItem*> _Children;
    QList<QVariant>  _ItemData;
    ViadeckSqlItem*        _Parent;
};

} // namespace data
} // namespace test


#endif // VIADECKSQLITEM_H

