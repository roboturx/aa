#ifndef VIADECKSQLMODEL_H
#define VIADECKSQLMODEL_H


class ViadeckSqlModel
{
public:
    ViadeckSqlModel();
};

#endif // VIADECKSQLMODEL_H
/**
     @file
    */

#ifndef TEST_DATA_SQLTREEMODEL_HPP
#define TEST_DATA_SQLTREEMODEL_HPP

// Qt headers
#include <QtCore/QAbstractItemModel>
#include <QtSql/QSqlQuery>


namespace test {
namespace data {

// Forward declarations
class TreeItem;

class SqlTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SqlTreeModel(QObject* parent = NULL);
    ~SqlTreeModel();

    void SetQuery(const QSqlQuery& query);
    bool Select();

    void SetGroupByIndexes(const QList<int>& columnIndexes);
    void SetGroupTitleFormat(const QString& format);

    QVariant GetData(const QModelIndex& index, int role) const;
    Qt::ItemFlags GetFlags(const QModelIndex& index) const;
    QVariant GetHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex GetIndex(int rowIndex, int columnIndex, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex GetParent(const QModelIndex& index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

private:
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int rowIndex, int columnIndex, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    TreeItem*  _Root;

    QSqlQuery  _Query;
    QList<int> _GroupColumns;
    QString    _GroupTitleFormat;

    void Create(TreeItem* parent);
};

} // namespace data
} // namespace test

#endif // TEST_DATA_SQLTREEMODEL_HPP
