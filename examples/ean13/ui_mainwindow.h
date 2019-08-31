/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 1. Feb 19:06:21 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *CodeEdit;
    QLabel *label;
    QPushButton *UpdateSwt;
    QPushButton *PrintSwt;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CodeEdit = new QLineEdit(centralWidget);
        CodeEdit->setObjectName(QString::fromUtf8("CodeEdit"));
        CodeEdit->setGeometry(QRect(80, 10, 96, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 66, 16));
        UpdateSwt = new QPushButton(centralWidget);
        UpdateSwt->setObjectName(QString::fromUtf8("UpdateSwt"));
        UpdateSwt->setGeometry(QRect(205, 10, 75, 23));
        PrintSwt = new QPushButton(centralWidget);
        PrintSwt->setObjectName(QString::fromUtf8("PrintSwt"));
        PrintSwt->setGeometry(QRect(300, 10, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 18));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle("EAN13 Barcode Generator test program" );
        CodeEdit->setText("8026833045034" );
        label->setText("EAN13 Code");
        UpdateSwt->setText("Update");
        PrintSwt->setText("Print");
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
