#include "hc_hspadd.h"

hC_hspAdd::hC_hspAdd(QWidget *parent)
    : QMainWindow {parent}
{

    qDebug()<<"-----------    ::hChsp NEWWWWWW Add";

    mainwdgt = new QWidget(this);
    setCentralWidget (mainwdgt);

    yeniItem = new TaskItem;

    QGridLayout *lyt = new QGridLayout(mainwdgt);
    mainwdgt->setLayout(lyt);
    QLabel* a1 = new QLabel("Hesap Adı   : ");
    QLabel* a2 = new QLabel("Açıklama    : ");
    QLabel* a3 = new QLabel("Toplu Hesap : ");
    QLabel* a4 = new QLabel("Hesap Türü  : ");
    QLabel* a5 = new QLabel("Üst Hesap   : ");

    le_ad = new QLineEdit;
    le_acklama = new QLineEdit;
    cb_topluHesap = new QComboBox;
    cb_topluHesap->addItem ("Normal Hesap ");
    cb_topluHesap->addItem ("Toplu Hesap - Normal hesapların toplandığı hesap");



    cb_hesapTuru = new QComboBox;
    cb_ustHesap = new QComboBox;

    lyt->addWidget (a1,         3, 1, 1, 1);
    lyt->addWidget (le_ad,      3, 2, 1, 2);
    lyt->addWidget (a2,         4, 1, 1, 1);
    lyt->addWidget (le_acklama, 4, 2, 1, 2);
    lyt->addWidget (a3,         5, 1, 1, 1);
    lyt->addWidget (cb_topluHesap, 5, 2, 1, 2);
    lyt->addWidget (a4,           6, 1, 1, 1);
    lyt->addWidget (cb_hesapTuru, 6, 2, 1, 2);
    lyt->addWidget (a5,          7, 1, 1, 1);
    lyt->addWidget (cb_ustHesap, 7, 2, 1, 2);

    connect(le_ad        , &QLineEdit::editingFinished, this, &hC_hspAdd::yaz );
    connect(le_acklama   , &QLineEdit::editingFinished, this, &hC_hspAdd::yaz );
    connect(cb_topluHesap, &QComboBox::currentTextChanged, this, &hC_hspAdd::yaz );
    connect(cb_hesapTuru , &QComboBox::currentTextChanged, this, &hC_hspAdd::yaz );
    connect(cb_ustHesap  , &QComboBox::currentTextChanged, this, &hC_hspAdd::yaz );
}





hC_hspAdd::~hC_hspAdd()
{

}


void hC_hspAdd::yaz()
{

    yeniItem->setHesapAd (le_ad->text ());
    yeniItem->setHesapAcklm (le_acklama->text ());
    if (cb_topluHesap->currentIndex () == 0)
    {
        yeniItem->setTopluHesap (0);
    }
    else
    {
        yeniItem->setTopluHesap (1);
    }

    yeniItem->setHesapTuru (cb_hesapTuru->currentText ());
    yeniItem->setUstHesap (cb_ustHesap->currentText ());
    yeniItem->setDBFile ("xxx");
}





