#include "logger.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <qsqlrecord.h>

#include "./rdbmy/tableitemmodel.h"

#include "editdialog.h"
#include "tables.h"
#include "models.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // arayüz
    qDebug () << "arayüz";

    setupUi( );

    // pushbutton bağlantıları
    qDebug () << "connect";

    connects();

    // debugger
    qDebug () << "logger";
    logger();

    //database connection
    qDebug () << "dbase";
    dbConnector();

    // data manager
    m_manager = new DataManager( this );

    // datadan ekrana
    fillSampleData();

    QList<int> columns;
    columns <<  Column_Name << Column_Address << Column_Phone;

    //RDB::TableItemModel* projectsModel = new RDB::TableItemModel( this );
    projectsModel = new RDB::TableItemModel( this );
    projectsModel->setColumns( columns );

    projectsModel->setRootTableModel(
        new CompaniesModel( m_manager ), m_manager->companies()->index() );

    projectsModel->addChildTableModel(
        new ProjectsModel( m_manager ), m_manager->projects()->index(),
        m_manager->projects()->parentIndex() );

    projectsModel->addChildTableModel(
        new PersonsModel( m_manager ), m_manager->members()->index().first(),
        m_manager->members()->index().second() );

    connect( m_manager, SIGNAL( projectsChanged() ), projectsModel,
            SLOT( updateData() ) );

    PersonsFilter* filter = new PersonsFilter( m_manager );
    connect( searchEdit, SIGNAL( textChanged(QString) ), filter,
            SLOT( setNameFilter(QString) ) );

    RDB::TableItemModel* personsModel = new RDB::TableItemModel( this );
    personsModel->setColumns( columns );

    personsModel->setRootTableModel(
        new PersonsModel( m_manager ), m_manager->persons()->index() );

    personsModel->setRowFilter( filter );

    connect( m_manager, SIGNAL( personsChanged() ), personsModel,
            SLOT( updateData() ) );

    projectsView->setModel( projectsModel );
    personsView->setModel( personsModel );

    projectsView->setColumnWidth( 0, 200 );
    projectsView->sortByColumn( 0, Qt::AscendingOrder );
    projectsView->expandAll();

    personsView->setColumnWidth( 0, 120 );
    personsView->sortByColumn( 0, Qt::AscendingOrder );

    connect( projectsView->selectionModel(),
            SIGNAL( selectionChanged(QItemSelection,QItemSelection) ), this,
            SLOT( updateButtons() ) );

    connect( personsView->selectionModel(),
            SIGNAL( selectionChanged(QItemSelection,QItemSelection) ),this,
            SLOT( updateButtons() ) );

    connect( projectsView->model(), SIGNAL( layoutChanged() ), this,
            SLOT( updateButtons() ) );

    connect( personsView->model(), SIGNAL( layoutChanged() ), this,
            SLOT( updateButtons() ) );

    updateButtons();
}

MainWindow::~MainWindow()
{
}

