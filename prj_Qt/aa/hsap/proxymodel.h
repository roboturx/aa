#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModel(int column, QObject *parent = nullptr )
        :QSortFilterProxyModel(parent), Column(column) {}
    void setSourceModel (QAbstractItemModel *sourceModel);
protected:
    bool filterAcceptRow (int sourceRow,
                         const QModelIndex &sourceParent) const;
private slots:
    void clearCache() { cache.clear(); }
private:
    const int Column;
    mutable QSet<QString> cache;
};

#endif // PROXYMODEL_H
