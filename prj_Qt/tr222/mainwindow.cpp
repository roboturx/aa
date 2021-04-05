#include "mainwindow.h"
#include "database.h"
#include "treemodel.h"
#include <QtWidgets>
#include <QtSql>
#include <QTreeView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle ("Treeeeeeeee");
    // Veritabanı
    DataBase db;



    model = new TreeModel(this);

    tview = new QTreeView(this);
    tview-> setAnimated(true);
    tview-> setHeaderHidden(true);
    tview-> setRootIsDecorated(true);
   // tview-> setIcon(QIcon(":/order.png"));

    /*if (ai_type == FolderItem)
        w.setIcon(QIcon(":/order.png"));
    else if (ai_type == PlaylistItem)
        setIcon(QIcon(":/images/playlist.png"));
    else if (ai_type == TrainingItem)
        setIcon(QIcon(":/images/training.png"));
    */

    tview->setModel(model);
    tview->expandAll();
    setCentralWidget (tview);

}

MainWindow::~MainWindow()
{
}

