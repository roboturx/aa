﻿#include "cw_ftr.h"
#include "globals.h"
#include "hc_tableview.h"
#include "mw_main.h"

Cw_ftr::Cw_ftr(QWidget *parent) :  QWidget(parent)
{
}

//************************************************************
//*****************  F A T U R A  ****************************


void Cw_ftr::setup_fatura()
{
    qDebug() << "FATURA";
    this->setWindowTitle ("FATURA");
    this->showMaximized ();
    lB_FTR     = new QLabel ("Fatura");

    setup_uiFtr();

    setup_modelFtr();
    setup_viewFtr();
    setup_mapFtr();

    setup_modelFtrDet();
    setup_viewFtrDet();
    setup_mapFtrDet();

    /// depo map nav tuslari kontrol
    ( connect(FTRmapper, &QDataWidgetMapper::currentIndexChanged,
              this, &Cw_ftr::slt_ftr_updButtons));
    /// depo da kolon değiştiğinde indexte değişsin
    ( connect(  FTRtview->table->selectionModel(),
                SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
                FTRmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    // ( connect(  FTRtview->table->selectionModel(),
    //                   SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //                 cw_mkn, SLOT( onMKNtview_resimGosterSLOT(QModelIndex))));
    /// depo da row değiştiğinde indexte değişsin
    ( connect(  FTRtview->table->selectionModel(),
                SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                FTRmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    /// row değiştiğnde resmide değiştirelim
    (connect( FTRtview->table->selectionModel (), &QItemSelectionModel::currentRowChanged,
              this, &Cw_ftr::slt_ftr_resimGoster ));
    /// depodet miktar değiştiğinde depo envanter hesabı
    connect (lE_mlzdetmiktar, &QLineEdit::editingFinished, this,
             &Cw_ftr::slt_ftr_hesap);

    //tableviewde barkod veya mlzm değiştiğinde arama yapılsın
    connect (FTRtview->table->model (),
             &QSqlTableModel::dataChanged, this,
             &Cw_ftr::slt_mlz_ara  );

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    connect(FTRDETtview->table->model() ,
            &QSqlTableModel::dataChanged , this,
            &Cw_ftr::slt_ftr_hesap);


    /// depodet grs_cks değiştiğinde depo envanter hesabı
    //   (connect (lEcbx_d_grs_cks, &QComboBox::editTextChanged , this,
    //                   &Cw_ftr::slt_ftr_hesap));
    /// depodan makina ikmale firma transferi
    //   (connect ( cX_mkn, &QCheckBox::pressed, this,
    //                    &Cw_ftr::slt_ftr_cX_mkn));
    /// depo ilk kayıda
   Cw_ftr::FTRmapper->toFirst ();

    /// depoda row değiştiğinde
    Cw_ftr::slt_ftr_tV_rowchanged (FTRmodel->index (0,0));


    /// depodet map değiştiğinde nav tuşalrı ayarlansın
    ( connect(FTRDETmapper, &QDataWidgetMapper::currentIndexChanged,
              this, &Cw_ftr::slt_ftrd_updButtons));
    /// depodet table da koon değiştiğnde index değişsin
    ( connect(  FTRDETtview->table->selectionModel(),
                SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
                FTRDETmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    /// depodet table da row değiştiğnde index değişsin
    ( connect(  FTRDETtview->table->selectionModel(),
                SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                FTRDETmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    ///depoda row değiştiğinde
    (connect (FTRtview->table->selectionModel (),
              &QItemSelectionModel::currentRowChanged,
              this, &Cw_ftr::slt_ftr_tV_rowchanged));

    //    (connect ( FTRtview->table->selectionModel (),
    //                       QItemSelectionModel::currentRowChanged,
    //                      cw_mkn->MKNtview->selectionModel (),
    //                       &QItemSelectionModel::currentRowChanged ));

    /// depodetay varsa ilk kayda
    Cw_ftr::FTRDETmapper->toFirst ();
    //    FTRtview->table->setFocus ();
}


void Cw_ftr::setup_uiFtr()
{
    qDebug() << "  setup_uiFtr";

    ////////////////////////////////////////// widgets
    wd_FTR();
    wd_FTRdet();

    QWidget *wdgt_rsm = new QWidget();
    lB_rsm = new QLabel(wdgt_rsm);
    lB_rsm->setMinimumSize (180,120);
    /*
    QMovie *movie = new QMovie("animations/fire.gif");

    lB_rsm->setMovie(movie);
    movie->start();
    */

    QFrame frame1(this);
    QGridLayout grid1;
    frame1.setLayout (&grid1);
    grid1.addWidget (FTRtview    , 0, 0 );
    grid1.addWidget (wdgt_mapFTR , 0, 1 );
    grid1.addWidget (wdgt_rsm    , 0, 2 );

    QFrame frame2(this);
    auto *grid2 = new QGridLayout;
    frame2.setLayout (grid2);
    grid2->addWidget (FTRDETtview    , 0, 0 );
    grid2->addWidget (wdgt_mapFTR_dty, 0, 1 );

    ////////////////////////////////////////////// layout
    auto *LyG_FTR = new QGridLayout();
    LyG_FTR->addWidget (&frame1 , 0, 0, 1, 1);
    LyG_FTR->addWidget (&frame2 , 1, 0, 1, 1);


}

void Cw_ftr::wd_FTR()
{
    qDebug() << "  wd_FTR";
    QLabel *lB_faturano = new QLabel(tr("Fatura &No"));
    lE_faturano = new QLineEdit();
    lE_faturano->setPlaceholderText ("Malzeme Kaydı için Fatura No Giriniz");

    lB_faturano->setBuddy(lE_faturano);

    //  lB_brkd->setText (lB_faturano->text ());

    QLabel *lB_firma = new QLabel(tr("&Firma Ünvanı "));
    lE_firma = new QLineEdit();
    lB_firma->setBuddy(lE_firma);

    QLabel *lB_tarih = new QLabel(tr("Fatura &Tarihi"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

    QLabel *lB_ack = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_ack->setBuddy(lE_aciklama);


    //////////////////////////////////// depo tableview
    int i=1;
    FTRtview = new HC_TableView(i);
    FTRtview->setMinimumSize (180,120);

    ///////////////////////////////////////  mapper buttonz
    lB_rsm = new QLabel;
    LyG_FTR = new QGridLayout();

    LyG_FTR ->addWidget(lB_faturano  , 0, 0, 1, 1);
    LyG_FTR ->addWidget(lE_faturano  , 0, 1, 1, 1);
    LyG_FTR ->addWidget(lB_firma , 2, 0, 1, 1);
    LyG_FTR ->addWidget(lE_firma , 2, 1, 1, 1);
    LyG_FTR ->addWidget(lB_tarih, 4, 0, 1, 1);
    LyG_FTR ->addWidget(lE_tarih, 4, 1, 1, 1);
    LyG_FTR ->addWidget(lB_ack, 5, 0, 1, 1);
    LyG_FTR ->addWidget(lE_aciklama, 5, 1, 1, 1);

    wdgt_mapFTR = new QWidget;
    wdgt_mapFTR->setLayout(LyG_FTR);
}



void Cw_ftr::setup_modelFtr()
{
    qDebug() << "  setupmodelfatura";
    auto *mwmain = new MW_main;;
    FTRmodel = mwmain->modelFatura() ;

}

void Cw_ftr::setup_viewFtr()
{

    qDebug() << "  setup_viewFtr";
qDebug()<<"ekle 2" << FTRmodel;
    FTRtview->table->setModel(FTRmodel);

    FTRtview->table->resizeColumnsToContents();
    FTRtview->table->resizeRowsToContents ();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///
    tV_ftr_selectionMdl = new QItemSelectionModel(FTRmodel);
    FTRtview->table->setSelectionModel (tV_ftr_selectionMdl);

    FTRtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FTRtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    //// kullanıcı bu alanları görmesin
    FTRtview->table->setColumnHidden(FTRmodel->fieldIndex("ftr_kod"), true);
    FTRtview->table->setColumnHidden(FTRmodel->fieldIndex("ftr_resim"), true);


    FTRtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    FTRtview->table->horizontalHeader()->setStretchLastSection(true);
    FTRtview->table->horizontalHeader()->resizeContentsPrecision();

    ///// tableview kontrol connectleri
    ///
    ///

    connect(FTRtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_ftr::slt_ftr_pB_EKLE_clicked  ) ;
    connect(FTRtview->pB_eklersm, &QPushButton::clicked,this ,
             &Cw_ftr::slt_ftr_pB_Eklersm_clicked  ) ;

    connect(FTRtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_ftr::slt_ftr_pB_SIL_clicked ) ;
    connect(FTRtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
            FTRmapper->toFirst ();
            int map_row = FTRmapper->currentIndex ();
            FTRtview->pB_ilk->setEnabled (map_row>0);
            FTRtview->table->setCurrentIndex(FTRmodel->index( 0  ,0));
    });

    connect(FTRtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toPrevious ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_ncki->setEnabled(map_row > 0);
        FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));
    });

    connect(FTRtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toNext ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_snrki->setEnabled(map_row < FTRmodel->rowCount() - 1);
        FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));
    });

    connect(FTRtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toLast ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_son->setEnabled(map_row < FTRmodel->rowCount() - 1);
        FTRtview->table->setCurrentIndex(FTRmodel->index( FTRmodel->rowCount() - 1  ,0));
    });


    FTRtview->pB_grscks->setVisible (false);
    //  (connect(FTRtview->pB_grscks, &QPushButton::clicked,this ,
    //                 &Cw_ftr::slt_ftr_cX_grs_clicked  )) ;


}

void Cw_ftr::setup_mapFtr()
{
    qDebug() << "  setup_mapFtr";
    FTRmapper = new QDataWidgetMapper(this);
    FTRmapper->setModel(FTRmodel);

    FTRmapper->addMapping(lE_faturano , FTRmodel->fieldIndex("ftr_no"));
    FTRmapper->addMapping(lE_firma, FTRmodel->fieldIndex("ftr_firma"));
    FTRmapper->addMapping(lE_tarih, FTRmodel->fieldIndex("ftr_tarih"));
    FTRmapper->addMapping(lE_aciklama, FTRmodel->fieldIndex("ftr_aciklama"));
}

///************************************************************
///****************  F A T U R A   S  L  O  T  S  ************




void Cw_ftr::slt_ftr_tV_rowchanged(const QModelIndex &index )
{
    qDebug() << "  slt_ftr_tV_rowchanged";
    if (index.isValid())
    {
        QSqlRecord record = FTRmodel->record(index.row());
        QString fatura_no = record.value("ftr_no").toString ();

        //QString barkid = record.value("ftr_ftno").toString ();
        //lB_brkd->setText (barkid);

        /// giris cikisa filtre koyalım
        //QString flt = QString("fatura_no = %1").arg(fatura_no);
        FTRDETmodel->setFilter (QString("mlzmdet_gcno = %1").arg(fatura_no) );

    }
    else
    {
        FTRDETmodel->setFilter("mlzdet_gcno=-1");
    }
    FTRDETmodel->select();

}


void Cw_ftr::slt_ftr_resimGoster(QModelIndex)
{
    qDebug() << "  slt_ftr_resimGoster";
    // makina stok tablosundan resim gösterme
    // view row unu tespit et
    int rowidx = FTRtview->table->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = FTRtview->table->
            model()->index( rowidx, FTRmodel->fieldIndex ("resim") ).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    if ( ! outByteArray.isNull ())
    {
        lB_rsm->setPixmap( outPixmap );
    }
    else
    {
        lB_rsm->setPixmap (QPixmap (":/rsm/rsm_yok.svg"));
    }

    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}       ///     ontV_per_resimGosterSLOT

void Cw_ftr::slt_ftr_pB_Eklersm_clicked()
{
    qDebug() << "  slt_ftr_pB_Eklersm_clicked";
    // depo resim ekle
    QString myfile = QFileDialog::
            getOpenFileName(this,
                            tr("Resim Aç"), "/home/mr/Resimler",
                            tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
                               " ;; Tüm Dosyalar (*,*)"));

    if (myfile == "")
        return;

    QImage image(myfile);
    lB_rsm->setPixmap(QPixmap::fromImage(image));
    QByteArray inByteArray;
    QFile file(  myfile ); //dosyayı açmak için al

    if ( file.open(QIODevice::ReadOnly))
    {
        //qDebug ()<<"file read";
        inByteArray = file.readAll();

        // table view de hangi rowdayız ?
        QModelIndex index = FTRtview->table->currentIndex();
        int row = index.row() ;

        /// resmi değiştirelim
        FTRmodel->setData(FTRmodel->
                          index(row, FTRmodel->
                                fieldIndex ("resim")),inByteArray);
        /// yeni eklenenleri kaydedelim
        FTRmodel->submitAll();

        //QByteArray outByteArray = FTRtview->table->
          //      model()->index( row, FTRmodel->fieldIndex ("resim") ).data().toByteArray();
        /// makina ikmalde resmi değiştirelim
        /*        cw_mkn->MKNmodel->setData (
                    cw_mkn->MKNmodel-> index (
                        0 ,cw_mkn->MKNmodel-> fieldIndex ("resim")),outByteArray );

        cw_mkn->MKNmodel-> submitAll ();
        QModelIndex xx = cw_mkn->MKNtview->currentIndex ();
        cw_mkn->onMKNtview_resimGosterSLOT (xx);
*/
    }
}       ///     onpb_resimEkleSLOT



void Cw_ftr::slt_ftr_updButtons(int row)
{
    qDebug() << "  slt_ftr_updButtons";
    FTRtview->pB_ilk->setEnabled (row>0);
    FTRtview->pB_ncki->setEnabled(row > 0);
    FTRtview->pB_snrki->setEnabled(row < FTRmodel->rowCount() - 1);
    FTRtview->pB_son->setEnabled(row < FTRmodel->rowCount() - 1);
}


void Cw_ftr::slt_ftr_hesap()
{
    qDebug() << "ftr_hesappppppppppppppppppp";
    // QModelIndex indx_ftrdet = FTRDETtview->currentIndex ();

    //int tpl_grs=0, tpl_cks=0;
    //int id_ftr ;

    QModelIndex ftr_indx = FTRtview->table->currentIndex ();
    if ( ftr_indx.row () >= 0 )
    {
        int fatura_row = ftr_indx.row ();
        int id = FTRmodel->
                data ( FTRmodel->
                       index(fatura_row,FTRmodel->
                             fieldIndex("ftr_kod"))).toInt () ;

        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM mlzdet__dbtb "
                         "WHERE mlzdet_gcno= %1 AND "
                         "mlzdet_gc='Faturalı Giriş'").arg(id);
        q_qry.exec (s_qry);

        ///QSqlRecord fatura_rec = FTRmodel->record ();
        double grs=0,cks=0;
        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            FTRmodel->setData(FTRmodel->
                              index(fatura_row, FTRmodel->
                                    fieldIndex ("mlzdet_giris")), grs);



            qDebug()<<"toplam giriş data    "<<q_qry.value(0);

        }
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM dbtb_ftrdet "
                         "WHERE mlzdet_gcno= %1 AND "
                         "mlzdet_gc='Malzeme Teslim Fişi'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            FTRmodel->setData(FTRmodel->
                              index(fatura_row, FTRmodel->
                                    fieldIndex ("mlzdet_cikis")), cks);

            qDebug()<<"toplam çıkış data    "<<q_qry.value(0);
            //ftr_rec.setValue ("cikis", q_qry.value(0).toDouble ());
        }

        FTRmodel->setData(FTRmodel->
                          index(fatura_row, FTRmodel->
                                fieldIndex ("mlzdet_mevcut")), grs-cks);
        FTRmodel->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
}