void MainWindow::fillSampleData()
{
    //////////////////////////////////////////
    QSqlQuery q("select * from tb_konum");
    if (!q.isActive())
    {
        qDebug() << " ------- HATA tb_konum dosyası  " ;
    } else {
        qDebug() << "MW-fsdata - tb_konum Dosyası Aktif : " ;
        q.last();
        qDebug() << "MW-fsdata - Kayıt sayısı: " << q.at()+1;
        q.first();
    }

    QSqlRecord rec = q.record();

    //  int company1 =1;
    int id{0};
    QString nm{""};
    QString ad{""};
    do
    {
        id = q.value(rec.indexOf("f_konumID")).toInt();
        nm = q.value(rec.indexOf("f_konumAdi")).toString();
        ad = q.value(rec.indexOf("f_konumAdres")).toString();

        qDebug() << id;
        qDebug() << nm;
        qDebug() << ad;

        // girişte listeyi table dan al ve oluştur
        m_manager->addCompanygrs( id, nm, ad );

    }while (q.next());

    //////////////////////////////////////////




    //int company1 = m_manager->addCompany( "First Company", "Gliwice, Poland" );
    //int company2 = m_manager->addCompany( "Second Company", "Berlin, Germany" );
    int project1 = m_manager->addProjectlst( 0, "Project Alpha" );
    int project2 = m_manager->addProjectlst( 1, "Project Beta" );
    int project3 = m_manager->addProjectlst( 2, "Project Delta" );
    int person1 = m_manager->addPerson( "Mecinski, Michal", "Gliwice, Poland", "555 12 45" );
    int person2 = m_manager->addPerson( "Kowalski, Jan", "Katowice, Poland", "555 64 12" );
    int person3 = m_manager->addPerson( "Schmidt, Hans", "Berlin, Germany", "555 77 35" );
    int person4 = m_manager->addPerson( "Smith, John", "New York, USA", "555 01 33" );
    m_manager->addMember( person1, project1 );
    m_manager->addMember( person1, project2 );
    m_manager->addMember( person2, project1 );
    m_manager->addMember( person1, project3 );
    m_manager->addMember( person3, project3 );
    m_manager->addMember( person4, project2 );
}

void MainWindow::updateButtons()
{
    m_companyId = 0;
    m_projectId = 0;
    m_memberId = 0;

    QModelIndexList selectedProjects = projectsView->selectionModel()->selectedRows();
    QModelIndex index = !selectedProjects.isEmpty() ? selectedProjects.first() : QModelIndex();

    //    qDebug()<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    //    //    qDebug()<< "indexlist projects" << selectedProjects;
    //    qDebug()<< "---------------------------------------------";
    //    qDebug()<<"prj modelindex : " << index;
    //    qDebug()<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";

    QString ndx0{};
    QString ndx1{};
    QString ndx2{};
    while ( index.isValid() ) {
        int level = projectsView->model()->data( index, RDB::TableItemModel::LevelRole ).toInt();
        int rowId = projectsView->model()->data( index, RDB::TableItemModel::RowIdRole ).toInt();

        //        if (level == 0)
        //        {
        //            ndx0 += "Konum : " + QString::number(rowId) ;

        //        }
        //        if (level == 1)
        //        {
        //            ndx1 += "Araç : " + QString::number(rowId);

        //        }
        //        if (level == 2)
        //        {
        //            ndx2 += "İş emri : " + QString::number(rowId);

        //        }



        //        qDebug() << ndx0;
        //        qDebug() << ndx1;
        //        qDebug() << ndx2;

        switch ( level )
        {
        case 0:
        {
            ndx0 += "K : " + QString::number(rowId) ;
            m_companyId = rowId;
            break;
        }
        case 1:
        {
            ndx1 += "A : " + QString::number(rowId);
            m_projectId = rowId;
            break;
        }
        case 2:
        {
            ndx2 += "İ : " + QString::number(rowId);
            m_memberId = rowId;
            break;
        }
        }

        index = projectsView->model()->parent( index );
        //   ndx += " - "+ QString::number(level) +":" + QString::number(rowId);

    }

    // qDebug() << ndx;
    qDebug() << "================";
    qDebug() << ndx0 <<" " << ndx1 << " " << ndx2;
    qDebug() << "=============================================================";

    m_personId = 0;


    QModelIndexList selectedPersons = personsView->selectionModel()->selectedRows();
    if ( !selectedPersons.isEmpty() )
        m_personId =personsView->model()->data( selectedPersons.first(), RDB::TableItemModel::RowIdRole ).toInt();

    addProject->setEnabled( m_companyId != 0 );
    editProject->setEnabled( m_companyId != 0 );
    removeProject->setEnabled( m_companyId != 0 );
    editPerson->setEnabled( m_personId != 0 );
    removePerson->setEnabled( m_personId != 0 );
    addMember->setEnabled( m_projectId != 0 && m_personId != 0 );
}

