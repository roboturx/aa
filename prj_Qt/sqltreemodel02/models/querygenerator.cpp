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

#include "querygenerator.h"

#include "data/datamanager.h"
#include "data/issuetypecache.h"
#include "models/foldermodel.h"
#include "utils/attributehelper.h"
#include "utils/datetimehelper.h"

#include <QSqlQuery>
#include <QDateTime>

QueryGenerator::QueryGenerator() :
    m_folderId( 0 ),
    m_typeId( 0 ),
    m_viewId( 0 ),
    m_projectId( 0 ),
    m_searchColumn( -1 ),
    m_sortColumn( -1 ),
    m_sortOrder( Qt::AscendingOrder ),
    m_valid( false )
{
}

QueryGenerator::~QueryGenerator()
{
}

void QueryGenerator::initializeFolder( int folderId, int viewId )
{
    m_folderId = folderId;
    m_viewId = viewId;

    QSqlQuery sqlQuery;
    sqlQuery.prepare( "SELECT f.type_id"
        " FROM folders AS f"
        " WHERE f.folder_id = ?" );
    sqlQuery.addBindValue( folderId );
    sqlQuery.exec();

    if ( !sqlQuery.next() )
        return;

    m_typeId = sqlQuery.value( 0 ).toInt();

    initializeCommon( false );
}

void QueryGenerator::initializeGlobalList( int typeId, int viewId )
{
    m_typeId = typeId;
    m_viewId = viewId;

    initializeCommon( true );
}

void QueryGenerator::initializeCommon( bool withLocation )
{
    IssueTypeCache* cache = dataManager->issueTypeCache( m_typeId );

    DefinitionInfo info;

    if ( m_viewId != 0 ) {
        QSqlQuery sqlQuery;
        sqlQuery.prepare( "SELECT v.view_def"
            " FROM views AS v"
            " WHERE v.view_id = ? AND v.type_id = ?" );
        sqlQuery.addBindValue( m_viewId );
        sqlQuery.addBindValue( m_typeId );
        sqlQuery.exec();

        if ( !sqlQuery.next() )
            return;

        info = DefinitionInfo::fromString( sqlQuery.value( 0 ).toString() );
    } else {
        info = cache->defaultView();
    }

    m_columns = cache->viewColumns( info, withLocation );
    m_filters = cache->viewFilters( info );

    QPair<int, Qt::SortOrder> order = cache->viewSortOrder( info );
    m_sortColumn = m_columns.indexOf( order.first );
    m_sortOrder = order.second;
}

void QueryGenerator::setProject( int projectId )
{
    m_projectId = projectId;
}

void QueryGenerator::setSearchText( int column, const QString& text )
{
    m_searchColumn = column;
    m_searchText = text;
}

void QueryGenerator::setColumns( const QList<int>& columns )
{
    m_columns = columns;

    m_sortColumn = 0;
    m_sortOrder = Qt::AscendingOrder;
}

QString QueryGenerator::query( bool allColumns )
{
    if ( !m_typeId )
        return QString();

    m_valid = true;
    m_arguments.clear();

    QString select = generateSelect( allColumns );
    QString joins = generateJoins( allColumns );
    QString conditions = generateConditions();

    if ( !m_valid )
        return QString();

    return QString( "SELECT %1 FROM %2 WHERE %3" ).arg( select, joins, conditions );
}

QString QueryGenerator::generateSelect( bool allColumns )
{
    QStringList result;
    result.append( "i.issue_id" );
    result.append( "i.stamp_id" );
    result.append( "s.read_id" );
    result.append( "s.subscription_id" );

    if ( allColumns ) {
        foreach ( int column, m_columns ) {
            switch ( column ) {
                case Column_ID:
                    break;
                case Column_Name:
                    result.append( "i.issue_name" );
                    break;
                case Column_CreatedDate:
                    result.append( "i.created_time" );
                    break;
                case Column_ModifiedDate:
                    result.append( "i.modified_time" );
                    break;
                case Column_CreatedBy:
                    result.append( "uc.user_name" );
                    break;
                case Column_ModifiedBy:
                    result.append( "um.user_name" );
                    break;
                case Column_Location:
                    result.append( "f.folder_name" );
                    break;
                default:
                    if ( column > Column_UserDefined )
                        result.append( QString( "a%1.attr_value" ).arg( column - Column_UserDefined ) );
                    else
                        m_valid = false;
                    break;
            }
        }

        if ( m_folderId == 0 )
            result.append( "p.project_name" );
    }

    return result.join( ", " );
}

