#include "cw_ambar.h"
#include "cw_ftr.h"
#include "globals.h"
#include "hc_tableview.h"
#include "mw_main.h"

Cw_Ambar::Cw_Ambar(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "AMBAR";

    //*****************************************************
    //*****************  A M B A R ************************

    setup_uiAmbar();

    setup_modelAmbar();
    setup_viewAmbar();
    // setup_mapAmbar();

    //setup_modelAmbardet();
    // setup_viewAmbardet();
    //aa  setup_mapAmbardet();

    /// Ambar map nav tuslari kontrol
    //   connect(AMBARmapper, &QDataWidgetMapper::currentIndexChanged,
    //                   this, &Cw_Ambar::slt_Ambar_updButtons);
    /// Ambar da kolon değiştiğinde indexte değişsin
    //  ( connect(  AMBARtview->table->selectionModel(),
    //                    SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //                  AMBARmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    // ( connect(  AMBARtview->table->selectionModel(),
    //                   SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //                 cw_mkn, SLOT( onMKNtview_resimGosterSLOT(QModelIndex))));

    /// Ambar da row değiştiğinde indexte değişsin
    /*  connect(  AMBARtview->table->selectionModel(),
         &QItemSelectionModel::currentRowChanged, AMBARmapper,
         &QDataWidgetMapper::setCurrentModelIndex);
*/
    /// row değiştiğnde resmide değiştirelim
    /*    connect( AMBARtview->table->selectionModel (),
         &QItemSelectionModel::currentRowChanged, this,
         &Cw_Ambar::slt_Ambar_resimGoster );
*/
    /// Ambardet miktar değiştiğinde Ambar envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished, this,
    //                   &Cw_Ambar::slt_Ambar_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    //  connect(AMBARDETtview->table->model() ,
    //        &QSqlTableModel::dataChanged , this,
    //      &Cw_Ambar::slt_Ambar_hesap);


    /// Ambardet grs_cks değiştiğinde Ambar envanter hesabı
    //   (connect (cbx_d_grs_cks, &QComboBox::editTextChanged , this,
    //                   &Cw_Ambar::slt_Ambar_hesap));

    /// Ambar ilk kayıda
    //  Cw_Ambar::slt_Ambar_toFirst();

    /// Ambarda row değiştiğinde
    //    Cw_Ambar::slt_Ambar_tV_rowchanged (AMBARmodel->index (0,0));

    /*
    /// Ambardet map değiştiğinde nav tuşalrı ayarlansın
    connect(AMBARDETmapper,
              &QDataWidgetMapper::currentIndexChanged, this,
              &Cw_Ambar::slt_Ambard_updButtons);

    /// Ambardet table da koon değiştiğnde index değişsin
    connect(  AMBARDETtview->table->selectionModel(),
              &QItemSelectionModel::currentRowChanged, AMBARDETmapper,
              &QDataWidgetMapper::setCurrentModelIndex);
*/
    ///Ambarda row değiştiğinde
    /*   connect (AMBARtview->table->selectionModel (),
             &QItemSelectionModel::currentRowChanged, this,
             &Cw_Ambar::slt_Ambar_tV_rowchanged);
*/
    /// Ambardetay varsa ilk kayda
    //   Cw_Ambar::slt_Ambard_toFirst(); // detay ilk kayıda
    AMBARtview->table->setFocus ();
}



