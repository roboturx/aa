#include "cw_mlzm.h"
#include "cw_ftr.h"
#include "globals.h"
#include "hc_tableview.h"
#include "mw_main.h"

Cw_Mlzm::Cw_Mlzm(QWidget *parent) :
    QWidget(parent)
{
}

//TODO mlzm girişteki menuyu malzeme det ekle ye aktar
// TODO mlzmdet modeli mw maine aktar
// TODO mlzm ui yi düzenle
// WARNING app quit crashh
// WARNING başlangıçta dosya oluşumları gözükmüyor

void Cw_Mlzm::setup_mlzm()
{
    qDebug() << "MLZM";
    Cw_Mlzm::setWindowTitle ("AMBAR");
    Cw_Mlzm::showMaximized ();

    //*****************************************************
    //*****************  A M B A R ************************
    setup_uiMlzm();

    setup_modelMlzm();
    setup_viewMlzm();
    setup_mapMlzm();

    setup_modelMlzmdet();
    setup_viewMlzmdet();
    setup_mapMlzmdet();



    /// Mlzm map nav tuslari kontrol
    //   connect(MLZMmapper, &QDataWidgetMapper::currentIndexChanged,
    //                   this, &Cw_Mlzm::slt_Mlzm_updButtons);
    /// Mlzm da kolon değiştiğinde indexte değişsin
    //  ( connect(  MLZMtview->table->selectionModel(),
    //                    SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //                  MLZMmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    // ( connect(  MLZMtview->table->selectionModel(),
    //                   SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //                 cw_mkn, SLOT( onMKNtview_resimGosterSLOT(QModelIndex))));

    /// Mlzm da row değiştiğinde indexte değişsin
    /*  connect(  MLZMtview->table->selectionModel(),
         &QItemSelectionModel::currentRowChanged, MLZMmapper,
         &QDataWidgetMapper::setCurrentModelIndex);
*/
    /// row değiştiğnde resmide değiştirelim
    /*    connect( MLZMtview->table->selectionModel (),
         &QItemSelectionModel::currentRowChanged, this,
         &Cw_Mlzm::slt_Mlzm_resimGoster );
*/
    /// Mlzmdet miktar değiştiğinde Mlzm envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished, this,
    //                   &Cw_Mlzm::slt_Mlzm_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    //  connect(MLZMDETtview->table->model() ,
    //        &QSqlTableModel::dataChanged , this,
    //      &Cw_Mlzm::slt_Mlzm_hesap);


    /// Mlzmdet grs_cks değiştiğinde Mlzm envanter hesabı
    //   (connect (cbx_d_grs_cks, &QComboBox::editTextChanged , this,
    //                   &Cw_Mlzm::slt_Mlzm_hesap));

    /// Mlzm ilk kayıda
    //  Cw_Mlzm::slt_Mlzm_toFirst();

    /// Mlzmda row değiştiğinde
    //    Cw_Mlzm::slt_Mlzm_tV_rowchanged (MLZMmodel->index (0,0));

    /*
    /// Mlzmdet map değiştiğinde nav tuşalrı ayarlansın
    connect(MLZMDETmapper,
              &QDataWidgetMapper::currentIndexChanged, this,
              &Cw_Mlzm::slt_Mlzmd_updButtons);

    /// Mlzmdet table da koon değiştiğnde index değişsin
    connect(  MLZMDETtview->table->selectionModel(),
              &QItemSelectionModel::currentRowChanged, MLZMDETmapper,
              &QDataWidgetMapper::setCurrentModelIndex);
*/
    ///Mlzmda row değiştiğinde
    /*   connect (MLZMtview->table->selectionModel (),
             &QItemSelectionModel::currentRowChanged, this,
             &Cw_Mlzm::slt_Mlzm_tV_rowchanged);
*/
    /// Mlzmdetay varsa ilk kayda
    //   Cw_Mlzm::slt_Mlzmd_toFirst(); // detay ilk kayıda
    MLZMtview->table->setFocus ();
}




void Cw_Mlzm::setup_uiMlzm()
{
    wd_Mlzm ();
    wd_Mlzmdet();

    qDebug() << "  setup_uiMlzm";
    /////////////////////////////////////////////// buttonz

    //////////////////////////////////// Mlzm tableview
    int i=1;
    MLZMtview = new HC_TableView(i);
    MLZMtview->setMinimumSize (400,300);
    MLZMDETtview = new HC_TableView(i);
    MLZMDETtview->setMinimumSize (400,300);
    ////////////////////////////////////////////// layout
    QGridLayout *LyG_Mlzm = new QGridLayout(this);
    LyG_Mlzm->addWidget (MLZMtview  , 0, 0);
    LyG_Mlzm->addWidget (wdgt_mapMlzm  , 0, 1);
    LyG_Mlzm->addWidget (MLZMDETtview  , 1, 0);
    LyG_Mlzm->addWidget (wdgt_mapMlzm_dty  , 1, 1);

}


