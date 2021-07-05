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

#include "viewfactory.h"
#include "usersview.h"
#include "typesview.h"
#include "summaryview.h"
#include "folderview.h"
#include "globallistview.h"
#include "issueview.h"

#include <QMetaObject>

View* ViewFactory::createView( const char* className, QObject* parent, QWidget* parentWidget )
{
    if ( !qstrcmp( className, UsersView::staticMetaObject.className() ) )
        return new UsersView( parent, parentWidget );
    if ( !qstrcmp( className, TypesView::staticMetaObject.className() ) )
        return new TypesView( parent, parentWidget );
    if ( !qstrcmp( className, SummaryView::staticMetaObject.className() ) )
        return new SummaryView( parent, parentWidget );
    if ( !qstrcmp( className, FolderView::staticMetaObject.className() ) )
        return new FolderView( parent, parentWidget );
    if ( !qstrcmp( className, GlobalListView::staticMetaObject.className() ) )
        return new GlobalListView( parent, parentWidget );
    if ( !qstrcmp( className, IssueView::staticMetaObject.className() ) )
        return new IssueView( parent, parentWidget );
    return NULL;
}