void Cw_Ambar::slt_pB_ambar_grs_clicked()
{
    /// ambar girişi tıklandı
    ///
    ///
    qDebug () << "Ambar Giriş";



    wdgt_mapAmbar = new QWidget;
    wdgt_mapAmbar->setGeometry (0,0,100,300);

    LyG_Ambar = new QGridLayout();
    wdgt_mapAmbar->setLayout(LyG_Ambar);


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


    QLabel *lB_gt = new QLabel(tr("Malzeme Giriş Tipi"));
    QComboBox *cbx_grs_tipi =new QComboBox;
    cbx_grs_tipi->addItems ({"Faturalı Giriş",
                             "Envanter Giriş",
                             "Hibe Giriş"});
    QLabel *lB_1 = new QLabel("Fatura No");
    QLabel *lB_2 = new QLabel("Firma");
    connect( cbx_grs_tipi, QOverload<int>::of(
                 &QComboBox::currentIndexChanged),
             [=](int index){
        if ( index == 0 )
        {
            lB_1->setText ("Fatura No:");
            lB_2->setText ("Firma");
        }

        if ( index  == 1 )
        {

            lB_1->setText ("Envanter Belge No");
            lB_2->setText ("Depo");
        }

        if ( index  == 2 )
        {
            lB_1->setText ("Hibe Belge No");
            lB_2->setText ("Kurum");
        }
    });


    ///////////////////////////////////////  mapper buttonz
    lB_mlzrsm = new QLabel(wdgt_mapAmbar);
    lB_mlzrsm->setFixedSize (200,150);

    int str = 0;

    LyG_Ambar ->addWidget(lB_gt       , str, 0, 1, 1);
    LyG_Ambar ->addWidget(cbx_grs_tipi, str, 1, 1, 1);

    //QLabel *lB_gt2 = new QLabel(tr("fatura"));

    LyG_Ambar ->addWidget(lB_1   , ++str, 0, 1, 1);

    LyG_Ambar ->addWidget(lB_2   , ++str, 1, 1, 1);

    ++str;
    LyG_Ambar ->addWidget(lB_barkod   , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget(lE_barkod   , str , 1, 1, 1);
    LyG_Ambar ->addWidget(lB_brkd     , ++str, 1, 1, 1);
    LyG_Ambar ->addWidget(lB_malzeme  , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget(lE_malzeme  , str, 1, 1, 1);

    LyG_Ambar ->addWidget(lB_marka   , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget(lE_marka   , str, 1, 1, 1);

    LyG_Ambar ->addWidget(lB_aciklama, ++str, 0, 1, 1);
    LyG_Ambar ->addWidget(lE_aciklama, str, 1, 1, 1);
    LyG_Ambar ->addWidget(lB_model   , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget(lE_model   , str, 1, 1, 1);

    LyG_Ambar ->addWidget (lB_cins    , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget (lE_cins    , str, 1, 1, 1);
    LyG_Ambar ->addWidget (lB_birim   , ++str, 0, 1, 1);
    LyG_Ambar ->addWidget (cbx_birim   , str, 1, 1, 1);
    LyG_Ambar ->addWidget (lB_mlzrsm  , ++str, 1, 5, 1);
    wdgt_mapAmbar->show ();




}






void Cw_Ambar::slt_pB_ambar_cks_clicked()
{
    /// ambar çıkışı tıklandı
    ///
    ///
    qDebug () << "Ambar Çıkışı";




}







void Cw_Ambar::setup_uiAmbar()
{
    qDebug() << "  setup_uiAmbar";
    /////////////////////////////////////////////// buttonz
    QHBoxLayout *LyG_Ambargc = new QHBoxLayout();
    QPushButton *pB_ambar_grs = new QPushButton("Ambar &Giriş");
    connect(pB_ambar_grs, &QPushButton::clicked, this,
            &Cw_Ambar::slt_pB_ambar_grs_clicked );

    QPushButton *pB_ambar_cks = new QPushButton("Ambar &Çıkış");
    LyG_Ambargc->addWidget (pB_ambar_grs);
    LyG_Ambargc->addWidget (pB_ambar_cks);


    //////////////////////////////////// Ambar tableview
    int i=1;
    AMBARtview = new HC_TableView(i);

    ////////////////////////////////////////////// layout
    QGridLayout *LyG_Ambar = new QGridLayout(this);
    LyG_Ambar->addWidget (AMBARtview  , 0, 0);
    LyG_Ambar->addLayout ( LyG_Ambargc, 1, 0);

    ////////////////////////////////////////// widgets
    //    wd_Ambar();
    //   wd_Ambardet();



}



void Cw_Ambar::setup_modelAmbar()
{
    qDebug() << "  setup_modelAmbar";
    QString tableName = "mlzm__dbtb";
    QStringList fieldList;

    fieldList.append("Barkod");
    fieldList.append("Malzeme");
    fieldList.append("Açıklama");
    fieldList.append("Marka");
    fieldList.append("Model");
    fieldList.append("Cins");
    fieldList.append("Birim");

    AMBARmodel = new QSqlTableModel();
    AMBARmodel->setTable(tableName);
    AMBARmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    AMBARmodel->setSort(AMBARmodel->fieldIndex ("mlzm_malzeme"),Qt::AscendingOrder );
    for(int i = 1, j = 0; i < AMBARmodel->columnCount()-5; i++, j++)
    {
        AMBARmodel->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }
    // Populate the model_mkstok
    if (!AMBARmodel->select())
    {
        qDebug () <<  " HATA - Model Ambar select "
                   <<AMBARmodel->lastError();
    }
}


void Cw_Ambar::setup_viewAmbar()
{

    qDebug() << "  setup_viewAmbar";

    AMBARtview->table->setModel(AMBARmodel);
    AMBARtview->table->resizeColumnsToContents();
    AMBARtview->table->resizeRowsToContents ();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///
    tV_Ambar_selectionMdl = new QItemSelectionModel(AMBARmodel);
    AMBARtview->table->setSelectionModel (tV_Ambar_selectionMdl);

    AMBARtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    AMBARtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //// kullanıcı bu alanları görmesin
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_kod"), true);
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_giris"), true);
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_cikis"), true);
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_mevcut"), true);
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_resim"), true);
    AMBARtview->table->setColumnHidden(AMBARmodel->fieldIndex("mlzm_makina"), true);

    AMBARtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    AMBARtview->table->horizontalHeader()->setStretchLastSection(true);
    AMBARtview->table->horizontalHeader()->resizeContentsPrecision();

    ///// tableview kontrol connectleri
    ///
    ///
    ///
    (connect(AMBARtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_Ambar::slt_Ambar_pB_EKLE_clicked  )) ;
    (connect(AMBARtview->pB_eklersm, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambar_pB_Eklersm_clicked  )) ;

    (connect(AMBARtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambar_pB_SIL_clicked )) ;
    (connect(AMBARtview->pB_ilk, &QPushButton::clicked ,this ,
             &Cw_Ambar::slt_Ambar_toFirst )) ;
    (connect(AMBARtview->pB_ncki, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambar_toPrevious )) ;
    (connect(AMBARtview->pB_snrki, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambar_toNext )) ;
    (connect(AMBARtview->pB_son, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambar_toLast )) ;

    // AMBARtview->pB_grscks->setVisible (false);
    // (connect(AMBARtview->pB_grscks, &QPushButton::clicked,this ,
    //                &Cw_Ambar::slt_Ambar_cX_grs_clicked  )) ;


}

void Cw_Ambar::setup_mapAmbar()
{
    qDebug() << "  setup_mapAmbar";
    AMBARmapper = new QDataWidgetMapper(this);
    AMBARmapper->setModel(AMBARmodel);

    AMBARmapper->addMapping(lE_barkod , AMBARmodel->fieldIndex("mlzm_barkod"));
    AMBARmapper->addMapping(lE_malzeme, AMBARmodel->fieldIndex("mlzm_malzeme"));
    AMBARmapper->addMapping(lE_aciklama, AMBARmodel->fieldIndex("mlzm_aciklama"));
    AMBARmapper->addMapping(lE_marka, AMBARmodel->fieldIndex("mlzm_marka"));
    AMBARmapper->addMapping(lE_model, AMBARmodel->fieldIndex("mlzm_model"));
    AMBARmapper->addMapping(lE_cins, AMBARmodel->fieldIndex("mlzm_cins"));
    AMBARmapper->addMapping(cbx_birim, AMBARmodel->fieldIndex("mlzm_birim"));
    //AMBARmapper->addMapping( lE_giris, AMBARmodel->fieldIndex("giris"));
    //AMBARmapper->addMapping( lE_cikis, AMBARmodel->fieldIndex("cikis"));
    //AMBARmapper->addMapping( lE_mevcut, AMBARmodel->fieldIndex("mevcut"));
    //AMBARmapper->addMapping( cX_mkn, AMBARmodel->fieldIndex("makina"));

}

///************************************************************
///****************  D  E  P  O     S  L  O  T  S  ************




void Cw_Ambar::slt_Ambar_tV_rowchanged(const QModelIndex &index )
{
    qDebug() << "  slt_Ambar_tV_rowchanged";
    if (index.isValid())
    {
        QSqlRecord record = AMBARmodel->record(index.row());
        int Ambar_no = record.value("mlzm_kod").toInt();

        QString barkid = record.value("mlzm_barkod").toString ();
        lB_brkd->setText (barkid);

        /// giris cikisa filtre koyalım
        QString flt = QString("mlzm_kod = %1").arg(Ambar_no);
        AMBARDETmodel->setFilter (QString("mlzm_kod = %1").arg(Ambar_no) );

    }
    else
    {
        AMBARDETmodel->setFilter("mlzm_kod=-1");
    }
    AMBARDETmodel->select();

}


void Cw_Ambar::slt_Ambar_resimGoster(QModelIndex)
{
    qDebug() << "  slt_Ambar_resimGoster";
    // makina stok tablosundan resim gösterme
    // view row unu tespit et
    int rowidx = AMBARtview->table->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = AMBARtview->table->
            model()->index( rowidx, AMBARmodel->fieldIndex ("mlzm_resim") ).data().toByteArray();

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

void Cw_Ambar::slt_Ambar_pB_Eklersm_clicked()
{
    qDebug() << "  slt_Ambar_pB_Eklersm_clicked";
    // Ambar resim ekle
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
        QModelIndex index = AMBARtview->table->currentIndex();
        int row = index.row() ;

        /// resmi değiştirelim
        AMBARmodel->setData(AMBARmodel->
                            index(row, AMBARmodel->
                                  fieldIndex ("mlzm_resim")),inByteArray);
        /// yeni eklenenleri kaydedelim
        AMBARmodel->submitAll();
        AMBARmodel->select ();

    }
}       ///     onpb_resimEkleSLOT



void Cw_Ambar::slt_Ambar_updButtons(int row)
{
    qDebug() << "  slt_Ambar_updButtons";
    AMBARtview->pB_ilk->setEnabled (row>0);
    AMBARtview->pB_ncki->setEnabled(row > 0);
    AMBARtview->pB_snrki->setEnabled(row < AMBARmodel->rowCount() - 1);
    AMBARtview->pB_son->setEnabled(row < AMBARmodel->rowCount() - 1);
}

void Cw_Ambar::slt_Ambar_toFirst()
{
    qDebug() << "  slt_Ambar_toFirst";
    AMBARmapper->toFirst ();
    int map_row = AMBARmapper->currentIndex ();
    AMBARtview->pB_ilk->setEnabled (map_row>0);
    AMBARtview->table->setCurrentIndex(AMBARmodel->index( 0  ,0));
}

void Cw_Ambar::slt_Ambar_toPrevious()
{
    qDebug() << " slt_Ambar_toPrevious";
    AMBARmapper->toPrevious ();
    int map_row = AMBARmapper->currentIndex ();
    AMBARtview->pB_ncki->setEnabled(map_row > 0);
    AMBARtview->table->setCurrentIndex(AMBARmodel->index( map_row  ,0));
}

void Cw_Ambar::slt_Ambar_toNext()
{
    qDebug() << "  slt_Ambar_toNext";
    AMBARmapper->toNext ();
    int map_row = AMBARmapper->currentIndex ();
    AMBARtview->pB_snrki->setEnabled(map_row < AMBARmodel->rowCount() - 1);
    AMBARtview->table->setCurrentIndex(AMBARmodel->index( map_row  ,0));

}

void Cw_Ambar::slt_Ambar_toLast()
{
    qDebug() << "  slt_Ambar_toLast";
    AMBARmapper->toLast ();
    int map_row = AMBARmapper->currentIndex ();
    AMBARtview->pB_son->setEnabled(map_row < AMBARmodel->rowCount() - 1);
    AMBARtview->table->setCurrentIndex(AMBARmodel->index( AMBARmodel->rowCount() - 1  ,0));
}

void Cw_Ambar::slt_Ambar_hesap()
{
    qDebug() << "Ambar_hesappppppppppppppppppp";
    // QModelIndex indx_Ambardet = AMBARDETtview->currentIndex ();

    //int tpl_grs=0, tpl_cks=0;
    //int id_Ambar ;

    QModelIndex Ambar_indx = AMBARtview->table->currentIndex ();
    if ( Ambar_indx.row () >= 0 )
    {
        int Ambar_row = Ambar_indx.row ();
        int id = AMBARmodel->
                data ( AMBARmodel->
                       index(Ambar_row,AMBARmodel->
                             fieldIndex("mlzm_kod"))).toInt () ;

        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM mlzmDet_dbtb "
                         "WHERE mlzmDet_kod= %1 AND mlzmDet_gc='Giriş'").arg(id);
        q_qry.exec (s_qry);

        QSqlRecord Ambar_rec = AMBARmodel->record ();
        double grs=0,cks=0;
        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            AMBARmodel->setData(AMBARmodel->index(Ambar_row, AMBARmodel->
                                                  fieldIndex ("giris")), grs);


            //Ambar_rec.setValue ("giris", q_qry.value(0).toDouble ());
            qDebug()<<"toplam giriş data    "<<q_qry.value(0);

        }
        s_qry = QString ("SELECT TOTAL(miktar) "
                         "FROM dbtb_Ambardet "
                         "WHERE mlzmDet_kod= %1 AND mlzmDet_gc='Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            AMBARmodel->setData(AMBARmodel->
                                index(Ambar_row, AMBARmodel->
                                      fieldIndex ("mlzdet_cikis")),
                                cks);

            qDebug()<<"toplam çıkış data    "<<q_qry.value(0);
            //Ambar_rec.setValue ("cikis", q_qry.value(0).toDouble ());
        }

        AMBARmodel->setData(AMBARmodel->
                            index(Ambar_row, AMBARmodel->fieldIndex ("mevcut")), grs-cks);
        AMBARmodel->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
}

void Cw_Ambar::slt_Ambar_pB_EKLE_clicked ()
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

    QGroupBox *ft = new QGroupBox("Ambar Malzeme Giriş Tipi",dia);
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
            dia->close ();
        });
    dia->show ();
}

    /*    ambarda tek kayıt ekleme

    QModelIndex Ambar_ndx0=AMBARtview->table->currentIndex ();
    qDebug() << "4.index set edildi Ambar_ndx 0 - "<<Ambar_ndx0;

    QSqlRecord rec = AMBARmodel->record();
    rec.setValue ("mlzm_makina","0");
    rec.setValue ("mlzm_barkod","123");
    // insert a new record (-1)

    if ( ! AMBARmodel->insertRecord(AMBARmodel->rowCount (),rec))
    {
        qDebug() << " HATA - DEPO ya kayıt eklenemedi ";
    }
    else
    {
        qDebug() << " - Kayıt DEPO ya eklendi ";
        AMBARmodel->submitAll ();
        AMBARmodel->select ();
        QModelIndex Ambar_ndx= AMBARmodel->index (AMBARmodel->rowCount ()-1,0);
        AMBARtview->table->selectRow (Ambar_ndx.row ());

        //wdgt_mapAmbar->show ();
    }
    */


