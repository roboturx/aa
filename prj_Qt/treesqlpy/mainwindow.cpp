#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    db = QSqlDatabase.addDatabase("QSQLITE");
    db.setDatabaseName(':memory:');

    modelQuery = QSqlQueryModel();
    modelTable = QSqlRelationalTableModel();
}

MainWindow::~MainWindow()
{
}