///
/// \brief Cw_Mlzm::wd_Mlzm
///
void Cw_Mlzm::wd_Mlzm()
{
    qDebug () << "Mlzm Giriş";

    wdgt_mapMlzm = new QWidget;
    wdgt_mapMlzm->setGeometry (0,0,100,300);

    LyG_Mlzm = new QGridLayout();
    wdgt_mapMlzm->setLayout(LyG_Mlzm);


    QLabel *lB_barkod = new QLabel(tr("&Barkod"));
    lE_barkod = new QLineEdit();
    lB_barkod->setBuddy(lE_barkod);

    lB_brkd = new QLabel();
    lB_brkd->setFont (QFont ("code128",30));
    lB_brkd->setText (lB_barkod->text ());

    QLabel *lB_malzeme = new QLabel(tr("&Malzeme"));
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


    ///////////////////////////////////////  mapper buttonz
    lB_mlzrsm = new QLabel(wdgt_mapMlzm);
    lB_mlzrsm->setFixedSize (200,150);

    int str = 0;

    ++str;
    LyG_Mlzm ->addWidget(lB_barkod   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_barkod   , str , 1, 1, 1);
    LyG_Mlzm ->addWidget(lB_brkd     , ++str, 1, 1, 1);
    LyG_Mlzm ->addWidget(lB_malzeme  , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_malzeme  , str, 1, 1, 1);

    LyG_Mlzm ->addWidget(lB_marka   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_marka   , str, 1, 1, 1);

    LyG_Mlzm ->addWidget(lB_aciklama, ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_aciklama, str, 1, 1, 1);
    LyG_Mlzm ->addWidget(lB_model   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget(lE_model   , str, 1, 1, 1);

    LyG_Mlzm ->addWidget (lB_cins    , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (lE_cins    , str, 1, 1, 1);
    LyG_Mlzm ->addWidget (lB_birim   , ++str, 0, 1, 1);
    LyG_Mlzm ->addWidget (cbx_birim   , str, 1, 1, 1);
    LyG_Mlzm ->addWidget (lB_mlzrsm  , ++str, 1, 5, 1);

}


void Cw_Mlzm::setup_modelMlzm()
{
    qDebug() << "  setup_modelMalzeme";
    MW_main *mwmain = new MW_main;
    MLZMmodel = mwmain->modelMalzeme ();
}


void Cw_Mlzm::setup_viewMlzm()
{
    qDebug() << "  setup_viewMlzm";

    MLZMtview->table->setModel(MLZMmodel);
    MLZMtview->table->resizeColumnsToContents();
    MLZMtview->table->resizeRowsToContents ();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///
    tV_Mlzm_selectionMdl = new QItemSelectionModel(MLZMmodel);
    MLZMtview->table->setSelectionModel (tV_Mlzm_selectionMdl);

    MLZMtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    MLZMtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //// kullanıcı bu alanları görmesin
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_kod"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_giris"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_cikis"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_mevcut"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_resim"), true);
    MLZMtview->table->setColumnHidden(MLZMmodel->fieldIndex("mlzm_makina"), true);

    MLZMtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    MLZMtview->table->horizontalHeader()->setStretchLastSection(true);
    MLZMtview->table->horizontalHeader()->resizeContentsPrecision();

    ///// tableview kontrol connectleri
    ///
    ///
    ///
    (connect(MLZMtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_Mlzm::slt_Mlzm_pB_EKLE_clicked  )) ;
    (connect(MLZMtview->pB_eklersm, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzm_pB_Eklersm_clicked  )) ;

    (connect(MLZMtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzm_pB_SIL_clicked )) ;
    (connect(MLZMtview->pB_ilk, &QPushButton::clicked ,this ,
             &Cw_Mlzm::slt_Mlzm_toFirst )) ;
    (connect(MLZMtview->pB_ncki, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzm_toPrevious )) ;
    (connect(MLZMtview->pB_snrki, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzm_toNext )) ;
    (connect(MLZMtview->pB_son, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzm_toLast )) ;

}

void Cw_Mlzm::setup_mapMlzm()
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
    //MLZMmapper->addMapping( lE_giris, MLZMmodel->fieldIndex("giris"));
    //MLZMmapper->addMapping( lE_cikis, MLZMmodel->fieldIndex("cikis"));
    //MLZMmapper->addMapping( lE_mevcut, MLZMmodel->fieldIndex("mevcut"));
    //MLZMmapper->addMapping( cX_mkn, MLZMmodel->fieldIndex("makina"));
}

///************************************************************
///****************  D  E  P  O     S  L  O  T  S  ************


void Cw_Mlzm::slt_Mlzm_tV_rowchanged(const QModelIndex &index )
{
    qDebug() << "  slt_Mlzm_tV_rowchanged";
    if (index.isValid())
    {
        QSqlRecord record = MLZMmodel->record(index.row());
        int MlzmKod = record.value("mlzm_kod").toInt();

  //      QString barkid = record.value("mlzm_barkod").toString ();
    //    lB_brkd->setText (barkid);

        /// giris cikisa filtre koyalım
        /// mlzm_kod mlzm dosyasında ürün kodu,
        /// mlzmdet_mlzm_kod mlzmdet dosyasında ürüne
        /// ait giriş çıkış işlemleri için bağlantı
//        QString flt = QString("mlzmdet_mlzm_kod = %1").arg(MlzmKod);
        MLZMDETmodel->setFilter (QString("mlzmdet_mlzm_kod = %1").arg(MlzmKod) );

    }
    else
    {
        MLZMDETmodel->setFilter("mlzmdet_mlzm_kod=-1");
    }
    MLZMDETmodel->select();

}


void Cw_Mlzm::slt_Mlzm_resimGoster(QModelIndex)
{
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
    lB_mlzrsm->show();
}       ///     ontV_per_resimGosterSLOT

void Cw_Mlzm::slt_Mlzm_pB_Eklersm_clicked()
{
    qDebug() << "  slt_Mlzm_pB_Eklersm_clicked";
    // Mlzm resim ekle
    QString myfile = QFileDialog::
            getOpenFileName(this,
                            tr("Resim Aç"), "/home/mr/Resimler",
                            tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
                               " ;; Tüm Dosyalar (*,*)"));

    if (myfile == "")
        return;

    QImage image(myfile);
    lB_mlzrsm->setPixmap(QPixmap::fromImage(image));
    QByteArray inByteArray;
    QFile file(  myfile ); //dosyayı açmak için al

    if ( file.open(QIODevice::ReadOnly))
    {
        //qDebug ()<<"file read";
        inByteArray = file.readAll();

        // table view de hangi rowdayız ?
        QModelIndex index = MLZMtview->table->currentIndex();
        int row = index.row() ;

        /// resmi değiştirelim
        MLZMmodel->setData(MLZMmodel->
                            index(row, MLZMmodel->
                                  fieldIndex ("mlzm_resim")),inByteArray);
        /// yeni eklenenleri kaydedelim
        MLZMmodel->submitAll();
        MLZMmodel->select ();

    }
}       ///     onpb_resimEkleSLOT