QString QueryGenerator::generateJoins( bool allColumns )
{
    QStringList joins;
    joins.append( "issues AS i" );

    if ( m_folderId == 0 ) {
        joins.append( "INNER JOIN folders AS f ON f.folder_id = i.folder_id" );
        if ( allColumns )
            joins.append( "INNER JOIN projects AS p ON p.project_id = f.project_id" );
    }

    joins.append( "LEFT OUTER JOIN issue_states AS s ON s.issue_id = i.issue_id AND s.user_id = ?" );
    m_arguments.append( dataManager->currentUserId() );

    QList<int> columns;

    if ( allColumns )
        columns = m_columns;

    foreach ( const DefinitionInfo& filter, m_filters ) {
        int column = filter.metadata( "column" ).toInt();
        if ( !columns.contains( column ) )
            columns.append( column );
    }

    if ( !m_searchText.isEmpty() ) {
        if ( !columns.contains( m_searchColumn ) )
            columns.append( m_searchColumn );
    }

    foreach ( int column, columns ) {
        switch ( column ) {
            case Column_CreatedBy:
                joins.append( "LEFT OUTER JOIN users AS uc ON uc.user_id = i.created_user_id" );
                break;
            case Column_ModifiedBy:
                joins.append( "LEFT OUTER JOIN users AS um ON um.user_id = i.modified_user_id" );
                break;
            default:
                if ( column > Column_UserDefined ) {
                    joins.append( QString( "LEFT OUTER JOIN attr_values AS a%1 ON a%1.issue_id = i.issue_id AND a%1.attr_id = ?" ).arg( column - Column_UserDefined ) );
                    m_arguments.append( column - Column_UserDefined );
                }
                break;
        }
    }

    return joins.join( " " );
}

