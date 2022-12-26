#include "proxymodel.h"


void ProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    connect (sourceModel, &QAbstractItemModel::modelReset,
            this, &ProxyModel::clearCache);
    QSortFilterProxyModel::setSourceModel(sourceModel);
}

bool ProxyModel::filterAcceptRow(int sourceRow,
                                 const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel ()
                            ->index (sourceRow,Column,sourceParent);
    const QString &text = sourceModel ()->data (index).toString ();
    if (cache.contains (text))
    {
        return false;
    }
    cache << text;
    return true;
}
