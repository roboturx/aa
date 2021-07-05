/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
//#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QLabel *label;
    QLineEdit *txt_adsoyad;
    QLineEdit *txt_telefon;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txt_cep;
    QLabel *label_4;
    QLineEdit *txt_mail;
    QPushButton *btn_kaydet;
    QPushButton *btn_yeni;
    QPushButton *btn_sil;
    QPushButton *btn_sil_2;
    QTableView *tbl_liste;
    QLineEdit *txt_id;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *txt_ara;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(594, 508);
        MainWindow->setMinimumSize(QSize(594, 505));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(80, 80, 80, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(6, 6, 581, 497));
        widget->setStyleSheet(QLatin1String("#widget {\n"
"background-color: qlineargradient(spread:pad, x1:0.472318, y1:0.858, x2:0.444, y2:0.006, stop:0 rgba(14, 14, 14, 255), stop:1 rgba(100, 100, 100, 255));\n"
"border:1px solid rgb(107, 107, 107);\n"
"\n"
"\n"
"}"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(16, 48, 77, 29));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"padding:3px;\n"
"font: 11pt \"MS Serif\";"));
        txt_adsoyad = new QLineEdit(widget);
        txt_adsoyad->setObjectName(QStringLiteral("txt_adsoyad"));
        txt_adsoyad->setGeometry(QRect(108, 48, 449, 29));
        txt_adsoyad->setStyleSheet(QLatin1String("background-color: rgb(77, 77, 77);\n"
"border:solid;\n"
"border-width:1px;\n"
"border-color: rgb(116, 116, 116);\n"
"font: 12pt \"MS Serif\";\n"
"color: rgb(255, 255, 255);\n"
"padding:3px;"));
        txt_telefon = new QLineEdit(widget);
        txt_telefon->setObjectName(QStringLiteral("txt_telefon"));
        txt_telefon->setGeometry(QRect(108, 80, 449, 29));
        txt_telefon->setStyleSheet(QLatin1String("background-color: rgb(77, 77, 77);\n"
"border:solid;\n"
"border-width:1px;\n"
"border-color: rgb(116, 116, 116);\n"
"font: 12pt \"MS Serif\";\n"
"color: rgb(255, 255, 255);\n"
"padding:3px;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(16, 80, 77, 29));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"padding:3px;\n"
"font: 11pt \"MS Serif\";"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(16, 112, 77, 29));
        label_3->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"padding:3px;\n"
"font: 11pt \"MS Serif\";"));
        txt_cep = new QLineEdit(widget);
        txt_cep->setObjectName(QStringLiteral("txt_cep"));
        txt_cep->setGeometry(QRect(108, 112, 449, 29));
        txt_cep->setStyleSheet(QLatin1String("background-color: rgb(77, 77, 77);\n"
"border:solid;\n"
"border-width:1px;\n"
"border-color: rgb(116, 116, 116);\n"
"font: 12pt \"MS Serif\";\n"
"color: rgb(255, 255, 255);\n"
"padding:3px;"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(16, 144, 77, 29));
        label_4->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"padding:3px;\n"
"font: 11pt \"MS Serif\";"));
        txt_mail = new QLineEdit(widget);
        txt_mail->setObjectName(QStringLiteral("txt_mail"));
        txt_mail->setGeometry(QRect(108, 144, 449, 29));
        txt_mail->setStyleSheet(QLatin1String("background-color: rgb(77, 77, 77);\n"
"border:solid;\n"
"border-width:1px;\n"
"border-color: rgb(116, 116, 116);\n"
"font: 12pt \"MS Serif\";\n"
"color: rgb(255, 255, 255);\n"
"padding:3px;"));
        btn_kaydet = new QPushButton(widget);
        btn_kaydet->setObjectName(QStringLiteral("btn_kaydet"));
        btn_kaydet->setGeometry(QRect(108, 180, 93, 33));
        btn_kaydet->setCursor(QCursor(Qt::PointingHandCursor));
        btn_kaydet->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgb(16, 83, 165);\n"
"color: rgb(255, 255, 255);\n"
"border:solid;\n"
"font: 11pt \"Tahoma\";\n"
"}\n"
"QPushButton:hover {\n"
"background-color: rgb(0, 126, 244);\n"
"}"));
        btn_kaydet->setFlat(false);
        btn_yeni = new QPushButton(widget);
        btn_yeni->setObjectName(QStringLiteral("btn_yeni"));
        btn_yeni->setGeometry(QRect(200, 180, 93, 33));
        btn_yeni->setCursor(QCursor(Qt::PointingHandCursor));
        btn_yeni->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgb(0, 59, 35);\n"
"color: rgb(255, 255, 255);\n"
"border:solid;\n"
"	font: 11pt \"Tahoma\";\n"
"}\n"
"QPushButton:hover {\n"
"background-color: rgb(32, 189, 23);\n"
"}"));
        btn_yeni->setFlat(false);
        btn_sil = new QPushButton(widget);
        btn_sil->setObjectName(QStringLiteral("btn_sil"));
        btn_sil->setGeometry(QRect(292, 180, 93, 33));
        btn_sil->setCursor(QCursor(Qt::PointingHandCursor));
        btn_sil->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgb(148, 0, 2);\n"
