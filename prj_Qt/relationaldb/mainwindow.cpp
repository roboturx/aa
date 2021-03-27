    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* The first step is to create an object for the database and
     * initialize the database connection
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* After that produce content database tables
         * this content will displayed in the tableView and tableViewDevice
         * */
    for(int i = 1; i < 4; i++){
        QVariantList data;
        data.append("Device " + QString::number(i));
        data.append("192.168.0." + QString::number(i));
        db->inserIntoDeviceTable(data);
    }

    for(int i = 0; i < 10; i++){
        QVariantList data;
        QString random = QString::number( QRandomGenerator::global()->generate() % ((4 + 1) - 1) + 1);
        data.append(QDate::currentDate());
        data.append(QTime::currentTime());
        data.append(random);
        data.append(random);
        db->inserIntoMainTable(data);
    }

    /* Initialize the model to represent the data indicating the names of the columns
         * */
    this->setupMainModel(TABLE,
                         QStringList() << "id"
                                       << "Tarih - Дата"
                                       << "Zaman - Время"
                                       << "Ana bilgisayar adı - Имя хоста"
                                       << "IP Adres -IP адрес"
                         );

    this->setupDeviceModel(DEVICE,
                           QStringList() << "id"
                                         << "Ana bilgisayar adı - Имя хоста"
                                         << "IP Adres - IP адрес"
                           );
    /* Initialize the appearance of a table with data
         * */
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainModel(const QString &tableName, const QStringList &headers)
{
    /* Initializes the data model representation with the installation name
         * in the database table, on which will be accessed in the table
         * */
    modelMain = new QSqlRelationalTableModel(this);
    modelMain->setTable(tableName);
    /* Set the connection device table, which will be made data substitution.
         * The method setRelation specified column number in which substitution is made,
         * as well as through QSqlRelation class name of the table,
         * the option for which the sample line and column
         * from which the data will be taken will be made
         * */
    modelMain->setRelation(3, QSqlRelation(DEVICE, "id", DEVICE_HOSTNAME));
    modelMain->setRelation(4, QSqlRelation(DEVICE, "id", DEVICE_IP));

    /* Set the columns names in a table with sorted data
         * */
    for(int i = 0, j = 0; i < modelMain->columnCount(); i++, j++){
        modelMain->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Set Sort Ascending column zero data
    modelMain->setSort(0,Qt::AscendingOrder);
    modelMain->select(); // Делаем выборку данных из таблицы
}

void MainWindow::setupDeviceModel(const QString &tableName, const QStringList &headers)
{
    /* Initializes the data model representation
         * with the installation name in the database table,
         * on which will be accessed in the table
         * */
    modelDevice = new QSqlRelationalTableModel(this);
    modelDevice->setTable(tableName);

    for(int i = 0, j = 0; i < modelDevice->columnCount(); i++, j++){
        modelDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    modelDevice->setSort(0,Qt::AscendingOrder);
    modelDevice->select();
    }

void MainWindow::createUI()
{
    ui->tableView->setModel(modelMain);     // We set the model on the TableView
    ui->tableView->setColumnHidden(0, true);    // Hide the column id Records
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    modelMain->select(); // Fetches the data from the table

    ui->tableViewDevice->setModel(modelDevice);
        ui->tableViewDevice->setColumnHidden(0, true);
        ui->tableViewDevice->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDevice->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewDevice->resizeColumnsToContents();
    ui->tableViewDevice->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewDevice));
    ui->tableViewDevice->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewDevice->horizontalHeader()->setStretchLastSection(true);

    modelDevice->select();
}
