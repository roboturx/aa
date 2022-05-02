
#include <QGridLayout>
#include <QLabel>
#include <QSplitter>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    editableModel = new EditableSqlModel;
    initializeModel(editableModel);



    QTableView *tableView = new QTableView;
    tableView->setModel(editableModel);
  //  QItemSelectionModel *tableselectionModel = tableView->selectionModel ();

    QGridLayout* grlySol = new QGridLayout;
    wdgtSol = new QWidget;
    grlySol->addWidget (new QLabel("editable sql model--------------"),0,0,1,1);
    grlySol->addWidget (new QLabel("editable sql model 2---------------"),0,1,1,1);
    grlySol->addWidget (tableView,1,0,1,2);
    wdgtSol->setLayout (grlySol);



    QTreeView *treeview = new QTreeView;
    treeview->setModel(editableModel);
  //  QItemSelectionModel *treeselectionModel = treeview->selectionModel();
    QGridLayout* grlySag = new QGridLayout;
    wdgtSag = new QWidget;
    grlySag->addWidget (new QLabel("editable sql model--------------"),0,0,1,1);
    grlySag->addWidget (new QLabel("editable sql model 2---------------"),0,1,1,1);
    grlySag->addWidget (treeview,1,0,1,2);
    wdgtSag->setLayout (grlySag);



    QSplitter *splitter = new QSplitter(this);

    splitter->addWidget(wdgtSol);
    splitter->addWidget(wdgtSag);




    setCentralWidget (splitter);
    //wdgtSol->show ();



//    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
//  //  tableView->horizontalHeader()->setStretchLastSection(true);
//   // tableView->verticalHeader()->hide();
//    tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);
//    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//    tableView->setSortingEnabled(true);

//    connect(tableView->selectionModel(),
//            &QItemSelectionModel::selectionChanged,
//            treeview->selectionModel (),
//            &QItemSelectionModel::selectionChanged);
//    connect ( tableselectionModel,
//            &QItemSelectionModel::currentRowChanged,
//            treeselectionModel,
//              );
//connect(tableView->selectionModel (),
//            SIGNAL(selectionChanged(const QItemSelection &,
//           const QItemSelection &)),
//
//            SLOT(RepopulatetableView()));


}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from person");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}


