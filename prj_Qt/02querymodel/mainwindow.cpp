
#include <QGridLayout>
#include <QLabel>
#include <QSplitter>
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    const QStringList headers({tr("Title"), tr("Description")});

    //// editable model table
    lE_data01 =new QLineEdit("111111");
    editableModel = new EditableSqlModel;
    initializeModel(editableModel);

    QTableView *tableView = new QTableView;
    tableView->setModel(editableModel);

    QGridLayout* grly01 = new QGridLayout;
    wdgt01 = new QWidget;
    grly01->addWidget (new QLabel("ed sql model-----"),0,0,1,1);
    grly01->addWidget (new QLabel("sql model 2------"),0,1,1,1);
    grly01->addWidget (new QLabel("data-"),            1,0,1,1);
    grly01->addWidget (lE_data01,                      1,1,1,3);
    grly01->addWidget (tableView,                      2,0,1,2);
    wdgt01->setLayout (grly01);


    //// editable model tree
    ///
    lE_data02 =new QLineEdit("2222222");
    QTreeView *treeview = new QTreeView;
    treeview->setModel(editableModel);
    qDebug() << "1" ;
    QGridLayout* grly02 = new QGridLayout;
    wdgt02 = new QWidget;
    grly02->addWidget (new QLabel("treeview-----"),0,0,1,1);
    grly02->addWidget (new QLabel("treeview 2---"),0,1,1,1);
    grly02->addWidget (new QLabel("data02-      "),1,0,1,1);
    grly02->addWidget (lE_data02,                  1,1,1,3);
    grly02->addWidget (treeview,                   2,0,1,2);
    wdgt02->setLayout (grly02);
    qDebug() << "2" ;
    //// my item model
    ///

    lE_data03 =new QLineEdit("333333");
    QTreeView *xtreeview = new QTreeView;
//    myitemmodel = new MyItemModel;
 //   xtreeview->setModel(myitemmodel);
    QGridLayout* grly03 = new QGridLayout;
    wdgt03 = new QWidget;
    grly03->addWidget (new QLabel("my------"),0,0,1,1);
    grly03->addWidget (new QLabel("tyy 2---"),0,1,1,1);
    grly03->addWidget (new QLabel("mydata03"),1,0,1,1);
    grly03->addWidget (lE_data03,             1,1,1,3);
    grly03->addWidget (xtreeview,             2,0,1,2);
    wdgt03->setLayout (grly03);
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(wdgt01);
    splitter->addWidget(wdgt02);
    splitter->addWidget(wdgt03);

    setCentralWidget (splitter);


    /// iki view de aynı selection
    treeview->setSelectionModel(tableView->selectionModel());

    /// üzerinde bulunulan cell data to lineedit
    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            // use lambda as slot
            [=]()
            {
                lE_data01->setText ( tableView->model ()
                                       ->data(tableView
                                       ->currentIndex (),
                                       Qt::DisplayRole).toString ());
            });
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
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

qDebug() << "200" ;
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

