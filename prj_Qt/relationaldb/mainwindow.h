    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>

/* Connect the header file for work with the database */
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    /* The project uses objects to interact with the database and
     * model representation database table
     * */
    DataBase                    *db;
    QSqlRelationalTableModel    *modelMain;
    QSqlRelationalTableModel    *modelDevice;

private:
    /* Also present are two methods that form the model and
     * appearance TableView
     * */
    void setupMainModel(const QString &tableName, const QStringList &headers);
    void setupDeviceModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
