/********************************************************************************
** Form generated from reading UI file 'mn_navi.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MN_NAVI_H
#define UI_MN_NAVI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mN_navi
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *pB_ekle;
    QToolButton *pB_sil;
    QSpacerItem *horizontalSpacer;
    QToolButton *pB_ncki;
    QToolButton *p_snrki;
    QTableView *tableView;

    void setupUi(QWidget *mN_navi)
    {
        if (mN_navi->objectName().isEmpty())
            mN_navi->setObjectName(QString::fromUtf8("mN_navi"));
        mN_navi->resize(615, 482);
        mN_navi->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(26, 84, 43, 236), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        layoutWidget = new QWidget(mN_navi);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(2, 2, 190, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pB_ekle = new QToolButton(layoutWidget);
        pB_ekle->setObjectName(QString::fromUtf8("pB_ekle"));
        pB_ekle->setMouseTracking(true);
        pB_ekle->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(26, 26, 43, 255), stop:1 rgba(24, 0, 148, 255));\n"
"image: url(:/rsm/Add.ico);"));

        horizontalLayout->addWidget(pB_ekle);

        pB_sil = new QToolButton(layoutWidget);
        pB_sil->setObjectName(QString::fromUtf8("pB_sil"));
        pB_sil->setMouseTracking(true);
        pB_sil->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(26, 26, 43, 255), stop:1 rgba(24, 0, 148, 255));\n"
"image: url(:/rsm/Erase.ico);"));

        horizontalLayout->addWidget(pB_sil);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pB_ncki = new QToolButton(layoutWidget);
        pB_ncki->setObjectName(QString::fromUtf8("pB_ncki"));
        pB_ncki->setMouseTracking(true);
        pB_ncki->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(26, 26, 43, 255), stop:1 rgba(24, 0, 148, 255));\n"
"image: url(:/rsm/left.png);"));

        horizontalLayout->addWidget(pB_ncki);

        p_snrki = new QToolButton(layoutWidget);
        p_snrki->setObjectName(QString::fromUtf8("p_snrki"));
        p_snrki->setMouseTracking(true);
        p_snrki->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(26, 26, 43, 255), stop:1 rgba(24, 0, 148, 255));\n"
"image: url(:/rsm/right.png);"));

        horizontalLayout->addWidget(p_snrki);

        tableView = new QTableView(mN_navi);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(300, 160, 256, 192));
        tableView->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(26, 84, 43, 255), stop:1 rgba(24, 176, 148, 255));\n"
"\n"
""));

        retranslateUi(mN_navi);

        QMetaObject::connectSlotsByName(mN_navi);
    } // setupUi

    void retranslateUi(QWidget *mN_navi)
    {
        mN_navi->setWindowTitle(QCoreApplication::translate("mN_navi", "Form", nullptr));
        pB_ekle->setText(QString());
        pB_sil->setText(QString());
        pB_ncki->setText(QString());
        p_snrki->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mN_navi: public Ui_mN_navi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MN_NAVI_H
