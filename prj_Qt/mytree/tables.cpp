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
#include "mainwindow.h"
#include "./rdbmy/tableitemmodel.h"
#include <QSqlQuery>
#include <QSqlError>

Company::Company( int companyId, const QString& name, const QString& address ) :
    m_companyId( companyId ),
    m_name( name ),
    m_address( address )
{
}

Company::~Company()
{
}

Project::Project( int projectId, int companyId, const QString& name ) :
    m_projectId( projectId ),
    m_companyId( companyId ),
    m_name( name )
{
}

Project::~Project()
{
}

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

Member::Member( int personId, int projectId ) :
    m_personId( personId ),
    m_projectId( projectId )
{
}

Member::~Member()
{
}

DataManager::DataManager( QObject* parent ) : QObject( parent ),
    m_lastId( 0 )
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

int DataManager::addCompanylst( const QString& name, const QString& address )
{
    int companyId = nextId();
    m_companies.insert( new Company( companyId, name, address ) );
    emit projectsChanged();
    return companyId;
}

////////////////////////////////////
int DataManager::addCompanydb(const QString &name, const QString &address)
{
    //int companyId = nextId();

    QSqlQuery query;
    query.prepare("INSERT INTO konum "
                  "(name, address ) "
                  "VALUES (:A, :B     )");

    //query.bindValue(":A", companyId);
    query.bindValue(":A", name);
    query.bindValue(":B", address);


    if (!query.exec()) {
        qDebug() << "           ERROR insert into KONUM";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "            A record inserted to KONUM";
        return true;
    }
    query.prepare("select * from konum");
    if (!query.exec())
    {
        qDebug() << " - - - KONUM - - - HATA.tables.addcompany2";
    }
    int recc {};
    if (!query.last())
                {
        recc ={ query.value(0).toInt()};
                    qDebug() << "            son kayıtta";
                    qDebug() << "son kayıttaki id = " << recc;
                }



    m_companies.insert( new Company( recc, name, address ) );
    emit projectsChanged();
    return recc;
}
////////////////////////////////////
int DataManager::addCompanygrs(const int &id, const QString &name, const QString &address)
{
    // ekran indeksi  için eklendi
    nextId();

    qDebug ()<< "company 333333  "<<id << name<< address;
    m_companies.insert( new Company( id, name, address ) );
   // emit projectsChanged();
    return id;
//    QSqlQuery query;
//    query.prepare("select * from konum");

//    if (!query.exec()) {
//        qDebug() << " - - - KONUM - - - HATA";
//        qDebug() << query.lastError().text();
//        return false;
//    }
//    else
//    {
//        qDebug() << "            son kayıt to KONUM";
//        if (!query.last())
//        {
//            qDebug() << "            son kayıtta";
//            qDebug() << "son kayıttaki id = " << query.value(0).toInt();
//        }

//        return true;
//    }


}

//////////////////////////

void DataManager::editCompany( int companyId, const QString& name, const QString& address )
{
    Company* company = m_companies.find( companyId );
    if ( company ) {
        company->setName( name );
        company->setAddress( address );
        emit projectsChanged();
    }
}

////////////////////////////////////////
void DataManager::editCompany2( int konumId, const QString& name, const QString& address )
{
    //Company* company = m_companies.find( companyId );
    //find konumid in table konum


    QSqlQuery query("select * from konum");
    if (query.exec())
        qDebug ()<< "selected for edit";
    else
        qDebug ()<< "CAN NOT selected for edit";

    qDebug ()  << "aranan konumid :" << konumId;
    int id_knm{-1};
    while (query.next())
    {
        qDebug ()  << "in the while";
        qDebug ()  << "recc konumid :" << query.value(0).toInt();
        int id=-1;
        if (query.value(0).toInt() == konumId )
        {
            qDebug ()  << konumId << "id  found dddddddddddddddddddddddddddddddddd   = ";
            id_knm = query.value(0).toInt() ;
        }

    }
    if ( id_knm != -1 )
    {

        query.prepare( "UPDATE konum SET name = :A, address = :B WHERE companyID = :C") ;
        query.bindValue(":A" , name);
        query.bindValue(":B" , address);
        query.bindValue(":C" , QString::number( id_knm ));
        if( !query.exec() )
        {
            qDebug() << query.lastError();
        }
        else
        {
            qDebug() << "replaced";
        }
    }


    //  emit projectsChanged();

    //    if ( company ) {
    //        company->setName( name );
    //        company->setAddress( address );
    //        emit projectsChanged();
    //    }
}
////////////////////////////////////////////////////



void DataManager::removeCompany( int companyId )
{
    m_companies.remove( companyId );
    RDB::ForeignIterator<Project> it( m_projects.parentIndex(), companyId );
    while ( it.next() )
        m_members.removeFirst( it.get()->projectId() );
    m_projects.removeChildren( companyId );
    emit projectsChanged();
}

int DataManager::addProjectlst( int companyId, const QString& name )
{
    int projectId = nextId();
    m_projects.insert( new Project( projectId, companyId, name ) );
    emit projectsChanged();
    return projectId;
}
int DataManager::addProjectdb( int companyId, const QString& name )
{
   // int projectId = nextId();

    QSqlQuery query;

    /// ADD RECORD
    query.prepare("INSERT INTO isemri "
                  "(companyid, name ) "
                  "VALUES (:A, :B     )");

    //query.bindValue(":A", companyId);
    query.bindValue(":A", companyId);
    query.bindValue(":B", name);


    if (!query.exec()) {
        qDebug() << "           ERROR insert into KONUM";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "            A record inserted to ISEMRI";
        return true;
    }
    /// SELECT ALL RECORDS TO FIND RECCOUNT
    query.prepare("select * from isemri");
    if (!query.exec())
    {
        qDebug() << " - - - ISEMRI - - - HATA.tables.addprojectsdb";
    }
    int recc {};
    if (!query.last())
    {
        recc ={ query.value(0).toInt()};
        qDebug() << "            işemri son kayıtta";
        qDebug() << "son kayıttaki id = " << recc;
    }




    m_projects.insert( new Project( recc, companyId, name ) );
    emit projectsChanged();
    return recc;
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
