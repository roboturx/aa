/**************************************************************************
* This file is part of the WebIssues Desktop Client program
* Copyright (C) 2006 Michał Męciński
* Copyright (C) 2007-2017 WebIssues Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "alertsmodel.h"

#include "data/datamanager.h"
#include "utils/iconloader.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPixmap>
#include <QFont>

AlertsModel::AlertsModel( QObject* parent ) : BaseModel( parent ),
    m_folderId( 0 ),
    m_typeId( 0 )
{
    appendModel( new QSqlQueryModel( this ) );

    bool emailEnabled = dataManager->setting( "email_enabled" ).toInt();

    QList<int> columnMapping;
    columnMapping << 2 << 3 << 4 << 5;
    if ( emailEnabled )
        columnMapping << 6;
    columnMapping << 7;
    setColumnMapping( 0, columnMapping );

    setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
    setHeaderData( 1, Qt::Horizontal, tr( "Total" ) );
    setHeaderData( 2, Qt::Horizontal, tr( "Unread" ) );
    setHeaderData( 3, Qt::Horizontal, tr( "Modified" ) );
    if ( emailEnabled )
        setHeaderData( 4, Qt::Horizontal, tr( "Email Type" ) );
    setHeaderData( 5, Qt::Horizontal, tr( "Is Public" ) );

    refresh();
}

AlertsModel::~AlertsModel()
{
}

void AlertsModel::initializeFolder( int folderId )
{
    m_folderId = folderId;
    m_typeId = 0;

    refresh();
}

void AlertsModel::initializeGlobalList( int typeId )
{
    m_typeId = typeId;
    m_folderId = 0;

    refresh();
}

QVariant AlertsModel::data( const QModelIndex& index, int role ) const
{
    int level = levelOf( index );
    int row = mappedRow( index );

    if ( role == Qt::DisplayRole ) {
        QVariant value = rawData( level, row, mappedColumn( index ), role );

        if ( index.column() == 0 ) {
            int viewId = rawData( level, row, 1 ).toInt();
            return ( viewId != 0 ) ? value.toString() : tr( "All Issues" );
        }

        if ( mappedColumn( index ) == 6 ) {
            int email = value.toInt();
            if ( email == ImmediateNotificationEmail )
                return tr( "Immediate notifications" );
            if ( email == SummaryNotificationEmail )
                return tr( "Summary of notifications" );
            if ( email == SummaryReportEmail )
                return tr( "Summary reports" );
            return tr( "None" );
        }

        if ( mappedColumn( index ) == 7 )
            return value.toBool() ? tr( "Yes" ) : tr( "No" );

        return value;
    }

    if ( role == Qt::DecorationRole && index.column() == 0 ) {
        QString name = "alert";
        int unread = rawData( level, row, 4 ).toInt();
        if ( unread > 0 ) {
            name = "alert-unread";
        } else {
            int modified = rawData( level, row, 5 ).toInt();
            if ( modified > 0 )
                name = "alert-modified";
        }
        if ( rawData( level, row, 7 ).toBool() )
            return IconLoader::overlayedPixmap( name, "overlay-public" );
        return IconLoader::pixmap( name );
    }

    if ( role == Qt::FontRole && index.column() >= 1 && index.column() <= 3 ) {
        int count = rawData( level, row, mappedColumn( index ), Qt::DisplayRole ).toInt();
        if ( count > 0 ) {
            QFont font;
            font.setBold( true );
            return font;
        }
    }

    return QVariant();
}

void AlertsModel::refresh()
{
    QString query = "SELECT a.alert_id, v.view_id, v.view_name, ac.total_count, ac.new_count, ac.modified_count, a.alert_email, a.is_public"
        " FROM alerts AS a"
        " LEFT OUTER JOIN views AS v ON v.view_id = a.view_id"
        " LEFT OUTER JOIN alerts_cache AS ac ON ac.alert_id = a.alert_id";
    if ( m_folderId != 0 )
        query += " WHERE a.folder_id = ?";
    else if ( m_typeId != 0 )
        query += " WHERE a.type_id = ?";
    query += " ORDER BY v.view_name COLLATE LOCALE ASC";

    QSqlQuery sqlQuery;
    sqlQuery.prepare( query );
    if ( m_folderId != 0 )
        sqlQuery.addBindValue( m_folderId );
    else if ( m_typeId != 0 )
        sqlQuery.addBindValue( m_typeId );
    sqlQuery.exec();

    modelAt( 0 )->setQuery( sqlQuery );

    updateData();
}

void AlertsModel::updateEvent( UpdateEvent* e )
{
    if ( e->unit() == UpdateEvent::Projects || e->unit() == UpdateEvent::Types || e->unit() == UpdateEvent::AlertStates || e->unit() == UpdateEvent::States )
        refresh();
}
