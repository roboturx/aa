#include "viadecksqlmodel.h"

#include <QtCore/QTextStream>
#include <QtSql/QSqlRecord>


namespace test {
namespace data {

ViadeckSqlModel::ViadeckSqlModel(QObject* parent /* = NULL */)
    : QAbstractItemModel(parent),
    _Root(NULL)
{
    _GroupColumns << 0;
    _GroupTitleFormat = "{0}";
}

ViadeckSqlModel::~ViadeckSqlModel()
{
    if (_Root != NULL)
        delete _Root;
}

void ViadeckSqlModel::SetQuery(const QSqlQuery& query)
{ _Query = query; }

bool ViadeckSqlModel::Select()
{
    if (!_Query.isActive())
        return false;

    QSqlRecord      record       = _Query.record();
    const int       record_count = record.count();
    QList<QVariant> root_data;

    for (int i = 0; i < record_count; ++i)
    {
        if (_GroupColumns.indexOf(i) == -1)
            root_data << record.fieldName(i);
    }

    _Root = new ViadeckSqlItem(root_data);
    Create(_Root);

    return true;
}

void ViadeckSqlModel::SetGroupByIndexes(const QList<int>& columnIndexes)
{ _GroupColumns = columnIndexes; }

void ViadeckSqlModel::SetGroupTitleFormat(const QString& format)
{ _GroupTitleFormat = format; }

QVariant ViadeckSqlModel::GetData( const QModelIndex& index, int role ) const
{
    return data(index, role);
}

QVariant ViadeckSqlModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ViadeckSqlItem* item = static_cast<ViadeckSqlItem*>(index.internalPointer());
    return item->GetData(index.column());
}

Qt::ItemFlags ViadeckSqlModel::GetFlags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ViadeckSqlModel::GetHeaderData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/ ) const
{
    return headerData(section, orientation, role);
}
QVariant ViadeckSqlModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _Root->GetData(section);

    return QVariant();
}

QModelIndex ViadeckSqlModel::GetIndex( int rowIndex, int columnIndex, const QModelIndex& parent /*= QModelIndex()*/ ) const
{
    return index(rowIndex, columnIndex, parent);
}

QModelIndex ViadeckSqlModel::index(int rowIndex, int columnIndex, const QModelIndex& parent) const
{
    if (!hasIndex(rowIndex, columnIndex, parent))
        return QModelIndex();

    ViadeckSqlItem *parent_item;

    if (!parent.isValid())
        parent_item = _Root;
    else
        parent_item = static_cast<ViadeckSqlItem*>(parent.internalPointer());

    ViadeckSqlItem *child_item = parent_item->GetChild(rowIndex);

    if (child_item)
        return createIndex(rowIndex, columnIndex, child_item);
    else
        return QModelIndex();
}

QModelIndex ViadeckSqlModel::GetParent( const QModelIndex& index ) const
{
    return parent(index);
}

QModelIndex ViadeckSqlModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    ViadeckSqlItem* child_item  = static_cast<ViadeckSqlItem*>(index.internalPointer());
    ViadeckSqlItem* parent_item = child_item->GetParent();

    if (parent_item == _Root)
        return QModelIndex();

    return createIndex(parent_item->GetRowIndex(), 0, parent_item);
}

int ViadeckSqlModel::rowCount(const QModelIndex& parent) const
{
    ViadeckSqlItem* parent_item;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parent_item = _Root;
    else
        parent_item = static_cast<ViadeckSqlItem*>(parent.internalPointer());

    return parent_item->GetNumberOfChildren();
}

int ViadeckSqlModel::columnCount(const QModelIndex& parent) const
{

    if (parent.isValid())
        return static_cast<ViadeckSqlItem*>(parent.internalPointer())->GetNumberOfColumns();
    else
        return _Root->GetNumberOfColumns();
}

void ViadeckSqlModel::Create(ViadeckSqlItem *parent)
{
    ViadeckSqlItem* current_parent = parent;

    while (_Query.next())
    {
        QString   group_title         = _GroupTitleFormat;
        const int group_columns_count = _GroupColumns.count();
        const int number_of_columns   = _Query.record().count();

        for (int i = 0; i < group_columns_count; ++i)
        {
            const int column_index = _GroupColumns.at(i);

            QString     column_arg;
            QTextStream arg_stream(&column_arg);
            arg_stream << "{" << column_index << "}";

            group_title.replace(column_arg, _Query.value(column_index).toString());
        }

        if (current_parent->GetData(0).toString() != group_title)
        {
            QList<QVariant> parent_data;
            parent_data << group_title;

            for (int i = 1; i < number_of_columns; ++i)
                parent_data << "";

            ViadeckSqlItem* parent_item = new ViadeckSqlItem(parent_data, parent);
            parent->AddChild(parent_item);
            current_parent = parent_item;

            QList<QVariant> child_data;

            for (int j = 0; j < number_of_columns; ++j)
            {
                if (_GroupColumns.indexOf(j) == -1)
                    child_data << _Query.record().value(j);
            }

            ViadeckSqlItem* child_item = new ViadeckSqlItem(child_data, current_parent);
            current_parent->AddChild(child_item);
        }
        else
        {
            QList<QVariant> child_data;

            for (int i = 0; i < number_of_columns; ++i)
            {
                if (_GroupColumns.indexOf(i) == -1)
                    child_data << _Query.record().value(i);
            }

            ViadeckSqlItem* child_item = new ViadeckSqlItem(child_data, current_parent);
            current_parent->AddChild(child_item);
        }
    }
}

} // namespace data
} // namespace test
