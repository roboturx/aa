/********************************************************************************
** Form generated from reading UI file 'cw_fr.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CW_FR_H
#define UI_CW_FR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cw_fr
{
public:

    void setupUi(QWidget *cw_fr)
    {
        if (cw_fr->objectName().isEmpty())
            cw_fr->setObjectName(QString::fromUtf8("cw_fr"));
        cw_fr->resize(400, 300);

        retranslateUi(cw_fr);

        QMetaObject::connectSlotsByName(cw_fr);
    } // setupUi

    void retranslateUi(QWidget *cw_fr)
    {
        cw_fr->setWindowTitle(QCoreApplication::translate("cw_fr", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cw_fr: public Ui_cw_fr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CW_FR_H
