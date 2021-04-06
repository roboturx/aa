/********************************************************************************
** Form generated from reading UI file 'SectionContentListWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECTIONCONTENTLISTWIDGET_H
#define UI_SECTIONCONTENTLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SectionContentListWidgetForm
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *deleteButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SectionContentListWidgetForm)
    {
        if (SectionContentListWidgetForm->objectName().isEmpty())
            SectionContentListWidgetForm->setObjectName(QString::fromUtf8("SectionContentListWidgetForm"));
        SectionContentListWidgetForm->resize(522, 258);
        horizontalLayout = new QHBoxLayout(SectionContentListWidgetForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(SectionContentListWidgetForm);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        deleteButton = new QPushButton(SectionContentListWidgetForm);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        verticalLayout->addWidget(deleteButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(SectionContentListWidgetForm);

        QMetaObject::connectSlotsByName(SectionContentListWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *SectionContentListWidgetForm)
    {
        SectionContentListWidgetForm->setWindowTitle(QCoreApplication::translate("SectionContentListWidgetForm", "Form", nullptr));
        deleteButton->setText(QCoreApplication::translate("SectionContentListWidgetForm", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SectionContentListWidgetForm: public Ui_SectionContentListWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTIONCONTENTLISTWIDGET_H
