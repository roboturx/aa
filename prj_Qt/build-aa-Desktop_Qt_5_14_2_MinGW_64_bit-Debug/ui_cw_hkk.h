/********************************************************************************
** Form generated from reading UI file 'cw_hkk.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CW_HKK_H
#define UI_CW_HKK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CW_hkk
{
public:
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QPushButton *btnOK_2;
    QLabel *label;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QPushButton *btnOK;

    void setupUi(QDialog *CW_hkk)
    {
        if (CW_hkk->objectName().isEmpty())
            CW_hkk->setObjectName(QString::fromUtf8("CW_hkk"));
        CW_hkk->resize(680, 779);
        toolBox = new QToolBox(CW_hkk);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(30, 20, 611, 671));
        toolBox->setFocusPolicy(Qt::StrongFocus);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 611, 589));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnOK_2 = new QPushButton(page);
        btnOK_2->setObjectName(QString::fromUtf8("btnOK_2"));

        gridLayout->addWidget(btnOK_2, 1, 0, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(11);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        toolBox->addItem(page, QString::fromUtf8("\303\234r\303\274n Hakk\304\261nda"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 611, 589));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        btnOK = new QPushButton(page_2);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        verticalLayout->addWidget(btnOK);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        toolBox->addItem(page_2, QString::fromUtf8("Lisans Ko\305\237ullar\304\261"));

        retranslateUi(CW_hkk);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CW_hkk);
    } // setupUi

    void retranslateUi(QDialog *CW_hkk)
    {
        CW_hkk->setWindowTitle(QCoreApplication::translate("CW_hkk", "About", nullptr));
        btnOK_2->setText(QCoreApplication::translate("CW_hkk", "OK", nullptr));
        label->setText(QCoreApplication::translate("CW_hkk", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#ef2929;\">Makina \304\260kmal Uygulamas\304\261 </span><span style=\" font-weight:600; color:#ef2929;\"><br/><br/>ver. 1.0.0</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-size:12pt; font-weight:600; color:#ef2929;\">Murat BALCI (+90 505 320 22 40) </span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#ef2929;\">taraf\304\261ndan haz\304\261rlanm\304\261\305\237t\304\261r.</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#ef2929;\">T\303\274m i\305\237letim sistemlerinde</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#ef2929;\">(Linux, Windows, MacOS, Android;. FreeBSD vs.)</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#ef2929;\">\303\247al\304\261\305\237t\304\261r\304\261labilir.<"
                        "/span></p><p align=\"center\"><span style=\" font-weight:600; color:#ef2929;\"><br/>T\303\274m uygulama talepleriniz i\303\247in l\303\274tfen irtibata ge\303\247iniz</span></p><p align=\"center\"><span style=\" font-weight:600; color:#ef2929;\">roboturx@gmail.com<br/></span></p></body></html>", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("CW_hkk", "\303\234r\303\274n Hakk\304\261nda", nullptr));
        label_2->setText(QCoreApplication::translate("CW_hkk", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#d3d7cf;\">Makina \304\260kmal Uygulamas\304\261 </span></p><p align=\"center\"><span style=\" color:#d3d7cf;\"><br/></span><span style=\" font-weight:600; color:#d3d7cf;\">Bu \303\274r\303\274n GNU 3.0 Lisansl\304\261d\304\261r.</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#d3d7cf;\">Serbest\303\247e</span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-weight:600; color:#d3d7cf;\">kopyalanabilir, da\304\237\304\261t\304\261labilir, \303\247o\304\237alt\304\261labilir.</span></p><p align=\"center\"><span style=\" color:#d3d7cf;\"><br/></span></p><p align=\"center\"><span style=\" color:#d3d7cf;\">code developed by </span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-size:12pt; font-weight:600; color:#d3d7cf;\">Murat BALCI </span></p><p align=\"center\"><span style=\" font-family:'arial,sans-serif'; font-siz"
                        "e:12pt; font-weight:600; color:#d3d7cf;\">+90 505 320 22 40</span></p><p align=\"center\"><span style=\" color:#d3d7cf;\">2018-19</span></p><p align=\"center\"><span style=\" color:#0a4c24;\"><br/></span></p></body></html>", nullptr));
        btnOK->setText(QCoreApplication::translate("CW_hkk", "OK", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("CW_hkk", "Lisans Ko\305\237ullar\304\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CW_hkk: public Ui_CW_hkk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CW_HKK_H
