#include "mwkira.h"

MWkira::MWkira(QWidget *parent)
    : QMainWindow(parent)
{
    szlsm_wd = new QWidget;
    this->setCentralWidget (szlsm_wd);
    QGridLayout *szlsm_ly =new QGridLayout ;
    szlsm_wd->setLayout (szlsm_ly);

    QLabel    *s_x   = new QLabel("S Ö Z L E Ş M E ");

    QLabel *s_no     = new QLabel("Numarası :");
    QLineEdit *le_no = new QLineEdit;

    QLabel *s_trh     = new QLabel("Tarihi :");
    QLineEdit *le_trh = new QLineEdit;

    QLabel *s_krbsl  = new QLabel("Başlangıç Tarihi :");
    QLineEdit *le_krbsl = new QLineEdit;

    QLabel *s_krbts  = new QLabel("Bitiş Tarihi     :");
    QLineEdit *le_krbts = new QLineEdit;

    QLabel *s_taah   = new QLabel("Taahhüt Tarihi   :");
    QLineEdit *le_taah = new QLineEdit;

    QLabel *s_sure   = new QLabel("Süre             :");
    QLineEdit *le_sure = new QLineEdit;

    QLabel *s_bedel  = new QLabel("Bedeli           :");
    QLineEdit *le_bedel = new QLineEdit;


    szlsm_ly->addWidget (s_x      ,0,0,1,1);
    szlsm_ly->addWidget (s_no     ,1,0,1,1);
    szlsm_ly->addWidget (le_no    ,1,1,1,1);
    szlsm_ly->addWidget (s_trh    ,2,0,1,1);
    szlsm_ly->addWidget (le_trh   ,2,1,1,1);
    szlsm_ly->addWidget (s_krbsl  ,3,0,1,1);
    szlsm_ly->addWidget (le_krbsl ,3,1,1,1);
    szlsm_ly->addWidget (s_krbts  ,4,0,1,1);
    szlsm_ly->addWidget (le_krbts ,4,1,1,1);
    szlsm_ly->addWidget (s_taah   ,5,0,1,1);
    szlsm_ly->addWidget (le_taah  ,5,1,1,1);
    szlsm_ly->addWidget (s_sure   ,6,0,1,1);
    szlsm_ly->addWidget (le_sure  ,6,1,1,1);
    szlsm_ly->addWidget (s_bedel  ,7,0,1,1);
    szlsm_ly->addWidget (le_bedel ,7,1,1,1);



    szlsm_te = new QTextEdit(this);
    szlsm_te->append (QString("sdkmklsmcmslmclsmcmsşlcmşlsmcşlsmcşlsm"));

    szlsm_ly->addWidget (szlsm_te    ,0,2,7,2);


 /*
    shower = new QWidget;
    QGridLayout * layout = new QGridLayout;
    layout->addWidget(setScrollArea(upWindow), 0, 0);
    layout->addWidget(setScrollArea(downWindow), 1, 0);
    shower->setLayout(layout);
    */



}

MWkira::~MWkira()
{



}
