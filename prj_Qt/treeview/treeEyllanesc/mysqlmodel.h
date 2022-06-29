
#ifndef MySqlModel_H
#define MySqlModel_H

#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

    enum RelationRoles{
        CodeRole = Qt::UserRole + 1000,
        };


class MySqlModel : public QStandardItemModel//QSqlQueryModel
{
    Q_OBJECT

public:
    MySqlModel(QObject *parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
   // QStandardItemModel *stdmodel;
   // QSortFilterProxyModel* proxymodel;
private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();


    void populate();
};

#endif
