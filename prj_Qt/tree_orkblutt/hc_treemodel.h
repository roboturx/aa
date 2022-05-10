#ifndef HC_TREEMODEL_H
#define HC_TREEMODEL_H


#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QSqlQuery>

#include "hc_treeitem.h"
//#include "hc_tree.h"

class hC_TreeModel : public QAbstractItemModel //, public hC_Tree
{
    Q_OBJECT
public:
    explicit hC_TreeModel(QObject *parent = nullptr);

        ~hC_TreeModel();

        QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
        Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
        QModelIndex index(int row, int column,
                          const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

        //editables
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole) override;///
        bool setHeaderData(int section, Qt::Orientation orientation,///
                           const QVariant &value, int role = Qt::EditRole) override;

        QSqlQuery reSelectAll(const QString qStr);

    private:
        void setupModelData(hC_TreeItem *parent);
        int findNode(unsigned int& hash, const QList<hC_TreeItem*>& tList);

        hC_TreeItem *rootItem;

        //////editable
        hC_TreeItem *getItem(const QModelIndex &index) const;///

        void refresh();
        bool setFirstName(int personId, const QString &firstName);
       // bool setLastName(int personId, const QString &lastName);
    };
#endif // HC_TREEMODEL_H
