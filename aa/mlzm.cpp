﻿#include "mlzm.h"
#include "ftr.h"
#include "globals.h"
#include "dbase.h"
#include "ftr_frmekle.h"

hC_MLZM::hC_MLZM(QWidget *parent) : QWidget(parent)
{
    //************************************************************
    //*****************  M A L Z E M E  **************************
}


void hC_MLZM::setup_mlzm()
{

    mlzm_VTd();

    setup_uiMlzm();       // 100100

    qDebug() << "  setup_modelMalzeme";
    MLZMmodel = new QSqlRelationalTableModel;
    mlzm_model ( MLZMmodel ) ;



    setup_viewMlzm();     // 200200
    setup_mapMlzm();      // 200300


    qDebug() << "  setup_modelmlzmDet";
    MLZMDETmodel = new QSqlRelationalTableModel ;
    mlzmdet_model ( MLZMDETmodel ) ;



    setup_viewMlzmdet();  // 300200
    setup_mapMlzmdet();   // 300300

    setup_kontrol();      // 100300


}




void hC_MLZM::setup_uiMlzm()      // 100100
{
    qDebug() << "  setup_uiMlzm";
    hC_MLZM::setWindowTitle ("AMBAR");
    hC_MLZM::showMaximized ();

    ////////////////////////////////////////// widgets
    lB_rsm = new QLabel (tr("Resim"));
    hC_Rs resim(lB_rsm);

    wd_Mlzm ();                  // 100110
    wd_Mlzmdet();                // 100120
    //////////////////////////////////// Mlzm tableview
    // 100130
    MLZMtview = new hC_Tv;
    MLZMtview->setMinimumSize (200,150);
    MLZMDETtview = new hC_Tv;  // 100140
    MLZMDETtview->setMinimumSize (200,150);

    ////////////////////////////////////////////// layout
    auto *LyG_Mlzm = new QGridLayout(this);  // 100150
    int str{};
    LyG_Mlzm->addWidget (new QLabel("<b>Ambar Malzeme Listesi</b>")
                         ,  str, 0, 1, 5);
    LyG_Mlzm->addWidget (MLZMtview       ,++str, 0, 1, 5);
    LyG_Mlzm->addWidget (wdgt_mapMlzm    ,  str, 5, 1, 5);
    //   LyG_Mlzm ->addWidget (lB_rsm      ,  str, 9, 1, 1);

    LyG_Mlzm->addWidget (new QLabel("<b>Malzemeye Ait Gİriş-Çıkış Bilgileri</b>")
                         ,++str, 0, 1, 5);

    LyG_Mlzm->addWidget (MLZMDETtview    ,++str, 0, 1, 6);
    LyG_Mlzm->addWidget (wdgt_mapMlzm_dty,  str, 6, 1, 4);

}


