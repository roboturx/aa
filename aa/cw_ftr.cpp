#include "cw_ftr.h"
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
    lB_FTR     = new QLabel ("Fatura");

    setup_uiFtr();
    setup_modelFtr();
    setup_modelFtrDet();
    setup_viewFtr();
    setup_viewFtrDet();
    setup_mapFtr();
    setup_mapFtrDet();

    /// depo map nav tuslari kontrol
    ( connect(FTRmapper, &QDataWidgetMapper::currentIndexChanged,
                      this, &Cw_ftr::slt_dp_updButtons));
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
                      this, &Cw_ftr::slt_dp_resimGoster ));
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
   //                    &Cw_ftr::slt_dp_cX_mkn));
    /// depo ilk kayıda
    Cw_ftr::slt_dp_toFirst();

    /// depoda row değiştiğinde
    Cw_ftr::slt_ftr_tV_rowchanged (FTRmodel->index (0,0));


    /// depodet map değiştiğinde nav tuşalrı ayarlansın
    ( connect(FTRDETmapper, &QDataWidgetMapper::currentIndexChanged,
                      this, &Cw_ftr::slt_dpd_updButtons));
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
    Cw_ftr::slt_dpd_toFirst(); // detay ilk kayıda
FTRtview->table->setFocus ();
}


void Cw_ftr::setup_uiFtr()
{
    qDebug() << "  setup_uiFtr";
    /////////////////////////////////////////////// buttonz

    //lB_brkd = new QLabel();
    //lB_brkd->setFont (QFont ("code128",30));


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


    //////////////////////////////////// depo tableview
    int i=1;
    FTRtview = new HC_TableView(i);
    FTRtview->setMinimumSize (400,300);

    ////////////////////////////////////////////// layout
    QGridLayout *LyG_FTR = new QGridLayout(this);
    LyG_FTR->addWidget (FTRtview       , 0, 0, 1, 1);
    LyG_FTR->addWidget (wdgt_mapFTR    , 0, 1, 1, 1);
    LyG_FTR->addWidget (wdgt_rsm       , 0, 2, 1, 1);
    LyG_FTR->addWidget (FTRDETtview    , 1, 0, 1, 1);
    LyG_FTR->addWidget (wdgt_mapFTR_dty, 1, 1, 1, 2);

}