void Cw_ftr::slt_mlz_ara()
{
    qDebug()<<"malzeme araaaaaaaaaaaaaa    ";
}

void Cw_ftr::slt_ftr_pB_EKLE_clicked ()
{
    qDebug() << "  slt_ftr_pB_EKLE_clicked";

    QDialog *dia_ekle = new QDialog;
    auto *lay_dia = new QGridLayout(dia_ekle);
    QLabel *lft_no = new QLabel("Fatura No");
    QLabel *lft_fr = new QLabel("Firma");
    QLabel *lft_tr = new QLabel("Tarih");
    QLabel *lft_ac = new QLabel("Açıklama");

    auto *eft_no = new QLineEdit;
    auto *eft_fr = new QLineEdit;
    auto *eft_tr = new QLineEdit;
    eft_tr->setText (QDate::currentDate ().toString ("dd.MM.yyyy"));
    auto *eft_ac = new QLineEdit;
    lay_dia->addWidget (lft_no,0,0,1,1);
    lay_dia->addWidget (eft_no,0,1,1,2);
    lay_dia->addWidget (lft_fr,1,0,1,1);
    lay_dia->addWidget (eft_fr,1,1,1,2);
    lay_dia->addWidget (lft_tr,2,0,1,1);
    lay_dia->addWidget (eft_tr,2,1,1,2);
    lay_dia->addWidget (lft_ac,3,0,1,1);
    lay_dia->addWidget (eft_ac,3,1,1,2);

    QPushButton *pB_ftrekle = new QPushButton("Fatura Ekle");
    QPushButton *pB_vzgc = new QPushButton("Vazgeç");
    lay_dia->addWidget (pB_ftrekle,4,1);
    lay_dia->addWidget (pB_vzgc,4,0);

    connect (pB_vzgc, &QPushButton::clicked,dia_ekle, &QDialog::close );
    connect (pB_ftrekle, &QPushButton::clicked,
             [eft_no,eft_ac,eft_fr,eft_tr,this,dia_ekle]()
    {


        if ( eft_no->text () =="")
        {
            qDebug()<<"fatura no boş geçilemez";
        }
        else {


            //QModelIndex fatura_ndx = FTRtview->table->currentIndex ();
            QSqlRecord rec = FTRmodel->record();
            rec.setValue ("ftr_no"      , eft_no->text ());
            rec.setValue ("ftr_firma"   , eft_fr->text ());
            rec.setValue ("ftr_tarih"   , eft_tr->text ());
            rec.setValue ("ftr_aciklama", eft_ac->text ());

            // insert a new record (-1)

            if ( ! FTRmodel->insertRecord(FTRmodel->rowCount (),rec))
            {
                qDebug() << " HATA - FATURA ya kayıt eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt FATURA ya eklendi ";
                FTRmodel->submitAll ();
                FTRmodel->select ();
                QModelIndex ftr_ndx= FTRmodel->
                        index (FTRmodel->rowCount ()-1,0);
                FTRtview->table->selectRow (ftr_ndx.row ());
            }
            dia_ekle->close ();
        }


    });

    dia_ekle->show ();



}