void MainWindow::on_addCompany_clicked()
{
    EditDialog dialog( this );
    dialog.setWindowTitle( tr( "Add Company" ) );
    dialog.setPhoneEnabled( false );

    if ( dialog.exec() == QDialog::Accepted )
    {
        //dbye ekle
        m_manager->addCompanydb( dialog.name(), dialog.address() );
        // tree ye ekle
        m_manager->addCompanylst( dialog.name(), dialog.address() );
    }
}

void MainWindow::on_addProject_clicked()
{
    if ( m_companyId != 0 ) {
        EditDialog dialog( this );
        dialog.setWindowTitle( tr( "Add Project" ) );
        dialog.setAddressEnabled( false );
        dialog.setPhoneEnabled( false );

        if ( dialog.exec() == QDialog::Accepted )
        {
            m_manager->addProjectlst( m_companyId, dialog.name() );
            m_manager->addProjectdb( m_companyId, dialog.name() );
        }
    }
}

void MainWindow::on_editProject_clicked()
{
    if ( m_projectId != 0 ) {
        const Project* project = m_manager->projects()->find( m_projectId );
        if ( project ) {
            EditDialog dialog( this );
            dialog.setWindowTitle( tr( "Edit Project" ) );
            dialog.setName( project->name() );
            dialog.setAddressEnabled( false );
            dialog.setPhoneEnabled( false );

            if ( dialog.exec() == QDialog::Accepted )
                m_manager->editProject( m_projectId, dialog.name() );
        }
    } else if ( m_companyId != 0 ) {
        const Company* company = m_manager->companies()->find( m_companyId );

        ///////////////////////////////
        qDebug () << "KONUM - " << QString::number(m_companyId )<<
            " - selecting for edit...........................";
        // find company id in table

        QSqlQuery query("select * from tb_konum where f_konumID = "+QString::number(m_companyId ));

        if (!query.exec())
            qDebug ()<< "Konum CAN NOT selected for edit  "  ;
        else
            qDebug ()<< "Konum selected for edit";

        if ( company ) {
            EditDialog dialog( this );
            dialog.setWindowTitle( tr( "Edit Company" ) );
            /////////////////////////////////
            //dialog.setName( tb_konum );
            //dialog.setAddress( address );
            //dialog.setPhoneEnabled( false );
            qDebug () << "--------------------------------------------------------";
            //     qDebug () << "db tb_konum adres  : " << f_konumAdi +" "+ f_konumAdres ;
            qDebug () << "obj tb_konum adres : " << company->name() + " " + company->address();
            qDebug () << "--------------------------------------------------------";

            /////////////////////////////////
            dialog.setName( company->name() );
            dialog.setAddress( company->address() );
            dialog.setPhoneEnabled( false );

            if ( dialog.exec() == QDialog::Accepted )
            {
                // listeyi değiştir
                m_manager->editCompany( m_companyId, dialog.name(), dialog.address() );
                /////////////////////////////////// db değiştir.
                m_manager->editCompany2( m_companyId , dialog.name(), dialog.address() );
                ////////////////////m_companyId
            }
        }
    }
}

void MainWindow::on_removeProject_clicked()
{
    if ( m_memberId != 0 && m_projectId != 0 )
        m_manager->removeMember( m_memberId, m_projectId );
    else if ( m_projectId != 0 )
        m_manager->removeProject( m_projectId );
    else if ( m_companyId != 0 )
        m_manager->removeCompany( m_companyId );
}

void MainWindow::on_addPerson_clicked()
{
    EditDialog dialog( this );
    dialog.setWindowTitle( tr( "Add Person" ) );

    if ( dialog.exec() == QDialog::Accepted )
        m_manager->addPerson( dialog.name(), dialog.address(), dialog.phone() );
}

