/********************************************************************************
** Form generated from reading UI file 'ww_mkcins.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WW_MKCINS_H
#define UI_WW_MKCINS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WW_Mkcins
{
public:
    QGridLayout *gridLayout;
    QTableView *tv_mkcins;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *WW_Mkcins)
    {
        if (WW_Mkcins->objectName().isEmpty())
            WW_Mkcins->setObjectName(QString::fromUtf8("WW_Mkcins"));
        WW_Mkcins->resize(494, 635);
        gridLayout = new QGridLayout(WW_Mkcins);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tv_mkcins = new QTableView(WW_Mkcins);
        tv_mkcins->setObjectName(QString::fromUtf8("tv_mkcins"));

        gridLayout->addWidget(tv_mkcins, 0, 0, 4, 1);

        pushButton = new QPushButton(WW_Mkcins);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        groupBox = new QGroupBox(WW_Mkcins);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        gridLayout->addWidget(groupBox, 2, 1, 1, 1);


        retranslateUi(WW_Mkcins);

        QMetaObject::connectSlotsByName(WW_Mkcins);
    } // setupUi

    void retranslateUi(QDialog *WW_Mkcins)
    {
        WW_Mkcins->setWindowTitle(QCoreApplication::translate("WW_Mkcins", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("WW_Mkcins", "Tamam", nullptr));
        groupBox->setTitle(QString());
        pushButton_2->setText(QCoreApplication::translate("WW_Mkcins", "Ekle", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WW_Mkcins", "Sil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WW_Mkcins: public Ui_WW_Mkcins {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WW_MKCINS_H
