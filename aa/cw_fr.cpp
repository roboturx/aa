#include "cw_fr.h"
#include "dbase.h"
#include "globals.h"

Cw_fr::Cw_fr(QWidget *parent) :
    QWidget(parent)
{
    qDebug ()<<"Firma Constructor";
    //************************************************************
    //*****************  F İ R m A  ****************************
}

void Cw_fr::setup_firma()
{
    qDebug() << "FİRMA";

    setup_ui();

    dbase = new DBase ;

    setup_modelfr();
    setup_viewfr();
    setup_mapfr();




  /*  (connect(FRMmapper, &QDataWidgetMapper::currentIndexChanged,
             this, &Cw_fr::on_updateButtonsSLOT));

    (connect(  FRMtview->selectionModel(),
               SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
               FRMmapper, SLOT(setCurrentModelIndex(QModelIndex))));

    //  (connect(  FRMmapper->currentIndexChanged(FRMmapper->currentIndex ()) , &FRMmapper::currentIndexChanged, FRMtview,
    //                   &FRMtview->setCurrentIndex (FRMmapper->currentIndex ());

    (connect(  FRMtview->selectionModel(),
               SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
               FRMmapper, SLOT(setCurrentModelIndex(QModelIndex))));

*/

    /// per değiştiğnde resmide değiştirelim
    connect( FRMtview->selectionModel (), &QItemSelectionModel::currentRowChanged,
             this, &Cw_fr::onFRMtview_resimGosterSLOT );


 //   on_updateButtonsSLOT(0);

}



