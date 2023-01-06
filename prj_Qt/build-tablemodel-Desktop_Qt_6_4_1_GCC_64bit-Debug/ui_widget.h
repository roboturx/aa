/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTableView *tableView;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *submitButton;
    QLineEdit *edIsbn;
    QLineEdit *edTitle;
    QLineEdit *edEdition;
    QLineEdit *edPublisher;
    QLineEdit *edCopyright;
    QLineEdit *edAuthors;
    QSpinBox *dspinPrice;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        tableView = new QTableView(Widget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 161, 551, 111));
        addButton = new QPushButton(Widget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(120, 120, 80, 22));
        deleteButton = new QPushButton(Widget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(230, 120, 80, 22));
        submitButton = new QPushButton(Widget);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(360, 120, 80, 22));
        edIsbn = new QLineEdit(Widget);
        edIsbn->setObjectName("edIsbn");
        edIsbn->setGeometry(QRect(30, 10, 113, 21));
        edTitle = new QLineEdit(Widget);
        edTitle->setObjectName("edTitle");
        edTitle->setGeometry(QRect(30, 40, 113, 21));
        edEdition = new QLineEdit(Widget);
        edEdition->setObjectName("edEdition");
        edEdition->setGeometry(QRect(30, 70, 113, 21));
        edPublisher = new QLineEdit(Widget);
        edPublisher->setObjectName("edPublisher");
        edPublisher->setGeometry(QRect(170, 10, 113, 21));
        edCopyright = new QLineEdit(Widget);
        edCopyright->setObjectName("edCopyright");
        edCopyright->setGeometry(QRect(180, 40, 113, 21));
        edAuthors = new QLineEdit(Widget);
        edAuthors->setObjectName("edAuthors");
        edAuthors->setGeometry(QRect(320, 40, 113, 21));
        dspinPrice = new QSpinBox(Widget);
        dspinPrice->setObjectName("dspinPrice");
        dspinPrice->setGeometry(QRect(210, 70, 101, 21));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        addButton->setText(QCoreApplication::translate("Widget", "ekle", nullptr));
        deleteButton->setText(QCoreApplication::translate("Widget", "sil", nullptr));
        submitButton->setText(QCoreApplication::translate("Widget", "kaydet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
