#include "hc_tree.h"
#include <QGridLayout>

hC_Tree::hC_Tree(QWidget *parent)
    : QWidget(parent)
{
    qDebug() <<"begin---------------------------------------------";
    hC_model = new hC_TreeModel(this);
    qDebug() <<"modelled------------------------------------------";
    view = new QTreeView(this);
    qDebug() <<"viewed--------------------------------------------";
    view->setModel(hC_model);
    qDebug() <<"model ->view--------------------------------------";
    for (int column = 0; column < hC_model->columnCount(); ++column)
        view->resizeColumnToContents(column);
   // connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
           // this, &MainWindow::updateActions);
    QGridLayout *ly = new QGridLayout(this);
    ly->addWidget (view,0,0,1,1);
    qDebug() <<"layouted-------------------------------------------";
}

hC_Tree::~hC_Tree()
{
}

