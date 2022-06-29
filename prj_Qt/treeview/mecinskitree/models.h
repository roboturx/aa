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

#ifndef MODELS_H

#include "./rdbmy/abstracttablemodel.h"
#include "./rdbmy/abstractrowfilter.h"

enum Columns
{
    Column_id,
    Column_Name,
    Column_Address,
    Column_Phone
};

class DataManager;

class BaseTableModel : public RDB::AbstractTableModel
{
    Q_OBJECT
public:
    BaseTableModel( DataManager* parent );
    ~BaseTableModel();

public: // overrides
    QString columnName( int column ) const;

protected:
    DataManager* dataManager() const;
};

class CompaniesModel : public BaseTableModel
{
    Q_OBJECT
public:
    CompaniesModel( DataManager* parent );
    ~CompaniesModel();

public: // overrides
    QString text( int id, int column ) const;
    QPixmap icon( int id, int column ) const;
};

class ProjectsModel : public BaseTableModel
{
    Q_OBJECT
public:
    ProjectsModel( DataManager* parent );
    ~ProjectsModel();

public: // overrides
    QString text( int id, int column ) const;
    QPixmap icon( int id, int column ) const;
};

class PersonsModel : public BaseTableModel
{
    Q_OBJECT
public:
    PersonsModel( DataManager* parent );
    ~PersonsModel();

public: // overrides
    QString text( int id, int column ) const;
    QPixmap icon( int id, int column ) const;
};

class PersonsFilter : public RDB::AbstractRowFilter
{
    Q_OBJECT
public:
    PersonsFilter( DataManager* parent );
    ~PersonsFilter();

public slots:
    void setNameFilter( const QString& filter );

public: // overrides
    bool filterRow( int id );

private:
    QString m_nameFilter;
};

#endif
