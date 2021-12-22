#include "globals.h"
#include "arayuz.h"


Arayuz::Arayuz(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "mwmain.login.arayuz constructor - 1230 ";
//    dbase=new DBase;
//    dbase->setGeometry (20,30,300,480);
//    dbase->setWindowTitle("Veri Tabanı Kontrol");
//    dbase->show();
    duzenle = new Duzenle;
    kveren  = new Kveren;
    kiraci  = new Kirac;
    krlnn   = new Kiralanan;
    kr      = new Kira;
    srt     = new Sart;
    osrt    = new Osart;

    //this->adjustSize();
    auto g_lytara = new QGridLayout();

    g_lytara->setColumnStretch(0,1);
    g_lytara->setColumnStretch(1,20);
    g_lytara->setColumnStretch(2,1);
    g_lytara->setColumnStretch(3,20);
    g_lytara->setColumnStretch(4,1);
    g_lytara->setColumnStretch(5,40);
    g_lytara->setColumnStretch(6,1);


    this->setLayout(g_lytara);
    g_lytara->addWidget(duzenle, 0, 1, 1, 1);
    g_lytara->addWidget(kveren , 1, 1, 1, 1);
    g_lytara->addWidget(kiraci , 1, 3, 1, 1);
    g_lytara->addWidget(krlnn  , 2, 1, 1, 1);
    g_lytara->addWidget(kr     , 2, 3, 1, 1);

    g_lytara->addWidget(osrt   , 3, 1, 5, 3);
    g_lytara->addWidget(srt    , 0, 5, 8, 1);
}

Arayuz::~Arayuz()
{

}

// ----------------------------------- düzenleme tarih - no
Duzenle::Duzenle(QWidget *parent) :
    QWidget(parent)
{

    dE_duztar = new QDateEdit ;
    lE_duzno  = new QLineEdit ;
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("Düzenleme Tarihi :"), dE_duztar);
    formLayout->addRow(tr("Düzenleme No :"), lE_duzno);
    setLayout(formLayout);
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

    lE_kvtc = new QLineEdit ;
    lE_kvad = new QLineEdit ;
    lE_kvsyd = new QLineEdit ;
    lE_kvadres = new QLineEdit ;
    lE_kvtel = new QLineEdit ;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&TC No :"), lE_kvtc);
    formLayout->addRow(tr("&Adı :"), lE_kvad);
    formLayout->addRow(tr("&Soyadı :"), lE_kvsyd);
    formLayout->addRow(tr("A&dres :"), lE_kvadres);
    formLayout->addRow(tr("T&elefon :"), lE_kvtel);
    setLayout(formLayout);


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
    lE_krctc = new QLineEdit ;
    lE_krcad = new QLineEdit ;
    lE_krcsyd = new QLineEdit ;
    lE_krcadres = new QLineEdit ;
    lE_krctel = new QLineEdit ;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&TC No :"), lE_krctc);
    formLayout->addRow(tr("&Adı :"), lE_krcad);
    formLayout->addRow(tr("&Soyadı :"), lE_krcsyd);
    formLayout->addRow(tr("A&dres :"), lE_krcadres);
    formLayout->addRow(tr("T&elefon :"), lE_krctel);
    setLayout(formLayout);

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
    lE_krlnnadreskod = new QLineEdit ;
    lE_krlnnadres = new QLineEdit ;
    lE_krlnnada = new QLineEdit ;
    lE_krlnnpafta = new QLineEdit ;
    lE_krlnnparsel = new QLineEdit ;
    lE_krlnnsu = new QLineEdit ;
    lE_krlnnelktrk = new QLineEdit ;
    lE_krlnndgaz = new QLineEdit ;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Adres Kodu :")  , lE_krlnnadreskod );
    formLayout->addRow(tr("Adres :")    , lE_krlnnadres );
    formLayout->addRow(tr("Tapu Pafta :") ,  lE_krlnnada );
    formLayout->addRow(tr("       Ada :")  , lE_krlnnpafta );
    formLayout->addRow(tr("    Parsel :"), lE_krlnnparsel );
    formLayout->addRow(tr("Abone Elektrik :"), lE_krlnnsu );
    formLayout->addRow(tr("            Su :"), lE_krlnnelktrk );
    formLayout->addRow(tr("      Doğalgaz :"), lE_krlnndgaz );
    setLayout(formLayout);
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
    lE_krbastar = new QLineEdit ;
    lE_krbittar = new QLineEdit ;
    lE_krsure = new QLineEdit ;
    lE_krbedel = new QLineEdit ;
    lE_krteminat = new QLineEdit ;
    lE_krodeme = new QLineEdit ;
    lE_krodyeri = new QLineEdit ;


    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("Başlangıç Tarihi :")  , lE_krbastar );
    formLayout->addRow(tr("Bitiş Tarihi:")    , lE_krbittar );
    formLayout->addRow(tr("Süresi:") ,  lE_krsure );
    formLayout->addRow(tr("Bedeli:")  , lE_krbedel );
    formLayout->addRow(tr("Teminat:"), lE_krteminat );
    formLayout->addRow(tr("Ödeme Şekli:"), lE_krodeme );
    formLayout->addRow(tr("Banka Hesap No:"), lE_krodyeri );

    setLayout(formLayout);
}

Kira::~Kira()
{

}

Sart::Sart(QWidget *parent) :
    QWidget(parent)
{
    tE_sart = new QTextEdit;
    QLabel *x = new QLabel;


    QVBoxLayout *vertLayout = new QVBoxLayout;
    vertLayout->addWidget(x );
    vertLayout->addWidget(tE_sart );

    setLayout(vertLayout);
}

Sart::~Sart()
{

}

Osart::Osart(QWidget *parent) :
    QWidget(parent)
{
    tE_osart = new QTextEdit;
    QLabel *x = new QLabel;


    QVBoxLayout *vertLayout = new QVBoxLayout;
    vertLayout->addWidget(x);
    vertLayout->addWidget(tE_osart );

    setLayout(vertLayout);
}

Osart::~Osart()
{

}