void Cw_ftr::slt_ftr_pB_SIL_clicked ()
{
    qDebug() << "  slt_ftr_pB_SIL_clicked";
    //QSqlQuery q_qry;
    //QString s_qry;
    QModelIndex ftrindex = FTRtview->table->currentIndex();
    if( ftrindex.row() >= 0 )
    {
        QSqlRecord ftrrec = FTRmodel->record(ftrindex.row ());
        int fatkod = ftrrec.value ("ftr_kod").toInt();
        QString fatno = ftrrec.value("ftr_no").toString();

        /// depo detay kayıtlarını soralım - silelim
        QSqlQuery q_qry;
        QString s_qry;
        /// silinecek kayıt sayısı   mlzmdet__dbtb
        s_qry = QString("SELECT count() FROM mlzmdet__dbtb"
                        "where mlzmdet_gcno = %1 and "
                        "mlzmdet_gc = 'Faturalı Giriş'").arg (fatno);
        q_qry.exec(s_qry);
        int xx = 0 ;

        if ( q_qry.isActive ())
        {
            xx = s_qry.size () ;
            qDebug()<< xx <<" adet kayıt silinecek ";
        }


        QString mess="\n";
        mess += fatno + " nolu fatura"
                        "\n  silinsin mi ?\n"+
                "İşlemi onaylarsanız bu fatura kaydına ait\n " ;

        int mlzdet_count = FTRDETmodel->rowCount () ;
        if ( mlzdet_count > 0 )
        {
            mess +=QString::number (mlzdet_count) +
                    " adet Ambar GİRİŞ kaydı da SİLİNECEK";
        }
        mess +="\n\nİŞLEMİ ONAYLIYORMUSUNUZ ?";


        /// model makina kaydı var
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox
                ::question(this,
                           "KAYIT SİL", mess,
                           QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            /// ambara ait mlzm_det giriş kayıtlarını sil
            s_qry = QString("DELETE FROM mlzmdet__dbtb "
                            "where mlzmdet_gcno = %1").arg (fatno);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<<" - "<< mlzdet_count <<
                          " - adet Faturalı Giriş Kaydı Silindi";
            }
            else
            {
                qDebug()<< "HATA - Faturalı Giriş Kayıtları Silinemedi"
                        << q_qry.lastError() ;
            }



            /// depo kayıtlarını silelim
            s_qry = QString("DELETE FROM ftr__dbtb "
                            "where ftr_kod = %1").arg (fatkod);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< "1 adet Fatura Kaydı Silindi";
                FTRtview->setFocus ();
                FTRmodel->select ();



                if (FTRmodel->rowCount () == 1)
                {
                    FTRtview->table->selectRow (0);
                    FTRtview->setCurrentIndex (FTRmodel->index(0,0));
                }
                if (FTRmodel->rowCount () > 1)
                {
                    if (ftrindex.row () == 0)
                    {
                        FTRtview->table->selectRow (0);
                        FTRtview->setCurrentIndex (FTRmodel->index(0,0));
                    }
                    else if (ftrindex.row () > 0)
                    {
                        FTRtview->table->selectRow (ftrindex.row()-1);
                        FTRtview->setCurrentIndex (FTRmodel->index(ftrindex.row ()-1,0));
                    }
                }
            }
            else
            {
                qDebug()<< "HATA - Fatura Kaydı Silinemedi"
                        << q_qry.lastError() ;
            }
        }
    }
}

