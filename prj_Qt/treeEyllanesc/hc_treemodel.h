#ifndef HC_TREEMODEL_H
#define HC_TREEMODEL_H

#include <QStandardItemModel>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

enum RelationRoles{
    CodeRole = Qt::UserRole + 1000,
};

class hC_TreeModel :  public QStandardItemModel
{
    Q_OBJECT
public:
    explicit hC_TreeModel(QObject *parent = nullptr);

    void modelle();
    QStandardItemModel *treemodel;

signals:

};

#endif // HC_TREEMODEL_H
