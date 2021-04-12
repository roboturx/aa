/********************************************************************************
** Form generated from reading UI file 'mw.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MW_H
#define UI_MW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MW
{
public:
    QWidget *centralwidget;
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MW)
    {
        if (MW->objectName().isEmpty())
            MW->setObjectName(QString::fromUtf8("MW"));
        MW->resize(800, 600);
        centralwidget = new QWidget(MW);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(40, 10, 744, 439));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        projectsView = new QTreeView(groupBox);
        projectsView->setObjectName(QString::fromUtf8("projectsView"));
        projectsView->setSortingEnabled(true);

        verticalLayout->addWidget(projectsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addCompany = new QPushButton(groupBox);
        addCompany->setObjectName(QString::fromUtf8("addCompany"));

        horizontalLayout->addWidget(addCompany);

        addProject = new QPushButton(groupBox);
        addProject->setObjectName(QString::fromUtf8("addProject"));

        horizontalLayout->addWidget(addProject);

        addMember = new QPushButton(groupBox);
        addMember->setObjectName(QString::fromUtf8("addMember"));

        horizontalLayout->addWidget(addMember);

        editProject = new QPushButton(groupBox);
        editProject->setObjectName(QString::fromUtf8("editProject"));

        horizontalLayout->addWidget(editProject);

        removeProject = new QPushButton(groupBox);
        removeProject->setObjectName(QString::fromUtf8("removeProject"));

        horizontalLayout->addWidget(removeProject);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        searchEdit = new QLineEdit(groupBox_2);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

        horizontalLayout_3->addWidget(searchEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        personsView = new QTreeView(groupBox_2);
        personsView->setObjectName(QString::fromUtf8("personsView"));
        personsView->setRootIsDecorated(false);
        personsView->setSortingEnabled(true);

        verticalLayout_2->addWidget(personsView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addPerson = new QPushButton(groupBox_2);
        addPerson->setObjectName(QString::fromUtf8("addPerson"));

        horizontalLayout_2->addWidget(addPerson);

        editPerson = new QPushButton(groupBox_2);
        editPerson->setObjectName(QString::fromUtf8("editPerson"));

        horizontalLayout_2->addWidget(editPerson);

        removePerson = new QPushButton(groupBox_2);
        removePerson->setObjectName(QString::fromUtf8("removePerson"));

        horizontalLayout_2->addWidget(removePerson);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        splitter->addWidget(groupBox_2);
        MW->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MW);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MW->setMenuBar(menubar);
        statusbar = new QStatusBar(MW);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MW->setStatusBar(statusbar);

        retranslateUi(MW);

        QMetaObject::connectSlotsByName(MW);
    } // setupUi

    void retranslateUi(QMainWindow *MW)
    {
        MW->setWindowTitle(QCoreApplication::translate("MW", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MW", "\304\260\305\237 Emri Takibi", nullptr));
        addCompany->setText(QCoreApplication::translate("MW", "Ara\303\247 Konumu", nullptr));
        addProject->setText(QCoreApplication::translate("MW", "\304\260\305\237 Emri Ekle", nullptr));
        addMember->setText(QCoreApplication::translate("MW", "Ara\303\247 Ekle", nullptr));
        editProject->setText(QCoreApplication::translate("MW", "D\303\274zenle", nullptr));
        removeProject->setText(QCoreApplication::translate("MW", "Sil", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MW", "Ara\303\247lar", nullptr));
        label->setText(QCoreApplication::translate("MW", "Ara", nullptr));
        addPerson->setText(QCoreApplication::translate("MW", "Ara\303\247 Ekle", nullptr));
        editPerson->setText(QCoreApplication::translate("MW", "D\303\274zenle", nullptr));
        removePerson->setText(QCoreApplication::translate("MW", "Sil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MW: public Ui_MW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MW_H