void MainWindow::on_editPerson_clicked()
{
    if ( m_personId != 0 ) {
        const Person* person = m_manager->persons()->find( m_personId );
        if ( person ) {
            EditDialog dialog( this );
            dialog.setWindowTitle( tr( "Edit Person" ) );
            dialog.setName( person->name() );
            dialog.setAddress( person->address() );
            dialog.setPhone( person->phone() );

            if ( dialog.exec() == QDialog::Accepted )
                m_manager->editPerson( m_personId, dialog.name(), dialog.address(), dialog.phone() );
        }
    }
}

void MainWindow::on_removePerson_clicked()
{
    if ( m_personId != 0 )
        m_manager->removePerson( m_personId );
}

void MainWindow::on_addMember_clicked()
{
    if ( m_projectId != 0 && m_personId != 0 ) {
        if ( m_manager->members()->find( m_personId, m_projectId ) ) {
            const Person* person = m_manager->persons()->find( m_personId );
            QString personName = person ? person->name() : QString();
            const Project* project = m_manager->projects()->find( m_projectId );
            QString projectName = project ? project->name() : QString();
            QMessageBox::warning( this, tr( "Warning" ),
                                 tr( "Person '%1' is already a member of project '%2'." ).arg( personName, projectName ) );
        } else {
            m_manager->addMember( m_personId, m_projectId );
        }
    }
}


