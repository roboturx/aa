#include "mainwindow.h"
#include "sqltreemodeltest.h"
#include "proxytreemodeltest.h"


#include <QTreeView>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget     *centralWidget  = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(centralWidget);
    treeView = new QTreeView(centralWidget);

    lb1 = new QLabel (centralWidget);
    lb2 = new QLabel (centralWidget);
    lb3 = new QLabel (centralWidget);



    verticalLayout->addWidget(treeView);
    verticalLayout->addWidget(lb1);
    verticalLayout->addWidget(lb2);
    verticalLayout->addWidget(lb3);

    setCentralWidget(centralWidget);

    QSqlError error = initdb();
    if(error.isValid())
        qDebug() << error.text();
    setupModel();
}

QSqlError MainWindow::initdb() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(":memory:");
    if(!db.open())
        return db.lastError();

    QSqlQuery q;
    QStringList tables = db.tables();
    if(tables.contains("test", Qt::CaseInsensitive))
        if(!q.exec("DROP TABLE test"))
            return q.lastError();

    if(!q.exec(QLatin1String("CREATE TABLE test(id INTEGER PRIMARY KEY,"
                             " title VARCHAR, "
                             " type INTEGER, "
                             "parentId INTEGER DEFAULT 0)")))
        return q.lastError();
    if(!q.exec(QLatin1String("INSERT INTO test (title, type, parentId)"
                             "VALUES ('root0', 0, 0),"
                                    "('root1', 0, 0),"
                                    "('child1', 0, 1),"
                                    "('cc1'   , 0, 3),"
                              "('ccc1'   , 0, 4),"
                                    "('child2', 0, 2)")))

                                            //VALUES ('row0', 0, 0),"
                                           // "      ('row0a', 0, 1)")))


        return q.lastError();
    return QSqlError();
}

void MainWindow::setupModel() {

    sqlTreeModelTest *testModel = new sqlTreeModelTest(this);
    testModel->setTable("test");
    testModel->select();

    proxyTreeModelTest *treeProxy = new proxyTreeModelTest(this);
    treeProxy->setSourceModel(testModel);

    treeView->setModel(treeProxy);
    treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->expandAll();

    connect(treeView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            [=]()
    {
        QModelIndex index =  treeView->selectionModel()->currentIndex();
        lb1->setText("Row="+QString::number(index.row())
                    );
        lb2->setText("Data="+treeView->model()->data(index).toString()) ;

        lb3->setText ("intpointer");
static_cast<TreeItem*>(parent.internalPointer());
            }
    );

}