void Cw_fr::setup_ui()
{

    qDebug() << "  setup_uiFr";

    Cw_fr::setWindowTitle ("FİRMA");
    //Cw_fr::resize(qApp->screens()[0]->size()*.8);
    Cw_fr::showMaximized ();


    // ///////////////////////////////////////////////////////
    // pButtonzzz


    lB_fr = new QLabel     (tr("Personel"));

//    lB_rsm = new QLabel      (tr("Resim"));
//    pB_ekle = new QPushButton (tr("&Ekle"));
//    pB_sil = new QPushButton (tr("&Sil"));
//    pB_ara = new QPushButton (tr("Ara"));
//    pB_yaz = new QPushButton (tr("Yazdır"));
//    pB_kpt = new QPushButton (tr("Kapat"));
//    pB_rsm = new QPushButton (tr("Resim"));
//    (connect( pB_kpt , &QPushButton::clicked,
//              this, &Cw_fr::on_pB_KPT_clicked ));
//    (connect( pB_ara , &QPushButton::clicked,
//              this, &Cw_fr::on_pB_ARA_clicked ));
//    (connect( pB_yaz , &QPushButton::clicked,
//              this, &Cw_fr::on_pB_YAZ_clicked ));
//    connect ( pB_rsm , &QPushButton::clicked, this,
//              &Cw_fr::onpB_fr_resimEklE_clickedSLOT );

/*

    auto *wd_bttns = new QWidget();
    wd_bttns->setWindowTitle ("wd_bttns window");
    auto *LG_pBs = new QHBoxLayout();
    wd_bttns->setLayout (LG_pBs);

    //    LG_pBs->addWidget( lB_rsm );
//    LG_pBs->addWidget( pB_ekle);
//    LG_pBs->addWidget( pB_sil );
//    LG_pBs->addWidget( pB_ara );
//    LG_pBs->addWidget( pB_yaz );
//    LG_pBs->addWidget( pB_rsm );
//    LG_pBs->addWidget( pB_kpt );
    LG_pBs->addStretch (1);

*/
    // ///////////////////////////////////////////////////////
    // views
    int i=1;
    FRMtview = new HC_TableView(i);
   // FRMtview->setMinimumSize (60,100);

    auto *wd_tvs = new QWidget() ;
    wd_tvs->setWindowTitle ("wd_tvs window");
    auto *lYG_tv = new QVBoxLayout();
    wd_tvs->setLayout (lYG_tv);

  //  lYG_tv->addWidget (wd_bttns );
    lYG_tv->addWidget (FRMtview);


    // ///////////////////////////////////////////////////////
    // wdgt lbls
    //

    auto *lB_unvan  = new QLabel(tr("Unvan"        ));
    lE_unvan = new QLineEdit() ;
    lB_unvan->setBuddy(lE_unvan);
    auto *lB_adres = new QLabel(tr("Adres"       ));
    lE_adres = new QLineEdit();
    lB_adres->setBuddy(lE_adres);
    auto *lB_sehir = new QLabel(tr("Şehir"       ));
    lE_sehir = new QLineEdit();
    lB_sehir->setBuddy(lE_sehir);
    auto *lB_vd    = new QLabel(tr("Vergi Dairesi" ));
    lE_vd = new QLineEdit();
    lB_vd->setBuddy(lE_vd);
    auto *lB_vdno = new QLabel(tr("VD No"  ));
    lE_vdno = new QLineEdit();
    lB_vdno->setBuddy(lE_vdno);
    auto *lB_tel  = new QLabel(tr("Telefon "  ));
    lE_tel = new QLineEdit();
    lB_tel->setBuddy(lE_tel);
    auto *lB_eposta    = new QLabel(tr("e-posta"  ));
    lE_eposta = new QLineEdit();
    lB_eposta->setBuddy(lE_eposta);

    auto  *lB_yisim  = new QLabel(tr("Yetkili İsim"  ));
    lE_yisim = new QLineEdit();
    lB_yisim->setBuddy(lE_yisim);
    auto  *lB_ysoyad   = new QLabel(tr("Yetkili Soyad"  ));
    lE_ysoyad = new QLineEdit();
    lB_ysoyad->setBuddy(lE_ysoyad);
    auto  *lB_ytel = new QLabel(tr("Yetkili Tel"));
    lE_ytel = new QLineEdit();
    lB_ytel->setBuddy(lE_ytel);


    auto *wd_lBs = new QWidget() ;
    wd_lBs->setWindowTitle ("lbs window");
    auto *lYG_map = new QGridLayout();
    wd_lBs->setLayout (lYG_map);


    lYG_map->addWidget(lB_unvan   , 0, 0, 1, 1);
    lYG_map->addWidget(lE_unvan   , 0, 1, 1, 2);
    lYG_map->addWidget(lB_adres   , 1, 0, 1, 1);
    lYG_map->addWidget(lE_adres   , 1, 1, 1, 2);
    lYG_map->addWidget(lB_sehir   , 2, 0, 1, 1);
    lYG_map->addWidget(lE_sehir   , 2, 1, 1, 2);
    lYG_map->addWidget(lB_vd      , 3, 0, 1, 1);
    lYG_map->addWidget(lE_vd      , 3, 1, 1, 2);
    lYG_map->addWidget(lB_vdno    , 4, 0, 1, 1);
    lYG_map->addWidget(lE_vdno    , 4, 1, 1, 2);
    lYG_map->addWidget(lB_tel     , 5, 0, 1, 1);
    lYG_map->addWidget(lE_tel     , 5, 1, 1, 2);
    lYG_map->addWidget(lB_eposta  , 6, 0, 1, 1);
    lYG_map->addWidget(lE_eposta  , 6, 1, 1, 2);
    lYG_map->addWidget(lB_yisim   , 7, 0, 1, 1);
    lYG_map->addWidget(lE_yisim   , 7, 1, 1, 2);
    lYG_map->addWidget(lB_ysoyad  , 8, 0, 1, 1);
    lYG_map->addWidget(lE_ysoyad  , 8, 1, 1, 2);
    lYG_map->addWidget(lB_ytel    , 9, 0, 1, 1);
    lYG_map->addWidget(lE_ytel    , 9, 1, 1, 2);

    // /////////////////////////////////////
    // main layout

    auto *wd_all = new QWidget(this);
    auto *lYG_per = new QHBoxLayout();
    wd_all->setLayout (lYG_per);
    this->setLayout (lYG_per);
    lYG_per->addWidget ( wd_tvs );
    lYG_per->addWidget ( wd_lBs   );


}

void Cw_fr::setup_modelfr()
{

    FRMmodel = new QSqlRelationalTableModel ;
    FRMmodel = dbase->modelFirma() ;
}


