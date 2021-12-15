/********************************************************************************
** Form generated from reading UI file 'arayuz.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARAYUZ_H
#define UI_ARAYUZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Arayuz
{
public:

    void setupUi(QWidget *Arayuz)
    {
        if (Arayuz->objectName().isEmpty())
            Arayuz->setObjectName(QString::fromUtf8("Arayuz"));
        Arayuz->resize(400, 300);

        retranslateUi(Arayuz);

        QMetaObject::connectSlotsByName(Arayuz);
    } // setupUi

    void retranslateUi(QWidget *Arayuz)
    {
        Arayuz->setWindowTitle(QCoreApplication::translate("Arayuz", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Arayuz: public Ui_Arayuz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARAYUZ_H
