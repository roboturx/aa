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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Arayuz
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *Arayuz)
    {
        if (Arayuz->objectName().isEmpty())
            Arayuz->setObjectName(QString::fromUtf8("Arayuz"));
        Arayuz->resize(645, 437);
        textEdit = new QTextEdit(Arayuz);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 0, 341, 70));

        retranslateUi(Arayuz);

        QMetaObject::connectSlotsByName(Arayuz);
    } // setupUi

    void retranslateUi(QWidget *Arayuz)
    {
        Arayuz->setWindowTitle(QCoreApplication::translate("Arayuz", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Arayuz", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:700; text-decoration: underline; color:#118711;\">ARAY\303\234Z</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Arayuz: public Ui_Arayuz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARAYUZ_H
