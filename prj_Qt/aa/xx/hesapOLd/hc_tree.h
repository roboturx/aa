#ifndef HC_TREE_H
#define HC_TREE_H

//#include <QObject>
//#include <QWidget>

#include "main/globals.h"
#include "treeitem.h"
#include "treemodel.h"

class hC_tree : public QWidget
{
    Q_OBJECT
public:
    explicit hC_tree(QWidget *parent = nullptr);

    TreeModel *treemodel;
    QTreeView *treeview;


public slots:
    void updateActions();
private slots:
    void insertChild();
    bool insertColumn();
    void insertRow();
    bool removeColumn();
    void removeRow();

};

#endif // HC_TREE_H
