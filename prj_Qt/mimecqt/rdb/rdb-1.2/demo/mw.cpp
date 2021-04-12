#include "mw.h"
#include "ui_mw.h"

#include <QMessageBox>

#include "rdb/tableitemmodel.h"

#include "editdialog.h"
#include "tables.h"
#include "models.h"
#include "database.h"

MW::MW()
{
    m_ui.setupUi( this );

    m_manager = new DataManager( this );

    fillSampleData();

    DataBase* db= new DataBase;

    QList<int> columns;
    columns << Column_Name << Column_Address << Column_Phone;

    RDB::TableItemModel* projectsModel = new RDB::TableItemModel( this );
    projectsModel->setColumns( columns );
    projectsModel->setRootTableModel( new CompaniesModel( m_manager ), m_manager->companies()->index() );
    projectsModel->addChildTableModel( new ProjectsModel( m_manager ),
        m_manager->projects()->index(), m_manager->projects()->parentIndex() );
    projectsModel->addChildTableModel( new PersonsModel( m_manager ),
        m_manager->members()->index().first(), m_manager->members()->index().second() );

    connect( m_manager, SIGNAL( projectsChanged() ), projectsModel,
             SLOT( updateData() ) );

    PersonsFilter* filter = new PersonsFilter( m_manager );
    connect( m_ui.searchEdit, SIGNAL( textChanged( const QString& ) ), filter, SLOT( setNameFilter( const QString& ) ) );

    RDB::TableItemModel* personsModel = new RDB::TableItemModel( this );
    personsModel->setColumns( columns );
    personsModel->setRootTableModel( new PersonsModel( m_manager ), m_manager->persons()->index() );
    personsModel->setRowFilter( filter );

    connect( m_manager, SIGNAL( personsChanged() ), personsModel, SLOT( updateData() ) );

    m_ui.projectsView->setModel( projectsModel );
    m_ui.personsView->setModel( personsModel );

    m_ui.projectsView->setColumnWidth( 0, 200 );
    m_ui.projectsView->sortByColumn( 0, Qt::AscendingOrder );
    m_ui.projectsView->expandAll();

    m_ui.personsView->setColumnWidth( 0, 120 );
    m_ui.personsView->sortByColumn( 0, Qt::AscendingOrder );

    connect( m_ui.projectsView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ),
        this, SLOT( updateButtons() ) );
    connect( m_ui.personsView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ),
        this, SLOT( updateButtons() ) );

    connect( m_ui.projectsView->model(), SIGNAL( layoutChanged() ), this, SLOT( updateButtons() ) );
    connect( m_ui.personsView->model(), SIGNAL( layoutChanged() ), this, SLOT( updateButtons() ) );

    updateButtons();
}

MW::~MW()
{
}

void MW::fillSampleData()
{
    int company1 = m_manager->addCompany( "First Company", "Gliwice, Poland" );
    int company2 = m_manager->addCompany( "Second Company", "Berlin, Germany" );
    int project1 = m_manager->addProject( company1, "Project Alpha" );
    int project2 = m_manager->addProject( company1, "Project Beta" );
    int project3 = m_manager->addProject( company2, "Project Delta" );
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

void MW::updateButtons()
{
    m_companyId = 0;
    m_projectId = 0;
    m_memberId = 0;

    QModelIndexList selectedProjects = m_ui.projectsView->selectionModel()->selectedRows();
    QModelIndex index = !selectedProjects.isEmpty() ? selectedProjects.first() : QModelIndex();

    while ( index.isValid() ) {
        int level = m_ui.projectsView->model()->data( index, RDB::TableItemModel::LevelRole ).toInt();
        int rowId = m_ui.projectsView->model()->data( index, RDB::TableItemModel::RowIdRole ).toInt();
        switch ( level ) {
            case 0:
                m_companyId = rowId;
                break;
            case 1:
                m_projectId = rowId;
                break;
            case 2:
                m_memberId = rowId;
                break;
        }
        index = m_ui.projectsView->model()->parent( index );
    }

    m_personId = 0;

    QModelIndexList selectedPersons = m_ui.personsView->selectionModel()->selectedRows();
    if ( !selectedPersons.isEmpty() )
        m_personId = m_ui.personsView->model()->data( selectedPersons.first(), RDB::TableItemModel::RowIdRole ).toInt();

    m_ui.addProject->setEnabled( m_companyId != 0 );
    m_ui.editProject->setEnabled( m_companyId != 0 );
    m_ui.removeProject->setEnabled( m_companyId != 0 );
    m_ui.editPerson->setEnabled( m_personId != 0 );
    m_ui.removePerson->setEnabled( m_personId != 0 );
    m_ui.addMember->setEnabled( m_projectId != 0 && m_personId != 0 );
}

void MW::on_addCompany_clicked()
{
    EditDialog dialog( this );
    dialog.setWindowTitle( tr( "Add Company" ) );
    dialog.setPhoneEnabled( false );

    if ( dialog.exec() == QDialog::Accepted )
        m_manager->addCompany( dialog.name(), dialog.address() );
}

void MW::on_addProject_clicked()
{
    if ( m_companyId != 0 ) {
        EditDialog dialog( this );
        dialog.setWindowTitle( tr( "Add Project" ) );
        dialog.setAddressEnabled( false );
        dialog.setPhoneEnabled( false );

        if ( dialog.exec() == QDialog::Accepted )
            m_manager->addProject( m_companyId, dialog.name() );
    }
}

void MW::on_editProject_clicked()
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
        if ( company ) {
            EditDialog dialog( this );
            dialog.setWindowTitle( tr( "Edit Company" ) );
            dialog.setName( company->name() );
            dialog.setAddress( company->address() );
            dialog.setPhoneEnabled( false );

            if ( dialog.exec() == QDialog::Accepted )
                m_manager->editCompany( m_companyId, dialog.name(), dialog.address() );
        }
    }
}

void MW::on_removeProject_clicked()
{
    if ( m_memberId != 0 && m_projectId != 0 )
        m_manager->removeMember( m_memberId, m_projectId );
    else if ( m_projectId != 0 )
        m_manager->removeProject( m_projectId );
    else if ( m_companyId != 0 )
        m_manager->removeCompany( m_companyId );
}

void MW::on_addPerson_clicked()
{
    EditDialog dialog( this );
    dialog.setWindowTitle( tr( "Add Person" ) );

    if ( dialog.exec() == QDialog::Accepted )
        m_manager->addPerson( dialog.name(), dialog.address(), dialog.phone() );
}

void MW::on_editPerson_clicked()
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

void MW::on_removePerson_clicked()
{
    if ( m_personId != 0 )
        m_manager->removePerson( m_personId );
}

void MW::on_addMember_clicked()
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
