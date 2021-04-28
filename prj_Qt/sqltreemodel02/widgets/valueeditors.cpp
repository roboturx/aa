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

#include "valueeditors.h"

#include "data/datamanager.h"
#include "data/entities.h"
#include "utils/definitioninfo.h"
#include "utils/datetimehelper.h"
#include "utils/attributehelper.h"
#include "widgets/inputlineedit.h"
#include "widgets/inputtextedit.h"

#include <QVariant>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QCalendarWidget>

// fix for GCC 4.3-snapshot
#include <climits>

InputLineValueEditor::InputLineValueEditor( const DefinitionInfo& info, bool initial, int projectId, QObject* parent, QWidget* parentWidget ) : AbstractValueEditor( parent ),
    m_initial( initial ),
    m_projectId( projectId ),
    m_members( false )
{
    switch ( AttributeHelper::toAttributeType( info ) ) {
        case TextAttribute:
            initializeText( info, parentWidget );
            break;
        case EnumAttribute:
            initializeEnum( info, parentWidget );
            break;
        case NumericAttribute:
            initializeNumeric( info, parentWidget );
            break;
        case DateTimeAttribute:
            initializeDateTime( info, parentWidget );
            break;
        case UserAttribute:
            initializeUser( info, parentWidget );
            break;
        default:
            break;
    }
}

InputLineValueEditor::~InputLineValueEditor()
{
}

void InputLineValueEditor::initializeText( const DefinitionInfo& info, QWidget* parentWidget )
{
    InputLineEdit* edit = new InputLineEdit( parentWidget );

    QVariant maxLength = info.metadata( "max-length" );
    if ( maxLength.isValid() )
        edit->setMaxLength( maxLength.toInt() );
    else
        edit->setMaxLength( 255 );

    QVariant minLength = info.metadata( "min-length" );
    if ( minLength.isValid() )
        edit->setMinLength( minLength.toInt() );

    edit->setRequired( info.metadata( "required" ).toBool() );

    if ( m_initial )
        edit->setFunctions( InputLineEdit::MeFunction );

    setWidget( edit );
}

void InputLineValueEditor::initializeEnum( const DefinitionInfo& info, QWidget* parentWidget )
{
    EnumLineEdit* edit = new EnumLineEdit( parentWidget );

    QVariant items = info.metadata( "items" );
    bool multiSelect = info.metadata( "multi-select" ).toBool();

    edit->setItems( items.toStringList() );
    edit->setMultiSelect( multiSelect );

    QVariant maxLength = info.metadata( "max-length" );
    if ( maxLength.isValid() )
        edit->setMaxLength( maxLength.toInt() );
    else
        edit->setMaxLength( 255 );

    QVariant minLength = info.metadata( "min-length" );
    if ( minLength.isValid() )
        edit->setMinLength( minLength.toInt() );

    edit->setEditable( info.metadata( "editable" ).toBool() );

    edit->setRequired( info.metadata( "required" ).toBool() );

    if ( m_initial )
        edit->setFunctions( InputLineEdit::MeFunction );

    setWidget( edit );
}

void InputLineValueEditor::initializeNumeric( const DefinitionInfo& info, QWidget* parentWidget )
{
    NumericLineEdit* edit = new NumericLineEdit( parentWidget );

    edit->setDecimal( info.metadata( "decimal" ).toInt() );
    edit->setStripZeros( info.metadata( "strip" ).toBool() );

    QVariant minValue = info.metadata( "min-value" );
    if ( minValue.isValid() )
        edit->setMinValue( minValue.toDouble() );

    QVariant maxValue = info.metadata( "max-value" );
    if ( maxValue.isValid() )
        edit->setMaxValue( maxValue.toDouble() );

    edit->setRequired( info.metadata( "required" ).toBool() );

    setWidget( edit );
}

void InputLineValueEditor::initializeDateTime( const DefinitionInfo& info, QWidget* parentWidget )
{
    DateTimeLineEdit* edit = new DateTimeLineEdit( parentWidget );

    edit->setWithTime( info.metadata( "time" ).toBool() );
    edit->setLocalTime( info.metadata( "local" ).toBool() );

    edit->setRequired( info.metadata( "required" ).toBool() );

    if ( m_initial )
        edit->setFunctions( DateTimeLineEdit::TodayFunction );

    setWidget( edit );
}

void InputLineValueEditor::initializeUser( const DefinitionInfo& info, QWidget* parentWidget )
{
    EnumLineEdit* edit = new EnumLineEdit( parentWidget );

    m_members = info.metadata( "members" ).toBool();

    QStringList items = userItems();

    bool multiSelect = info.metadata( "multi-select" ).toBool();

    edit->setItems( items );
    edit->setMultiSelect( multiSelect );
    edit->setEditable( false );

    edit->setRequired( info.metadata( "required" ).toBool() );

    if ( m_initial )
        edit->setFunctions( InputLineEdit::MeFunction );

    setWidget( edit );
}

void InputLineValueEditor::setInputValue( const QString& value )
{
    InputLineEdit* edit = (InputLineEdit*)widget();
    edit->setInputValue( value );
}

QString InputLineValueEditor::inputValue()
{
    InputLineEdit* edit = (InputLineEdit*)widget();
    return edit->inputValue();
}

void InputLineValueEditor::setProjectId( int projectId )
{
    if ( m_members && m_projectId != projectId ) {
        m_projectId = projectId;

        EnumLineEdit* edit = (EnumLineEdit*)widget();
        edit->setItems( userItems() );
    }
}

QStringList InputLineValueEditor::userItems()
{
    QStringList items;

    if ( m_initial )
        items.append( QString( "[%1]" ).arg( tr( "Me" ) ) );

    QList<UserEntity> users;
    if ( m_members && m_projectId != 0 ) {
        ProjectEntity project = ProjectEntity::find( m_projectId );
        users = project.members();
    } else if ( dataManager->currentUserAccess() == AdminAccess ) {
        users = UserEntity::list();
    } else {
        users = UserEntity::visible();
    }

    foreach ( const UserEntity& user, users )
        items.append( user.name() );

    return items;
}

InputTextValueEditor::InputTextValueEditor( const DefinitionInfo& info, QObject* parent, QWidget* parentWidget ) : AbstractValueEditor( parent )
{
    InputTextEdit* edit = new InputTextEdit( parentWidget );

    QVariant maxLength = info.metadata( "max-length" );
    if ( maxLength.isValid() )
        edit->setMaxLength( maxLength.toInt() );
    else
        edit->setMaxLength( 255 );

    QVariant minLength = info.metadata( "min-length" );
    if ( minLength.isValid() )
        edit->setMinLength( minLength.toInt() );

    edit->setRequired( info.metadata( "required" ).toBool() );

    setWidget( edit );
}

InputTextValueEditor::~InputTextValueEditor()
{
}

void InputTextValueEditor::setInputValue( const QString& value )
{
    InputTextEdit* edit = (InputTextEdit*)widget();
    edit->setInputValue( value );
}

QString InputTextValueEditor::inputValue()
{
    InputTextEdit* edit = (InputTextEdit*)widget();
    return edit->inputValue();
}

void InputTextValueEditor::setProjectId( int /*projectId*/ )
{
}
