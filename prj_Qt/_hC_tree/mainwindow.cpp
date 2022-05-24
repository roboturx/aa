
#include "mainwindow.h"
#include "hc_tree.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    hC_Tree* tree = new hC_Tree(this);
    setCentralWidget(tree);
}
