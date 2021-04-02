#ifndef READONLYMODEL_H
#define READONLYMODEL_H

#include <QAbstractItemModel>

class ReadOnlyModel : public QAbstractItemModel
{
public:
    ReadOnlyModel();
    QModelIndex index (int row , int column, QModelIndex parent ) const;
    QModelIndex
};

#endif // READONLYMODEL_H
