#include "hc_tree.h"

#include <QGridLayout>

hC_Tree::hC_Tree(QWidget *parent)
    : QWidget(parent)
{
    hC_model = new hC_TreeModel(this);
    view = new QTreeView(this);
    view->setModel(hC_model);
    QGridLayout *ly = new QGridLayout(this);
    ly->addWidget (view,0,0,1,1);
}

hC_Tree::~hC_Tree()
{
}

