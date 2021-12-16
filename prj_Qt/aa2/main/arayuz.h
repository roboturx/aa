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
    QLabel lB_tc;
    QLineEdit lE_tc;
    QLabel lB_ad;
    QLineEdit lE_ad;
    QLabel lB_syd;
    QLineEdit lE_syd;
    QLabel lB_adres;
    QLineEdit lE_adres;
    QLabel lB_tel;
    QLineEdit lE_tel;

};

//----------------------------------------------  kirac
class Kirac : public QWidget
{
    Q_OBJECT

public:
    explicit Kirac(QWidget *parent = nullptr);
    ~Kirac();


private:

};



//----------------------------------------------  kiralanan
class Kiralanan : public QWidget
{
    Q_OBJECT

public:
    explicit Kiralanan(QWidget *parent = nullptr);
    ~Kiralanan();


private:

};

//---------------------------------------------- kira
class Kira : public QWidget
{
    Q_OBJECT

public:
    explicit Kira(QWidget *parent = nullptr);
    ~Kira();


private:

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

};


#endif // ARAYUZ_H

