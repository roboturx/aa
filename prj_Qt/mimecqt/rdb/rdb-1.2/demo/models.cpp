/****************************************************************************
* Simple template-based relational database
* Copyright (C) 2006-2010 Michał Męciński
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*   3. Neither the name of the copyright holder nor the names of the
*      contributors may be used to endorse or promote products derived from
*      this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

#include "models.h"

#include <QPixmap>

#include "tables.h"

BaseTableModel::BaseTableModel( DataManager* parent ) : RDB::AbstractTableModel( parent )
{
}

BaseTableModel::~BaseTableModel()
{
}

QString BaseTableModel::columnName( int column ) const
{
    switch ( column ) {
        case Column_Name:
            return tr( "Name" );
        case Column_Address:
            return tr( "Address" );
        case Column_Phone:
            return tr( "Phone" );
        default:
            return QString();
    }
}

DataManager* BaseTableModel::dataManager() const
{
    return (DataManager*)parent();
}

CompaniesModel::CompaniesModel( DataManager* parent ) : BaseTableModel( parent )
{
}

CompaniesModel::~CompaniesModel()
{
}

QString CompaniesModel::text( int id, int column ) const
{
    const Company* company = dataManager()->companies()->find( id );
    if ( !company )
        return QString();

    switch ( column ) {
        case Column_Name:
            return company->name();
        case Column_Address:
            return company->address();
        default:
            return QString();
    }
}

QPixmap CompaniesModel::icon( int /*id*/, int column ) const
{
    if ( column == Column_Name )
        return QPixmap( ":/icons/folder.png" );
    return QPixmap();
}

ProjectsModel::ProjectsModel( DataManager* parent ) : BaseTableModel( parent )
{
}

ProjectsModel::~ProjectsModel()
{
}

QString ProjectsModel::text( int id, int column ) const
{
    const Project* project = dataManager()->projects()->find( id );
    if ( !project )
        return QString();

    switch ( column ) {
        case Column_Name:
            return project->name();
        default:
            return QString();
    }
}

QPixmap ProjectsModel::icon( int /*id*/, int column ) const
{
    if ( column == Column_Name )
        return QPixmap( ":/icons/folder.png" );
    return QPixmap();
}

PersonsModel::PersonsModel( DataManager* parent ) : BaseTableModel( parent )
{
}

PersonsModel::~PersonsModel()
{
}

QString PersonsModel::text( int id, int column ) const
{
    const Person* person = dataManager()->persons()->find( id );
    if ( !person )
        return QString();

    switch ( column ) {
        case Column_Name:
            return person->name();
        case Column_Address:
            return person->address();
        case Column_Phone:
            return person->phone();
        default:
            return QString();
    }
}

QPixmap PersonsModel::icon( int /*id*/, int column ) const
{
    if ( column == Column_Name )
        return QPixmap( ":/icons/person.png" );
    return QPixmap();
}

PersonsFilter::PersonsFilter( DataManager* parent ) : RDB::AbstractRowFilter( parent )
{
}

PersonsFilter::~PersonsFilter()
{
}

void PersonsFilter::setNameFilter( const QString& filter )
{
    m_nameFilter = filter;
    emit conditionsChanged();
}

bool PersonsFilter::filterRow( int id )
{
    if ( m_nameFilter.isEmpty() )
        return true;

    DataManager* dataManager = (DataManager*)parent();
    const Person* person = dataManager->persons()->find( id );
    QString name = person ? person->name() : QString();

    return name.contains( m_nameFilter, Qt::CaseInsensitive );
}
