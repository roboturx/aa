#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filterheader.h"
#include <QMainWindow>
#include <QTreeView>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QStatusBar>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QStandardItemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlQueryModel* modelQuery;
    QSqlRelationalTableModel* modelTable;
    QSqlDatabase* db;
    FilterHeader* header;
    HumanProxyModel* proxy;
    void create_sample_data();
    void setupUi();
    QStandardItemModel* model;
    QStandardItemModel createPersonModel();
    void addPerson( QStandardItemModel &model,int id,
                    QString &last_name, QString &first_name);
    void handleFilterActivated();


};









#endif // MAINWINDOW_H