void Cw_ftr::wd_FTR()
{
    qDebug() << "  wd_FTR";
    QLabel *lB_faturano = new QLabel(tr("Fatura No"));
    lE_faturano = new QLineEdit();
    lB_faturano->setBuddy(lE_faturano);
  //  lB_brkd->setText (lB_faturano->text ());

    QLabel *lB_firma = new QLabel(tr("&Malzeme"));
    lE_firma = new QLineEdit();
    lB_firma->setBuddy(lE_firma);

    QLabel *lB_tarih = new QLabel(tr("&Açıklama"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

 //   cX_mkn = new QCheckBox("Bu Malzeme Makina İkmalde Takip Edilsin.");

    ///////////////////////////////////////  mapper buttonz
    lB_rsm = new QLabel;


    LyG_FTR = new QGridLayout();

    LyG_FTR ->addWidget(lB_faturano  , 0, 0, 1, 1);
    LyG_FTR ->addWidget(lE_faturano  , 0, 1, 1, 1);
    LyG_FTR ->addWidget(lB_firma , 2, 0, 1, 1);
    LyG_FTR ->addWidget(lE_firma , 2, 1, 1, 1);


    LyG_FTR ->addWidget(lB_tarih, 4, 0, 1, 1);
    LyG_FTR ->addWidget(lE_tarih, 4, 1, 1, 1);

    wdgt_mapFTR = new QWidget;
    wdgt_mapFTR->setLayout(LyG_FTR);
}



void Cw_ftr::setup_modelFtr()
{
    MW_main *mwmain = new MW_main;
    FTRmodel = new QSqlRelationalTableModel ;
    FTRmodel = mwmain->modelFatura ();


    /*
    FTRmodel = new QSqlTableModel();
    FTRmodel->setTable( *tableName);
    qDebug() << "  tablename " << *tableName <<"  indexfield "<< *indexField ;
    FTRmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    FTRmodel->setSort(FTRmodel->fieldIndex (*indexField),Qt::AscendingOrder );

    qDebug() << " view column count = i "<< FTRmodel->columnCount();
    for(int i = 0, j = 0; i < fieldList->size (); i++, j++)
    {

        qDebug() << "  header data i önce = "<< i << "," <<
                    FTRmodel->headerData (i,Qt::Horizontal);

        FTRmodel->setHeaderData(i,Qt::Horizontal,fieldList->value (j));

        qDebug() << "  header data i = "<< i << "," <<
                    FTRmodel->headerData (i,Qt::Horizontal);
        qDebug() << "  setup_modelFtr i,j = "<< i << "," << j;
        qDebug() << "  field list j "<< fieldList->value (j);
    }

    // Populate the model_mkstok
    if (!FTRmodel->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<FTRmodel->lastError();
    }
*/
}

void Cw_ftr::setup_viewFtr()
{

    qDebug() << "  setup_viewFtr";

    FTRtview->table->setModel(FTRmodel);
    FTRtview->table->resizeColumnsToContents();
    FTRtview->table->resizeRowsToContents ();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///
    tV_dp_selectionMdl = new QItemSelectionModel(FTRmodel);
    FTRtview->table->setSelectionModel (tV_dp_selectionMdl);

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
///
    (connect(FTRtview->pB_ekle, &QPushButton::clicked ,this ,
                     &Cw_ftr::slt_ftr_pB_EKLE_clicked  )) ;
    (connect(FTRtview->pB_eklersm, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dp_pB_Eklersm_clicked  )) ;

    (connect(FTRtview->pB_sil, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_ftr_pB_SIL_clicked )) ;
    (connect(FTRtview->pB_ilk, &QPushButton::clicked ,this ,
                     &Cw_ftr::slt_dp_toFirst )) ;
    (connect(FTRtview->pB_ncki, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dp_toPrevious )) ;
    (connect(FTRtview->pB_snrki, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dp_toNext )) ;
    (connect(FTRtview->pB_son, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dp_toLast )) ;

    FTRtview->pB_grscks->setVisible (false);
  //  (connect(FTRtview->pB_grscks, &QPushButton::clicked,this ,
    //                 &Cw_ftr::slt_dp_cX_grs_clicked  )) ;


}

void Cw_ftr::setup_mapFtr()
{
    qDebug() << "  setup_mapFtr";
    FTRmapper = new QDataWidgetMapper(this);
    FTRmapper->setModel(FTRmodel);

    FTRmapper->addMapping(lE_faturano , FTRmodel->fieldIndex("ftr_no"));
    FTRmapper->addMapping(lE_firma, FTRmodel->fieldIndex("ftr_firma"));
    FTRmapper->addMapping(lE_tarih, FTRmodel->fieldIndex("ftr_tarih"));

}

///************************************************************
///****************  F A T U R A   S  L  O  T  S  ************




void Cw_ftr::slt_ftr_tV_rowchanged(const QModelIndex &index )
{
    qDebug() << "  slt_ftr_tV_rowchanged";
    if (index.isValid())
    {
        QSqlRecord record = FTRmodel->record(index.row());
        int fatura_no = record.value("ftr_no").toInt();

        //QString barkid = record.value("ftr_ftno").toString ();
        //lB_brkd->setText (barkid);

        /// giris cikisa filtre koyalım
        //QString flt = QString("fatura_no = %1").arg(fatura_no);
        mlzDETmodel->setFilter (QString("mlzmdet_gcno = %1").arg(fatura_no) );

    }
    else
    {
        mlzDETmodel->setFilter("mlzdet_gcno=-1");
    }
    mlzDETmodel->select();

}


void Cw_ftr::slt_dp_resimGoster(QModelIndex)
{
    qDebug() << "  slt_dp_resimGoster";
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

void Cw_ftr::slt_dp_pB_Eklersm_clicked()
{
    qDebug() << "  slt_dp_pB_Eklersm_clicked";
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

        QByteArray outByteArray = FTRtview->table->
                model()->index( row, FTRmodel->fieldIndex ("resim") ).data().toByteArray();
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



void Cw_ftr::slt_dp_updButtons(int row)
{
        qDebug() << "  slt_dp_updButtons";
    FTRtview->pB_ilk->setEnabled (row>0);
    FTRtview->pB_ncki->setEnabled(row > 0);
    FTRtview->pB_snrki->setEnabled(row < FTRmodel->rowCount() - 1);
    FTRtview->pB_son->setEnabled(row < FTRmodel->rowCount() - 1);
}

void Cw_ftr::slt_dp_toFirst()
{
    qDebug() << "  slt_dp_toFirst";
    FTRmapper->toFirst ();
    int map_row = FTRmapper->currentIndex ();
    FTRtview->pB_ilk->setEnabled (map_row>0);
    FTRtview->table->setCurrentIndex(FTRmodel->index( 0  ,0));
}

void Cw_ftr::slt_dp_toPrevious()
{
    qDebug() << " slt_dp_toPrevious";
    FTRmapper->toPrevious ();
    int map_row = FTRmapper->currentIndex ();
    FTRtview->pB_ncki->setEnabled(map_row > 0);
    FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));
}

void Cw_ftr::slt_dp_toNext()
{
    qDebug() << "  slt_dp_toNext";
    FTRmapper->toNext ();
    int map_row = FTRmapper->currentIndex ();
    FTRtview->pB_snrki->setEnabled(map_row < FTRmodel->rowCount() - 1);
    FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));

}