"color: rgb(255, 255, 255);\n"
"border:solid;\n"
"font: 11pt \"Tahoma\";\n"
"}\n"
"QPushButton:hover {\n"
"background-color: rgb(255, 0, 4);\n"
"}"));
        btn_sil->setFlat(false);
        btn_sil_2 = new QPushButton(widget);
        btn_sil_2->setObjectName(QStringLiteral("btn_sil_2"));
        btn_sil_2->setGeometry(QRect(496, 180, 61, 33));
        btn_sil_2->setCursor(QCursor(Qt::PointingHandCursor));
        btn_sil_2->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgb(148, 0, 2);\n"
"color: rgb(255, 255, 255);\n"
"border:solid;\n"
"font: 11pt \"Tahoma\";\n"
"}\n"
"QPushButton:hover {\n"
"background-color: rgb(255, 0, 4);\n"
"}"));
        btn_sil_2->setFlat(false);
        tbl_liste = new QTableView(widget);
        tbl_liste->setObjectName(QStringLiteral("tbl_liste"));
        tbl_liste->setGeometry(QRect(8, 256, 565, 233));
        tbl_liste->setStyleSheet(QLatin1String("QTableView {\n"
"	background-color: rgb(79, 79, 79);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"QTableView ::section{\n"
"	background-color: rgb(79, 79, 79);\n"
"}\n"
"QTableView QHeaderView\n"
"{\n"
"background-color: rgb(79, 79, 79);\n"
"}\n"
"QTableView  QHeaderView::section:horizonta{\n"
"    height: 24px;\n"
"    border-style: none;\n"
"    border: 1px solid  rgb(147, 147, 147);\n"
"	background-color: qlineargradient(spread:pad, x1:0.472318, y1:0.858, x2:0.444, y2:0.006, stop:0 rgba(75, 75, 75, 255), stop:1 rgba(137, 137, 137, 255));\n"
"	color: rgb(255, 255, 255);\n"
" }\n"
"QTableView  QHeaderView::section:vertical{\n"
"	width:0px;\n"
"	border-style: none;\n"
" }"));
        tbl_liste->setSelectionBehavior(QAbstractItemView::SelectRows);
        txt_id = new QLineEdit(widget);
        txt_id->setObjectName(QStringLiteral("txt_id"));
        txt_id->setGeometry(QRect(16, 188, 37, 20));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(4, 4, 573, 33));
        label_5->setStyleSheet(QLatin1String("font: 75 14pt \"MS Sans Serif\";\n"
"color: rgb(152, 255, 146);\n"
"background-color: rgb(71, 71, 71);\n"
"padding:6px;\n"
"\n"
""));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(8, 224, 565, 33));
        label_6->setStyleSheet(QLatin1String("background-color: rgb(68, 68, 68);\n"
"color: rgb(255, 255, 255);\n"
"font: 11pt \"Tahoma\";\n"
"padding:3px;"));
        txt_ara = new QLineEdit(widget);
        txt_ara->setObjectName(QStringLiteral("txt_ara"));
        txt_ara->setGeometry(QRect(112, 228, 457, 25));
        txt_ara->setStyleSheet(QLatin1String("padding:3px;\n"
"background-color: qlineargradient(spread:pad, x1:0.472318, y1:0.858, x2:0.444, y2:0.006, stop:0 rgba(16, 16, 16, 255), stop:1 rgba(55, 55, 55, 255));\n"
"border:1px solid rgb(98, 98, 98);\n"
"color: rgb(255, 255, 255);"));
        label->raise();
        txt_adsoyad->raise();
        txt_telefon->raise();
        label_2->raise();
        label_3->raise();
        txt_cep->raise();
        label_4->raise();
        txt_mail->raise();
        btn_kaydet->raise();
        btn_yeni->raise();
        btn_sil->raise();
        btn_sil_2->raise();
        txt_id->raise();
        label_5->raise();
        label_6->raise();
        txt_ara->raise();
        tbl_liste->raise();
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TELEFON DEFTER\304\260", 0));
        label->setText(QApplication::translate("MainWindow", "AD SOYAD", 0));
        txt_adsoyad->setText(QString());
        txt_telefon->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "TELEFON", 0));
        label_3->setText(QApplication::translate("MainWindow", "CEP", 0));
        txt_cep->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "MA\304\260L", 0));
        txt_mail->setText(QString());
        btn_kaydet->setText(QApplication::translate("MainWindow", "KAYDET", 0));
        btn_yeni->setText(QApplication::translate("MainWindow", "YEN\304\260", 0));
        btn_sil->setText(QApplication::translate("MainWindow", "S\304\260L", 0));
        btn_sil_2->setText(QApplication::translate("MainWindow", "\303\207IKI\305\236", 0));
        label_5->setText(QApplication::translate("MainWindow", "TELEFON DEFTER\304\260 V0.1", 0));
        label_6->setText(QApplication::translate("MainWindow", "Defterde Ara", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
