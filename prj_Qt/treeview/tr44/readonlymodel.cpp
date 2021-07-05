#include "readonlymodel.h"

ReadOnlyModel::ReadOnlyModel(QObject *parent) : QAbstractItemModel(parent)
{
    rootNode = 0;
}

ReadOnlyModel::~ReadOnlyModel()
{
    delete rootNode;
}

void ReadOnlyModel::setRootNode(Node *node)
{
    delete rootNode;
    rootNode = node;
    resetInternalData ();
}
//
QModelIndex ReadOnlyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent)) {
        Node *parentNode = nodeForIndex(parent);
        Node *childNode = parentNode->children.at(row);
        return createIndex(row, column, childNode);
    }
    return QModelIndex();
}

//
QModelIndex ReadOnlyModel::parent(const QModelIndex &child) const
{
    Node *childNode = nodeForIndex(child);
    Node *parentNode = childNode->parent;

    if (parentNode == m_root)
        return QModelIndex();

    int row = rowForNode(parentNode);
    int column = 0;
    return createIndex(row, column, parentNode);
}

//
int ReadOnlyModel::rowCount(const QModelIndex &parent) const
{
    Node *parentNode = nodeForIndex(parent);
    return parentNode->children.count();
}

//
int ReadOnlyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}
///
QVariant ReadOnlyModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        Node *node = nodeForIndex(index);
        return node->data ();
    }
    return QVariant();
}
/*
QVariant ReadOnlyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
        {
            return tr("Node");
        }
        else
        if (section == 1)
        {
            return tr("Value");
        }
    }
    return QVariant();
    
}*/
///
Node *ReadOnlyModel::nodeForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<Node *>(index.internalPointer());
    } 
        return m_root;
        
}
////
int ReadOnlyModel::rowForNode(Node *node) const
{
    return node->parent->children.indexOf(node);
}


///
QModelIndex ReadOnlyModel::indexForNode(Node *node) const
{
    if (node == m_root) {
        return QModelIndex();
    }
    int row = rowForNode(node);
    int column = 0;
    return createIndex(row, column, node);
}
