#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeitem.h"
#include "sqltreemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> group_column_indexes;

    /// group by column 0... can be any combination
    /// of column indexes
    group_column_indexes << 0;

    //test::data::SqlTreeModel* model = new test::data::SqlTreeModel();
    test::data::SqlTreeModel* model =
        new test::data::SqlTreeModel();
    // SELECT ... statement, for example
    model->SetQuery(query);
    model->SetGroupByIndexes(group_column_indexes);
    /// Note, that you must format this using same
    /// indexes for grouping...
    /// if we choose to hide columns 0, 3 & 4, then
    /// the code/format would be something like:
    ///
    /// group_column_indexes << 0 << 3 << 4
    /// ...
    /// model->SetGroupTitleFormat("Group {0} is grouped
    /// with {3} and {4}");
    model->SetGroupTitleFormat("Group {0}");
    model->Select();

    _TrvPackages->setAllColumnsShowFocus(false);
    _TrvPackages->setModel(model);

    for (int i = 0; i < _TrvPackages->model()->rowCount(); ++i)
        _TrvPackages->setFirstColumnSpanned(i, QModelIndex(), true);

    _TrvPackages->expandAll();


}

MainWindow::~MainWindow()
{
    delete ui;
}

