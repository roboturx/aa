#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QtSql/QSqlError>

class QTreeView;
class QSqlTableModel;
class sqlTreeModelTest;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlError initdb();

    QLabel* lb1;
    QLabel* lb2;
    QLabel* lb3;



private:
    QTreeView *treeView;
    void setupModel();
};

#endif // MAINWINDOW_H