void Cw_Ambar::slt_Ambar_pB_SIL_clicked ()
{
    qDebug() << "  slt_Ambar_pB_SIL_clicked";
    QSqlQuery q_qry;
    QString s_qry;
    QModelIndex sample =   AMBARtview->table->currentIndex();
    if( sample.row() >= 0 )
    {
        QSqlRecord rec = AMBARmodel->record(sample.row ());
        int Ambar_no = rec.value ("mlzm_kod").toInt();
        QString val = rec.value("mlzm_barkod").toString();
        QString val2= rec.value("mlzm_malzeme").toString() ;


        /// Ambar detay kayıtlarını silelim
        /*      QSqlQuery q_qry;
        QString s_qry;
        /// silinecek kayıt sayısı
        s_qry = QString("SELECT count() FROM dbtb_Ambardet where Ambar_no = %1").arg (Ambar_no);
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
                "İşlemi onaylarsanız bu Ambar kaydına ait\n " ;

        int Ambardet_count = AMBARDETmodel->rowCount () ;
        if ( Ambardet_count > 0 )
        {
            mess +="\n"+ QString::number (Ambardet_count) + " adet DEPO GİRİŞ - ÇIKIŞ kaydı";
        }


        /// model makina kaydı var
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox
                ::question(this,
                           "KAYIT SİL", mess,
                           QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            /// Ambarya ait Ambardet giriş kayıtlarını sil
            s_qry = QString("DELETE FROM mlzmDet__dbtb where mlzmDet_mlzm_kod = %1").arg (Ambar_no);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<<" - "<< Ambardet_count << " - adet Ambar Giriş_Çıkış Kaydı Silindi";
            }
            else
            {
                qDebug()<< "HATA - Ambar Giriş Kayıtları Silinemedi"
                        << q_qry.lastError() ;
            }

            /// Ambar ya ait makina ikmal kayıtlarını silelim
            ///
            /// burada makina ikmal kaydı varsa
            /// makina ikmale bağlı sgrt, muayene vb
            /// tüm kayıtlarıda silmek gerekir
            //  int sil_makina_kayitlerini;


            /// Ambar kayıtlarını silelim
            s_qry = QString("DELETE FROM mlzm__dbtb where mlzm_kod = %1").arg (Ambar_no);
            q_qry.exec(s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< "1 adet Ambar Kaydı Silindi";
                AMBARtview->setFocus ();
                AMBARmodel->select ();



                if (AMBARmodel->rowCount () == 1)
                {
                    AMBARtview->table->selectRow (0);
                    AMBARtview->setCurrentIndex (AMBARmodel->index(0,0));
                }
                if (AMBARmodel->rowCount () > 1)
                {
                    if (sample.row () == 0)
                    {
                        AMBARtview->table->selectRow (0);
                        AMBARtview->setCurrentIndex (AMBARmodel->index(0,0));
                    }
                    else if (sample.row () > 0)
                    {
                        AMBARtview->table->selectRow (sample.row()-1);
                        AMBARtview->setCurrentIndex (AMBARmodel->index(sample.row ()-1,0));
                    }


                }
                else
                {
                    qDebug()<< "HATA - Ambar Kaydı Silinemedi"
                            << q_qry.lastError() ;
                }
            }
            else
            {
                /// SİLME
                /// Ambarya ait Ambardet giriş kayıtlarını SİLinMEdi
            }
        }
    }
}


void Cw_Ambar::slt_Ambar_cX_grs_clicked()
{
    qDebug() << "  slt_Ambar_cX_grs_clicked";
    QIcon icon;
    if ( ! AMBARtview->pB_grscks->isFlat ())
    {

        QModelIndex Ambar_indx = AMBARtview->table->currentIndex ();
        slt_Ambar_tV_rowchanged (Ambar_indx);
        AMBARtview->pB_grscks->setFlat (true);
        icon.addPixmap(QPixmap (":/rsm/nv_eklesil.svg") ,
                       QIcon::Normal, QIcon::On);
        AMBARtview->pB_grscks->setIcon (icon);
        wdgt_mapAmbar_dty->show ();
    }
    else
    {
        AMBARtview->pB_grscks->setFlat (false);
        icon.addPixmap(QPixmap (":/rsm/nv_eklesil2.svg") ,
                       QIcon::Normal, QIcon::On);
        AMBARtview->pB_grscks->setIcon (icon);
        wdgt_mapAmbar_dty->hide ();
    }
}







///************************************************************
///****************  D  E  P  O     D  E  T  A  Y  ************
///
///
///

void Cw_Ambar::wd_Ambardet()
{
    qDebug() << "  wd_Ambardet";
    lB_Ambardet = new QLabel("Malzeme Ambar Giriş - Çıkış İşlemleri");

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

    //////////////////////////////////// Ambardet tableview
    int i= 1;
    AMBARDETtview = new HC_TableView(i);
    (connect(AMBARDETtview->pB_ekle, &QPushButton::clicked ,this ,
             &Cw_Ambar::slt_Ambard_pB_EKLE_clicked  )) ;

    (connect(AMBARDETtview->pB_sil, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambard_pB_SIL_clicked )) ;
    (connect(AMBARDETtview->pB_ilk, &QPushButton::clicked ,this ,
             &Cw_Ambar::slt_Ambard_toFirst )) ;
    (connect(AMBARDETtview->pB_ncki, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambard_toPrevious )) ;
    (connect(AMBARDETtview->pB_snrki, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambard_toNext )) ;
    (connect(AMBARDETtview->pB_son, &QPushButton::clicked,this ,
             &Cw_Ambar::slt_Ambard_toLast )) ;
    AMBARDETtview->pB_grscks->setVisible (false);




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



    LyG_Ambar_dty = new QGridLayout( );

    LyG_Ambar_dty->addWidget (lB_Ambardet  , 0, 0, 1, 1);
    LyG_Ambar_dty->addLayout (lYG_d_map   , 2, 0, 1, 1);

    wdgt_mapAmbar_dty = new QWidget;
    wdgt_mapAmbar_dty->setLayout(LyG_Ambar_dty);


}










///////////////////////////////////////////  end setup view

void Cw_Ambar::setup_modelAmbardet()
{
    qDebug() << "  setup_ambardet";
    QString tableName = "mlzmDet__dbtb";
    QStringList fieldList;

    fieldList.append("Tarih");
    fieldList.append("G-Ç");
    fieldList.append("Miktar");
    fieldList.append("Fiyat");
    fieldList.append("Açıklama");

    AMBARDETmodel = new QSqlTableModel() ;
    AMBARDETmodel->setTable(tableName);
    AMBARDETmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    AMBARDETmodel->setSort(2,Qt::AscendingOrder);

    for(int i = 4, j = 0; i < AMBARDETmodel->columnCount()-4; i++, j++)
    {
        AMBARDETmodel->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }

    // Populate the model
    if (!AMBARDETmodel->select())
    {
        qDebug () << " HATA - Model Ambardet select "
                  << AMBARDETmodel->lastError();
    }
}

void Cw_Ambar::setup_viewAmbardet()
{
    qDebug() << "  setup_viewAmbardet";

    AMBARDETtview->table->setModel(AMBARDETmodel);
    // Hide the column id Records
    //// kullanıcı bu alanları görmesin
    AMBARDETtview->table->setColumnHidden(AMBARDETmodel->fieldIndex("id_Ambardet"), true);
    AMBARDETtview->table->setColumnHidden(AMBARDETmodel->fieldIndex("Ambar_no"), true);
    AMBARDETtview->table->setColumnHidden(AMBARDETmodel->fieldIndex("barkod"), true);
    AMBARDETtview->table->setColumnHidden(AMBARDETmodel->fieldIndex("malzeme"), true);

    // Allow the selection of lines
    AMBARDETtview->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    AMBARDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    AMBARDETtview->table->resizeRowsToContents ();
    AMBARDETtview->table->resizeColumnsToContents();
    // AMBARDETtview->table->setStyleSheet ("background-color: darkgreen;"
    //                         "color : yellow;");
    AMBARDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    AMBARDETtview->table->horizontalHeader()->
            setStretchLastSection(true);
    AMBARDETtview->table->horizontalHeader()->
            resizeContentsPrecision();

    // AMBARDETtview->table->setCurrentIndex (AMBARDETmodel->index (0,0));
    // AMBARDETmodel->select ();
}

void Cw_Ambar::setup_mapAmbardet()
{
    qDebug() << "  setup_mapAmbardet";
    AMBARDETmapper = new QDataWidgetMapper(this);
    AMBARDETmapper->setModel(AMBARDETmodel);

    //AMBARDETmapper->addMapping(lE_d_barkod , AMBARDETmodel->fieldIndex("barkod"));
    //AMBARDETmapper->addMapping(lE_d_malzeme, AMBARDETmodel->fieldIndex("malzeme"));
    AMBARDETmapper->addMapping(lE_d_tarih, AMBARDETmodel->fieldIndex("mlzmDet_tarih"));
    AMBARDETmapper->addMapping(cbx_d_grs_cks, AMBARDETmodel->fieldIndex("mlzmDet_gc"));
    AMBARDETmapper->addMapping(lE_d_miktar, AMBARDETmodel->fieldIndex("mlzmDet_miktar"));
    AMBARDETmapper->addMapping(lE_d_fiyat, AMBARDETmodel->fieldIndex("mlzmDet_fiyat"));
    AMBARDETmapper->addMapping(lE_d_aciklama, AMBARDETmodel->fieldIndex("mlzmDet_aciklama"));

}

///************************************************************
///****************  D  E  P  O     D  E  T  A  Y  ************
///*******                 S  L  O  T  S           ************
///
///







void Cw_Ambar::slt_Ambard_updButtons(int row)
{
    qDebug() << "  slt_Ambard_updButtons";
    AMBARDETtview->pB_ilk->setEnabled (row>0);
    AMBARDETtview->pB_ncki->setEnabled(row > 0);
    AMBARDETtview->pB_snrki->setEnabled(row < AMBARDETmodel->rowCount() - 1);
    AMBARDETtview->pB_son->setEnabled(row < AMBARDETmodel->rowCount() - 1);
}


void Cw_Ambar::slt_Ambard_toFirst()
{
    qDebug() << "  slt_Ambard_toFirst";
    QDataWidgetMapper *x=AMBARDETmapper;
    x->toFirst ();

    int map_row = AMBARDETmapper->currentIndex ();
    AMBARDETtview->pB_ilk->setEnabled (map_row>0);
    AMBARDETtview->table->setCurrentIndex(AMBARDETmodel->index( 0  ,0));
}

void Cw_Ambar::slt_Ambard_toPrevious()
{
    qDebug() << "  slt_Ambard_toPrevious";
    AMBARDETmapper->toPrevious ();
    int map_row = AMBARDETmapper->currentIndex ();
    AMBARDETtview->pB_ncki->setEnabled(map_row > 0);
    AMBARDETtview->table->setCurrentIndex(AMBARDETmodel->index( map_row  ,0));
}

void Cw_Ambar::slt_Ambard_toNext()
{
    qDebug() << "  slt_Ambard_toNext";
    AMBARDETmapper->toNext ();
    int map_row = AMBARDETmapper->currentIndex ();
    AMBARDETtview->pB_snrki->setEnabled(map_row < AMBARDETmodel->rowCount() - 1);
    AMBARDETtview->table->setCurrentIndex(AMBARDETmodel->index( map_row  ,0));
}

void Cw_Ambar::slt_Ambard_toLast()
{
    qDebug() << "  slt_Ambard_toLast";
    AMBARDETmapper->toLast ();
    int map_row = AMBARDETmapper->currentIndex ();
    AMBARDETtview->pB_son->setEnabled(map_row < AMBARDETmodel->rowCount() - 1);
    AMBARDETtview->table->setCurrentIndex(AMBARDETmodel->index( AMBARDETmodel->rowCount() - 1  ,0));
}






void Cw_Ambar::slt_Ambard_pB_EKLE_clicked ()
{

    qDebug() << "  slt_Ambard_pB_EKLE_clicked";
    //AMBARtview->table->setFocus ();
    AMBARDETtview->table->setFocus ();

    QModelIndex Ambar_indx = AMBARtview->table->currentIndex () ;
    if ( Ambar_indx.row () >= 0 )
    {
        /// Ambar kaydı var -
        ///
        /// yeni eklenecek kayıda -
        /// Ambardan
        /// malzeme - barkod - Ambar_id
        /// ekle
        ///
        ///
        /// Ambar modelden kaydı al

        // QSqlRecord Ambar_rec = AMBARmodel->record (Ambar_indx.row ());
        int Ambar_row = Ambar_indx.row ();

        /// kayıt içerisinde belirli bir
        /// field in içeriğini değişkene at

        QString brkd = AMBARmodel->
                data ( AMBARmodel->
                       index(Ambar_row,AMBARmodel->
                             fieldIndex("mlzm_barkod"))).toString() ;
        QString mlzm = AMBARmodel->
                data ( AMBARmodel->
                       index(Ambar_row,AMBARmodel->
                             fieldIndex("mlzm_malzeme"))).toString() ;
        int Ambar_no = AMBARmodel->
                data ( AMBARmodel->
                       index(Ambar_row,AMBARmodel->
                             fieldIndex("mlzm_kod"))).toInt ();

        /// Ambardet den yeni boş bir record al = Ambar_rec
        QSqlRecord Ambardet_rec = AMBARDETmodel->record ();
        /// rec in içerisinde istediğin fieldleri doldur
        Ambardet_rec.setValue ("mlzm_barkod",brkd);
        Ambardet_rec.setValue ("mlzm_malzeme",mlzm);
        Ambardet_rec.setValue ("mlzm_kod", Ambar_no);

        // insert a new record (-1) with new data
        if ( ! AMBARDETmodel->insertRecord(-1,Ambardet_rec))
        {
            qDebug() << "HATA - kayıt DEPO DETAY a eklenemedi ";
        }
        else /// Ambardet_rec detaya eklendi
        {
            AMBARDETmodel->submitAll ();
            AMBARDETmodel->select();
        }
    }
    else /// tVAmbar row yok - Ambar_indx.row () < 0
    {
        qDebug()<<"HATA - Ambar Ekleme .row yokk ";
    }
}



void Cw_Ambar::slt_Ambard_pB_SIL_clicked ()
{
    qDebug() << "  slt_Ambard_pB_SIL_clicked";
    QModelIndex sample =   AMBARDETtview->table->currentIndex();
    if( sample.row() >= 0 )
    {
        QSqlRecord rec = AMBARDETmodel->record();

        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;

        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,// + "\n barkodli personelin kaydı silinsin mi? ?" ,
                                    QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            AMBARDETmodel->removeRow(sample.row());
            //pmodel->endRemoveColumns();
            AMBARDETmodel->select ();
        }
    }
}






Cw_Ambar::~Cw_Ambar()
{
    qDebug() << "   destructor";
}

void Cw_Ambar::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Ambar dosyası açılıyor";
}