void Cw_ftr::slt_dp_toLast()
{
    qDebug() << "  slt_dp_toLast";
    FTRmapper->toLast ();
    int map_row = FTRmapper->currentIndex ();
    FTRtview->pB_son->setEnabled(map_row < FTRmodel->rowCount() - 1);
    FTRtview->table->setCurrentIndex(FTRmodel->index( FTRmodel->rowCount() - 1  ,0));
}

void Cw_ftr::slt_ftr_hesap()
{
    qDebug() << "ftr_hesappppppppppppppppppp";
    // QModelIndex indx_dpdet = FTRDETtview->currentIndex ();

    //int tpl_grs=0, tpl_cks=0;
    //int id_dp ;

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

        QSqlRecord fatura_rec = FTRmodel->record ();
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
                         "FROM dbtb_dpdet "
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
            //dp_rec.setValue ("cikis", q_qry.value(0).toDouble ());
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

    QModelIndex fatura_ndx = FTRtview->table->currentIndex ();
    qDebug() << "4.index set edildi dp_ndx 0 - "<<fatura_ndx;


    QSqlRecord rec = FTRmodel->record();

    rec.setValue ("ftr_tarih",QDate::currentDate ().toString ("dd.MM.yyyy"));

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
}

void Cw_ftr::slt_ftr_pB_SIL_clicked ()
{
    qDebug() << "  slt_ftr_pB_SIL_clicked";
    QSqlQuery q_qry;
    QString s_qry;
    QModelIndex sample =   FTRtview->table->currentIndex();
    if( sample.row() >= 0 )
    {
        QSqlRecord rec = FTRmodel->record(sample.row ());
        int fat_no = rec.value ("ftr_kod").toInt();
        QString val = rec.value("ftr_no").toString();
        QString val2= rec.value("ftr_firma").toString() ;


        /// depo detay kayıtlarını silelim
        /*      QSqlQuery q_qry;
        QString s_qry;
        /// silinecek kayıt sayısı
        s_qry = QString("SELECT count() FROM dbtb_dpdet where dp_no = %1").arg (dp_no);
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
                "İşlemi onaylarsanız bu fatura kaydına ait\n " ;

        int mlzdet_count = mlzDETmodel->rowCount () ;
        if ( mlzdet_count > 0 )
        {
            mess +="\n"+ QString::number (mlzdet_count) + " adet DEPO GİRİŞ - ÇIKIŞ kaydı";
        }


        mess +="\n1 adet FATURA DETAY kaydı silinecektir .! \n\n"
               "İŞLEMİ ONAYLIYORMUSUNUZ ?";


        /// model makina kaydı var
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox
                ::question(this,
                           "KAYIT SİL", mess,
                           QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            /// depoya ait depodet giriş kayıtlarını sil
            s_qry = QString("DELETE FROM mlzdet__dbtb "
                            "where mlzdet_kod = %1").arg (fat_no);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<<" - "<< mlzdet_count << " - adet Ftr Giriş_Çıkış Kaydı Silindi";
            }
            else
            {
                qDebug()<< "HATA - Ftr Giriş Kayıtları Silinemedi"
                        << q_qry.lastError() ;
            }

            /// depo ya ait makina ikmal kayıtlarını silelim
            ///
            /// burada makina ikmal kaydı varsa
            /// makina ikmale bağlı sgrt, muayene vb
            /// tüm kayıtlarıda silmek gerekir
            //int sil_makina_kayitlerini;


            /// depo kayıtlarını silelim
            s_qry = QString("DELETE FROM ftr_dbtb "
                            "where ftr_kod = %1").arg (fat_no);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< "1 adet Ftr Kaydı Silindi";
                FTRtview->setFocus ();
                FTRmodel->select ();



                if (FTRmodel->rowCount () == 1)
                {
                    FTRtview->table->selectRow (0);
                    FTRtview->setCurrentIndex (FTRmodel->index(0,0));
                }
                if (FTRmodel->rowCount () > 1)
                {
                    if (sample.row () == 0)
                    {
                        FTRtview->table->selectRow (0);
                        FTRtview->setCurrentIndex (FTRmodel->index(0,0));
                    }
                    else if (sample.row () > 0)
                    {
                        FTRtview->table->selectRow (sample.row()-1);
                        FTRtview->setCurrentIndex (FTRmodel->index(sample.row ()-1,0));
                    }


                }
                else
                {
                    qDebug()<< "HATA - Ftr Kaydı Silinemedi"
                            << q_qry.lastError() ;
                }
            }
            else
            {
                /// SİLME
                /// depoya ait depodet giriş kayıtlarını SİLinMEdi
            }
        }
    }
}


/*
void Cw_ftr::slt_dp_cX_grs_clicked()
{
        qDebug() << "  slt_dp_cX_grs_clicked";
    QIcon icon;
    if ( ! FTRtview->pB_grscks->isFlat ())
    {

        QModelIndex dp_indx = FTRtview->table->currentIndex ();
        slt_ftr_tV_rowchanged (dp_indx);
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
    (connect(FTRDETtview->pB_ekle, &QPushButton::clicked ,this ,
                     &Cw_ftr::slt_mlz_pB_EKLE_clicked  )) ;

    (connect(FTRDETtview->pB_sil, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dpd_pB_SIL_clicked )) ;
    (connect(FTRDETtview->pB_ilk, &QPushButton::clicked ,this ,
                     &Cw_ftr::slt_dpd_toFirst )) ;
    (connect(FTRDETtview->pB_ncki, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dpd_toPrevious )) ;
    (connect(FTRDETtview->pB_snrki, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dpd_toNext )) ;
    (connect(FTRDETtview->pB_son, &QPushButton::clicked,this ,
                     &Cw_ftr::slt_dpd_toLast )) ;
    FTRDETtview->pB_grscks->setVisible (false);




    QGridLayout *lYG_d_map = new QGridLayout();


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
    qDebug() << "  setup_modelFtrDet";
    QString tableName = "mlzmdet__dbtb";
    QStringList fieldList;

    fieldList.append("FTD Kod");
    fieldList.append("Malzeme Kod");
    fieldList.append("Barkod");
    fieldList.append("Malzeme Adı");
    fieldList.append("Tarih");
    fieldList.append("GC");
    fieldList.append("GCNo");
    fieldList.append("Miktar");
    fieldList.append("Birim");
    fieldList.append("Fiyat");
    fieldList.append("KDV %");
    fieldList.append("Açıklama");

    mlzDETmodel = new QSqlTableModel() ;


    mlzDETmodel->setTable(tableName);
    mlzDETmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    mlzDETmodel->setSort(2,Qt::AscendingOrder);

  //  qDebug () << tableName << "dosya adıııııııııııııııı "
    //          << mlzDETmodel->columnCount()<<" - fld size "<<fieldList.size ();
  //  for(int i = 1, j = 0; i < mlzDETmodel->columnCount()-1; i++, j++)
    for(int i = 0, j = 0; i < fieldList.size (); i++, j++)
    {
        mlzDETmodel->setHeaderData(i,Qt::Horizontal,
                                   fieldList[j]);
         qDebug () << fieldList[j];
    }

    // Populate the model
    if (!mlzDETmodel->select())
    {
        qDebug () << " HATA - Model faturadet select "
                  << mlzDETmodel->lastError();
    }
}

void Cw_ftr::setup_viewFtrDet()
{
    qDebug() << "  setup_viewFtrDet";

    FTRDETtview->table->setModel(mlzDETmodel);
    // Hide the column id Records
    //// kullanıcı bu alanları görmesin
    FTRDETtview->table->setColumnHidden(mlzDETmodel->fieldIndex("mlzmdet_kod"), true);
    FTRDETtview->table->setColumnHidden(mlzDETmodel->fieldIndex("mlzmdet_mlzm_kod"), true);
    FTRDETtview->table->setColumnHidden(mlzDETmodel->fieldIndex("mlzmdet_tarih"), true);
    FTRDETtview->table->setColumnHidden(mlzDETmodel->fieldIndex("mlzmdet_gc"), true);
    FTRDETtview->table->setColumnHidden(mlzDETmodel->fieldIndex("mlzmdet_gcno"), true);

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

    // FTRDETtview->table->setCurrentIndex (mlzDETmodel->index (0,0));
    // mlzDETmodel->select ();
}

void Cw_ftr::setup_mapFtrDet()
{
    qDebug() << "  setup_mapFtrDet";
    FTRDETmapper = new QDataWidgetMapper(this);
    FTRDETmapper->setModel(mlzDETmodel);

    //FTRDETmapper->addMapping(lE_d_faturano , mlzDETmodel->fieldIndex("faturano"));
    //FTRDETmapper->addMapping(lE_d_firma, mlzDETmodel->fieldIndex("firma"));
    FTRDETmapper->addMapping(lE_mlzdetbarkod, mlzDETmodel->fieldIndex("mlzmdet_barkod"));
    FTRDETmapper->addMapping(lE_mlzdetmlzm, mlzDETmodel->fieldIndex("mlzmdet_malzeme"));
    FTRDETmapper->addMapping(lE_mlzdetmiktar, mlzDETmodel->fieldIndex("mlzmdet_miktar"));
    FTRDETmapper->addMapping(lE_mlzdetbirim, mlzDETmodel->fieldIndex("mlzmdet_birim"));
    FTRDETmapper->addMapping(lE_mlzdetfiyat, mlzDETmodel->fieldIndex("mlzmdet_fiyat"));
    FTRDETmapper->addMapping(lE_mlzdetkdv, mlzDETmodel->fieldIndex("mlzmdet_kdv"));
    FTRDETmapper->addMapping(lE_mlzdetaciklama, mlzDETmodel->fieldIndex("mlzmdet_aciklama"));
}


///************************************************************
///****************  F A T U R A  D  E  T  A  Y  ************
///*******                 S  L  O  T  S           ************
///
///




void Cw_ftr::slt_dpd_updButtons(int row)
{
    qDebug() << "  slt_dpd_updButtons";
    FTRDETtview->pB_ilk->setEnabled (row>0);
    FTRDETtview->pB_ncki->setEnabled(row > 0);
    FTRDETtview->pB_snrki->setEnabled(row < mlzDETmodel->rowCount() - 1);
    FTRDETtview->pB_son->setEnabled(row < mlzDETmodel->rowCount() - 1);
}


void Cw_ftr::slt_dpd_toFirst()
{
    qDebug() << "  slt_dpd_toFirst";
    QDataWidgetMapper *x=FTRDETmapper;
    x->toFirst ();

    int map_row = FTRDETmapper->currentIndex ();
    FTRDETtview->pB_ilk->setEnabled (map_row>0);
    FTRDETtview->table->setCurrentIndex(mlzDETmodel->index( 0  ,0));
}

void Cw_ftr::slt_dpd_toPrevious()
{
    qDebug() << "  slt_dpd_toPrevious";
    FTRDETmapper->toPrevious ();
    int map_row = FTRDETmapper->currentIndex ();
    FTRDETtview->pB_ncki->setEnabled(map_row > 0);
    FTRDETtview->table->setCurrentIndex(mlzDETmodel->index( map_row  ,0));
}

void Cw_ftr::slt_dpd_toNext()
{
    qDebug() << "  slt_dpd_toNext";
    FTRDETmapper->toNext ();
    int map_row = FTRDETmapper->currentIndex ();
    FTRDETtview->pB_snrki->setEnabled(map_row < mlzDETmodel->rowCount() - 1);
    FTRDETtview->table->setCurrentIndex(mlzDETmodel->index( map_row  ,0));
}

void Cw_ftr::slt_dpd_toLast()
{
    qDebug() << "  slt_dpd_toLast";
    FTRDETmapper->toLast ();
    int map_row = FTRDETmapper->currentIndex ();
    FTRDETtview->pB_son->setEnabled(map_row < mlzDETmodel->rowCount() - 1);
    FTRDETtview->table->setCurrentIndex(mlzDETmodel->index( mlzDETmodel->rowCount() - 1  ,0));
}





/// Fatura detayına malzeme ekle
void Cw_ftr::slt_mlz_pB_EKLE_clicked ()
{

    qDebug() << "  slt_mlz_pB_EKLE_clicked";
    //FTRtview->table->setFocus ();


    QModelIndex ftr_indx = FTRtview->table->currentIndex () ;
    if ( ftr_indx.row () >= 0 )
    {
        int ftr_row = ftr_indx.row ();

        /// kayıt içerisinde belirli bir
        /// field in içeriğini değişkene at

        QString gcno = FTRmodel->
                data ( FTRmodel->
                       index(ftr_row,FTRmodel->
                             fieldIndex("ftr_no"))).toString() ;

        QSqlQuery q;
        QString s_q;
        s_q ="INSERT INTO mlzmdet__dbtb "
             "( mlzmdet_gc, mlzmdet_gcno )"
             " values( ?,?)"  ;
        q.prepare(s_q);

        q.bindValue(0, "Faturalı Giriş" );
        q.bindValue(1, gcno );
        q.exec();
        //qDebug () << q.lastError();
        if (q.isActive())
        {

 //           Hata hata("İş Emri Yeni Kayıt",
   //                   "Yeni İş Emri Kaydı Eklendi","" );

            qDebug () <<"Fatura Detay Yeni Kayıt Eklendi - "<< gcno << " -   Eklendi";
            //mppMKN->toLast;

FTRDETtview->table->setFocus ();
mlzDETmodel->select ();
        }
        else
        {
            qDebug () << "Fatura Detay Yeni Kayıt Eklenemedi - " << q.lastError() ;
        }







     /*   /// depodet den yeni boş bir record al = dp_rec
        QSqlRecord mlzdet_rec = mlzDETmodel->record ();
        /// rec in içerisinde istediğin fieldleri doldur
        mlzdet_rec.setValue ("mlzmdet_gcno",gcno);

        // insert a new record (-1) with new data
        if ( ! mlzDETmodel->insertRecord(-1,mlzdet_rec))
        {
            qDebug() << "HATA - kayıt fatura DETAY a eklenemedi ";
        }
        else /// dpdet_rec detaya eklendi
        {
            qDebug() << "OK - kayıt fatura DETAY a eklendi ";
            mlzDETmodel->submitAll ();
            mlzDETmodel->select();
        }*/
    }
    else /// tVdepo row yok - dp_indx.row () < 0
    {
        qDebug()<<"HATA - Ftr Ekleme .row yokk ";
    }
}



void Cw_ftr::slt_dpd_pB_SIL_clicked ()
{
    qDebug() << "  slt_dpd_pB_SIL_clicked";
    QModelIndex sample =   FTRDETtview->table->currentIndex();
    if( sample.row() >= 0 )
    {
        QSqlRecord rec = mlzDETmodel->record();

        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;

        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,// + "\n faturanoli personelin kaydı silinsin mi? ?" ,
                                    QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            mlzDETmodel->removeRow(sample.row());
            mlzDETmodel->submitAll ();
            //pmodel->endRemoveColumns();
            mlzDETmodel->select ();
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
