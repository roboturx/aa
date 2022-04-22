#include "mainwindow.h"
#include "humanproxymodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    db->addDatabase("QSQLITE");
    db->setDatabaseName(":memory:");

    modelQuery = new QSqlQueryModel;
    modelTable = new QSqlRelationalTableModel;

    setupUi();


}

void MainWindow::setupUi()
{
    QWidget centralwidget;// = new QWidget;
    QHBoxLayout* horizontalLayout = new QHBoxLayout(centralwidget);

    QTreeView* treeView = new QTreeView(centralwidget);

    treeView->setSortingEnabled(true);
    treeView->setAlternatingRowColors(true);
    treeView->setEditTriggers(QTreeView::NoEditTriggers);
    treeView->setSelectionMode(QTreeView::ExtendedSelection);
    treeView->setAnimated(true);
    treeView->setItemsExpandable(true);

    horizontalLayout->addWidget(treeView);
    setCentralWidget(centralwidget);

    header = new FilterHeader(treeView);
    treeView->setHeader(header);

    QStatusBar statusBar;
    this->setStatusBar(statusBar);

    modelTable->setTable("person");
    treeView->setModel(modelTable);

    proxy = new HumanProxyModel(this)
            proxy.setSourceModel(modelTable)
            treeView.setModel(proxy)

            header.setFilterBoxes(modelTable.columnCount())
            header.filterActivated.connect(handleFilterActivated)
}

MainWindow::~MainWindow()
{
}

void create_sample_data()
{
    modelQuery.setQuery("CREATE TABLE IF NOT EXISTS country ("
                        " id   INTEGER PRIMARY KEY UNIQUE NOT NULL,"
                        "name TEXT"
                        ")");

    modelQuery.setQuery("CREATE TABLE IF NOT EXISTS person ("
                        " id         INTEGER PRIMARY KEY UNIQUE NOT NULL,"
                        " persId     TEXT,"
                        " lastName   TEXT,"
                        " firstName  TEXT,"
                        " country_id INTEGER NOT NULL DEFAULT 3,"
                        "FOREIGN KEY (country_id) REFERENCES country(id)"
                        ")");

    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (0, 'None')");
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (1, 'Angola')");
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (2, 'Serbia')");
    modelQuery.setQuery("INSERT INTO country (id, name) VALUES (3, 'Georgia')");

    modelQuery.setQuery("INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (1, '1001', 'Martin', 'Robert', 1)");
    modelQuery.setQuery("INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (2, '1002', 'Smith', 'Brad', 2)");
    modelQuery.setQuery("INSERT INTO person (id, persId, lastName, firstName, country_id) VALUES (3, '1003', 'Smith', 'Angelina', 3)");

}

QStandardItemModel MainWindow::createPersonModel()
{
    model = new QStandardItemModel(this, 0, COUNT_PERS_COLS, parent);
    model->setHorizontalHeaderLabels(["ID", "Last Name", "First Name"]);

    return model
}
void MainWindow::addPerson(self, model, id, last_name, first_name)
{
    model.insertRow(0);
            model.setData(model.index(0, col_persID), id);
            model.setData(model.index(0, col_persLAST_NAME), last_name);
            model.setData(model.index(0, col_persFIRST_NAME), first_name);
}
void MainWindow::handleFilterActivated(self)
{
    header = treeView.header();
            filters = [];

            for i in range(header.count());
            text = header.filterText(i);
            if (text)
            filters.append((i, text));

            proxy = treeView.model()
            proxy.filters = filters
}
