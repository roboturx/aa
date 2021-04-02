#ifndef READONLYMODEL_H
#define READONLYMODEL_H

#include <QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "node.h"

class ReadOnlyModel : public QAbstractItemModel
{
public:
    ReadOnlyModel(QObject *parent = 0);
    ~ReadOnlyModel();

    void setRootNode(Node *node);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Node *rootNode;
    Node *m_root;
    
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
  
protected: // important helper methods
    QModelIndex indexForNode(Node *node) const;
    Node *nodeForIndex(const QModelIndex &index) const;
    int rowForNode(Node *node) const;
};



#endif // READONLYMODEL_H
