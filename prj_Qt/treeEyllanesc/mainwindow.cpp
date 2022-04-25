#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    treemodel = new hC_TreeModel;


}

MainWindow::~MainWindow()
{
}

