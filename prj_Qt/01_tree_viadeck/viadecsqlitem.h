#ifndef VIADECKSQLITEM_H
#define VIADECKSQLITEM_H

#include <QtCore/QList>
#include <QtCore/QVariant>

namespace test{
namespace itemdata {

class ViadeckSqlItem
{
public:
    ViadeckSqlItem(const QList<QVariant>& itemdata,
                   ViadeckSqlItem* parent = 0);
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

} // namespace itemdata
} // namespace test


#endif // VIADECKSQLITEM_H

