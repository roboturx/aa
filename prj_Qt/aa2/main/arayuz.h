#ifndef ARAYUZ_H
#define ARAYUZ_H

#include "globals.h"
#include "dbase.h"
namespace ns_arayuz {
class Arayuz;
class Duzenle;
class Kveren;
class Kirac;
class Kiralanan;
class Kira;
class Sart;
class Osart;
}


//----------------------------------------------  duzenle
class Duzenle : public QWidget
{
    Q_OBJECT

public:
    explicit Duzenle(QWidget *parent = nullptr);
    ~Duzenle();


private:
    //QLabel lB_dtar;
    QDateEdit *dE_duztar;
    QLineEdit *lE_duzno;
};

//----------------------------------------------  kveren
class Kveren : public QWidget
{
    Q_OBJECT

public:
    explicit Kveren(QWidget *parent = nullptr);
    ~Kveren();


private:
    QLineEdit *lE_kvtc;
    QLineEdit *lE_kvad;
    QLineEdit *lE_kvsyd;
    QLineEdit *lE_kvadres;
    QLineEdit *lE_kvtel;
};

//----------------------------------------------  kirac
class Kirac : public QWidget
{
    Q_OBJECT

public:
    explicit Kirac(QWidget *parent = nullptr);
    ~Kirac();


private:
    QLineEdit *lE_krctc;
    QLineEdit *lE_krcad;
    QLineEdit *lE_krcsyd;
    QLineEdit *lE_krcadres;
    QLineEdit *lE_krctel;
};



//----------------------------------------------  kiralanan
class Kiralanan : public QWidget
{
    Q_OBJECT

public:
    explicit Kiralanan(QWidget *parent = nullptr);
    ~Kiralanan();


private:
    QLineEdit *lE_krlnnadreskod;
    QLineEdit *lE_krlnnadres;
    QLineEdit *lE_krlnnada;
    QLineEdit *lE_krlnnpafta;
    QLineEdit *lE_krlnnparsel;
    QLineEdit *lE_krlnnsu;
    QLineEdit *lE_krlnnelktrk;
    QLineEdit *lE_krlnndgaz;
};

//---------------------------------------------- kira
class Kira : public QWidget
{
    Q_OBJECT

public:
    explicit Kira(QWidget *parent = nullptr);
    ~Kira();


private:
    QLineEdit *lE_krbastar ;
    QLineEdit *lE_krbittar ;
    QLineEdit *lE_krsure ;
    QLineEdit *lE_krbedel ;
    QLineEdit *lE_krteminat ;
    QLineEdit *lE_krodeme ;
    QLineEdit *lE_krodyeri ;
};

//---------------------------------------------- kira genel maddeleri
class Sart : public QWidget
{
    Q_OBJECT

public:
    explicit Sart(QWidget *parent = nullptr);
    ~Sart();
private:
    QTextEdit *tE_sart ;
};



//---------------------------------------------- kira özel maddeleri
class Osart : public QWidget
{
    Q_OBJECT

public:
    explicit Osart(QWidget *parent = nullptr);
    ~Osart();
private:
    QTextEdit *tE_osart ;
};




//---------------------------------------------- arayuz
class Arayuz : public QWidget
{
    Q_OBJECT

public:
    explicit Arayuz(QWidget *parent = nullptr);
    ~Arayuz();


private:
    Duzenle *duzenle;
    Kveren *kveren;
    Kirac *kiraci;
    Kiralanan *krlnn;
    Kira *kr;
    Sart *srt;
    Osart *osrt;
};


#endif // ARAYUZ_H

