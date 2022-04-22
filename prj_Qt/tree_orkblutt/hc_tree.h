#ifndef HC_TREE_H
#define HC_TREE_H

#include <QWidget>
#include <QTreeView>
#include "hc_treeitem.h"
#include "hc_treemodel.h"

//class hC_TreeModel;

class hC_Tree : public QWidget
{
    Q_OBJECT

public:
    hC_Tree(QWidget *parent = nullptr);
    ~hC_Tree();

    hC_TreeModel* hC_model;
    QTreeView* view;
};
#endif // HC_TREE_H