void Cw_Mlzm::slt_Mlzm_updButtons(int row)
{
    qDebug() << "  slt_Mlzm_updButtons";
    MLZMtview->pB_ilk->setEnabled (row>0);
    MLZMtview->pB_ncki->setEnabled(row > 0);
    MLZMtview->pB_snrki->setEnabled(row < MLZMmodel->rowCount() - 1);
    MLZMtview->pB_son->setEnabled(row < MLZMmodel->rowCount() - 1);
}

void Cw_Mlzm::slt_Mlzm_toFirst()
{
    qDebug() << "  slt_Mlzm_toFirst";
    MLZMmapper->toFirst ();
    int map_row = MLZMmapper->currentIndex ();
    MLZMtview->pB_ilk->setEnabled (map_row>0);
    MLZMtview->table->setCurrentIndex(MLZMmodel->index( 0  ,0));
}

void Cw_Mlzm::slt_Mlzm_toPrevious()
{
    qDebug() << " slt_Mlzm_toPrevious";
    MLZMmapper->toPrevious ();
    int map_row = MLZMmapper->currentIndex ();
    MLZMtview->pB_ncki->setEnabled(map_row > 0);
    MLZMtview->table->setCurrentIndex(MLZMmodel->index( map_row  ,0));
}

void Cw_Mlzm::slt_Mlzm_toNext()
{
    qDebug() << "  slt_Mlzm_toNext";
    MLZMmapper->toNext ();
    int map_row = MLZMmapper->currentIndex ();
    MLZMtview->pB_snrki->setEnabled(map_row < MLZMmodel->rowCount() - 1);
    MLZMtview->table->setCurrentIndex(MLZMmodel->index( map_row  ,0));

}

