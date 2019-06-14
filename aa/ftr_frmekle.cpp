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





Resim::Resim(QLabel *lB_resim, QWidget *parent) : QWidget(parent)
{
    if (lB_resim != nullptr)
    {

        lB_resim->setScaledContents( true );
        lB_resim->setSizePolicy( QSizePolicy::Preferred,
                                 QSizePolicy::Preferred );
        lB_resim->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(lB_resim , &QLabel::customContextMenuRequested,
                [ lB_resim]()
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
            x->setPixmap(QPixmap (*lB_resim->pixmap() ) );
            xx.setWindowTitle("RESİM GÖRÜNTÜLEME");
            xx.exec();
        });

    }
}




void Resim::resimUpdate(  QLabel *rsm_updResim,
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
            rsm_updResim->setPixmap( outPixmap );
        }
        else
        {
            rsm_updResim->setPixmap (QPixmap (":/rsm/icon/photo_camera.png"));
        }

        rsm_updResim->setScaledContents( true );
        rsm_updResim->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        rsm_updResim->show();

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
        rsm_updResim->setPixmap(QPixmap::fromImage(image));
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
