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

#ifndef VIEWSETTINGSDIALOG_H
#define VIEWSETTINGSDIALOG_H

#include "dialogs/informationdialog.h"
#include "xmlui/client.h"

class ViewsModel;

class QLineEdit;
class QTreeView;
class QModelIndex;

/**
* Dialog for managing public or personal view settings.
*/
class ViewSettingsDialog : public InformationDialog, public XmlUi::Client
{
    Q_OBJECT
protected:
    /**
    * Constructor.
    */
    ViewSettingsDialog( int typeId, bool isPublic );

    /**
    * Destructor.
    */
    ~ViewSettingsDialog();

protected: // overrides
    void customEvent( QEvent* e );

private slots:
    void modifyOrder();
    void modifyDefaultView();
    void modifyInitialView();

    void addView();
    void cloneView();
    void editRename();
    void editDelete();
    void editModify();
    void editPublish();
    void switchMode();

    void updateActions();

    void doubleClicked( const QModelIndex& index );
    void listContextMenu( const QPoint& pos );

private:
    void updateViewSettings();

private:
    int m_typeId;
    bool m_isPublic;

    int m_selectedViewId;

    QLineEdit* m_orderEdit;
    QLineEdit* m_columnsEdit;
    QLineEdit* m_sortByEdit;
    QLineEdit* m_initialEdit;

    QTreeView* m_list;
    ViewsModel* m_model;
};

class PublicViewSettingsDialog : public ViewSettingsDialog
{
    Q_OBJECT
public:
    PublicViewSettingsDialog( int typeId );
    ~PublicViewSettingsDialog();
};

class PersonalViewSettingsDialog : public ViewSettingsDialog
{
    Q_OBJECT
public:
    PersonalViewSettingsDialog( int typeId );
    ~PersonalViewSettingsDialog();
};

#endif
