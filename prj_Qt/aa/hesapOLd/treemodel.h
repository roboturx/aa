
#ifndef TREEMODEL_H
#define TREEMODEL_H

//#include <QAbstractItemModel>
//#include <QModelIndex>
//#include <QVariant>
#include "main/globals.h"
#include "treeitem.h"

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    //TreeModel(const QStringList &headers, const QString &data,
              //QObject *parent = nullptr);
    explicit TreeModel(const QStringList &headers,
                       QObject *parent = nullptr);
    ~TreeModel();
//! [0] //! [1]

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;///
    bool setHeaderData(int section, Qt::Orientation orientation,///
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;///
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;///
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;///
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;///

private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);
    void setupModelData(TreeItem *parent );///
    TreeItem *getItem(const QModelIndex &index) const;///

    int findNode(unsigned int& hash, const QList<TreeItem*>& tList);//
    TreeItem *rootItem;///
};
//! [2]

#endif // TREEMODEL_H


/////
/// orj file
///

//#ifndef RESTORETREEMODEL_H
//#define RESTORETREEMODEL_H

//#include "treeitem.h"
//#include <QAbstractItemModel>
//#include <QModelIndex>
//#include <QVariant>


//class RestoreTreeModel : public QAbstractItemModel
//{
//    Q_OBJECT
//public:
//    explicit RestoreTreeModel(QObject* parent=0);
//    ~RestoreTreeModel();

//    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
//    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
//    QVariant headerData(int section, Qt::Orientation orientation,
//                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
//    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

//private:
//    void setupModelData(TreeItem *parent);
//    int findNode(unsigned int& hash, const QList<TreeItem*>& tList);

//    TreeItem *rootItem;

//};

//#endif // RESTORETREEMODEL_H