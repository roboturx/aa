#include "globals.h"
#include "arayuz.h"


Arayuz::Arayuz(QWidget *parent) :
    QWidget(parent)
{

//    dbase=new DBase;
//    dbase->setGeometry (20,30,300,480);
//    dbase->setWindowTitle("Veri Tabanı Kontrol");
//    dbase->show();
    duzenle = new Duzenle;

    //this->adjustSize();
    auto g_lytara = new QGridLayout();
    this->setLayout(g_lytara);
    g_lytara->addWidget(duzenle, 0, 0, 1, 1);

}

Arayuz::~Arayuz()
{

}

// ----------------------------------- düzenleme tarih - no
Duzenle::Duzenle(QWidget *parent) :
    QWidget(parent)
{
    auto *x1 = new QHBoxLayout ;
    auto *lB_duztar = new QLabel("Sözleşmenin Düzenleme &Tarihi",this) ;
    dE_duztar = new QDateEdit(this);
    lB_duztar->setBuddy(dE_duztar);
    x1->addWidget(lB_duztar);
    x1->addWidget(dE_duztar);


    auto *x2 = new QHBoxLayout ;
    auto *lB_duzno = new QLabel("Düzenleme &No",this) ;
    lE_duzno = new QLineEdit(this);
    lB_duzno->setBuddy(lE_duzno);
    x2->addWidget(lB_duzno);
    x2->addWidget(lE_duzno);

   // this->adjustSize();
    auto g_lytduz = new QGridLayout;
    this->setLayout(g_lytduz);

    g_lytduz->setColumnMinimumWidth(0,20);
    g_lytduz->setColumnStretch(0,0);
    g_lytduz->setColumnMinimumWidth(1,100);
    g_lytduz->setColumnStretch(1,0);
    g_lytduz->setColumnMinimumWidth(2,20);
    g_lytduz->setColumnStretch(2,0);
    g_lytduz->setColumnMinimumWidth(3,100);
    g_lytduz->setColumnStretch(3,0);
    g_lytduz->setColumnMinimumWidth(4,100);
    g_lytduz->setColumnStretch(4,0);


    g_lytduz->addLayout(x1, 0, 0, 1, 1);
    //g_lytduz->addWidget(dE_duztar, 0, 4, 1, 2);
    g_lytduz->addLayout(x2, 0, 2, 1, 1);
    //g_lytduz->addWidget(lE_duzno,  0, 8, 1, 2);



}

Duzenle::~Duzenle()
{

}


/// ----------------------------------- kiraya veren
/// kiraya veren
///
/// tc
/// ad soyad
/// adres
/// telefon
///
Kveren::Kveren(QWidget *parent) :
    QWidget(parent)
{

}

Kveren::~Kveren()
{

}


/// ----------------------------------- kiracı
/// kiracı
///
/// tc
/// ad soyad
/// adres
/// telefon
///

Kirac::Kirac(QWidget *parent) :
    QWidget(parent)
{

}

Kirac::~Kirac()
{

}


/// ----------------------------------- mecur
/// kiralanan yer
///
/// adres kodu
/// adres
/// tapu pafta ada parsel
/// abone su elektrik doğalgaz
///


// -----------------------------------
Kiralanan::Kiralanan(QWidget *parent) :
    QWidget(parent)
{

}

Kiralanan::~Kiralanan()
{

}


/// -----------------------------------  kira
/// kiranın
///
/// başlangıç tarihi
/// bitiş tarihi
/// süresi
/// bedeli
/// teminat bedeli
/// ödeme şekli
/// ödeme yeri
///
Kira::Kira(QWidget *parent) :
    QWidget(parent)
{

}

Kira::~Kira()
{

}