///
/// \brief hC_MLZM::wd_Mlzm
///
void hC_MLZM::wd_Mlzm()    // 100110
{
    qDebug () << "Mlzm Giriş";

    wdgt_mapMlzm = new QWidget;
    wdgt_mapMlzm->setGeometry (0,0,100,300);

    LyG_Mlzm = new QGridLayout();
    wdgt_mapMlzm->setLayout(LyG_Mlzm);


    auto *lB_barkod = new QLabel(tr("&Barkod"));
    lE_barkod = new QLineEdit();
    lB_barkod->setBuddy(lE_barkod);

    lB_brkd = new QLabel();
    lB_brkd->setFont (QFont ("code128",30));
    lB_brkd->setText (lE_barkod->text ());

    auto *lB_malzeme = new QLabel(tr("&Malzeme"));
    lE_malzeme = new QLineEdit();
    lB_malzeme->setBuddy(lE_malzeme);

    QLabel *lB_aciklama = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_aciklama->setBuddy(lE_aciklama);

    QLabel *lB_marka = new QLabel(tr("Ma&rka"));
    lE_marka = new QLineEdit();
    lB_marka->setBuddy(lE_marka);

    QLabel *lB_model = new QLabel(tr("Mo&del"));
    lE_model = new QLineEdit();
    lB_model->setBuddy(lE_model);

    QLabel *lB_cins = new QLabel(tr("&Cins"));
    lE_cins = new QLineEdit();
    lB_cins->setBuddy(lE_cins);

    QLabel *lB_birim = new QLabel(tr("&Birim"));
    cbx_birim = new QComboBox;
    QStringList br = {"adet","takım","ton","kg","gr","torba"};
    cbx_birim->insertItems (0,  br );
    lB_birim->setBuddy(cbx_birim);


    //  QDoubleValidator *doubleVal = new QDoubleValidator(
    //            -100.00,100'000'000.00, 4, this);


    QLabel *lB_g = new QLabel(tr("Toplam Giriş"));
    lE_giris = new QLineEdit();
    lE_giris->setAlignment (Qt::AlignRight);
    lE_giris->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_giris)) ;
    lB_g->setBuddy(lE_giris);

    QLabel *lB_c = new QLabel(tr("Toplam Çıkış"));
    lE_cikis = new QLineEdit();
    lE_cikis->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_cikis)) ;
    lE_cikis->setAlignment (Qt::AlignRight);
    lB_c->setBuddy(lE_cikis);
    QLabel *lB_m = new QLabel(tr("Ambar Mevcudu"));
    lE_mevcut = new QLineEdit();
    lE_mevcut->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_mevcut)) ;
    lE_mevcut->setAlignment (Qt::AlignRight);
    lB_m->setBuddy(lE_mevcut);


    ///////////////////////////////////////  mapper buttonz
    lB_mlzrsm = new QLabel(wdgt_mapMlzm);
    lB_mlzrsm->setFixedSize (200,150);

    int str = 0;

    ++str;
    LyG_Mlzm ->addWidget(lB_barkod  , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_barkod  ,   str, 1, 1, 2);
    LyG_Mlzm ->addWidget(lB_brkd    ,   str, 3, 1, 2);
    LyG_Mlzm ->addWidget(lB_malzeme , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_malzeme ,   str, 1, 1, 4);

    LyG_Mlzm ->addWidget(lB_marka   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_marka   ,   str, 1, 1, 4);

    LyG_Mlzm ->addWidget(lB_aciklama, ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_aciklama,   str, 1, 1, 4);
    LyG_Mlzm ->addWidget(lB_model   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_model   ,   str, 1, 1, 4);

    LyG_Mlzm ->addWidget (lB_cins   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (lE_cins   ,   str, 1, 1, 4);

    LyG_Mlzm ->addWidget (lB_birim  , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (cbx_birim ,   str, 1, 1, 2);
    LyG_Mlzm ->addWidget (lB_g      , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (lE_giris  ,   str, 1, 1, 2);
    LyG_Mlzm ->addWidget (lB_c      , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (lE_cikis  ,   str, 1, 1, 2);
    LyG_Mlzm ->addWidget (lB_m      , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (lE_mevcut ,   str, 1, 1, 2);
    LyG_Mlzm ->addWidget (lB_rsm    , str-3, 3, 4, 2);

}


void hC_MLZM::setup_viewMlzm()  // 200200
{
    qDebug() << "  setup_viewMlzm";

    MLZMtview->table->setModel(MLZMmodel);
    MLZMtview->table->setSelectionMode(
                QAbstractItemView::SingleSelection);
    MLZMtview->table->setSelectionBehavior(
                QAbstractItemView::SelectItems);
    MLZMselectionMdl =   MLZMtview->table->selectionModel ();


    //// kullanıcı bu alanları görmesin
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_kod"), true);
    //    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_giris"), true);
    //    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_cikis"), true);
    //    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_mevcut"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_resim"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_makina"), true);


    MLZMtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    MLZMtview->table->horizontalHeader()->setStretchLastSection(true);
    MLZMtview->table->horizontalHeader()->resizeContentsPrecision();
    MLZMtview->table->resizeColumnsToContents();
    MLZMtview->table->resizeRowsToContents ();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///


    //             &hC_MLZM::slt_Mlzm_toLast )) ;

}

void hC_MLZM::setup_mapMlzm()  // 200300
{
    qDebug() << "  setup_mapMlzm";
    MLZMmapper = new QDataWidgetMapper(this);
    MLZMmapper->setModel(MLZMmodel);

    MLZMmapper->addMapping(lE_barkod , MLZMmodel->fieldIndex("mlzm_barkod"));
    MLZMmapper->addMapping(lE_malzeme, MLZMmodel->fieldIndex("mlzm_malzeme"));
    MLZMmapper->addMapping(lE_aciklama, MLZMmodel->fieldIndex("mlzm_aciklama"));
    MLZMmapper->addMapping(lE_marka, MLZMmodel->fieldIndex("mlzm_marka"));
    MLZMmapper->addMapping(lE_model, MLZMmodel->fieldIndex("mlzm_model"));
    MLZMmapper->addMapping(lE_cins, MLZMmodel->fieldIndex("mlzm_cins"));
    MLZMmapper->addMapping(cbx_birim, MLZMmodel->fieldIndex("mlzm_birim"));
    MLZMmapper->addMapping( lE_giris, MLZMmodel->fieldIndex("mlzm_giris"));
    MLZMmapper->addMapping( lE_cikis, MLZMmodel->fieldIndex("mlzm_cikis"));
    MLZMmapper->addMapping( lE_mevcut, MLZMmodel->fieldIndex("mlzm_mevcut"));
    //MLZMmapper->addMapping( cX_mkn, MLZMmodel->fieldIndex("makina"));


    //this, &hC_MLZM::slt_Mlzm_tV_rowchanged);

    /// Mlzmdetay varsa ilk kayda
    //    hC_MLZM::MLZMmapper->toFirst(); // detay ilk kayıda
    MLZMtview->table->setFocus ();

    /// Mlzmda row değiştiğinde
    //  hC_MLZM::slt_Mlzm_tV_rowchanged (MLZMmodel->index (0,0));

    /// Mlzm ilk kayıda
    hC_MLZM::MLZMmapper->toFirst() ;


}

///************************************************************
///****************  D  E  P  O     S  L  O  T  S  ************


void hC_MLZM::setup_kontrol()
{
    qDebug() << "setup_kontrol";

    ///// tableview kontrol connectleri
    ///
    ///
    ///

    // /// yeni malzeme ekle
    connect(MLZMtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        qDebug() << "pb ekle clicked";
        QSqlRecord rec = MLZMmodel->record();
        rec.setValue ("mlzm_makina","0");
        rec.setValue ("mlzm_barkod","123");
        // insert a new record (-1)
        if ( ! MLZMmodel->insertRecord(MLZMmodel->rowCount (),rec))
        {
            qDebug() << " HATA - Malzeme eklenemedi ";
        }
        else
        {
            qDebug() << " - Malzeme eklendi ";
            MLZMmodel->submitAll ();
            MLZMmodel->select ();
            QModelIndex Mlzm_ndx= MLZMmodel->index (MLZMmodel->rowCount ()-1,0);
            MLZMtview->table->selectRow (Mlzm_ndx.row ());
        }
    });

    /// // malzeme resmi ekle
    connect(MLZMtview->pB_eklersm, &QPushButton::clicked,
            [this] ()
    {
        hC_Rs resim (lB_rsm, MLZMtview, MLZMmodel, MLZMselectionMdl,
                     "mlzm_resim","ekle");

    });
    //&hC_MLZM::slt_Mlzm_pB_Eklersm_clicked  )) ;

    connect(MLZMtview->pB_sil, &QPushButton::clicked,
            [this] ()
    {

        qDebug() << "  slt_Mlzm_pB_SIL_clicked";
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex sample =   MLZMtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = MLZMmodel->record(sample.row ());
            int Mlzm_no = rec.value ("mlzm_kod").toInt();
            QString val = rec.value("mlzm_barkod").toString();
            QString val2= rec.value("mlzm_malzeme").toString() ;


            /// Mlzm detay kayıtlarını silelim
            /*      QSqlQuery q_qry;
            QString s_qry;
            /// silinecek kayıt sayısı
            s_qry = QString("SELECT count() FROM dbtb_Mlzmdet where Mlzm_no = %1").arg (Mlzm_no);
            q_qry.exec(s_qry);
            int xx = 0 ;

            if ( q_qry.isActive ())
            {
                xx = s_qry.size () ;
                qDebug()<< xx <<" adet kayıt silinecek ";
            }
    */

            QString mess="\n";
            mess +=val + "\n" +
                    val2 +
                    "\n\n  silinsin mi ?\n"+
                    "İşlemi onaylarsanız bu Mlzm kaydına ait\n " ;

            int Mlzmdet_count = MLZMDETmodel->rowCount () ;
            if ( Mlzmdet_count > 0 )
            {
                mess +="\n"+ QString::number (Mlzmdet_count) + " adet DEPO GİRİŞ - ÇIKIŞ kaydı";
            }


            /// model makina kaydı var
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox
                    ::question(this,
                               "KAYIT SİL", mess,
                               QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                /// Mlzmya ait Mlzmdet giriş kayıtlarını sil
                s_qry = QString("DELETE FROM mlzmDet__dbtb where mlzmDet_mlzm_kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<<" - "<< Mlzmdet_count << " - adet Mlzm Giriş_Çıkış Kaydı Silindi";
                }
                else
                {
                    qDebug()<< "HATA - Mlzm Giriş Kayıtları Silinemedi"
                            << q_qry.lastError() ;
                }

                /// Mlzm ya ait makina ikmal kayıtlarını silelim
                ///
                /// burada makina ikmal kaydı varsa
                /// makina ikmale bağlı sgrt, muayene vb
                /// tüm kayıtlarıda silmek gerekir
                //  int sil_makina_kayitlerini;


                /// Mlzm kayıtlarını silelim
                s_qry = QString("DELETE FROM mlzm__dbtb where mlzm_kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<< "1 adet Mlzm Kaydı Silindi";
                    MLZMtview->setFocus ();
                    MLZMmodel->select ();



                    if (MLZMmodel->rowCount () == 1)
                    {
                        MLZMtview->table->selectRow (0);
                        MLZMtview->table->setCurrentIndex (MLZMmodel->index(0,0));
                    }
                    if (MLZMmodel->rowCount () > 1)
                    {
                        if (sample.row () == 0)
                        {
                            MLZMtview->table->selectRow (0);
                            MLZMtview->table->setCurrentIndex (MLZMmodel->index(0,0));
                        }
                        else if (sample.row () > 0)
                        {
                            MLZMtview->table->selectRow (sample.row()-1);
                            MLZMtview->table->setCurrentIndex (MLZMmodel->index(sample.row ()-1,0));
                        }


                    }
                    else
                    {
                        qDebug()<< "HATA - Mlzm Kaydı Silinemedi"
                                << q_qry.lastError() ;
                    }
                }
                else
                {
                    /// SİLME
                    /// Mlzmya ait Mlzmdet giriş kayıtlarını SİLinMEdi
                }
            }
        }
    });

    //             &hC_MLZM::slt_Mlzm_pB_SIL_clicked )) ;
    connect(MLZMtview->pB_ilk, &QPushButton::clicked ,
            [this] ()
    {
     MLZMtview->hC_TvPb ("ilk", MLZMmodel, MLZMmapper);
    });

    // &hC_MLZM::slt_Mlzm_toFirst )) ;
    connect(MLZMtview->pB_ncki, &QPushButton::clicked,
            [this] ()
    {
        MLZMtview->hC_TvPb ("ncki", MLZMmodel, MLZMmapper);
    });

    //             &hC_MLZM::slt_Mlzm_toPrevious )) ;
    connect(MLZMtview->pB_snrki, &QPushButton::clicked,
            [this] ()
    {
        MLZMtview->hC_TvPb ("snrki", MLZMmodel, MLZMmapper);
    });

    //             &hC_MLZM::slt_Mlzm_toNext )) ;
    connect(MLZMtview->pB_son, &QPushButton::clicked,
            [this] ()
    {
        MLZMDETtview->hC_TvPb ("son", MLZMDETmodel, MLZMDETmapper);
    });

    /// mlzm nav tuslari kontrol
    connect(MLZMmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        MLZMtview->hC_TvPb ("yenile", MLZMmodel, MLZMmapper);
    });

    /// Mlzm da kolon değiştiğinde indexte değişsin
    connect(  MLZMselectionMdl, &QItemSelectionModel::currentColumnChanged,
              MLZMmapper, &QDataWidgetMapper::setCurrentModelIndex);

    /// Mlzm da row değiştiğinde indexte değişsin
    connect(  MLZMselectionMdl , &QItemSelectionModel::currentRowChanged,
              MLZMmapper, &QDataWidgetMapper::setCurrentModelIndex);

    // malzemede row değiştiğnde 3 şeyi değiştirelim
    // 1 map indexi
    // 2 malzeme kodunu ve ismini yayalım
    // 3 resim
    connect( MLZMselectionMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index)
    {


        // 1 map indexi değiştirelim
        MLZMmapper->setCurrentModelIndex(Index);

        // 2 malzeme kod - barkod - isim ve birim yayalım
        emit hC_MLZM::sgnMalzeme(

                    MLZMtview->table->
                    model()->index( Index.row() ,
                                    MLZMmodel->fieldIndex ("mlzm_kod") ).data().toString(),

                    MLZMtview->table->
                    model()->index( Index.row() ,
                                    MLZMmodel->fieldIndex ("mlzm_barkod") ).data().toString(),

                    MLZMtview->table->
                    model()->index( Index.row() ,
                                    MLZMmodel->fieldIndex ("mlzm_malzeme") ).data().toString(),

                    MLZMtview->table->
                    model()->index( Index.row() ,
                                    MLZMmodel->fieldIndex ("mlzm_birim") ).data().toString()

                    );


        // 3 resimi değiştirelim
        hC_Rs resim ( lB_rsm, MLZMtview, MLZMmodel, MLZMselectionMdl,
                      "mlzm_resim", "değiştir" ) ;

        /*

        qDebug() << "  slt_Mlzm_resimGoster";
        // makina stok tablosundan resim gösterme
        // view row unu tespit et
        int rowidx = MLZMtview->table->selectionModel()->currentIndex().row();

        // row, xolumn daki veriyi bytearray a at
        QByteArray outByteArray = MLZMtview->table->
                model()->index( rowidx, MLZMmodel->fieldIndex ("mlzm_resim") ).data().toByteArray();

        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData( outByteArray  );
        if ( ! outByteArray.isNull ())
        {
            lB_mlzrsm->setPixmap( outPixmap );
        }
        else
        {
            lB_mlzrsm->setPixmap (QPixmap (":/rsm/rsm_yok.svg"));
        }

        lB_mlzrsm->setScaledContents( true );
        lB_mlzrsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        lB_mlzrsm->show();*/
    });

    //      this,  &hC_MLZM::slt_Mlzm_resimGoster );

    //////////////////////////////////////////////////
    ///
    ///
    /// M L Z M     D E T
    ///
    ///Mlzmda row değiştiğinde
    connect (MLZMselectionMdl, &QItemSelectionModel::currentRowChanged,

             [this](QModelIndex Index)
    {

        qDebug() << "  slt_Mlzm_tV_rowchanged";
        if (Index.isValid())
        {
            QSqlRecord record = MLZMmodel->record(Index.row());
            QString MlzmKod = record.value("mlzm_kod").toString() ;
            MLZMDETmodel->setFilter (
                        QString("mlzmdet_mlzm_kod = %1").arg(MlzmKod) );
        }
        else
        {
            MLZMDETmodel->setFilter("mlzmdet_mlzm_kod=-1");
        }
        MLZMDETmodel->select();
        qDebug() << "  slt_Mlzm_tV_rowchanged son";
    });








    /// Mlzmdet miktar değiştiğinde Mlzm envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished,
    //          this, &hC_MLZM::slt_Mlzm_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın

    connect(MLZMselectionMdl, &QItemSelectionModel::currentRowChanged,
            this, &hC_MLZM::slt_Mlzm_hesap);



    /// Mlzmdet table da koon değiştiğnde index değişsin
    connect(  MLZMDETselectionMdl, &QItemSelectionModel::currentRowChanged,
              MLZMDETmapper,       &QDataWidgetMapper::setCurrentModelIndex);



    connect(MLZMDETtview->pB_ekle, &QPushButton::clicked ,
            //this , &hC_MLZM::slt_Mlzmd_pB_EKLE_clicked  )) ;
            [] ()
    {

        QWidget *dia = new QWidget();
        auto *gg = new QGridLayout;
        dia->setLayout (gg);

        dia->setWindowTitle ("Giriş Tipi");
        dia->setMinimumSize (250,200);

        QPushButton* fat = new QPushButton("Faturalı Malzeme Girişi",dia);
        QPushButton* fat1 = new QPushButton("Hibe Giriş",dia);
        QPushButton* fat2 = new QPushButton("Envanter Giriş",dia);
        fat->setDefault (true) ;

        QGroupBox *ft = new QGroupBox("Mlzm Malzeme Giriş Tipi",dia);
        auto *ff = new QVBoxLayout();
        ff->addWidget (fat);
        ff->addWidget (fat1);
        ff->addWidget (fat2);
        ft->setLayout (ff);

        gg->addWidget (ft);

        connect(fat, &QPushButton::clicked,
                [dia]()
        {
            qDebug()<<"clicked";
            auto *ftr = new hC_FTR;
            ftr->show ();
            ftr->ftr_setup ();
            dia->close ();
        });
        dia->show ();
    });

    connect(MLZMDETtview->pB_sil, &QPushButton::clicked,
            // this , &hC_MLZM::slt_Mlzmd_pB_SIL_clicked )) ;
            [this] ()
    {

        qDebug() << "  slt_Mlzmd_pB_SIL_clicked";
        QModelIndex sample =   MLZMDETtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = MLZMDETmodel->record();

            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;

            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n barkodli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                MLZMDETmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                MLZMDETmodel->select ();
            }
        }
    });

    connect(MLZMDETtview->pB_ilk, &QPushButton::clicked ,
            [this] ()
    {
        MLZMDETtview->hC_TvPb ("ilk", MLZMDETmodel, MLZMDETmapper);
    });


    connect(MLZMDETtview->pB_ncki, &QPushButton::clicked,
            [this] ()
    {
        MLZMDETtview->hC_TvPb ("ncki", MLZMDETmodel, MLZMDETmapper);
    });

    connect(MLZMDETtview->pB_snrki, &QPushButton::clicked,
            [this] ()
    {
        MLZMDETtview->hC_TvPb ("snrki", MLZMDETmodel, MLZMDETmapper);
    });


    connect(MLZMDETtview->pB_son, &QPushButton::clicked,
                  [this] ()
    {
        MLZMDETtview->hC_TvPb ("son", MLZMDETmodel,MLZMDETmapper);
    });


    connect(MLZMDETmapper, &QDataWidgetMapper::currentIndexChanged,
            [this ]()
    {
        MLZMDETtview->hC_TvPb ("yenile", MLZMDETmodel, MLZMDETmapper);
    });


}









