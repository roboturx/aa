/********************************************************************************
** Form generated from reading UI file 'mainForm.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMakina;
    QAction *actionFaturta;
    QAction *actionFirma;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGraphicsView *graphicsView;
    QLabel *label;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menuAt_lye;
    QMenu *menuSat_nAlma;
    QMenu *menuAyarlar;
    QMenu *menuAmbar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QTreeView *treeView;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(463, 430);
        actionMakina = new QAction(MainWindow);
        actionMakina->setObjectName(QString::fromUtf8("actionMakina"));
        actionFaturta = new QAction(MainWindow);
        actionFaturta->setObjectName(QString::fromUtf8("actionFaturta"));
        actionFirma = new QAction(MainWindow);
        actionFirma->setObjectName(QString::fromUtf8("actionFirma"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        graphicsView = new QGraphicsView(page);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 30, 411, 221));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 121, 16));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        mdiArea = new QMdiArea(page_2);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));

        gridLayout_2->addWidget(mdiArea, 1, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 463, 26));
        menuAt_lye = new QMenu(menubar);
        menuAt_lye->setObjectName(QString::fromUtf8("menuAt_lye"));
        menuSat_nAlma = new QMenu(menubar);
        menuSat_nAlma->setObjectName(QString::fromUtf8("menuSat_nAlma"));
        menuAyarlar = new QMenu(menubar);
        menuAyarlar->setObjectName(QString::fromUtf8("menuAyarlar"));
        menuAmbar = new QMenu(menubar);
        menuAmbar->setObjectName(QString::fromUtf8("menuAmbar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout_3->addWidget(treeView, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        dockWidget_2->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_2);

        menubar->addAction(menuAt_lye->menuAction());
        menubar->addAction(menuSat_nAlma->menuAction());
        menubar->addAction(menuAyarlar->menuAction());
        menubar->addAction(menuAmbar->menuAction());
        menuAt_lye->addAction(actionMakina);
        menuSat_nAlma->addAction(actionFaturta);
        menuSat_nAlma->addAction(actionFirma);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionMakina->setText(QCoreApplication::translate("MainWindow", "Makina ", nullptr));
        actionFaturta->setText(QCoreApplication::translate("MainWindow", "Faturta", nullptr));
        actionFirma->setText(QCoreApplication::translate("MainWindow", "Firma", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Grafik view", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "MDI Area", nullptr));
        menuAt_lye->setTitle(QCoreApplication::translate("MainWindow", "At\303\266lye", nullptr));
        menuSat_nAlma->setTitle(QCoreApplication::translate("MainWindow", "Sat\304\261nAlma", nullptr));
        menuAyarlar->setTitle(QCoreApplication::translate("MainWindow", "Ayarlar", nullptr));
        menuAmbar->setTitle(QCoreApplication::translate("MainWindow", "Ambar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
