/********************************************************************************
** Form generated from reading UI file 'ww_makina.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WW_MAKINA_H
#define UI_WW_MAKINA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WW_Makina
{
public:
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_4;
    QTableView *Table_DBTB_MKSTOK;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_kurumno;
    QLineEdit *ledit_ioi;
    QGridLayout *gridLayout_3;
    QLabel *lbl_cins;
    QToolButton *tbtn_cins;
    QComboBox *ledit_cins;
    QGridLayout *gridLayout_2;
    QLabel *lbl_marka;
    QToolButton *tbtn_mark;
    QComboBox *ledit_marka;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_plaka;
    QLineEdit *ledit_plaka;
    QGridLayout *gridLayout;
    QLabel *lbl_model;
    QToolButton *tbtn_modl;
    QComboBox *ledit_model;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *lbl_yil;
    QSpinBox *ledit_yil;
    QVBoxLayout *verticalLayout_7;
    QLabel *lbl_sase;
    QLineEdit *ledit_sase;
    QVBoxLayout *verticalLayout_9;
    QLabel *lbl_byer;
    QLineEdit *ledit_byer;
    QVBoxLayout *verticalLayout_8;
    QLabel *lbl_motor;
    QLineEdit *ledit_motor;
    QVBoxLayout *verticalLayout_10;
    QSpinBox *ledit_rating;
    QVBoxLayout *verticalLayout_11;
    QLabel *lbl_motor_2;
    QTextEdit *textEdit;
    QLabel *lbl_foto;
    QGroupBox *groupBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTableView *Table_DBTB_MKMODL;
    QTableView *Table_DBTB_MKMARK;

    void setupUi(QWidget *WW_Makina)
    {
        if (WW_Makina->objectName().isEmpty())
            WW_Makina->setObjectName(QString::fromUtf8("WW_Makina"));
        WW_Makina->resize(1146, 759);
        gridLayout_6 = new QGridLayout(WW_Makina);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox = new QGroupBox(WW_Makina);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        Table_DBTB_MKSTOK = new QTableView(groupBox);
        Table_DBTB_MKSTOK->setObjectName(QString::fromUtf8("Table_DBTB_MKSTOK"));
        Table_DBTB_MKSTOK->setFrameShape(QFrame::Box);
        Table_DBTB_MKSTOK->setFrameShadow(QFrame::Raised);
        Table_DBTB_MKSTOK->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        Table_DBTB_MKSTOK->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        Table_DBTB_MKSTOK->setDragEnabled(true);
        Table_DBTB_MKSTOK->setDragDropMode(QAbstractItemView::DragDrop);
        Table_DBTB_MKSTOK->setAlternatingRowColors(true);
        Table_DBTB_MKSTOK->setSelectionMode(QAbstractItemView::NoSelection);
        Table_DBTB_MKSTOK->setSelectionBehavior(QAbstractItemView::SelectColumns);
        Table_DBTB_MKSTOK->setIconSize(QSize(10, 10));
        Table_DBTB_MKSTOK->setSortingEnabled(true);

        verticalLayout_4->addWidget(Table_DBTB_MKSTOK);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbl_kurumno = new QLabel(groupBox_2);
        lbl_kurumno->setObjectName(QString::fromUtf8("lbl_kurumno"));

        verticalLayout->addWidget(lbl_kurumno);

        ledit_ioi = new QLineEdit(groupBox_2);
        ledit_ioi->setObjectName(QString::fromUtf8("ledit_ioi"));
        ledit_ioi->setEnabled(true);

        verticalLayout->addWidget(ledit_ioi);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lbl_cins = new QLabel(groupBox_2);
        lbl_cins->setObjectName(QString::fromUtf8("lbl_cins"));

        gridLayout_3->addWidget(lbl_cins, 0, 0, 1, 1);

        tbtn_cins = new QToolButton(groupBox_2);
        tbtn_cins->setObjectName(QString::fromUtf8("tbtn_cins"));

        gridLayout_3->addWidget(tbtn_cins, 0, 1, 1, 1);

        ledit_cins = new QComboBox(groupBox_2);
        ledit_cins->setObjectName(QString::fromUtf8("ledit_cins"));
        ledit_cins->setEnabled(true);

        gridLayout_3->addWidget(ledit_cins, 1, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_3, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lbl_marka = new QLabel(groupBox_2);
        lbl_marka->setObjectName(QString::fromUtf8("lbl_marka"));

        gridLayout_2->addWidget(lbl_marka, 0, 0, 1, 1);

        tbtn_mark = new QToolButton(groupBox_2);
        tbtn_mark->setObjectName(QString::fromUtf8("tbtn_mark"));

        gridLayout_2->addWidget(tbtn_mark, 0, 1, 1, 1);

        ledit_marka = new QComboBox(groupBox_2);
        ledit_marka->setObjectName(QString::fromUtf8("ledit_marka"));
        ledit_marka->setEnabled(true);

        gridLayout_2->addWidget(ledit_marka, 1, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_2, 0, 2, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lbl_plaka = new QLabel(groupBox_2);
        lbl_plaka->setObjectName(QString::fromUtf8("lbl_plaka"));

        verticalLayout_2->addWidget(lbl_plaka);

        ledit_plaka = new QLineEdit(groupBox_2);
        ledit_plaka->setObjectName(QString::fromUtf8("ledit_plaka"));
        ledit_plaka->setEnabled(true);

        verticalLayout_2->addWidget(ledit_plaka);


        gridLayout_4->addLayout(verticalLayout_2, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbl_model = new QLabel(groupBox_2);
        lbl_model->setObjectName(QString::fromUtf8("lbl_model"));

        gridLayout->addWidget(lbl_model, 0, 0, 1, 1);

        tbtn_modl = new QToolButton(groupBox_2);
        tbtn_modl->setObjectName(QString::fromUtf8("tbtn_modl"));
        tbtn_modl->setAutoFillBackground(true);

        gridLayout->addWidget(tbtn_modl, 0, 1, 1, 1);

        ledit_model = new QComboBox(groupBox_2);
        ledit_model->setObjectName(QString::fromUtf8("ledit_model"));
        ledit_model->setEnabled(true);

        gridLayout->addWidget(ledit_model, 1, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        lbl_yil = new QLabel(groupBox_2);
        lbl_yil->setObjectName(QString::fromUtf8("lbl_yil"));

        verticalLayout_6->addWidget(lbl_yil);

        ledit_yil = new QSpinBox(groupBox_2);
        ledit_yil->setObjectName(QString::fromUtf8("ledit_yil"));
        ledit_yil->setEnabled(true);
        ledit_yil->setMinimum(-1000);
        ledit_yil->setMaximum(2100);

        verticalLayout_6->addWidget(ledit_yil);


        gridLayout_4->addLayout(verticalLayout_6, 1, 3, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lbl_sase = new QLabel(groupBox_2);
        lbl_sase->setObjectName(QString::fromUtf8("lbl_sase"));

        verticalLayout_7->addWidget(lbl_sase);

        ledit_sase = new QLineEdit(groupBox_2);
        ledit_sase->setObjectName(QString::fromUtf8("ledit_sase"));
        ledit_sase->setEnabled(true);

        verticalLayout_7->addWidget(ledit_sase);


        gridLayout_4->addLayout(verticalLayout_7, 2, 0, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        lbl_byer = new QLabel(groupBox_2);
        lbl_byer->setObjectName(QString::fromUtf8("lbl_byer"));

        verticalLayout_9->addWidget(lbl_byer);

        ledit_byer = new QLineEdit(groupBox_2);
        ledit_byer->setObjectName(QString::fromUtf8("ledit_byer"));
        ledit_byer->setEnabled(true);

        verticalLayout_9->addWidget(ledit_byer);


        gridLayout_4->addLayout(verticalLayout_9, 2, 1, 1, 3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        lbl_motor = new QLabel(groupBox_2);
        lbl_motor->setObjectName(QString::fromUtf8("lbl_motor"));

        verticalLayout_8->addWidget(lbl_motor);

        ledit_motor = new QLineEdit(groupBox_2);
        ledit_motor->setObjectName(QString::fromUtf8("ledit_motor"));
        ledit_motor->setEnabled(true);

        verticalLayout_8->addWidget(ledit_motor);


        gridLayout_4->addLayout(verticalLayout_8, 3, 0, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        ledit_rating = new QSpinBox(groupBox_2);
        ledit_rating->setObjectName(QString::fromUtf8("ledit_rating"));
        ledit_rating->setMaximum(5);

        verticalLayout_10->addWidget(ledit_rating);


        gridLayout_4->addLayout(verticalLayout_10, 3, 1, 1, 2);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        lbl_motor_2 = new QLabel(groupBox_2);
        lbl_motor_2->setObjectName(QString::fromUtf8("lbl_motor_2"));

        verticalLayout_11->addWidget(lbl_motor_2);

        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_11->addWidget(textEdit);


        gridLayout_4->addLayout(verticalLayout_11, 4, 0, 1, 4);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_4);

        lbl_foto = new QLabel(groupBox_2);
        lbl_foto->setObjectName(QString::fromUtf8("lbl_foto"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(200);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl_foto->sizePolicy().hasHeightForWidth());
        lbl_foto->setSizePolicy(sizePolicy);
        lbl_foto->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, lbl_foto);


        horizontalLayout->addLayout(formLayout);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 40, 93, 27));
        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 80, 93, 27));
        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 120, 93, 27));
        Table_DBTB_MKMODL = new QTableView(groupBox_3);
        Table_DBTB_MKMODL->setObjectName(QString::fromUtf8("Table_DBTB_MKMODL"));
        Table_DBTB_MKMODL->setGeometry(QRect(10, 180, 256, 137));
        Table_DBTB_MKMARK = new QTableView(groupBox_3);
        Table_DBTB_MKMARK->setObjectName(QString::fromUtf8("Table_DBTB_MKMARK"));
        Table_DBTB_MKMARK->setGeometry(QRect(10, 320, 256, 137));

        horizontalLayout->addWidget(groupBox_3);


        verticalLayout_4->addWidget(groupBox_2);


        gridLayout_5->addLayout(verticalLayout_4, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        lbl_kurumno->setBuddy(ledit_ioi);
        lbl_cins->setBuddy(ledit_cins);
        lbl_marka->setBuddy(ledit_marka);
        lbl_plaka->setBuddy(ledit_plaka);
        lbl_model->setBuddy(ledit_model);
        lbl_yil->setBuddy(ledit_yil);
        lbl_sase->setBuddy(ledit_sase);
        lbl_byer->setBuddy(ledit_byer);
        lbl_motor->setBuddy(ledit_motor);
        lbl_motor_2->setBuddy(ledit_motor);
#endif // QT_CONFIG(shortcut)

        retranslateUi(WW_Makina);

        QMetaObject::connectSlotsByName(WW_Makina);
    } // setupUi

    void retranslateUi(QWidget *WW_Makina)
    {
        WW_Makina->setWindowTitle(QCoreApplication::translate("WW_Makina", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WW_Makina", "Makina Stok", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WW_Makina", "Detaylar", nullptr));
        lbl_kurumno->setText(QCoreApplication::translate("WW_Makina", "<b>KURUM NO :</b>", nullptr));
        lbl_cins->setText(QCoreApplication::translate("WW_Makina", "<b>C\304\260NS\304\260 :</b>", nullptr));
        tbtn_cins->setText(QCoreApplication::translate("WW_Makina", "...", nullptr));
        lbl_marka->setText(QCoreApplication::translate("WW_Makina", "<b>MARKA : </b>", nullptr));
        tbtn_mark->setText(QCoreApplication::translate("WW_Makina", "...", nullptr));
        lbl_plaka->setText(QCoreApplication::translate("WW_Makina", "<b>PLAKA :</b>", nullptr));
        lbl_model->setText(QCoreApplication::translate("WW_Makina", "<b>MODEL\304\260 : </b>", nullptr));
        tbtn_modl->setText(QCoreApplication::translate("WW_Makina", "...", nullptr));
        lbl_yil->setText(QCoreApplication::translate("WW_Makina", "<b>YILI:</b>", nullptr));
        ledit_yil->setPrefix(QString());
        lbl_sase->setText(QCoreApplication::translate("WW_Makina", "<b>\305\236ASE NO :</b>", nullptr));
        lbl_byer->setText(QCoreApplication::translate("WW_Makina", "<b>BULUNDU\304\236U YER :</b>", nullptr));
        lbl_motor->setText(QCoreApplication::translate("WW_Makina", "<b>MOTOR NO :</b>", nullptr));
        lbl_motor_2->setText(QCoreApplication::translate("WW_Makina", "<b>A\303\207IKLAMA :</b>", nullptr));
        lbl_foto->setText(QCoreApplication::translate("WW_Makina", "lbl_foto", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WW_Makina", "GroupBox", nullptr));
        pushButton->setText(QCoreApplication::translate("WW_Makina", "Ekle", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WW_Makina", "Sil", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WW_Makina", "Resim", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WW_Makina: public Ui_WW_Makina {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WW_MAKINA_H
