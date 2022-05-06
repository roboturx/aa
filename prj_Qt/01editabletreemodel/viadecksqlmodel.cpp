#include "viadecksqlmodel.h"

ViadeckSqlModel::ViadeckSqlModel()
{

}
/**
     @file
    */

// Project headers
#include "TreeItem.hpp"
#include "SqlTreeModel.hpp"

// Qt headers
#include <QtCore/QTextStream>
#include <QtSql/QSqlRecord>


namespace test {
namespace data {

SqlTreeModel::SqlTreeModel(QObject* parent /* = NULL */)
    : _Root(NULL),
    QAbstractItemModel(parent)
{
    _GroupColumns << 0;
    _GroupTitleFormat = "{0}";
}

SqlTreeModel::~SqlTreeModel()
{
    if (_Root != NULL)
        delete _Root;
}

void SqlTreeModel::SetQuery(const QSqlQuery& query)
{ _Query = query; }

bool SqlTreeModel::Select()
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

    _Root = new TreeItem(root_data);
    Create(_Root);

    return true;
}

void SqlTreeModel::SetGroupByIndexes(const QList<int>& columnIndexes)
{ _GroupColumns = columnIndexes; }

void SqlTreeModel::SetGroupTitleFormat(const QString& format)
{ _GroupTitleFormat = format; }

QVariant SqlTreeModel::GetData( const QModelIndex& index, int role ) const
{
    return data(index, role);
}

QVariant SqlTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item->GetData(index.column());
}

Qt::ItemFlags SqlTreeModel::GetFlags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SqlTreeModel::GetHeaderData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/ ) const
{
    return headerData(section, orientation, role);
}
QVariant SqlTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _Root->GetData(section);

    return QVariant();
}

QModelIndex SqlTreeModel::GetIndex( int rowIndex, int columnIndex, const QModelIndex& parent /*= QModelIndex()*/ ) const
{
    return index(rowIndex, columnIndex, parent);
}

QModelIndex SqlTreeModel::index(int rowIndex, int columnIndex, const QModelIndex& parent) const
{
    if (!hasIndex(rowIndex, columnIndex, parent))
        return QModelIndex();

    TreeItem *parent_item;

    if (!parent.isValid())
        parent_item = _Root;
    else
        parent_item = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *child_item = parent_item->GetChild(rowIndex);

    if (child_item)
        return createIndex(rowIndex, columnIndex, child_item);
    else
        return QModelIndex();
}

QModelIndex SqlTreeModel::GetParent( const QModelIndex& index ) const
{
    return parent(index);
}

QModelIndex SqlTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* child_item  = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parent_item = child_item->GetParent();

    if (parent_item == _Root)
        return QModelIndex();

    return createIndex(parent_item->GetRowIndex(), 0, parent_item);
}

int SqlTreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parent_item;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parent_item = _Root;
    else
        parent_item = static_cast<TreeItem*>(parent.internalPointer());

    return parent_item->GetNumberOfChildren();
}

int SqlTreeModel::columnCount(const QModelIndex& parent) const
{

    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->GetNumberOfColumns();
    else
        return _Root->GetNumberOfColumns();
}

void SqlTreeModel::Create(TreeItem* parent)
{
    TreeItem* current_parent = parent;

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

            TreeItem* parent_item = new TreeItem(parent_data, parent);
            parent->AddChild(parent_item);
            current_parent = parent_item;

            QList<QVariant> child_data;

            for (int j = 0; j < number_of_columns; ++j)
            {
                if (_GroupColumns.indexOf(j) == -1)
                    child_data << _Query.record().value(j);
            }

            TreeItem* child_item = new TreeItem(child_data, current_parent);
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

            TreeItem* child_item = new TreeItem(child_data, current_parent);
            current_parent->AddChild(child_item);
        }
    }
}

} // namespace data
} // namespace test