void Cw_Mlzm::slt_Mlzm_toLast()
{
    qDebug() << "  slt_Mlzm_toLast";
    MLZMmapper->toLast ();
    int map_row = MLZMmapper->currentIndex ();
    MLZMtview->pB_son->setEnabled(map_row < MLZMmodel->rowCount() - 1);
    MLZMtview->table->setCurrentIndex(MLZMmodel->index( MLZMmodel->rowCount() - 1  ,0));
}

void Cw_Mlzm::slt_Mlzm_hesap()
{
    qDebug() << "Mlzm_hesappppppppppppppppppp";
    // QModelIndex indx_Mlzmdet = MLZMDETtview->currentIndex ();

    //int tpl_grs=0, tpl_cks=0;
    //int id_Mlzm ;

    QModelIndex Mlzm_indx = MLZMtview->table->currentIndex ();
    if ( Mlzm_indx.row () >= 0 )
    {
        int Mlzm_row = Mlzm_indx.row ();
        int id = MLZMmodel->
                data ( MLZMmodel->
                       index(Mlzm_row,MLZMmodel->
                             fieldIndex("mlzm_kod"))).toInt () ;

        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM mlzmDet_dbtb "
                         "WHERE mlzmDet_kod= %1 AND mlzmDet_gc='Giriş'").arg(id);
        q_qry.exec (s_qry);

        QSqlRecord Mlzm_rec = MLZMmodel->record ();
        double grs=0,cks=0;
        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            MLZMmodel->setData(MLZMmodel->index(Mlzm_row, MLZMmodel->
                                                  fieldIndex ("giris")), grs);


            //Mlzm_rec.setValue ("giris", q_qry.value(0).toDouble ());
            qDebug()<<"toplam giriş data    "<<q_qry.value(0);

        }
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM dbtb_Mlzmdet "
                         "WHERE mlzmDet_kod= %1 AND mlzmDet_gc='Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            MLZMmodel->setData(MLZMmodel->
                                index(Mlzm_row, MLZMmodel->
                                      fieldIndex ("mlzdet_cikis")),
                                cks);

            qDebug()<<"toplam çıkış data    "<<q_qry.value(0);
            //Mlzm_rec.setValue ("cikis", q_qry.value(0).toDouble ());
        }

        MLZMmodel->setData(MLZMmodel->
                            index(Mlzm_row, MLZMmodel->fieldIndex ("mevcut")), grs-cks);
        MLZMmodel->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
}

void Cw_Mlzm::slt_Mlzm_pB_EKLE_clicked ()
{
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
}