/*
void Cw_ftr::slt_ftr_cX_grs_clicked()
{
        qDebug() << "  slt_ftr_cX_grs_clicked";
    QIcon icon;
    if ( ! FTRtview->pB_grscks->isFlat ())
    {

        QModelIndex ftr_indx = FTRtview->table->currentIndex ();
        slt_ftr_tV_rowchanged (ftr_indx);
        FTRtview->pB_grscks->setFlat (true);
        icon.addPixmap(QPixmap (":/rsm/nv_eklesil.svg") ,
                       QIcon::Normal, QIcon::On);
        FTRtview->pB_grscks->setIcon (icon);
        wdgt_mapFTR_dty->show ();
    }
    else
    {
        FTRtview->pB_grscks->setFlat (false);
        icon.addPixmap(QPixmap (":/rsm/nv_eklesil2.svg") ,
                       QIcon::Normal, QIcon::On);
        FTRtview->pB_grscks->setIcon (icon);
        wdgt_mapFTR_dty->hide ();
    }
}


*/




///************************************************************
///****************  F A T U R A    D  E  T  A  Y  ************
///
///                  malzeme detay olarak işlem yapılıyor
///

void Cw_ftr::wd_FTRdet()
{
    qDebug() << "  wd_FTRdet";
    lB_FTRdet = new QLabel("Malzeme Ftr Giriş - Çıkış İşlemleri");

    //  QLabel *lB_d_tarih = new QLabel(tr("&Tarih"));
    // lE_d_tarih = new QLineEdit();
    // lB_d_tarih->setBuddy(lE_d_tarih);

    QLabel *lB_mlzdetbarkod = new QLabel(tr("Barkod"));
    lE_mlzdetbarkod = new QLineEdit();
    lB_mlzdetbarkod->setBuddy(lE_mlzdetbarkod);


    QLabel *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
    lE_mlzdetmlzm = new QLineEdit();
    lB_mlzdetmlzm->setBuddy(lE_mlzdetmlzm);

    QLabel *lB_mlzdettarih = new QLabel(tr("Tarih"));
    lE_mlzdettarih = new QLineEdit();
    lB_mlzdettarih->setBuddy(lE_mlzdettarih);

    QLabel *lB_mlzdetgc = new QLabel(tr("İşlem"));
    lE_mlzdetgc = new QLineEdit;
    lB_mlzdetgc->setBuddy(lE_mlzdetgc);

    QLabel *lB_mlzdetgcno = new QLabel(tr("Belge No"));
    lE_mlzdetgcno = new QLineEdit;
    lB_mlzdetgcno->setBuddy(lE_mlzdetgcno);


    QLabel *lB_mlzdetmiktar = new QLabel(tr("Miktar"));
    lE_mlzdetmiktar = new QLineEdit();
    lB_mlzdetmiktar->setBuddy(lE_mlzdetmiktar);


    QLabel *lB_mlzdetbirim = new QLabel(tr("Birim"));
    lE_mlzdetbirim = new QLineEdit();
    lB_mlzdetbirim->setBuddy(lE_mlzdetbirim);


    QLabel *lB_mlzdetfiyat = new QLabel(tr("Birim Fiyat"));
    lE_mlzdetfiyat = new QLineEdit();
    lB_mlzdetfiyat->setBuddy(lE_mlzdetfiyat);


    QLabel *lB_mlzdetkdv = new QLabel(tr("KDV %"));
    lE_mlzdetkdv = new QLineEdit();
    lB_mlzdetkdv->setBuddy(lE_mlzdetkdv);


    QLabel *lB_mlzdetaciklama = new QLabel(tr("Açıklama"));
    lE_mlzdetaciklama = new QLineEdit();
    lB_mlzdetaciklama->setBuddy(lE_mlzdetaciklama);



    //////////////////////////////////// depodet tableview
    int i= 1;
    FTRDETtview = new HC_TableView(i);
    FTRDETtview->setMinimumSize (180,120);



    auto *lYG_d_map = new QGridLayout();


    lYG_d_map->addWidget(lB_mlzdetbarkod  , 0, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbarkod  , 0, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmlzm    , 1, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetmlzm    , 1, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetgc      , 2, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetgc      , 2, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmiktar  , 3, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetmiktar  , 3, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetbirim   , 4, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbirim   , 4, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetfiyat   , 5, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetfiyat   , 5, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetkdv     , 6, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetkdv     , 6, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetaciklama, 7, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetaciklama, 7, 1, 1, 1);


    LyG_FTR_dty = new QGridLayout( );

    LyG_FTR_dty->addWidget (lB_FTRdet  , 0, 0, 1, 1);
    LyG_FTR_dty->addLayout (lYG_d_map   , 2, 0, 1, 1);

    wdgt_mapFTR_dty = new QWidget;
    wdgt_mapFTR_dty->setLayout(LyG_FTR_dty);


}










