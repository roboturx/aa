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

#ifndef TABLES_H

#include <QObject>

#include "rdb/rdb.h"

class Company
{
public:
    Company( int companyId, const QString& name, const QString& address );
    ~Company();

public:
    int companyId() const { return m_companyId; }

    void setName( const QString& name ) { m_name = name; }
    QString name() const { return m_name; }

    void setAddress( const QString& address ) { m_address = address; }
    QString address() const { return m_address; }

private:
    int m_companyId;
    QString m_name;
    QString m_address;
};

typedef RDB::SimpleTable<Company> Companies;

class Project
{
public:
    Project( int projectId, int companyId, const QString& name );
    ~Project();

public:
    int projectId() const { return m_projectId; }
    int companyId() const { return m_companyId; }

    void setName( const QString& name ) { m_name = name; }
    QString name() const { return m_name; }

private:
    int m_projectId;
    int m_companyId;
    QString m_name;
};

typedef RDB::ChildTable<Project> Projects;

class Person
{
public:
    Person( int personId, const QString& name, const QString& address, const QString& phone );
    ~Person();

public:
    int personId() const { return m_personId; }

    void setName( const QString& name ) { m_name = name; }
    QString name() const { return m_name; }

    void setAddress( const QString& address ) { m_address = address; }
    QString address() const { return m_address; }

    void setPhone( const QString& phone ) { m_phone = phone; }
    QString phone() const { return m_phone; }

private:
    int m_personId;
    QString m_name;
    QString m_address;
    QString m_phone;
};

class Member
{
public:
    Member( int personId, int projectId );
    ~Member();

public:
    int personId() const { return m_personId; }
    int projectId() const { return m_projectId; }

private:
    int m_personId;
    int m_projectId;
};

typedef RDB::CrossTable<Member> Members;

typedef RDB::SimpleTable<Person> Persons;

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager( QObject* parent );
    ~DataManager();

public:
    const Companies* companies() const { return &m_companies; }

    int addCompany( const QString& name, const QString& address );
    void editCompany( int companyId, const QString& name, const QString& address );
    void removeCompany( int companyId );

    const Projects* projects() const { return &m_projects; }

    int addProject( int companyId, const QString& name );
    void editProject( int projectId, const QString& name );
    void removeProject( int projectId );

    const Persons* persons() const { return &m_persons; }

    int addPerson( const QString& name, const QString& address, const QString& phone );
    void editPerson( int personId, const QString& name, const QString& address, const QString& phone );
    void removePerson( int personId );

    const Members* members() const { return &m_members; }

    void addMember( int personId, int projectId );
    void removeMember( int personId, int projectId );

signals:
    void projectsChanged();
    void personsChanged();

private:
    int nextId();

private:
    Companies m_companies;
    Projects m_projects;
    Persons m_persons;
    Members m_members;

    int m_lastId;
};

#endif