void hC_MLZM::slt_Mlzm_hesap(QModelIndex Index)
{
    qDebug() << "Mlzm_hesappppppppppppppppppp";
    // QModelIndex indx_Mlzmdet = MLZMDETtview->currentIndex ();

    //int tpl_grs=0, tpl_cks=0;
    //int id_Mlzm ;

    QModelIndex Mlzm_indx = Index;
    qDebug() << "mlzm_indx     = " << Mlzm_indx ;
    qDebug() << "mlzm_indx.row = " << Mlzm_indx.row ();
    if ( Mlzm_indx.row () >= 0 )
    {
        int Mlzm_row = Mlzm_indx.row ();
        int id = MLZMmodel->
                data ( MLZMmodel->
                       index(Mlzm_row,MLZMmodel->
                             fieldIndex("mlzm_kod"))).toInt () ;

        qDebug() << "mlzm_row  = " << Mlzm_row;
        qDebug() << "mlzm_indx = " << Mlzm_indx ;
        qDebug() << "id mlz kod= " << QString::number (id);
        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_mlzm_kod = %1 AND "
                         "mlzmDet_gc = 'Faturalı Giriş'").arg(id);
        q_qry.exec (s_qry);

        //QSqlRecord Mlzm_rec = MLZMmodel->record ();
        double grs=0,cks=0;

        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            MLZMmodel->setData(MLZMmodel->index(Mlzm_row, MLZMmodel->
                                                fieldIndex ("mlzm_giris")), grs);
        }
        else
        {
            qDebug() << "qury not active"<<endl<<
                        q_qry.lastError ().text()<<endl;
        }
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_mlzm_kod = %1 AND "
                         "mlzmDet_gc = 'Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            MLZMmodel->setData(MLZMmodel->
                               index(Mlzm_row, MLZMmodel->
                                     fieldIndex ("mlzm_cikis")), cks);
        }
        else
        {
            qDebug() << "qury not active 2  " <<endl<<
                        q_qry.lastError ().text()<<endl;
        }

        MLZMmodel->setData(MLZMmodel->
                           index(Mlzm_row, MLZMmodel->
                                 fieldIndex ("mlzm_mevcut")), grs-cks);
        MLZMmodel->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
    else
    {
        qDebug() << "index invalid"<<endl          ;
    }


}