///////////////////////////////////////////  end setup view

void Cw_ftr::setup_modelFtrDet()
{
    auto *mwmain = new MW_main;
    FTRDETmodel = mwmain->modelFaturaDetay ();
}

void Cw_ftr::setup_viewFtrDet()
{
    qDebug() << "  setup_viewFtrDet";

    FTRDETtview->table->setModel(FTRDETmodel);
    // Hide the column id Records
    //// kullanıcı bu alanları görmesin
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_kod"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_mlzm_kod"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_tarih"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_gc"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_gcno"), true);

    // Allow the selection of lines
    FTRDETtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    // Set selection mode, only one row in table
    FTRDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    FTRDETtview->table->resizeRowsToContents ();
    FTRDETtview->table->resizeColumnsToContents();
    // FTRDETtview->table->setStyleSheet ("background-color: darkgreen;"
    //                         "color : yellow;");
    FTRDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    FTRDETtview->table->horizontalHeader()->
            setStretchLastSection(true);
    FTRDETtview->table->horizontalHeader()->
            resizeContentsPrecision();

    // FTRDETtview->table->setCurrentIndex (FTRDETmodel->index (0,0));
    // FTRDETmodel->select ();

    (connect(FTRDETtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_ftr::slt_mlz_pB_EKLE_clicked  )) ;

    (connect(FTRDETtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_ftr::slt_ftrd_pB_SIL_clicked )) ;
    connect(FTRDETtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FTRDETmapper->toFirst ();
        FTRDETtview->pB_ilk->setEnabled (FTRDETmapper->currentIndex ()>0);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( 0  ,0));
    });


    connect(FTRDETtview->pB_ncki, &QPushButton::clicked,
             [this]()
    {
             FTRDETmapper->toPrevious ();
             FTRDETtview->pB_ncki->setEnabled(FTRDETmapper->currentIndex () > 0);
             FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmapper->currentIndex () ,0));
    });
    connect(FTRDETtview->pB_snrki, &QPushButton::clicked,
             [this]()
    {
            FTRDETmapper->toNext ();
            int map_row = FTRDETmapper->currentIndex ();
            FTRDETtview->pB_snrki->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
            FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( map_row  ,0));
     });

    connect(FTRDETtview->pB_son, &QPushButton::clicked,
            [this]()
    {
            FTRDETmapper->toNext ();
            int map_row = FTRDETmapper->currentIndex ();
            FTRDETtview->pB_snrki->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
            FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( map_row  ,0));
    });
    //FTRDETtview->pB_grscks->setVisible (false);

}

