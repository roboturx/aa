/********************************************************************************
** Form generated from reading UI file 'wd_login.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WD_LOGIN_H
#define UI_WD_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WD_login
{
public:
    QGroupBox *groupBoxLogin;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QGridLayout *gridLayout_3;
    QTextEdit *durum;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_login;
    QLineEdit *lineedit_username;
    QLineEdit *lineedit_password;
    QPushButton *pushButton_login_2;
    QGridLayout *gridLayout;
    QLabel *lbl_bayrak;

    void setupUi(QDialog *WD_login)
    {
        if (WD_login->objectName().isEmpty())
            WD_login->setObjectName(QString::fromUtf8("WD_login"));
        WD_login->resize(825, 692);
        groupBoxLogin = new QGroupBox(WD_login);
        groupBoxLogin->setObjectName(QString::fromUtf8("groupBoxLogin"));
        groupBoxLogin->setGeometry(QRect(51, 11, 414, 443));
        groupBoxLogin->setStyleSheet(QString::fromUtf8("<b>color:red<b>"));
        verticalLayout_2 = new QVBoxLayout(groupBoxLogin);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(groupBoxLogin);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/rsm/logo.png")));
        label_4->setScaledContents(true);

        verticalLayout_2->addWidget(label_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        durum = new QTextEdit(groupBoxLogin);
        durum->setObjectName(QString::fromUtf8("durum"));

        gridLayout_3->addWidget(durum, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBoxLogin);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(groupBoxLogin);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(196, 160, 0);\n"
"font: 10pt \"DejaVu Sans\";"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        pushButton_login = new QPushButton(groupBoxLogin);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setMinimumSize(QSize(80, 0));
        pushButton_login->setMaximumSize(QSize(100, 100));
        pushButton_login->setStyleSheet(QString::fromUtf8("font: 75 oblique 14pt \"DejaVu Sans Mono\";\n"
"color: rgb(204, 255, 0);\n"
"image: url(:/rsm/tkt.png);"));
        pushButton_login->setAutoDefault(true);
        pushButton_login->setFlat(true);

        gridLayout_2->addWidget(pushButton_login, 1, 2, 2, 1);

        lineedit_username = new QLineEdit(groupBoxLogin);
        lineedit_username->setObjectName(QString::fromUtf8("lineedit_username"));
        lineedit_username->setDragEnabled(false);

        gridLayout_2->addWidget(lineedit_username, 1, 1, 1, 1);

        lineedit_password = new QLineEdit(groupBoxLogin);
        lineedit_password->setObjectName(QString::fromUtf8("lineedit_password"));
        lineedit_password->setFocusPolicy(Qt::StrongFocus);
        lineedit_password->setEchoMode(QLineEdit::Password);
        lineedit_password->setDragEnabled(false);

        gridLayout_2->addWidget(lineedit_password, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        pushButton_login_2 = new QPushButton(groupBoxLogin);
        pushButton_login_2->setObjectName(QString::fromUtf8("pushButton_login_2"));
        pushButton_login_2->setMinimumSize(QSize(80, 0));
        pushButton_login_2->setMaximumSize(QSize(400, 35));
        pushButton_login_2->setStyleSheet(QString::fromUtf8("font: 75 oblique 14pt \"DejaVu Sans Mono\";\n"
"color: rgb(204, 255, 0);\n"
"image: url(:/rsm/tkt.png);"));
        pushButton_login_2->setAutoDefault(false);
        pushButton_login_2->setFlat(true);

        verticalLayout_2->addWidget(pushButton_login_2);

        gridLayout = new QGridLayout(WD_login);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbl_bayrak = new QLabel(WD_login);
        lbl_bayrak->setObjectName(QString::fromUtf8("lbl_bayrak"));
        lbl_bayrak->setPixmap(QPixmap(QString::fromUtf8(":/rsm/trb.gif")));
        lbl_bayrak->setScaledContents(true);

        gridLayout->addWidget(lbl_bayrak, 0, 0, 1, 1);

        lbl_bayrak->raise();
        groupBoxLogin->raise();
#if QT_CONFIG(shortcut)
        label_2->setBuddy(lineedit_username);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(pushButton_login, durum);
        QWidget::setTabOrder(durum, pushButton_login_2);

        retranslateUi(WD_login);

        pushButton_login->setDefault(true);
        pushButton_login_2->setDefault(false);


        QMetaObject::connectSlotsByName(WD_login);
    } // setupUi

    void retranslateUi(QDialog *WD_login)
    {
        WD_login->setWindowTitle(QCoreApplication::translate("WD_login", "Dialog", nullptr));
        groupBoxLogin->setTitle(QCoreApplication::translate("WD_login", "Kullan\304\261c\304\261 Giri\305\237 Ekran\304\261", nullptr));
        label_4->setText(QString());
        label_2->setText(QCoreApplication::translate("WD_login", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#c4a000;\">\305\236ifre</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("WD_login", "<html><head/><body><p><span style=\" font-weight:600; color:#c4a000;\">Kullan\304\261c\304\261 Ad\304\261</span></p></body></html>", nullptr));
        pushButton_login->setText(QCoreApplication::translate("WD_login", "Giri\305\237", nullptr));
        pushButton_login_2->setText(QCoreApplication::translate("WD_login", "Programdan \303\207\304\261k", nullptr));
        lbl_bayrak->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WD_login: public Ui_WD_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WD_LOGIN_H
