#ifndef LAZYMODEL_H
#define LAZYMODEL_H

#include "readonlymodel.h"
#include <QtCore/qglobal.h>

class LazyModel : public ReadOnlyModel
{
    Q_OBJECT
public:
    LazyModel();
    ~LazyModel();
    bool hasChildren(QModelIndex &parent) const;
    bool canFetchMore(QModelIndex &parent) const;
    void fetchMore(QModelIndex &parent);
};



#endif // LAZYMODEL_H
