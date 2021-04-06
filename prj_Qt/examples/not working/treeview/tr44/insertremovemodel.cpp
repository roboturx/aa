#include "insertremovemodel.h"

InsertRemoveModel::InsertRemoveModel()
{
    
}

InsertRemoveModel::~InsertRemoveModel() {}


void InsertRemoveModel::insertNode(Node *parentNode, int pos, Node *node)
{
    const QModelIndex parent = indexForNode(parentNode);
    int firstRow = pos;
    int lastRow = pos;

    beginInsertRows(parent, firstRow, lastRow);
    parentNode->children.insert(pos, node);
    endInsertRows();
}

void InsertRemoveModel::removeNode(Node *node)
{
    Node *parentNode = node->parent;
    const QModelIndex parent = indexForNode(parentNode);
    int pos = rowForNode(node);
    int firstRow = pos;
    int lastRow = pos;
    
    beginRemoveRows(parent, firstRow, lastRow);
    parentNode->children.removeAt (pos);
    endRemoveRows();
}

void InsertRemoveModel::removeAllNodes()
{
    
}
