#include "mw.h"
#include "modelle.h"

Mw::Mw(QWidget *parent) :
    QMainWindow(parent)
    //, tableView(new QTableView(this))
    , treeView(new QTreeView(this))
{
    //this->setCentralWidget( tableView);
    this->setCentralWidget( treeView);
    Modelle *modelle = new Modelle(this);

    //tableView->setModel(modelle);
    treeView->setModel(modelle);
    connect(modelle, &Modelle::editCompleted,
            this, &Mw::ShowWindowTitle );

}

void Mw::ShowWindowTitle(const QString &title)
{
    setWindowTitle(title);
}
