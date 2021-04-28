#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSplitter>
#include <QTreeView>
#include <QWidget>
#include "database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



   // RDB::TableItemModel* projectsModel ;

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


      // DataManager* m_manager;


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





};
#endif // MAINWINDOW_H
