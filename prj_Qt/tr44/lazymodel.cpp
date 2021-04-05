#include "lazymodel.h"

LazyModel::LazyModel()
{
    
}

LazyModel::~LazyModel()
{
    
}

bool LazyModel::hasChildren(QModelIndex &parent) const {
    
}

bool LazyModel::canFetchMore(QModelIndex &parent) const
{
    static const int maxChildren = 100;
    Node *parentNode = nodeForIndex(parent);
    return parentNode->children.count() < maxChildren ;
    
}

void LazyModel::fetchMore(QModelIndex &parent)
{
    static const int maxChildren = 100;
    Node *parentNode = nodeForIndex(parent);
    
    
    int count = parentNode->children.count();
    if (count < maxChildren) {
        beginInsertRows(parent, count, maxChildren - count);
        while (parentNode->children.count() < maxChildren) {
            new Node("Lazy Node", parentNode);
        }
        endInsertRows();
    }
    
}
