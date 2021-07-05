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

#ifndef STATEDIALOGS_H
#define STATEDIALOGS_H

#include "dialogs/commanddialog.h"

/**
* Dialog for executing the <tt>SET ISSUE READ</tt> command.
*/
class IssueStateDialog : public CommandDialog
{
    Q_OBJECT
public:
    /**
    * Constructor.
    * @param issueId Identifier of the issue.
    * @param readId The new read stamp of the issue.
    * @param parent The parent widget.
    */
    IssueStateDialog( int issueId, int readId, QWidget* parent );

    /**
    * Destructor.
    */
    ~IssueStateDialog();

public: // overrides
    void accept();

private:
    int m_issueId;
    int m_readId;
};

/**
* Dialog for executing the <tt>SET FOLDER READ</tt> command.
*/
class FolderStateDialog : public CommandDialog
{
    Q_OBJECT
public:
    /**
    * Constructor.
    * @param folderId Identifier of the folder.
    * @param readId The new read stamp of the folder.
    * @param parent The parent widget.
    */
    FolderStateDialog( int folderId, int readId, QWidget* parent );

    /**
    * Destructor.
    */
    ~FolderStateDialog();

public: // overrides
    void accept();

private:
    int m_folderId;
    int m_readId;
};

/**
* Dialog for executing the <tt>SET FOLDER READ</tt> command for all folders of a given type.
*/
class GlobalListStateDialog : public CommandDialog
{
    Q_OBJECT
public:
    /**
    * Constructor.
    * @param typeId Identifier of the type of the folders.
    * @param isRead The new state of the folders.
    * @param parent The parent widget.
    */
    GlobalListStateDialog( int typeId, bool isRead, QWidget* parent );

    /**
    * Destructor.
    */
    ~GlobalListStateDialog();

public: // overrides
    void accept();

private:
    int m_typeId;
    int m_isRead;
};

/**
* Dialog for executing the <tt>ADD SUBSCRIPTION</tt> command.
*/
class AddSubscriptionDialog : public CommandDialog
{
    Q_OBJECT
public:
    /**
    * Constructor.
    * @param issueId Identifier of the issue.
    * @param parent The parent widget.
    */
    AddSubscriptionDialog( int issueId, QWidget* parent );

    /**
    * Destructor.
    */
    ~AddSubscriptionDialog();

public: // overrides
    void accept();

private:
    int m_issueId;
};

/**
* Dialog for executing the <tt>DELETE SUBSCRIPTION</tt> command.
*/
class DeleteSubscriptionDialog : public CommandDialog
{
    Q_OBJECT
public:
    /**
    * Constructor.
    * @param issueId Identifier of the issue.
    * @param parent The parent widget.
    */
    DeleteSubscriptionDialog( int issueId, QWidget* parent );

    /**
    * Destructor.
    */
    ~DeleteSubscriptionDialog();

public: // overrides
    void accept();

private:
    int m_issueId;
};

#endif