///************************************************************
///****************  D  E  P  O     D  E  T  A  Y  ************
///
///
///

void hC_MLZM::wd_Mlzmdet()
{
    qDebug() << "  wd_Mlzmdet";
    lB_Mlzmdet = new QLabel("Malzeme Mlzm Giriş - Çıkış İşlemleri");

    /*lE_d_barkod = new QLineEdit();
    lE_d_barkod->setReadOnly (1);


    lE_d_malzeme = new QLineEdit();
    lE_d_malzeme->setReadOnly (1);
*/
    QLabel *lB_d_tarih = new QLabel(tr("&Tarih"));
    lE_d_tarih = new QLineEdit();
    lB_d_tarih->setBuddy(lE_d_tarih);

    QLabel *lB_d_grs_cks = new QLabel(tr("Grş_Çkş"));
    cbx_d_grs_cks = new QComboBox;
    QStringList GC = {"Faturalı Giriş","Çıkış"};
    cbx_d_grs_cks->insertItems (0,  GC );
    lB_d_grs_cks->setBuddy(cbx_d_grs_cks);

    QLabel *lB_d_miktar = new QLabel(tr("&Miktar"));
    lE_d_miktar = new QLineEdit();
    lB_d_miktar->setBuddy(lE_d_miktar);

    QLabel *lB_d_fiyat = new QLabel(tr("&Fiyat"));
    lE_d_fiyat = new QLineEdit();
    lB_d_fiyat->setBuddy(lE_d_fiyat);

    QLabel *lB_d_aciklama = new QLabel(tr("&Açıklama"));
    lE_d_aciklama = new QLineEdit();
    lB_d_aciklama->setBuddy(lE_d_aciklama);

    //////////////////////////////////// Mlzmdet tableview

    MLZMDETtview = new hC_Tv;
    //  MLZMDETtview->pB_grscks->setVisible (false);

    auto *lYG_d_map = new QGridLayout();
    lYG_d_map->addWidget(lB_d_tarih   , 0, 0, 1, 1);
    lYG_d_map->addWidget(lE_d_tarih   , 0, 1, 1, 1);
    lYG_d_map->addWidget(lB_d_grs_cks , 1, 0, 1, 1);
    lYG_d_map->addWidget(cbx_d_grs_cks , 1, 1, 1, 1);
    lYG_d_map->addWidget(lB_d_miktar  , 2, 0, 1, 1);
    lYG_d_map->addWidget(lE_d_miktar  , 2, 1, 1, 1);
    lYG_d_map->addWidget(lB_d_fiyat   , 3, 0, 1, 1);
    lYG_d_map->addWidget(lE_d_fiyat   , 3, 1, 1, 1);
    lYG_d_map->addWidget(lB_d_aciklama, 4, 0, 1, 1);
    lYG_d_map->addWidget(lE_d_aciklama, 4, 1, 1, 1);

    LyG_Mlzm_dty = new QGridLayout( );
    LyG_Mlzm_dty->addWidget (lB_Mlzmdet  , 0, 0, 1, 1);
    LyG_Mlzm_dty->addLayout (lYG_d_map   , 2, 0, 1, 1);

    wdgt_mapMlzm_dty = new QWidget;
    wdgt_mapMlzm_dty->setLayout(LyG_Mlzm_dty);

}