QString QueryGenerator::generateConditions()
{
    QStringList conditions;

    if ( m_folderId != 0 ) {
        conditions.append( "i.folder_id = ?" );
        m_arguments.append( m_folderId );
    } else {
        conditions.append( "f.type_id = ?" );
        m_arguments.append( m_typeId );
    }

    if ( m_folderId == 0 && m_projectId != 0 ) {
        conditions.append( "f.project_id = ?" );
        m_arguments.append( m_projectId );
    }

    IssueTypeCache* cache = dataManager->issueTypeCache( m_typeId );

    QList<DefinitionInfo> allFilters = m_filters;

    if ( !m_searchText.isEmpty() ) {
        DefinitionInfo info;
        info.setType( m_searchColumn == Column_ID ? "EQ" : "CON" );
        info.setMetadata( "column", m_searchColumn );
        info.setMetadata( "value", m_searchText );
        allFilters.append( info );
    }

    foreach ( const DefinitionInfo& filter, allFilters ) {
        QString type = filter.type();
        int column = filter.metadata( "column" ).toInt();
        QString value = filter.metadata( "value" ).toString();

        QString expression;

        switch ( column ) {
            case Column_ID:
                expression = "i.issue_id";
                break;
            case Column_Name:
                expression = "i.issue_name";
                break;
            case Column_CreatedDate:
                expression = "i.created_time";
                break;
            case Column_ModifiedDate:
                expression = "i.modified_time";
                break;
            case Column_CreatedBy:
                expression = "uc.user_name";
                break;
            case Column_ModifiedBy:
                expression = "um.user_name";
                break;
            default:
                if ( column > Column_UserDefined )
                    expression = QString( "a%1.attr_value" ).arg( column - Column_UserDefined );
                else
                    m_valid = false;
                break;
        }

        if ( value.isEmpty() ) {
            conditions.append( makeNullCondition( expression, type ) );
            continue;
        }

        switch ( column ) {
            case Column_ID:
                conditions.append( makeNumericCondition( expression, type, value.toInt() ) );
                break;
            case Column_Name:
            case Column_CreatedBy:
            case Column_ModifiedBy:
                conditions.append( makeStringCondition( expression, type, convertUserValue( value ) ) );
                break;
            case Column_CreatedDate:
            case Column_ModifiedDate:
                conditions.append( makeDateCondition( expression, type, convertDateTimeValue( value, false ) ) );
                break;
            default:
                if ( column > Column_UserDefined ) {
                    DefinitionInfo info = cache->attributeDefinition( column - Column_UserDefined );
                    switch ( AttributeHelper::toAttributeType( info ) ) {
                        case TextAttribute:
                        case EnumAttribute:
                        case UserAttribute:
                            conditions.append( makeStringCondition( QString( "COALESCE( %1, '' )" ).arg( expression ), type, convertUserValue( value ) ) );
                            break;
                        case NumericAttribute:
                            conditions.append( makeNumericCondition( QString( "CAST( %1 AS REAL )" ).arg( expression ), type, value.toDouble() ) );
                            break;
                        case DateTimeAttribute:
                            conditions.append( makeDateCondition( QString( "CAST( STRFTIME( '%s', %1 ) AS INTEGER )" ).arg( expression ), type, convertDateTimeValue( value, info.metadata( "local" ).toBool() ) ) );
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
    }

    return conditions.join( " AND " );
}

QString QueryGenerator::convertUserValue( const QString& value ) const
{
    if ( value.startsWith( QLatin1String( "[Me]" ) ) )
        return dataManager->currentUserName();
    return value;
}

QDateTime QueryGenerator::convertDateTimeValue( const QString& value, bool local ) const
{
    QDate date;
    if ( value.startsWith( QLatin1String( "[Today]" ) ) ) {
        date = QDate::currentDate();
        if ( value.length() > 7 ) {
            int days = value.mid( 8 ).toInt();
            if ( value.at( 7 ) == '-' )
                days = -days;
            date = date.addDays( days );
        }
    } else {
        date = DateTimeHelper::parseDate( value );
    }
    return QDateTime( date, QTime( 0, 0 ), local ? Qt::LocalTime : Qt::UTC );
}

QString QueryGenerator::makeStringCondition( const QString& expression, const QString& type, const QString& value )
{
    if ( type == QLatin1String( "EQ" ) ) {
        m_arguments.append( value );
        return QString( "%1 COLLATE NOCASE = ?" ).arg( expression );
    }
    if ( type == QLatin1String( "NEQ" ) ) {
        m_arguments.append( value );
        return QString( "%1 COLLATE NOCASE <> ?" ).arg( expression );
    }
    if ( type == QLatin1String( "CON" ) ) {
        m_arguments.append( QLatin1String( ".*" ) + QRegExp::escape( value ) + QLatin1String( ".*" ) );
        return QString( "%1 REGEXP ?" ).arg( expression );
    }
    if ( type == QLatin1String( "BEG" ) ) {
        m_arguments.append( QRegExp::escape( value ) + QLatin1String( ".*" ) );
        return QString( "%1 REGEXP ?" ).arg( expression );
    }
    if ( type == QLatin1String( "END" ) ) {
        m_arguments.append( QLatin1String( ".*" ) + QRegExp::escape( value ) );
        return QString( "%1 REGEXP ?" ).arg( expression );
    }
    if ( type == QLatin1String( "IN" ) ) {
        QStringList items = value.split(  ", " );
        if ( items.count() >= 2 ) {
            QStringList placeholders;
            foreach ( const QString item, items ) {
                m_arguments.append( item );
                placeholders.append( "?" );
            }
            return QString( "%1 COLLATE NOCASE IN ( %2 )" ).arg( expression, placeholders.join( ", " ) );
        } else {
            m_arguments.append( value );
            return QString( "%1 COLLATE NOCASE = ?" ).arg( expression );
        }
    }

    m_valid = false;
    return QString();
}

QString QueryGenerator::makeNullCondition( const QString& expression, const QString& type )
{
    if ( type == QLatin1String( "EQ" ) )
        return QString( "%1 IS NULL" ).arg( expression );
    if ( type == QLatin1String( "NEQ" ) )
        return QString( "%1 IS NOT NULL" ).arg( expression );

    m_valid = false;
    return QString();
}

QString QueryGenerator::makeNumericCondition( const QString& expression, const QString& type, const QVariant& value )
{
    m_arguments.append( value );

    if ( type == QLatin1String( "EQ" ) )
        return QString( "%1 = ?" ).arg( expression );
    if ( type == QLatin1String( "NEQ" ) )
        return QString( "%1 <> ?" ).arg( expression );
    if ( type == QLatin1String( "GT" ) )
        return QString( "%1 > ?" ).arg( expression );
    if ( type == QLatin1String( "LT" ) )
        return QString( "%1 < ?" ).arg( expression );
    if ( type == QLatin1String( "GTE" ) )
        return QString( "%1 >= ?" ).arg( expression );
    if ( type == QLatin1String( "LTE" ) )
        return QString( "%1 <= ?" ).arg( expression );

    m_valid = false;
    return QString();
}

QString QueryGenerator::makeDateCondition( const QString& expression, const QString& type, const QDateTime& value )
{
    int lower = value.toTime_t();
    int upper = value.addDays( 1 ).addSecs( -1 ).toTime_t();

    if ( type == QLatin1String( "EQ" ) ) {
        m_arguments.append( lower );
        m_arguments.append( upper );
        return QString( "%1 BETWEEN ? AND ?" ).arg( expression );
    }
    if ( type == QLatin1String( "NEQ" ) ) {
        m_arguments.append( lower );
        m_arguments.append( upper );
        return QString( "%1 NOT BETWEEN ? AND ?" ).arg( expression );
    }
    if ( type == QLatin1String( "GT" ) ) {
        m_arguments.append( upper );
        return QString( "%1 > ?" ).arg( expression );
    }
    if ( type == QLatin1String( "LT" ) ) {
        m_arguments.append( lower );
        return QString( "%1 < ?" ).arg( expression );
    }
    if ( type == QLatin1String( "GTE" ) ) {
        m_arguments.append( lower );
        return QString( "%1 >= ?" ).arg( expression );
    }
    if ( type == QLatin1String( "LTE" ) ) {
        m_arguments.append( upper );
        return QString( "%1 <= ?" ).arg( expression );
    }

    m_valid = false;
    return QString();
}

QList<QStringList> QueryGenerator::sortColumns() const
{
    QList<QStringList> result;

    IssueTypeCache* cache = dataManager->issueTypeCache( m_typeId );

    if ( m_valid ) {
        foreach ( int column, m_columns ) {
            QStringList columns;
            switch ( column ) {
                case Column_ID:
                    columns.append( "i.issue_id" );
                    break;
                case Column_Name:
                    columns.append( "i.issue_name COLLATE LOCALE" );
                    break;
                case Column_CreatedDate:
                    columns.append( "i.issue_id" );
                    break;
                case Column_ModifiedDate:
                    columns.append( "i.stamp_id" );
                    break;
                case Column_CreatedBy:
                    columns.append( "uc.user_name COLLATE LOCALE" );
                    break;
                case Column_ModifiedBy:
                    columns.append( "um.user_name COLLATE LOCALE" );
                    break;
                case Column_Location:
                    columns.append( "p.project_name COLLATE LOCALE" );
                    columns.append( "f.folder_name COLLATE LOCALE" );
                    break;
                default:
                    if ( column > Column_UserDefined ) {
                        DefinitionInfo info = cache->attributeDefinition( column - Column_UserDefined );
                        switch ( AttributeHelper::toAttributeType( info ) ) {
                            case TextAttribute:
                            case EnumAttribute:
                            case UserAttribute:
                                columns.append( QString( "a%1.attr_value COLLATE LOCALE" ).arg( column - Column_UserDefined ) );
                                break;
                            case NumericAttribute:
                                columns.append( QString( "CAST( a%1.attr_value AS REAL )" ).arg( column - Column_UserDefined ) );
                                break;
                            case DateTimeAttribute:
                                columns.append( QString( "CAST( STRFTIME( '%s', a%1.attr_value ) AS INTEGER )" ).arg( column - Column_UserDefined ) );
                                break;
                            default:
                                break;
                        }
                    }
                    break;
            }
            result.append( columns );
        }
    }

    return result;
}

QList<int> QueryGenerator::columnMapping() const
{
    QList<int> result;

    if ( m_valid ) {
        int index = 4;

        foreach ( int column, m_columns ) {
            if ( column == Column_ID )
                result.append( 0 );
            else
                result.append( index++ );
        }
    }

    return result;
}
