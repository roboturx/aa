#include "mytreemodel.h"
//#include <QAbstractTableModel>

MyTreeModel::MyTreeModel(QObject *root, QObject *parent) :
    QAbstractItemModel (parent)
{
    m_rows = root;
    m_columns = cols;
}

Qt::ItemFlags MyTreeModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return Qt::ItemIsEnabled;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant MyTreeModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return ((index.row()+1) * (index.column() +1 ));
    case Qt::ToolTipRole:
        return QString ("%1 x %2").arg(index.row()+1).arg(index.column()+1);
    default:
        return QVariant();
    }
}

QVariant MyTreeModel::headerData(int section,
                                 Qt::Orientation orientation,
                                 int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal )
        return QVariant();
    switch (section)
    {
    case 0:
        return QString ("Objject");
    case 1:
        return QString ("Cllass");
    default:
        return QVariant();
    }
}

int MyTreeModel::rowCount(const QModelIndex &parent) const
{
    return m_rows;
}

int MyTreeModel::columnCount(const QModelIndex &parent) const
{
    return m_columns;
}

QModelIndex MyTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QObject *parentObject;
    if (!parent.isValid())
        parentObject = m_root;
    else

}

QModelIndex MyTreeModel::parent(const QModelIndex &index) const
{

}

