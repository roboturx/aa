#ifndef MYTREEMODEL_H
#define MYTREEMODEL_H

#include <QAbstractItemModel>

#include <QVariant>

class MyTreeModel : public QAbstractItemModel
{
public:
    MyTreeModel( QObject *root, QObject* parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole) const ;
    QVariant headerData ( int section, Qt::Orientation,
                          int role = Qt::DisplayRole ) const ;
    int rowCount ( const QModelIndex &parent = QModelIndex()   ) const ;
    int columnCount ( const QModelIndex &parent = QModelIndex()   ) const ;

    QModelIndex index (int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent ( const QModelIndex &index) const ;

private:
    int m_root;

};

#endif // MYTREEMODEL_H
