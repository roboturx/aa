#ifndef MWKIRA_H
#define MWKIRA_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTextEdit>


class MWkira : public QMainWindow
{
    Q_OBJECT

public:
    MWkira(QWidget *parent = 0);
    ~MWkira();

    QTextEdit *szlsm_te;
    QWidget *szlsm_wd;




};
class kiraci
{
    QString krc_ad;
    QString krc_soyad;
    QString krc_tc;
    QString krc_telefon;
    QString krc_ceptel;
    QString krc_adres;
    QString krc_kefil;

};
class kiralayan
{
    QString krlyn_ad;
    QString krlyn_soyad;
    QString krlyn_tc;

};
class mecur
{
private:
    QString *mcr_ad;
    QString *mcr_adres;
    QString *mcr_ada;
    QString *mcr_parsel;
    QString *mcr_elk;
    QString *mcr_su;
    QString *mcr_gaz;
public:


};

class szlsm : public kiraci, public kiralayan , public mecur
{
    QString szlsm_no;
    QString szlsm_sahit;
    QDate szlsm_trh;
    QDate szlsm_trh_krbslngc;
    QDate szlsm_trh_krbts;
    QDate szlsm_trh_taah;
    int szlsm_sure;
    float szlsm_bedeli;
    QTextEdit szlsm_madde_01;
    QTextEdit szlsm_madde_02;
    QTextEdit szlsm_madde_03;
    QTextEdit szlsm_madde_04;
    QTextEdit szlsm_madde_05;
    QTextEdit szlsm_madde_06;
    QTextEdit szlsm_madde_07;
    QTextEdit szlsm_madde_08;
    QTextEdit szlsm_madde_09;
    QTextEdit szlsm_madde_10;
    QTextEdit szlsm_madde_11;
    QTextEdit szlsm_madde_12;
    QTextEdit szlsm_madde_13;
    QTextEdit szlsm_madde_14;
    QTextEdit szlsm_madde_15;
    QTextEdit szlsm_madde_16;

};

#endif // MWKIRA_H