void Cw_ftr::setup_mapFtrDet()
{
    qDebug() << "  setup_mapFtrDet";
    FTRDETmapper = new QDataWidgetMapper(this);
    FTRDETmapper->setModel(FTRDETmodel);

    //FTRDETmapper->addMapping(lE_d_faturano , FTRDETmodel->fieldIndex("faturano"));
    //FTRDETmapper->addMapping(lE_d_firma, FTRDETmodel->fieldIndex("firma"));
    FTRDETmapper->addMapping(lE_mlzdetbarkod, FTRDETmodel->fieldIndex("mlzmdet_barkod"));
    FTRDETmapper->addMapping(lE_mlzdetmlzm, FTRDETmodel->fieldIndex("mlzmdet_malzeme"));
    FTRDETmapper->addMapping(lE_mlzdetmiktar, FTRDETmodel->fieldIndex("mlzmdet_miktar"));
    FTRDETmapper->addMapping(lE_mlzdetbirim, FTRDETmodel->fieldIndex("mlzmdet_birim"));
    FTRDETmapper->addMapping(lE_mlzdetfiyat, FTRDETmodel->fieldIndex("mlzmdet_fiyat"));
    FTRDETmapper->addMapping(lE_mlzdetkdv, FTRDETmodel->fieldIndex("mlzmdet_kdv"));
    FTRDETmapper->addMapping(lE_mlzdetaciklama, FTRDETmodel->fieldIndex("mlzmdet_aciklama"));
}


