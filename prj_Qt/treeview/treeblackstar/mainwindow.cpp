#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTreeView* view = new QTreeView(this);
    TreeItemModel* model = new TreeItemModel(this);
    view->setModel(model);
    setCentralWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}