void Cw_fr::setup_viewfr()
{
    qDebug()<<"setup view fr";
    FRMtview->setModel(FRMmodel);
    FRMtview->table->resizeColumnsToContents();
    FRMtview->table->resizeRowsToContents ();

    qDebug()<<"3www view model " << FRMtview->model ();

    FRMselectionMdl = new QItemSelectionModel( FRMmodel );
    qDebug()<<"3www slctn model " << FRMtview->selectionModel ();

    FRMtview->table->setSelectionModel( FRMselectionMdl );
    qDebug()<<"3www frm selectmodel" << FRMselectionMdl;

    FRMtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FRMtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    qDebug()<<"3www" << FRMselectionMdl;

    // Hide the column id Records

    //// kullanıcı bu alanları görmesin
    FRMtview->setColumnHidden(FRMmodel->fieldIndex("kod_pr"), true);
    FRMtview->setColumnHidden(FRMmodel->fieldIndex("resim"), true);

    FRMtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    FRMtview->table->horizontalHeader()->setStretchLastSection(true);
    FRMtview->table->horizontalHeader()->resizeContentsPrecision();
    FRMtview->table->resizeRowsToContents ();
    FRMtview->table->resizeColumnsToContents();


    ///// tableview kontrol connectleri
    ///
    ///

    qDebug()<<"3www1";
    connect(FRMtview->pB_ekle, &QPushButton::clicked ,this ,
            &Cw_fr::on_pB_EKLE_clicked  ) ;
    qDebug()<<"3www2";
    connect(FRMtview->pB_eklersm, &QPushButton::clicked,this ,
            &Cw_fr::onpB_fr_resimEklE_clickedSLOT  ) ;

    qDebug()<<"3www3";
    connect(FRMtview->pB_sil, &QPushButton::clicked,this ,
            &Cw_fr::on_pB_SIL_clicked ) ;
    qDebug()<<"3www4";
    connect(FRMtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FRMmapper->toFirst ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_ilk->setEnabled (map_row>0);
        FRMtview->setCurrentIndex(FRMmodel->index( 0  ,0));
    });

    qDebug()<<"3www5";
    connect(FRMtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toPrevious ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_ncki->setEnabled(map_row > 0);
        FRMtview->setCurrentIndex(FRMmodel->index( map_row  ,0));
    });

    qDebug()<<"3www6";
    connect(FRMtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toNext ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_snrki->setEnabled(map_row < FRMmodel->rowCount() - 1);
        FRMtview->setCurrentIndex(FRMmodel->index( map_row  ,0));
    });

    qDebug()<<"3www7";
    connect(FRMtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toLast ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_son->setEnabled(map_row < FRMmodel->rowCount() - 1);
        FRMtview->setCurrentIndex(FRMmodel->index( FRMmodel->rowCount() - 1  ,0));
    });


qDebug()<<"3www8";
    FRMmodel->select();
    FRMtview->setCurrentIndex(FRMmodel->index(0,0));
qDebug()<<"3www33";
}


/* user interface */
void Cw_fr::setup_mapfr()
{
    qDebug()<<"3www00";
    FRMmapper = new QDataWidgetMapper(this);
    FRMmapper->setModel(FRMmodel);

    FRMmapper->addMapping(lE_unvan , FRMmodel->fieldIndex("frm_unvan"));
    FRMmapper->addMapping(lE_adres, FRMmodel->fieldIndex("frm_adres"));
    FRMmapper->addMapping(lE_sehir, FRMmodel->fieldIndex("frm_sehir"));
    FRMmapper->addMapping(lE_vd, FRMmodel->fieldIndex("frm_vd"));
    FRMmapper->addMapping(lE_vdno, FRMmodel->fieldIndex("frm_vdno"));
    FRMmapper->addMapping(lE_tel, FRMmodel->fieldIndex("frm_tel"));
    FRMmapper->addMapping(lE_eposta, FRMmodel->fieldIndex("frm_eposta"));
    FRMmapper->addMapping(lE_yisim, FRMmodel->fieldIndex("frm_yisim"));
    FRMmapper->addMapping(lE_ysoyad, FRMmodel->fieldIndex("frm_ysoyad"));
    FRMmapper->addMapping(lE_ytel, FRMmodel->fieldIndex("frm_ytel"));
    // FRMmapper->addMapping(lB_resim, FRMmodel->fieldIndex("frm_resim"));


    qDebug() << "  slt_ftr_updButtons"<<FRMmapper ;
    /// depo map nav tuslari kontrol
    connect(FRMmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {

        qDebug() << "  slt_ftr_updButtons";
        int row = Index; //FTRmapper->currentIndex ();
        FRMtview->pB_ilk->setEnabled (row>0);
        FRMtview->pB_ncki->setEnabled(row > 0);
        FRMtview->pB_snrki->setEnabled(row < FRMmodel->rowCount() - 1);
        FRMtview->pB_son->setEnabled(row < FRMmodel->rowCount() - 1);

    });
    // // firmada row değiştiğinde indexte değişsin

    qDebug() << "  slctiun model "<<FRMselectionMdl ;
    connect(  FRMselectionMdl ,
              &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        FRMmapper->setCurrentModelIndex(Index) ;
    });

            //  FRMmapper,
             // &QDataWidgetMapper::setCurrentModelIndex);

    FRMmapper->toFirst ();

    qDebug()<<"3www09";
}




