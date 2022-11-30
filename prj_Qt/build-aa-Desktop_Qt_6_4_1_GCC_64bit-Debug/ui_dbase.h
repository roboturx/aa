/********************************************************************************
** Form generated from reading UI file 'dbase.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBASE_H
#define UI_DBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBase
{
public:
    QGridLayout *gridLayout_3;
    QTextEdit *durum;

    void setupUi(QWidget *DBase)
    {
        if (DBase->objectName().isEmpty())
            DBase->setObjectName("DBase");
        DBase->resize(570, 399);
        gridLayout_3 = new QGridLayout(DBase);
        gridLayout_3->setObjectName("gridLayout_3");
        durum = new QTextEdit(DBase);
        durum->setObjectName("durum");

        gridLayout_3->addWidget(durum, 0, 0, 1, 1);


        retranslateUi(DBase);

        QMetaObject::connectSlotsByName(DBase);
    } // setupUi

    void retranslateUi(QWidget *DBase)
    {
        DBase->setWindowTitle(QCoreApplication::translate("DBase", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DBase: public Ui_DBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBASE_H
