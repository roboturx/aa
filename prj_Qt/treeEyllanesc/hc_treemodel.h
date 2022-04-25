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

class hC_TreeModel
{

public:
    explicit hC_TreeModel();

<<<<<<< HEAD
    void modelle();
    QStandardItemModel *trmodel;
=======
    QStandardItemModel *modelle();
    QStandardItemModel *stdmodel;
>>>>>>> 1a9f7586759c69f33fda9e4bc57a5bdac72774c7

signals:

};

#endif // HC_TREEMODEL_H
