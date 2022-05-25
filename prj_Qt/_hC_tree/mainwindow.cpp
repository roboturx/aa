
#include "mainwindow.h"
#include "hc_tree.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry (25,25,600,800);

    hC_Tree* tree = new hC_Tree(this);
    setCentralWidget(tree);
}
