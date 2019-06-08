#include "ftr_frmekle.h"
//#include "cw_fr.h"

Ftr_FrmEkle::Ftr_FrmEkle(QDialog *parent) : QDialog(parent)
{

    auto layout_diafr = new QGridLayout(this);
    this->setLayout (layout_diafr);
    // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
    this->setGeometry (100,220,800,500);

    this->setWhatsThis ("<br>"
                         "<br> Lütfen Girişi yapılan fatura bilgilerine "
                         "<br> Firma ünvanı girmek için seçim yapın "
                         "<br> "
                         "<br> Eğer aradığınız firma listede yoksa yeni  "
                         "<br> firma girişi yaparak işlemi tamamlayın"
                         "<br>");
    this->setToolTipDuration (5000);
    this->setToolTip ("<br>"
                       "<br> Lütfen Girişi yapılan fatura bilgilerine "
                       "<br> Firma ünvanı girmek için seçim yapın "
                       "<br> "
                       "<br> Eğer aradığınız firma listede yoksa yeni  "
                       "<br> firma girişi yaparak işlemi tamamlayın"
                       "<br>");


    // firma class ımızı getirelim
    firma = new Cw_fr;
    firma->setup_firma ();
    layout_diafr->addWidget (firma ,0 ,0 ,1, 1);
    //diafr->show();


    /////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------------
    // firma tableviewinde gezinirken firma adımız
    // seçim yapılan lineedit e aktaralım
    // ----------------------------------------------------
    connect (firma->FRMselectionMdlxxx,
             &QItemSelectionModel::currentChanged  ,
             [ this ] (QModelIndex Index )

    {

        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
        int fr_row = Index.row ();
        this->setFirma (firma->FRMmodel->data(
                            firma->FRMmodel->index
                            (fr_row,firma->FRMmodel->fieldIndex ("frm_unvan"))
                            ).toString () )  ;

    });

    this->show ();
}

void Ftr_FrmEkle::reject()
{
    qDebug()<<"rejected";

        QDialog::reject();
}


Ftr_FrmEkle::~Ftr_FrmEkle()
{
}

QString Ftr_FrmEkle::getFirma() const
{
        qDebug()<<"return from getfirma"<<m_firma;
    return m_firma;
}

void Ftr_FrmEkle::setFirma(const QString &value)
{
    m_firma = value;
}


// Fatura Detaya malzeme ekle
/// FtrDet_MlzEkle


FtrDet_MlzEkle::FtrDet_MlzEkle(QDialog *parent) : QDialog(parent)
{

    auto layout_diafr = new QGridLayout(this);
    this->setLayout (layout_diafr);
    // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
    this->setGeometry (100,220,800,500);

    this->setWhatsThis ("<br>"
                         "<br> Lütfen Girişi yapılan fatura bilgilerine "
                         "<br> Firma ünvanı girmek için seçim yapın "
                         "<br> "
                         "<br> Eğer aradığınız firma listede yoksa yeni  "
                         "<br> firma girişi yaparak işlemi tamamlayın"
                         "<br>");
    this->setToolTipDuration (5000);
    this->setToolTip ("<br>"
                       "<br> Lütfen Girişi yapılan fatura bilgilerine "
                       "<br> Firma ünvanı girmek için seçim yapın "
                       "<br> "
                       "<br> Eğer aradığınız firma listede yoksa yeni  "
                       "<br> firma girişi yaparak işlemi tamamlayın"
                       "<br>");


    // firma class ımızı getirelim
    malzeme = new Cw_Mlzm ;
    malzeme->setup_mlzm ();
    layout_diafr->addWidget (malzeme ,0 ,0 ,1, 1);
    //diafr->show();


    /////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------------
    // firma tableviewinde gezinirken firma adımız
    // seçim yapılan lineedit e aktaralım
    // ----------------------------------------------------
    connect (malzeme->MLZMselectionMdl,
             &QItemSelectionModel::currentChanged  ,
             [ this ] (QModelIndex Index )

    {

        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
        int fr_row = Index.row ();
        this->setMalzeme (malzeme->MLZMmodel->data(
                            malzeme->MLZMmodel->index
                            (fr_row,malzeme->MLZMmodel->fieldIndex ("mlzm_malzeme"))
                            ).toString () )  ;

    });

    this->show ();
}

void FtrDet_MlzEkle::reject()
{
    QDialog::reject();
}


FtrDet_MlzEkle::~FtrDet_MlzEkle()
{
}

QString FtrDet_MlzEkle::getMalzeme() const
{
    return m_malzeme;
}

void FtrDet_MlzEkle::setMalzeme(const QString &value)
{
    m_malzeme = value;
}
