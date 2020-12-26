/********************************************************************************
** Form generated from reading UI file 'cw_.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CW__H
#define UI_CW__H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cw_ftr
{
public:

    void setupUi(QWidget *cw_ftr)
    {
        if (cw_ftr->objectName().isEmpty())
            cw_ftr->setObjectName(QString::fromUtf8("cw_ftr"));
        cw_ftr->resize(400, 300);

        retranslateUi(cw_ftr);

        QMetaObject::connectSlotsByName(cw_ftr);
    } // setupUi

    void retranslateUi(QWidget *cw_ftr)
    {
        cw_ftr->setWindowTitle(QCoreApplication::translate("cw_ftr", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cw_ftr: public Ui_cw_ftr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CW__H
