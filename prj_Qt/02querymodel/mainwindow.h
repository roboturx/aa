#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editablesqlmodel.h"
#include <QTableView>
#include <QTreeView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeModel(QSqlQueryModel *model);

    EditableSqlModel* editableModel;
    QTableView* createView(QSqlQueryModel *model);

    QWidget *wdgtSol ;
    QWidget *wdgtSag ;
private:


};

#endif // MAINWINDOW_H
