#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>

#include "dbase.h"
#include "hc_treemodel.h"


class MainWindow : public QMainWindow, public hC_TreeModel
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   // dBase *db;
    hC_TreeModel *treemodel;


};
#endif // MAINWINDOW_H