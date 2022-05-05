#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>
#include <QTreeView>

#include "editablesqlmodel.h"
#include "myitemmodel.h"

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
    MyItemModel *myitemmodel;
    QTableView* createView(QSqlQueryModel *model);

    QWidget *wdgt01 ;
    QWidget *wdgt02 ;
    QWidget *wdgt03 ;

    QLineEdit *lE_data01 ;
    QLineEdit *lE_data02 ;
    QLineEdit *lE_data03 ;

private slots:


};

#endif // MAINWINDOW_H