void Cw_fr::on_pB_ARA_clicked ()
{

}

void Cw_fr::on_pB_EKLE_clicked ()
{
    QSqlRecord rec = FRMmodel->record();
    // insert a new record (-1) with null date

    /// date does not take null value
    /// line 126 at QDateEdit declaration
    /// with the
    /// dT_dotar->setSpecialValueText ("  ");
    /// line
    /// an invalid date value represents " "
    ///
    //    dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


    if ( ! FRMmodel->insertRecord(-1,rec))
    {
        qDebug() << "100111 -  HATA - kayıt eklenemedi ";
    }
    else
        qDebug() << "100111 - Kayıt personele eklendi ";
    FRMmodel->select();
}

void Cw_fr::on_pB_SIL_clicked ()
{
    QModelIndex sample =   FRMtview->currentIndex();
    if( sample.row() >= 0 )
    {

        //         FRMtview->selectionModel()->setCurrentIndex
        //             (sample,QItemSelectionModel::NoUpdate);

        QSqlRecord rec = FRMmodel->record();
        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                    QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            FRMmodel->removeRow(sample.row());
            //pmodel->endRemoveColumns();
            FRMmodel->select();
        }
    }
}

void Cw_fr::on_pB_YAZ_clicked ()
{

}

void Cw_fr::on_pB_KPT_clicked ()
{
    this->hide ();
}


void Cw_fr::onFRMtview_resimGosterSLOT(QModelIndex)
{
    // makina stok tablosundan resim gösterme
    // view row unu tespit et
    int rowidx = FRMtview->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = FRMtview->
            model()->index( rowidx, FRMmodel->fieldIndex ("resim") ).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    lB_rsm->setPixmap( outPixmap );
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}       ///     onFRMtview_resimGosterSLOT

void Cw_fr::onpB_fr_resimEklE_clickedSLOT()
{
    // makina stok resim ekle
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
        QModelIndex index = FRMtview->currentIndex();
        int row = index.row() ;
        // o row daki bilgelere ulaşalım
        FRMmodel->setData(FRMmodel->
                          index(row, FRMmodel->fieldIndex ("resim")),inByteArray);
        FRMmodel->submitAll();
    }
}       ///     onpb_resimEkleSLOT


/*


void Cw_fr::r_toFirst()
{
    FRMmapper->toFirst ();
    int map_row = FRMmapper->currentIndex ();
    pB_ilk->setEnabled (map_row>0);
    FRMtview->setCurrentIndex(FRMmodel->index( 0  ,0));
}

void Cw_fr::r_toPrevious( )
{
    FRMmapper->toPrevious ();
    int map_row = FRMmapper->currentIndex ();
    pB_oncki->setEnabled(map_row > 0);
    FRMtview->setCurrentIndex(FRMmodel->index( map_row  ,0));
}

void Cw_fr::r_toNext()
{
    FRMmapper->toNext ();
    int map_row = FRMmapper->currentIndex ();
    pB_snrki->setEnabled(map_row < FRMmodel->rowCount() - 1);

    FRMtview->setCurrentIndex(FRMmodel->index( map_row  ,0));
}

void Cw_fr::r_toLast()
{
    FRMmapper->toLast ();
    int map_row = FRMmapper->currentIndex ();
    pB_son->setEnabled(map_row < FRMmodel->rowCount() - 1);
    FRMtview->setCurrentIndex(FRMmodel->index( FRMmodel->rowCount() - 1  ,0));
}

*/

void Cw_fr::on_updateButtonsSLOT(int row)
{
    /* QModelIndex next_index = FRMtview->model()->index(row + 1, 0);
    FRMtview->setCurrentIndex(next_index);

    //FRMtview->setSelectionModel (Qt::m);*/

    FRMtview->pB_ilk->setEnabled (row>0);
    FRMtview->pB_ncki->setEnabled(row > 0);
    FRMtview->pB_snrki->setEnabled(row < FRMmodel->rowCount() - 1);
    FRMtview->pB_son->setEnabled(row < FRMmodel->rowCount() - 1);



}





void Cw_fr::showEvent(QShowEvent *)
{
    qDebug() << "Firma dosyası açılıyor";
}

/*
void Cw_fr::resim(QModelIndex)
{
    // personel tablosundan resim gösterme

    // view row unu tespit et
    int rowidx =   FRMtview->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray =   FRMtview->
            model()->index(rowidx,10).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );


    lB_rsm->setPixmap( outPixmap );
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}
*/


Cw_fr::~Cw_fr()
= default;