void Cw_Mlzm::slt_Mlzm_pB_SIL_clicked ()
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
                    MLZMtview->setCurrentIndex (MLZMmodel->index(0,0));
                }
                if (MLZMmodel->rowCount () > 1)
                {
                    if (sample.row () == 0)
                    {
                        MLZMtview->table->selectRow (0);
                        MLZMtview->setCurrentIndex (MLZMmodel->index(0,0));
                    }
                    else if (sample.row () > 0)
                    {
                        MLZMtview->table->selectRow (sample.row()-1);
                        MLZMtview->setCurrentIndex (MLZMmodel->index(sample.row ()-1,0));
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
}








///************************************************************
///****************  D  E  P  O     D  E  T  A  Y  ************
///
///
///

void Cw_Mlzm::wd_Mlzmdet()
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
    QStringList GC = {"Giriş","Çıkış"};
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
    int i= 1;
    MLZMDETtview = new HC_TableView(i);
    (connect(MLZMDETtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_Mlzm::slt_Mlzmd_pB_EKLE_clicked  )) ;

    (connect(MLZMDETtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzmd_pB_SIL_clicked )) ;
    (connect(MLZMDETtview->pB_ilk, &QPushButton::clicked ,this ,
             &Cw_Mlzm::slt_Mlzmd_toFirst )) ;
    (connect(MLZMDETtview->pB_ncki, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzmd_toPrevious )) ;
    (connect(MLZMDETtview->pB_snrki, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzmd_toNext )) ;
    (connect(MLZMDETtview->pB_son, &QPushButton::clicked,this ,
             &Cw_Mlzm::slt_Mlzmd_toLast )) ;
    MLZMDETtview->pB_grscks->setVisible (false);

    QGridLayout *lYG_d_map = new QGridLayout();
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

///
/// \brief Cw_Mlzm::setup_modelMlzmdet
///
void Cw_Mlzm::setup_modelMlzmdet()
{
    qDebug() << "  setup_modelmlzmDet";
    QString tableName = "mlzmDet__dbtb";
    QStringList fieldList;
    fieldList.append("Detay Kod");
    fieldList.append("Malzeme Kod");
    fieldList.append("Barkod");
    fieldList.append("Malzeme");
    fieldList.append("Tarih");
    fieldList.append("İşlem Türü");   // Faturalı Giriş vs.
    fieldList.append("İşlem No");     // Fatura No
    fieldList.append("Miktar");
    fieldList.append("Birim");
    fieldList.append("Fiyat");
    fieldList.append("KDV");
    fieldList.append("Açıklama");
    fieldList.append("Resim");

    MLZMDETmodel = new QSqlTableModel() ;
    MLZMDETmodel->setTable(tableName);
    MLZMDETmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    MLZMDETmodel->setSort(2,Qt::AscendingOrder);

    for(int i = 0, j = 0; i < fieldList.size(); i++, j++)
    {
        MLZMDETmodel->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }

    // Populate the model
    if (!MLZMDETmodel->select())
    {
        qDebug () << " HATA - Model Mlzmdet select "
                  << MLZMDETmodel->lastError();
    }
}

void Cw_Mlzm::setup_viewMlzmdet()
{
    qDebug() << "  setup_viewMlzmdet";

    MLZMDETtview->table->setModel(MLZMDETmodel);
    // Hide the column id Records
    //// kullanıcı bu alanları görmesin
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("id_Mlzmdet"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("Mlzm_no"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("barkod"), true);
    MLZMDETtview->table->setColumnHidden(MLZMDETmodel->fieldIndex("malzeme"), true);

    // Allow the selection of lines
    MLZMDETtview->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    MLZMDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    MLZMDETtview->table->resizeRowsToContents ();
    MLZMDETtview->table->resizeColumnsToContents();
    // MLZMDETtview->table->setStyleSheet ("background-color: darkgreen;"
    //                         "color : yellow;");
    MLZMDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    MLZMDETtview->table->horizontalHeader()->
            setStretchLastSection(true);
    MLZMDETtview->table->horizontalHeader()->
            resizeContentsPrecision();

    // MLZMDETtview->table->setCurrentIndex (MLZMDETmodel->index (0,0));
    // MLZMDETmodel->select ();
}

void Cw_Mlzm::setup_mapMlzmdet()
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







void Cw_Mlzm::slt_Mlzmd_updButtons(int row)
{
    qDebug() << "  slt_Mlzmd_updButtons";
    MLZMDETtview->pB_ilk->setEnabled (row>0);
    MLZMDETtview->pB_ncki->setEnabled(row > 0);
    MLZMDETtview->pB_snrki->setEnabled(row < MLZMDETmodel->rowCount() - 1);
    MLZMDETtview->pB_son->setEnabled(row < MLZMDETmodel->rowCount() - 1);
}


void Cw_Mlzm::slt_Mlzmd_toFirst()
{
    qDebug() << "  slt_Mlzmd_toFirst";
    QDataWidgetMapper *x=MLZMDETmapper;
    x->toFirst ();

    int map_row = MLZMDETmapper->currentIndex ();
    MLZMDETtview->pB_ilk->setEnabled (map_row>0);
    MLZMDETtview->table->setCurrentIndex(MLZMDETmodel->index( 0  ,0));
}

void Cw_Mlzm::slt_Mlzmd_toPrevious()
{
    qDebug() << "  slt_Mlzmd_toPrevious";
    MLZMDETmapper->toPrevious ();
    int map_row = MLZMDETmapper->currentIndex ();
    MLZMDETtview->pB_ncki->setEnabled(map_row > 0);
    MLZMDETtview->table->setCurrentIndex(MLZMDETmodel->index( map_row  ,0));
}

void Cw_Mlzm::slt_Mlzmd_toNext()
{
    qDebug() << "  slt_Mlzmd_toNext";
    MLZMDETmapper->toNext ();
    int map_row = MLZMDETmapper->currentIndex ();
    MLZMDETtview->pB_snrki->setEnabled(map_row < MLZMDETmodel->rowCount() - 1);
    MLZMDETtview->table->setCurrentIndex(MLZMDETmodel->index( map_row  ,0));
}

void Cw_Mlzm::slt_Mlzmd_toLast()
{
    qDebug() << "  slt_Mlzmd_toLast";
    MLZMDETmapper->toLast ();
    int map_row = MLZMDETmapper->currentIndex ();
    MLZMDETtview->pB_son->setEnabled(map_row < MLZMDETmodel->rowCount() - 1);
    MLZMDETtview->table->setCurrentIndex(MLZMDETmodel->index( MLZMDETmodel->rowCount() - 1  ,0));
}






void Cw_Mlzm::slt_Mlzmd_pB_EKLE_clicked ()
{

    QWidget *dia = new QWidget();
    QGridLayout *gg = new QGridLayout;
    dia->setLayout (gg);

    dia->setWindowTitle ("Giriş Tipi");
    dia->setMinimumSize (250,200);

    QPushButton* fat = new QPushButton("Faturalı Malzeme Girişi",dia);
    QPushButton* fat1 = new QPushButton("Hibe Giriş",dia);
    QPushButton* fat2 = new QPushButton("Envanter Giriş",dia);
    fat->setDefault (true) ;

    QGroupBox *ft = new QGroupBox("Mlzm Malzeme Giriş Tipi",dia);
    QVBoxLayout *ff = new QVBoxLayout();
    ff->addWidget (fat);
    ff->addWidget (fat1);
    ff->addWidget (fat2);
    ft->setLayout (ff);

    gg->addWidget (ft);

    connect(fat, &QPushButton::clicked,
                [dia]()
        {
            qDebug()<<"clicked";
            Cw_ftr *ftr = new Cw_ftr;
            ftr->show ();
            ftr->setup_fatura ();
            dia->close ();
        });
    dia->show ();

    qDebug() << "  slt_Mlzmd_pB_EKLE_clicked";
    /*MLZMtview->table->setFocus ();
    MLZMDETtview->table->setFocus ();

    QModelIndex Mlzm_indx = MLZMtview->table->currentIndex () ;
    if ( Mlzm_indx.row () >= 0 )
    {
        /// Mlzm kaydı var -
        ///
        /// yeni eklenecek kayıda -
        /// Mlzmdan
        /// malzeme - barkod - Mlzm_id
        /// ekle
        ///
        ///
        /// Mlzm modelden kaydı al

        // QSqlRecord Mlzm_rec = MLZMmodel->record (Mlzm_indx.row ());
        int Mlzm_row = Mlzm_indx.row ();

        /// kayıt içerisinde belirli bir
        /// field in içeriğini değişkene at

        QString brkd = MLZMmodel->
                data ( MLZMmodel->
                       index(Mlzm_row,MLZMmodel->
                             fieldIndex("mlzm_barkod"))).toString() ;
        QString mlzm = MLZMmodel->
                data ( MLZMmodel->
                       index(Mlzm_row,MLZMmodel->
                             fieldIndex("mlzm_malzeme"))).toString() ;
        int Mlzm_no = MLZMmodel->
                data ( MLZMmodel->
                       index(Mlzm_row,MLZMmodel->
                             fieldIndex("mlzm_kod"))).toInt ();

        /// Mlzmdet den yeni boş bir record al = Mlzm_rec
        QSqlRecord Mlzmdet_rec = MLZMDETmodel->record ();
        /// rec in içerisinde istediğin fieldleri doldur
        Mlzmdet_rec.setValue ("mlzm_barkod",brkd);
        Mlzmdet_rec.setValue ("mlzm_malzeme",mlzm);
        Mlzmdet_rec.setValue ("mlzm_kod", Mlzm_no);

        // insert a new record (-1) with new data
        if ( ! MLZMDETmodel->insertRecord(-1,Mlzmdet_rec))
        {
            qDebug() << "HATA - kayıt DEPO DETAY a eklenemedi ";
        }
        else /// Mlzmdet_rec detaya eklendi
        {
            MLZMDETmodel->submitAll ();
            MLZMDETmodel->select();
        }
    }
    else /// tVMlzm row yok - Mlzm_indx.row () < 0
    {
        qDebug()<<"HATA - Mlzm Ekleme .row yokk ";
    }
    */
}



void Cw_Mlzm::slt_Mlzmd_pB_SIL_clicked ()
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
}






Cw_Mlzm::~Cw_Mlzm()
{
    qDebug() << "   destructor";
}

void Cw_Mlzm::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";
}