///************************************************************
///****************  F A T U R A  D  E  T  A  Y  ************
///*******                 S  L  O  T  S           ************
///
///




void Cw_ftr::slt_ftrd_updButtons(int row)
{
    qDebug() << "  slt_ftrd_updButtons";
    FTRDETtview->pB_ilk->setEnabled (row>0);
    FTRDETtview->pB_ncki->setEnabled(row > 0);
    FTRDETtview->pB_snrki->setEnabled(row < FTRDETmodel->rowCount() - 1);
    FTRDETtview->pB_son->setEnabled(row < FTRDETmodel->rowCount() - 1);
}


/// Fatura detayına malzeme ekle

///
/// \brief Cw_ftr::slt_mlz_pB_EKLE_clicked
///
void Cw_ftr::slt_mlz_pB_EKLE_clicked ()
{

    qDebug() << "  slt_mlz_pB_EKLE_clicked";


    QDialog *dia_ekle = new QDialog;
    auto *lay_dia = new QGridLayout(dia_ekle);

    QSqlTableModel *mlz_model = new QSqlTableModel();
    mlz_model->setTable ("mlzm__dbtb");
    mlz_model->select ();
    auto *mlz_view = new QTableView(this);
    mlz_view->setModel (mlz_model);

    QModelIndex ftr_indx = FTRtview->table->currentIndex () ;
    int ftr_row = ftr_indx.row ();
    QString ftrno = FTRmodel->
            data ( FTRmodel->
                   index(ftr_row,FTRmodel->
                         fieldIndex("ftr_no"))).toString() ;

    qDebug ()<<"ftrno " << ftrno;
    QString ftrtarih = FTRmodel->
            data ( FTRmodel->
                   index(ftr_row,FTRmodel->
                         fieldIndex("ftr_tarih"))).toString() ;
    QLineEdit fno;
    fno.insert (ftrno);
    fno.setReadOnly (true);
    QLineEdit ftr;
    ftr.setText (ftrtarih);
    ftr.setReadOnly (true);


    // lay_dia->addWidget (eml_br,1,0,1,1);

    QPushButton *pB_ftrekle = new QPushButton("Faturaya Malzeme Ekle");
    QPushButton *pB_kpt = new QPushButton("Kapat");

    lay_dia->addWidget (mlz_view  ,0,0,6,2);
    lay_dia->addWidget (new QLabel("Fatura No   :" + ftrno)      ,0,2,1,1);
    //  lay_dia->addWidget (&fno                          ,0,3,1,1);
    lay_dia->addWidget (new QLabel("Fatura Tarih:" + ftrtarih)    ,1,2,1,1);
    // lay_dia->addWidget (&ftr                          ,1,3,1,1);
    lay_dia->addWidget (pB_kpt    ,7,0,1,1);
    lay_dia->addWidget (pB_ftrekle,7,1,1,2);


    connect (pB_kpt, &QPushButton::clicked,dia_ekle, &QDialog::close );
    connect (pB_ftrekle, &QPushButton::clicked,
             [ftr_indx,ftrno,ftrtarih,this,mlz_model,mlz_view]()
    {  /// lambda


        QModelIndex mlz_indx = mlz_view->currentIndex () ;
        if ( ftr_indx.row () >= 0 )
        {

            int mlzm_row = mlz_indx.row ();

            /// kayıt içerisinde belirli bir
            /// field in içeriğini değişkene at

            QString mlzkod = mlz_model->data ( mlz_model->
                                               index(mlzm_row,mlz_model->
                                                     fieldIndex("mlzm_kod"))).toString() ;
            QString mlzbrkod = mlz_model->
                    data ( mlz_model->
                           index(mlzm_row,mlz_model->
                                 fieldIndex("mlzm_barkod"))).toString() ;
            QString mlzmMlzm = mlz_model->
                    data ( mlz_model->
                           index(mlzm_row,mlz_model->
                                 fieldIndex("mlzm_malzeme"))).toString() ;
            QString mlzmbirim = mlz_model->
                    data ( mlz_model->
                           index(mlzm_row,mlz_model->
                                 fieldIndex("mlzm_birim"))).toString() ;

            QSqlQuery q;
            QString s_q;
            s_q ="INSERT INTO mlzmdet__dbtb "
                 "( mlzmdet_mlzm_kod, mlzmdet_barkod, mlzmdet_malzeme,"
                 "  mlzmdet_tarih   , mlzmdet_gc    , mlzmdet_gcno,"
                 "  mlzmdet_birim     )"
                 " values( ?,?,?,?,?,?,?)"  ;
            q.prepare(s_q);

            q.bindValue(0, mlzkod  );
            q.bindValue(1, mlzbrkod );
            q.bindValue(2, mlzmMlzm );
            q.bindValue(3, ftrtarih );
            q.bindValue(4, "Faturalı Giriş" );
            q.bindValue(5, ftrno );
            q.bindValue(6, mlzmbirim);
            q.exec();
            //qDebug () << q.lastError();
            if (q.isActive())
            {

                //           Hata hata("İş Emri Yeni Kayıt",
                //                   "Yeni İş Emri Kaydı Eklendi","" );

                qDebug () <<"Fatura Detay Yeni Kayıt Eklendi - "<< ftrno << " -   Eklendi";
                //mppMKN->toLast;

                FTRDETtview->table->setFocus ();
                FTRDETmodel->select ();

            }
            else
            {
                qDebug () << "Fatura Detay Yeni Kayıt Eklenemedi - " << q.lastError() ;
            }
        }
        else /// tVdepo row yok - ftr_indx.row () < 0
        {
            qDebug()<<"HATA - Ftr Ekleme .row yokk ";
        }


    }); /// lambda

    dia_ekle->show ();



}



void Cw_ftr::slt_ftrd_pB_SIL_clicked ()
{
    qDebug() << "  slt_ftrd_pB_SIL_clicked";
    QModelIndex sample =   FTRDETtview->table->currentIndex();
    if( sample.row() >= 0 )
    {
        QSqlRecord rec = FTRDETmodel->record();

        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;

        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,// + "\n faturanoli personelin kaydı silinsin mi? ?" ,
                                    QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            FTRDETmodel->removeRow(sample.row());
            FTRDETmodel->submitAll ();
            //pmodel->endRemoveColumns();
            FTRDETmodel->select ();
        }
    }
}






void Cw_ftr::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Ftr dosyası açılıyor";
}











Cw_ftr::~Cw_ftr()
{
    //    delete ui;
}