void hC_MLZM::setup_viewMlzmdet()
{
    qDebug() << "  setup_viewMlzmdet";

    MLZMDETtview->table->setModel(MLZMDETmodel);
    MLZMDETtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    MLZMDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    MLZMDETselectionMdl = MLZMDETtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("mlzmdet_kod"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("mlzmdet_mlzm_kod"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("mlzmdet_barkod"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("mlzmdet_malzeme"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("mlzmdet_resim"), true);

    MLZMDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    MLZMDETtview->table->horizontalHeader()->
            setStretchLastSection(true);
    MLZMDETtview->table->horizontalHeader()->
            resizeContentsPrecision();

    MLZMDETtview->table->resizeRowsToContents ();
    MLZMDETtview->table->resizeColumnsToContents();




    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    //    FTRtview->table->setCurrentIndex(
    //                FTRmodel->index(0, 1)
    //                );
    // with blue rect
    //    FTRtview->table->setFocus();
    //   QTimer::singleShot(0, FRMtview->table, SLOT(setFocus()));

}

void hC_MLZM::setup_mapMlzmdet()
{
    qDebug() << "  setup_mapMlzmdet";
    MLZMDETmapper = new QDataWidgetMapper(this);
    MLZMDETmapper->setModel(MLZMDETmodel);

    //MLZMDETmapper->addMapping(lE_d_barkod , MLZMDETmodel->fieldIndex("barkod"));
    //MLZMDETmapper->addMapping(lE_d_malzeme, MLZMDETmodel->fieldIndex("malzeme"));
    MLZMDETmapper->addMapping(lE_d_tarih, MLZMDETmodel->fieldIndex("mlzmDet_tarih"));
    MLZMDETmapper->addMapping(cbx_d_grs_cks, MLZMDETmodel->fieldIndex("mlzmDet_gc"));
    MLZMDETmapper->addMapping(lE_d_miktar, MLZMDETmodel->fieldIndex("mlzmDet_miktar"));
    MLZMDETmapper->addMapping(lE_d_fiyat, MLZMDETmodel->fieldIndex("mlzmDet_fiyat"));
    MLZMDETmapper->addMapping(lE_d_aciklama, MLZMDETmodel->fieldIndex("mlzmDet_aciklama"));

}

///************************************************************
///****************  D  E  P  O     D  E  T  A  Y  ************
///*******                 S  L  O  T  S           ************
///
///









hC_MLZM::~hC_MLZM()
{
    qDebug() << "   destructor";
}

void hC_MLZM::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";
}










///
/// \brief DBase::VTd_Mlzm
/// \return
///
QString hC_MLZM::mlzm_VTd ()
{
    /// Malzeme create
    ///

    QString ct, mesaj ="OK - Malzeme";
    QSqlQuery q;
    QString MLZMtableName( "mlzm__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( "mlzm__dbtb"))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + MLZMtableName +
             "("
             "mlzm_kod integer primary key, "
             "mlzm_barkod	TEXT, "
             "mlzm_malzeme  TEXT,"
             "mlzm_aciklama TEXT,"
             "mlzm_marka	TEXT, "
             "mlzm_model	TEXT, "
             "mlzm_cins	    TEXT,"
             "mlzm_birim	TEXT,"
             "mlzm_giris	TEXT, "
             "mlzm_cikis	TEXT, "
             "mlzm_mevcut   TEXT,"
             "mlzm_makina   TEXT,"
             "mlzm_resim	BLOB) "    ;

        if (!q.exec( ct ))
        {
            mesaj="<br>HATA - Malzeme Dosyası Oluşturulamadı"
                  "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else /// dosya oluşturuldu
        {
            mesaj= "OK - Malzeme Dosyası YENİ Oluşturuldu ";
            if (
                    q.exec("INSERT INTO " + MLZMtableName +
                           "( mlzm_barkod,mlzm_malzeme )"
                           " values( '1111','KOD 1 ve 1111 barkodlu malzeme' )"  ))
            {
                mesaj= mesaj+"<br>İLK kayıt Eklendi";
            }
            else
            {
                mesaj= mesaj+"<br>İLK Malzeme kaydı eklenemdi "
                             "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }

        }
    }
    else /// dosya var
    {
        //        mdlMlzm = new QSqlRelationalTableModel;
        //      mdlMlzm = modelMalzeme();
    }
    qDebug() << mesaj;
    return mesaj;
}



void hC_MLZM::mlzm_model(QSqlRelationalTableModel* model)
{
    qDebug() << " mdlmlzm";
    QString tableName ("mlzm__dbtb");
    QString indexField = "mlzm_malzeme";
    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Kod");
    tB_FieldList->append("Barkod");
    tB_FieldList->append("Malzeme");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Marka");
    tB_FieldList->append("Model");
    tB_FieldList->append("Cins");
    tB_FieldList->append("Birim");
    tB_FieldList->append("Giriş");
    tB_FieldList->append("Çıkış");
    tB_FieldList->append("Mevcut");
    tB_FieldList->append("Makina");
    tB_FieldList->append("Resim");
    hC_Rm hC_Rm (&tableName,
                 model,
                 &indexField ,
                 tB_FieldList) ;

}///Malzeme Model






///
/// \brief DBase::VTd_MlzmDETAY
/// \return
///
QString hC_MLZM::mlzmdet_VTd ()
{
    QString ct, mesaj = "OK - Malzeme Detay";
    QSqlQuery q;
    QString MLZDETtableName ( "mlzmdet__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().
         tables().contains( MLZDETtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + MLZDETtableName +
             "("
             "mlzmDet_kod integer primary key, "
             "mlzmDet_mlzm_kod	INTEGER, "
             "mlzmDet_barkod	TEXT , "
             "mlzmDet_malzeme	TEXT , "
             "mlzmDet_tarih	    TEXT , "
             "mlzmDet_gc        TEXT , "    // faturalı giriş vs.
                "mlzmDet_gcno      TEXT , "    // fatura no  vs.
                "mlzmDet_miktar    TEXT , "
                "mlzmDet_birim     TEXT , "
                "mlzmDet_fiyat     TEXT , "
                "mlzmDet_kdv       TEXT , "
                "mlzmDet_aciklama  TEXT ,  "
                "mlzmDet_resim  BLOB  "
                ")";

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Malzeme Detay Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Malzeme Detay Dosyası YENİ Oluşturuldu";

            if (q.exec("INSERT INTO " + MLZDETtableName +
                       "( mlzmdet_malzeme, mlzmDet_gc, mlzmDet_gcno )"
                       " values( '1 nolu ürüne ait detay','Faturalı Giriş','1' )"  ))
            {
                mesaj = mesaj + "<br>İLK kayıt eklendi";
            }
            else
            {
                mesaj = mesaj +"<br>İLK Kayıt EKLENEMEDİ "
                               "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;
}   /// malzeme detay


void hC_MLZM::mlzmdet_model (QSqlRelationalTableModel *model)
{
    /// NOTE Model 1 mw_main de modeli oluştur
    /// fatura detayında
    /// malzeme detay dosyası oluşturuluyor
    QString tableName ("mlzmdet__dbtb");
    QString indexField = "mlzmdet_gcno";

    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Detay Kod");
    tB_FieldList->append("Malzeme Kod");
    tB_FieldList->append("Barkod");
    tB_FieldList->append("Malzeme");
    tB_FieldList->append("Tarih");
    tB_FieldList->append("İşlem Türü");
    tB_FieldList->append("İşlem No");
    tB_FieldList->append("Miktar");
    tB_FieldList->append("Birim");
    tB_FieldList->append("Fiyat");
    tB_FieldList->append("KDV");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Resim");

    hC_Rm hC_Rm (&tableName,
                 model,
                 &indexField ,
                 tB_FieldList) ;

}///fsturs detsy Model

