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

#ifndef MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "database.h"

#include "./rdbmy/tableitemmodel.h"

class DataManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent );
    ~MainWindow();

    RDB::TableItemModel* projectsModel ;

private slots:
    void updateButtons();

    void on_addCompany_clicked();
    void on_addProject_clicked();
    void on_editProject_clicked();
    void on_removeProject_clicked();
    void on_addPerson_clicked();
    void on_editPerson_clicked();
    void on_removePerson_clicked();
    void on_addMember_clicked();

private:
    void fillSampleData();



private:


    DataManager* m_manager;
    DataBase *Db;

    void setupUi();
    void retranslateUi();

    void connects();
    void logger();
    void dbConnector();

    int m_companyId;
    int m_projectId;
    int m_memberId;
    int m_personId;


public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTreeView *projectsView;
    QHBoxLayout *horizontalLayout;
    QPushButton *addCompany;
    QPushButton *addProject;
    QPushButton *addMember;
    QPushButton *editProject;
    QPushButton *removeProject;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *searchEdit;
    QTreeView *personsView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addPerson;
    QPushButton *editPerson;
    QPushButton *removePerson;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;


 public:


};

#endif
