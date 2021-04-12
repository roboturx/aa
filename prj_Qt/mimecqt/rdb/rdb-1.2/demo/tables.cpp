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

#include "tables.h"

///////////////////////////////////////////////////////

Company::Company( int companyId, const QString& name, const QString& address ) :
    m_companyId( companyId ),
    m_name( name ),
    m_address( address )
{
}

Company::~Company()
{
}

///////////////////////////////////////////////////////

Project::Project( int projectId, int companyId, const QString& name ) :
    m_projectId( projectId ),
    m_companyId( companyId ),
    m_name( name )
{
}

Project::~Project()
{
}

///////////////////////////////////////////////////////

Person::Person( int personId, const QString& name, const QString& address, const QString& phone ) :
    m_personId( personId ),
    m_name( name ),
    m_address( address ),
    m_phone( phone )
{
}

Person::~Person()
{
}

///////////////////////////////////////////////////////

Member::Member( int personId, int projectId ) :
    m_personId( personId ),
    m_projectId( projectId )
{
}

Member::~Member()
{
}

///////////////////////////////////////////////////////

DataManager::DataManager( QObject* parent )
    : QObject( parent ),    m_lastId( 0 )
{
    m_companies.initIndex( 63, &Company::companyId );
    m_projects.initIndex( 251, &Project::projectId );
    m_projects.initParentIndex( 63, &Project::companyId );
    m_members.initFirstIndex( 251, &Member::personId );
    m_members.initSecondIndex( 251, &Member::projectId );
    m_persons.initIndex( 251, &Person::personId );
}

DataManager::~DataManager()
{
}

int DataManager::addCompany( const QString& name, const QString& address )
{
    int companyId = nextId();
    m_companies.insert( new Company( companyId, name, address ) );
    emit projectsChanged();
    return companyId;
}

void DataManager::editCompany( int companyId, const QString& name, const QString& address )
{
    Company* company = m_companies.find( companyId );
    if ( company ) {
        company->setName( name );
        company->setAddress( address );
        emit projectsChanged();
    }
}

void DataManager::removeCompany( int companyId )
{
    m_companies.remove( companyId );
    RDB::ForeignIterator<Project> it( m_projects.parentIndex(), companyId );
    while ( it.next() )
        m_members.removeFirst( it.get()->projectId() );
    m_projects.removeChildren( companyId );
    emit projectsChanged();
}

int DataManager::addProject( int companyId, const QString& name )
{
    int projectId = nextId();
    m_projects.insert( new Project( projectId, companyId, name ) );
    emit projectsChanged();
    return projectId;
}

void DataManager::editProject( int projectId, const QString& name )
{
    Project* project = m_projects.find( projectId );
    if ( project ) {
        project->setName( name );
        emit projectsChanged();
    }
}

void DataManager::removeProject( int projectId )
{
    m_projects.remove( projectId );
    m_members.removeSecond( projectId );
    emit projectsChanged();
}

int DataManager::addPerson( const QString& name, const QString& address, const QString& phone )
{
    int personId = nextId();
    m_persons.insert( new Person( personId, name, address, phone ) );
    emit personsChanged();
    return personId;
}

void DataManager::editPerson( int personId, const QString& name, const QString& address, const QString& phone )
{
    Person* person = m_persons.find( personId );
    if ( person ) {
        person->setName( name );
        person->setAddress( address );
        person->setPhone( phone );
        emit projectsChanged();
        emit personsChanged();
    }
}

void DataManager::removePerson( int personId )
{
    m_persons.remove( personId );
    m_members.removeFirst( personId );
    emit projectsChanged();
    emit personsChanged();
}

void DataManager::addMember( int personId, int projectId )
{
    m_members.insert( new Member( personId, projectId ) );
    emit projectsChanged();
}

void DataManager::removeMember( int personId, int projectId )
{
    m_members.remove( personId, projectId );
    emit projectsChanged();
}

int DataManager::nextId()
{
    return ++m_lastId;
}
