/********************************************************************************
** Form generated from reading UI file 'wd_dptlp.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WD_DPTLP_H
#define UI_WD_DPTLP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wd_dptlp
{
public:

    void setupUi(QWidget *wd_dptlp)
    {
        if (wd_dptlp->objectName().isEmpty())
            wd_dptlp->setObjectName(QString::fromUtf8("wd_dptlp"));
        wd_dptlp->resize(400, 300);

        retranslateUi(wd_dptlp);

        QMetaObject::connectSlotsByName(wd_dptlp);
    } // setupUi

    void retranslateUi(QWidget *wd_dptlp)
    {
        wd_dptlp->setWindowTitle(QCoreApplication::translate("wd_dptlp", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wd_dptlp: public Ui_wd_dptlp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WD_DPTLP_H
