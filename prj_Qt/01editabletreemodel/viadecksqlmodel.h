#ifndef VIADECKSQLMODEL_H
#define VIADECKSQLMODEL_H


#include "viadecsqlitem.h"



/**
     @file
    */



// Qt headers
#include <QtCore/QAbstractItemModel>
#include <QtSql/QSqlQuery>


namespace test {
namespace data {

// Forward declarations
class TreeItem;

class ViadeckSqlModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ViadeckSqlModel(QObject* parent = NULL);
    ~ViadeckSqlModel();

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

    ViadeckSqlItem*  _Root;

    QSqlQuery  _Query;
    QList<int> _GroupColumns;
    QString    _GroupTitleFormat;

    void Create(ViadeckSqlItem* parent);
};

} // namespace data
} // namespace test

#endif // VIADECKSQLMODEL_H