void MainWindow::logger()
{
    ///////////////////////////////////
    ///////////////////////////////////

    QWidget *ui = new QWidget();
    //ui->setWindowFlags(Qt::WindowActive);
    ui->setAttribute( Qt::WA_QuitOnClose, false );
    ui->setAttribute( Qt::WA_TranslucentBackground, false);
    ui->setGeometry(800,0,400,800);
    QVBoxLayout *layout = new QVBoxLayout;

    ui->setLayout(layout);
    //   QListView* view = new QListView;
    QTextBrowser* browser = new QTextBrowser;
    // browser->setAttribute( Qt::WA_TranslucentBackground, true);
    //  layout->addWidget(new QLabel(QLatin1String(view->metaObject()->className())));
    //  layout->addWidget(view);
    layout->addWidget(new QLabel(QLatin1String(
        browser->metaObject()->className() )));
    layout->addWidget(browser);
    // QStringListModel* model = new QStringListModel;
    // view->setModel(model);

    //logToModel(view->model());

    logToModel(browser->document());
    //rescrollToBottom(view);
    rescrollToBottom(browser);
    /**
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [] {
            static int n;
            qDebug() << "Tick" << ++n;
        });

    timer.start(500);
    qDebug() << "Tick";*/
        ui->show();
    ////////////////////////////////////



    //QWidget ui;
    //QVBoxLayout layout{&ui};
    //QListView view;
    //QTextBrowser browser;
    //layout.addWidget(new QLabel(QLatin1String(view.metaObject()->className())));
    //layout.addWidget(&view);
    //layout.addWidget(new QLabel(QLatin1String(browser.metaObject()->className())));
    //layout.addWidget(&browser);
    //QStringListModel model;
    //thisview.setModel(&model);

    //logToModel(thisview.model());
    //logToModel(thisbrowser.document());
    //rescrollToBottom(&view);
    //rescrollToBottom(&browser);

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, [] {
    //    static int n;
    //    qDebug() << "Tick" << ++n;
    //});

    //timer.start(500);

    ////////////////////////////////////
}

void MainWindow::dbConnector()
{
    //////////////////////////////////////////
    Db = new DataBase();
    if (Db->connectToDataBase()) {
        qWarning() << "Database Connected... ";
        qDebug() << "----------------------------------------------------";
    }

    //////////////////////////////////////////

}



void MainWindow::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("objMainWindow"));

    this->resize(773, 499);
    this->setWindowTitle("222222222222222222222222222222222");
    actionQuit = new QAction(this);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionQuit->setCheckable(true);

    centralwidget = new QWidget();
    this->setCentralWidget(centralwidget);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout_3 = new QVBoxLayout(centralwidget);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

    splitter = new QSplitter(centralwidget);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Horizontal);

    groupBox = new QGroupBox(splitter);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));

    verticalLayout = new QVBoxLayout(groupBox);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    projectsView = new QTreeView(groupBox);
    projectsView->setObjectName(QString::fromUtf8("projectsView"));
    projectsView->setSortingEnabled(true);

    verticalLayout->addWidget(projectsView);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    addCompany = new QPushButton(groupBox);
    addCompany->setObjectName(QString::fromUtf8("addCompany"));

    horizontalLayout->addWidget(addCompany);

    addProject = new QPushButton(groupBox);
    addProject->setObjectName(QString::fromUtf8("addProject"));

    horizontalLayout->addWidget(addProject);

    addMember = new QPushButton(groupBox);
    addMember->setObjectName(QString::fromUtf8("addMember"));

    horizontalLayout->addWidget(addMember);

    editProject = new QPushButton(groupBox);
    editProject->setObjectName(QString::fromUtf8("editProject"));

    horizontalLayout->addWidget(editProject);

    removeProject = new QPushButton(groupBox);
    removeProject->setObjectName(QString::fromUtf8("removeProject"));

    horizontalLayout->addWidget(removeProject);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);


    verticalLayout->addLayout(horizontalLayout);

    splitter->addWidget(groupBox);

    groupBox_2 = new QGroupBox(splitter);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    verticalLayout_2 = new QVBoxLayout(groupBox_2);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_3->addWidget(label);

    searchEdit = new QLineEdit(groupBox_2);
    searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

    horizontalLayout_3->addWidget(searchEdit);


    verticalLayout_2->addLayout(horizontalLayout_3);

    personsView = new QTreeView(groupBox_2);
    personsView->setObjectName(QString::fromUtf8("personsView"));
    personsView->setRootIsDecorated(false);
    personsView->setSortingEnabled(true);

    verticalLayout_2->addWidget(personsView);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    addPerson = new QPushButton(groupBox_2);
    addPerson->setObjectName(QString::fromUtf8("addPerson"));

    horizontalLayout_2->addWidget(addPerson);

    editPerson = new QPushButton(groupBox_2);
    editPerson->setObjectName(QString::fromUtf8("editPerson"));

    horizontalLayout_2->addWidget(editPerson);

    removePerson = new QPushButton(groupBox_2);
    removePerson->setObjectName(QString::fromUtf8("removePerson"));

    horizontalLayout_2->addWidget(removePerson);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);


    verticalLayout_2->addLayout(horizontalLayout_2);

    splitter->addWidget(groupBox_2);

    verticalLayout_3->addWidget(splitter);

    this->setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 773, 22));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    this->setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionQuit);

    retranslateUi();
    QObject::connect(actionQuit, &QAction::triggered, this, qOverload<>(&QMainWindow::close));


    QMetaObject::connectSlotsByName(this);



}

void MainWindow::retranslateUi()
{
    setWindowTitle(QCoreApplication::translate("", "rrrRDB Demo", nullptr));
    actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
    actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
    groupBox->setTitle(QCoreApplication::translate("MainWindow", "Projects", nullptr));
    addCompany->setText(QCoreApplication::translate("MainWindow", "Add Company", nullptr));
    addProject->setText(QCoreApplication::translate("MainWindow", "Add Project", nullptr));
    addMember->setText(QCoreApplication::translate("MainWindow", "Add Member", nullptr));
    editProject->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
    removeProject->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
    groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Persons", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "Search:", nullptr));
    addPerson->setText(QCoreApplication::translate("MainWindow", "Add Person", nullptr));
    editPerson->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
    removePerson->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
    menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
} // retranslateUi


void MainWindow::connects()
{

}
