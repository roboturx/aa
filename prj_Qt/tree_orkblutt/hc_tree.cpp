#include "hc_tree.h"
#include "qmessagebox.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
hC_Tree::hC_Tree(QWidget *parent)
    : QWidget(parent)
{
    qDebug() <<"--------------------------------------------- hc tree begin";
    hC_model = new hC_TreeModel(this);
    qDebug() <<"------------------------------------------ hc modelled ----";
    view = new QTreeView(this);
    view->setModel(hC_model);
    qDebug() <<"model ->view--------------------------------------";
    for (int column = 0; column < hC_model->columnCount(); ++column)
        view->resizeColumnToContents(column);
    view->expandAll();

    connect(view->selectionModel(), &QItemSelectionModel::currentChanged,
            this , &hC_Tree::lineedits) ;
    QGridLayout *ly = new QGridLayout(this);
    lE_index = new QLineEdit("qqqq");
    lE_pindex = new QLineEdit;
    ly->addWidget (new QLabel ("index "),  0,0,1,1);
    ly->addWidget (lE_index,               0,1,1,1);
    ly->addWidget (new QLabel ("p index "),0,2,1,1);
    ly->addWidget (lE_pindex ,             0,3,1,1);
    ly->addWidget (view,                   2,0,1,4);
    qDebug() <<"layouted-------------------------------------------";
}

hC_Tree::~hC_Tree()
{
}

void hC_Tree::lineedits(const QModelIndex &currentindex,
                        const QModelIndex &previousindex )
{
    lE_index->setText(QString::number(currentindex.row()) +
                      QString::number(currentindex.column())+" "+
                      QString::number(previousindex.row()) +
                      QString::number(previousindex.column()));
    lE_pindex->setText(QString::number(currentindex.parent().row()) +
                       QString::number(currentindex.parent().column())+" "+
                       QString::number(previousindex.parent().row()) +
                       QString::number(previousindex.parent().column()));

}

