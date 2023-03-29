#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include "main/taskitem.h"
#include <QSortFilterProxyModel>


class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent=0);

    TaskItem* currentHesapItem;
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

public slots:
    void filtrele(TaskItem* currentHesap);
    void clearFilters();

};
//    int minimumZipcode() const { return m_minimumZipcode; }
//    int maximumZipcode() const { return m_maximumZipcode; }
//    QString county() const { return m_county; }
//    QString state() const { return m_state; }

//public slots:
//    void clearFilters();
//    void setMinimumZipcode(int minimumZipcode);
//    void setMaximumZipcode(int maximumZipcode);
//    void setCounty(const QString &county);
//    void setState(const QString &state);

//protected:
//    bool filterAcceptsRow(int sourceRow,
//                          const QModelIndex &sourceParent) const;

//private:
//    int m_minimumZipcode;
//    int m_maximumZipcode;
//    QString m_county;
//    QString m_state;
//};

#endif // PROXYMODEL_H
