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

public:
    explicit hC_TreeModel(QObject *parent = nullptr);

    void modelle();
    QStandardItemModel *trmodel;

signals:

};

#endif // HC_TREEMODEL_H
