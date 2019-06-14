#include "ftr_frmekle.h"
//#include "cw_fr.h"



// ////////////////////////////////////////
// / \brief Ftr_FrmEkle::Ftr_FrmEkle
// / \param parent
// /
// / faturaya firma ekle

Ftr_FrmEkle::Ftr_FrmEkle(QDialog *parent) : QDialog(parent)
{
    this->setModal (true);
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
    connect (firma->FRMselectionMdl,
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


// //////////////////////////////////////// Fatura Detaya malzeme ekle
// FtrDet_MlzEkle


FtrDet_MlzEkle::FtrDet_MlzEkle(QDialog *parent) : QDialog(parent)
{
    this->setModal (true);
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




// ////////////////////////////////////////////////////////// resim





Resim::Resim(QWidget *wD_resim, QWidget *parent) : QWidget(parent)
{
    if (wD_resim != nullptr)
    {
        wD_resim->lB_resim->setScaledContents( true );
        wD_resim->lB_resim->setSizePolicy( QSizePolicy::Preferred,
                                 QSizePolicy::Preferred );
        wD_resim->lB_resim->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(wD_resim->lB_resim , &QLabel::customContextMenuRequested,
                [ wD_resim->lB_resim]()
        {
            //QLabel *x = lB_rsm;
            QDialog xx;
            xx.setModal(true);
            xx.setSizeGripEnabled(true);
            xx.setAutoFillBackground(true);
            QLabel *x = new QLabel(&xx);
            x->resize(QGuiApplication::primaryScreen()->
                      availableSize() * 10 / 16);
            x->setScaledContents(true);
            x->setPixmap(QPixmap (*wD_resim->lB_resim->pixmap() ) );
            xx.setWindowTitle("RESİM GÖRÜNTÜLEME");
            xx.exec();
        });

    }
}



wD_Rsm::wD_Rsm(QString *png_name,
               QLabel *wD_resim,
               QWidget *parent)
{
    if (wD_resim != nullptr)
    {

    }


    QLabel *rsm1 = new QLabel ;
    QLabel *rsm2 = new QLabel ;
    QLabel *rsm3 = new QLabel ;
    QLabel *rsm4 = new QLabel ;

   // rsm2->setPixmap (QPixmap(":/rsm/logo/Audi.png"));
    rsm3->setPixmap (":/rsm/logo/"+ *png_name+".png");
   // rsm4->setPixmap (QPixmap (":/rsm/logo/hm/caterpillar.jpg"));

    auto *mkn_rs = new QGridLayout();
    mkn_rs->addWidget (rsm1,1,1,1,1);
    mkn_rs->addWidget (rsm2  ,0,1,1,1);
    mkn_rs->addWidget (rsm3  ,1,0,1,1);
    mkn_rs->addWidget (rsm4  ,0,0,1,1);


}



void Resim::resimUpdate(  QWidget *rsm_updResim,
                          HC_TableView *rsm_table,
                          QSqlRelationalTableModel *rsm_model,
                          QItemSelectionModel *rsm_selectionModel,
                          QString rsm_field,
                          QString rsm_new_upd
                          )
{
    // view row unu tespit et
    int rowidx = rsm_selectionModel->currentIndex().row();

    if (rsm_new_upd == nullptr) // yeni kayıt
    {
        // row, xolumn daki veriyi bytearray a at
        QByteArray outByteArray = rsm_table->table->
                model()->index( rowidx, rsm_model->
                                fieldIndex ( rsm_field ) ).data().toByteArray();

        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData( outByteArray  );
        if ( ! outByteArray.isNull ())
        {
            rsm_updResim->lB_resim->setPixmap( outPixmap );
        }
        else
        {
            rsm_updResim->lB_resim->setPixmap (QPixmap (":/rsm/icon/photo_camera.png"));
        }

        rsm_updResim->lB_resim->setScaledContents( true );
        rsm_updResim->lB_resim->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        rsm_updResim->lB_resim->show();

    }
    else  // resim uodate
    {
        // QModelIndex index = FTRtview->table->currentIndex();
        // int row = index.row() ;

        //     Resim resim;


        // fatura resim ekle
        QString myfile = QFileDialog::
                getOpenFileName (this,
                                 tr("Resim Aç"), "/home/mr/Resimler",
                                 tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
                                    " ;; Tüm Dosyalar (*,*)"));

        if (myfile == "")
            return ;

        QImage image(myfile);
        rsm_updResim->lB_resim->setPixmap(QPixmap::fromImage(image));
        QByteArray inByteArray;
        QFile file(  myfile ); //dosyayı açmak için al

        if (file.open(QIODevice::ReadOnly))
        {
            inByteArray = file.readAll();
            /// resmi değiştirelim
            rsm_model->setData(rsm_model->
                               index(rowidx, rsm_model->fieldIndex
                                     ( rsm_field )), inByteArray);
            /// yeni eklenenleri kaydedelim
            rsm_model->submitAll();
        }
    }
}




