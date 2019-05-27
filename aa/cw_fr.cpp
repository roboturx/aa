#include "cw_fr.h"
#include "globals.h"

Cw_fr::Cw_fr(QWidget *parent) :
    QWidget(parent)
{


    setup_ui();             //1
    setup_modelfr();
    setup_viewfr();
    setup_mapfr();

    (connect( pB_ara , &QPushButton::clicked,
                      this, &Cw_fr::on_pB_ARA_clicked ));

    (connect( pB_yaz , &QPushButton::clicked,
                      this, &Cw_fr::on_pB_YAZ_clicked ));

    (connect( pB_ekle , &QPushButton::clicked,
                      this, &Cw_fr::on_pB_EKLE_clicked ));


    (connect( pB_sil , &QPushButton::clicked,
                      this, &Cw_fr::on_pB_SIL_clicked ));

    ( connect(pB_ilk, &QPushButton::clicked,
                      this, &Cw_fr::r_toFirst));
    ( connect(pB_oncki, &QPushButton::clicked,
                      this, &Cw_fr::r_toPrevious));
    (connect(pB_snrki, &QPushButton::clicked,
                     this, &Cw_fr::r_toNext));
    (connect(pB_son, &QPushButton::clicked,
                    this,  &Cw_fr::r_toLast));

    (connect(map_fr, &QDataWidgetMapper::currentIndexChanged,
                     this, &Cw_fr::on_updateButtonsSLOT));

    (connect(  tV_fr->selectionModel(),
                       SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
                       map_fr, SLOT(setCurrentModelIndex(QModelIndex))));

  //  (connect(  map_fr->currentIndexChanged(map_fr->currentIndex ()) , &map_fr::currentIndexChanged, tV_fr,
    //                   &tV_fr->setCurrentIndex (map_fr->currentIndex ());

             (connect(  tV_fr->selectionModel(),
                       SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                       map_fr, SLOT(setCurrentModelIndex(QModelIndex))));

    (connect( pB_kpt , &QPushButton::clicked,
                      this, &Cw_fr::on_pB_KPT_clicked ));

    /// per değiştiğnde resmide değiştirelim
    connect( tV_fr->selectionModel (), &QItemSelectionModel::currentRowChanged,
             this, &Cw_fr::ontV_fr_resimGosterSLOT );

    connect ( pB_rsm , &QPushButton::clicked, this,
              &Cw_fr::onpB_fr_resimEklE_clickedSLOT );





    on_updateButtonsSLOT(0);

}


void Cw_fr::setup_ui()
{
   // this->setGeometry (130,130,1200,400);


    /// pButtonzzz
    QGroupBox *gR_pBs = new QGroupBox ("FİRMA",this);

    //lB_fr     = new QLabel     (tr("Personel" ),gR_pBs);

    lB_rsm     = new QLabel(tr("Resim"    ),gR_pBs);
    pB_ilk     = new QPushButton(tr("İl&k"     ),gR_pBs);
    pB_oncki   = new QPushButton(tr("Önce&ki"  ),gR_pBs);
    pB_snrki   = new QPushButton(tr("S&onraki" ),gR_pBs);
    pB_son     = new QPushButton(tr("So&n"     ),gR_pBs);
    pB_ekle    = new QPushButton(tr("&Ekle"    ),gR_pBs);
    pB_sil     = new QPushButton(tr("&Sil"     ),gR_pBs);
    //pB_duzenle = new QPushButton(tr("&Düzenle" ),gR_pBs);
    pB_ara     = new QPushButton(tr("Ara"      ),gR_pBs);
    pB_yaz     = new QPushButton(tr("Yazdır"   ),gR_pBs);
    pB_kpt     = new QPushButton(tr("Kapat"   ),gR_pBs);
    pB_rsm     = new QPushButton(tr("Resim"    ),gR_pBs);

    auto *LG_pBs = new QGridLayout();
    gR_pBs->setLayout (LG_pBs);

    LG_pBs->addWidget( lB_rsm    ,  1, 0,11, 4);
    LG_pBs->addWidget( pB_ekle   ,  1, 4, 1, 1);
    LG_pBs->addWidget( pB_sil    ,  2, 4, 1, 1);

    LG_pBs->addWidget( pB_ilk    ,  5, 4, 1, 1);
    LG_pBs->addWidget( pB_oncki  ,  6, 4, 1, 1);
    LG_pBs->addWidget( pB_snrki  ,  7, 4, 1, 1);
    LG_pBs->addWidget( pB_son    ,  8, 4, 1, 1);
    LG_pBs->addWidget( pB_ara    , 10, 4, 1, 1);
    LG_pBs->addWidget( pB_yaz    , 11, 4, 1, 1);
    LG_pBs->addWidget( pB_rsm    , 13, 0, 1, 1);
    LG_pBs->addWidget( pB_kpt    , 13, 3, 1, 2);

    tV_fr = new QTableView();
    /*   QItemSelectionModel::SelectionFlags flags =
            QItemSelectionModel::ClearAndSelect |
            QItemSelectionModel::Rows;
    QModelIndex index = tV_fr->model()->index(rowIndex, 0);
    tV_fr->selectionModel()->select(index, flags);
*/
    QGroupBox *gR_lBs = new QGroupBox ("FİRMA",this);

    QLabel *lB_unvan  = new QLabel(tr("Unvan"        ),gR_lBs);
    lE_unvan = new QLineEdit(gR_lBs) ;
    lB_unvan->setBuddy(lE_unvan);
    QLabel *lB_adres = new QLabel(tr("Adres"       ),gR_lBs);
    lE_adres = new QLineEdit(gR_lBs);
    lB_adres->setBuddy(lE_adres);
    QLabel *lB_sehir = new QLabel(tr("Şehir"       ),gR_lBs);
    lE_sehir = new QLineEdit(gR_lBs);
    lB_sehir->setBuddy(lE_sehir);
    QLabel *lB_vd    = new QLabel(tr("Vergi Dairesi" ),gR_lBs);
    lE_vd = new QLineEdit(gR_lBs);
    lB_vd->setBuddy(lE_vd);
    QLabel *lB_vdno = new QLabel(tr("VD No"  ),gR_lBs);
    lE_vdno = new QLineEdit(gR_lBs);
    lB_vdno->setBuddy(lE_vdno);
    QLabel *lB_tel  = new QLabel(tr("Telefon "  ),gR_lBs);
    lE_tel = new QLineEdit(gR_lBs);
    lB_tel->setBuddy(lE_tel);
    QLabel *lB_eposta    = new QLabel(tr("e-posta"  ),gR_lBs);
    lE_eposta = new QLineEdit(gR_lBs);
    lB_eposta->setBuddy(lE_eposta);

    QLabel *lB_yisim  = new QLabel(tr("Yetkili İsim"  ),gR_lBs);
    lE_yisim = new QLineEdit(gR_lBs);
    lB_yisim->setBuddy(lE_yisim);
    QLabel *lB_ysoyad   = new QLabel(tr("Yetkili Soyad"  ),gR_lBs);
    lE_ysoyad = new QLineEdit(gR_lBs);
    lB_ysoyad->setBuddy(lE_ysoyad);
    QLabel *lB_ytel = new QLabel(tr("Yetkili Tel"),gR_lBs);
    lE_ytel = new QLineEdit();
    lB_ytel->setBuddy(lE_ytel);

    auto *lYG_map = new QGridLayout();
    gR_lBs->setLayout (lYG_map);

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

    auto *lYG_per = new QGridLayout(this);

    lYG_per->addWidget (tV_fr     , 0, 0, 1, 2);
    lYG_per->addWidget (gR_lBs     , 1, 0, 1, 1);
    lYG_per->addWidget (gR_pBs     , 1, 1, 2, 1);

}

void Cw_fr::setup_modelfr()
{


    QString tableName = "frm__dbtb";
    QStringList fieldList;
    // fieldList.append("Kod");
    fieldList.append("Firma Unvanı");
    fieldList.append("Adres");
    fieldList.append("Şehir");
    fieldList.append("Vergi Dairesi");
    fieldList.append("VD No");
    fieldList.append("Telefon");
    fieldList.append("e-posta");
    fieldList.append("Yetkili İsim");
    fieldList.append("Yetkili Soyad");
    fieldList.append("Tetkili Telefon");
    // fieldList.append("resim");
    mdl_fr = new QSqlRelationalTableModel();
    mdl_fr->setTable(tableName);

    /// Set the columns names in a table with sorted data
    ///
    ///
    for(int i = 1, j = 0; i < mdl_fr->columnCount()-1; i++, j++){
        mdl_fr->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }

    // Set Sort Ascending steering column data
    mdl_fr->setSort(2,Qt::AscendingOrder);

    // her field değişiminde dosya yazılacak
    mdl_fr->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Populate the model_mkstok
    if (!mdl_fr->select())
    {
        qDebug () << mdl_fr->lastError();
    }


}
void Cw_fr::setup_viewfr()
{
    tV_fr->setModel(mdl_fr);

    // Hide the column id Records

    //// kullanıcı bu alanları görmesin
    tV_fr->setColumnHidden(mdl_fr->fieldIndex("kod_pr"), true);
    tV_fr->setColumnHidden(mdl_fr->fieldIndex("resim"), true);
    // Allow the selection of lines
    tV_fr->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    tV_fr->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    tV_fr->resizeRowsToContents ();
    tV_fr->resizeColumnsToContents();
    // tV_fr->setStyleSheet ("background-color: darkgreen;"
    //                         "color : yellow;");
    tV_fr->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    tV_fr->horizontalHeader()->
            setStretchLastSection(true);
    tV_fr->horizontalHeader()->
            resizeContentsPrecision();
    /*  tV_fr->setColumnWidth(0, this->width()/15);
    tV_fr->setColumnWidth(1, this->width()/15);
    tV_fr->setColumnWidth(2, this->width()/15);
    tV_fr->setColumnWidth(3, this->width()/15);
    tV_fr->setColumnWidth(4, this->width()/15);
    tV_fr->setColumnWidth(5, this->width()/15);
    tV_fr->setColumnWidth(6, this->width()/15);
    tV_fr->setColumnWidth(7, this->width()/10);
    tV_fr->setColumnWidth(8, this->width()/10);
    tV_fr->setColumnWidth(9, this->width()/10);
    tV_fr->setColumnWidth(10, this->width()/8);
    tV_fr->setColumnWidth(11, this->width()/8);
    tV_fr->setColumnWidth(12, this->width()/2);

*/
    mdl_fr->select();
    tV_fr->setCurrentIndex(mdl_fr->index(0,0));

}


void Cw_fr::on_pB_ARA_clicked ()
{

}

void Cw_fr::on_pB_EKLE_clicked ()
{
    QSqlRecord rec = mdl_fr->record();
    // insert a new record (-1) with null date

    /// date does not take null value
    /// line 126 at QDateEdit declaration
    /// with the
    /// dT_dotar->setSpecialValueText ("  ");
    /// line
    /// an invalid date value represents " "
    ///
//    dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


    if ( ! mdl_fr->insertRecord(-1,rec))
    {
        qDebug() << "100111 -  HATA - kayıt eklenemedi ";
    }
    else
        qDebug() << "100111 - Kayıt personele eklendi ";
    mdl_fr->select();
}

void Cw_fr::on_pB_SIL_clicked ()
{
    QModelIndex sample =   tV_fr->currentIndex();
    if( sample.row() >= 0 )
    {

        //         tV_fr->selectionModel()->setCurrentIndex
        //             (sample,QItemSelectionModel::NoUpdate);

        QSqlRecord rec = mdl_fr->record();
        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox::question(this,
              "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
               QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            mdl_fr->removeRow(sample.row());
            //pmodel->endRemoveColumns();
            mdl_fr->select();
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


void Cw_fr::ontV_fr_resimGosterSLOT(QModelIndex)
{
    // makina stok tablosundan resim gösterme
    // view row unu tespit et
    int rowidx = tV_fr->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = tV_fr->
            model()->index( rowidx, mdl_fr->fieldIndex ("resim") ).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    lB_rsm->setPixmap( outPixmap );
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}       ///     ontV_fr_resimGosterSLOT

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
        QModelIndex index = tV_fr->currentIndex();
        int row = index.row() ;
        // o row daki bilgelere ulaşalım
        mdl_fr->setData(mdl_fr->
                         index(row, mdl_fr->fieldIndex ("resim")),inByteArray);
        mdl_fr->submitAll();
    }
}       ///     onpb_resimEkleSLOT





void Cw_fr::r_toFirst()
{
    map_fr->toFirst ();
    int map_row = map_fr->currentIndex ();
    pB_ilk->setEnabled (map_row>0);
    tV_fr->setCurrentIndex(mdl_fr->index( 0  ,0));
}

void Cw_fr::r_toPrevious( )
{
    map_fr->toPrevious ();
    int map_row = map_fr->currentIndex ();
    pB_oncki->setEnabled(map_row > 0);
    tV_fr->setCurrentIndex(mdl_fr->index( map_row  ,0));
}

void Cw_fr::r_toNext()
{
   map_fr->toNext ();
   int map_row = map_fr->currentIndex ();
   pB_snrki->setEnabled(map_row < mdl_fr->rowCount() - 1);

   tV_fr->setCurrentIndex(mdl_fr->index( map_row  ,0));
}

void Cw_fr::r_toLast()
{
    map_fr->toLast ();
    int map_row = map_fr->currentIndex ();
    pB_son->setEnabled(map_row < mdl_fr->rowCount() - 1);
    tV_fr->setCurrentIndex(mdl_fr->index( mdl_fr->rowCount() - 1  ,0));
}



void Cw_fr::on_updateButtonsSLOT(int row)
{
   /* QModelIndex next_index = tV_fr->model()->index(row + 1, 0);
    tV_fr->setCurrentIndex(next_index);

    //tV_fr->setSelectionModel (Qt::m);*/

    pB_ilk->setEnabled (row>0);
    pB_oncki->setEnabled(row > 0);
    pB_snrki->setEnabled(row < mdl_fr->rowCount() - 1);
    pB_son->setEnabled(row < mdl_fr->rowCount() - 1);



}



/* user interface */
void Cw_fr::setup_mapfr()
{
    map_fr = new QDataWidgetMapper(this);
    map_fr->setModel(mdl_fr);

    map_fr->addMapping(lE_unvan , mdl_fr->fieldIndex("frm_unvan"));
    map_fr->addMapping(lE_adres, mdl_fr->fieldIndex("frm_adres"));
    map_fr->addMapping(lE_sehir, mdl_fr->fieldIndex("frm_sehir"));
    map_fr->addMapping(lE_vd, mdl_fr->fieldIndex("frm_vd"));
    map_fr->addMapping(lE_vdno, mdl_fr->fieldIndex("frm_vdno"));
    map_fr->addMapping(lE_tel, mdl_fr->fieldIndex("frm_tel"));
    map_fr->addMapping(lE_eposta, mdl_fr->fieldIndex("frm_eposta"));
    map_fr->addMapping(lE_yisim, mdl_fr->fieldIndex("frm_yisim"));
    map_fr->addMapping(lE_ysoyad, mdl_fr->fieldIndex("frm_ysoyad"));
    map_fr->addMapping(lE_ytel, mdl_fr->fieldIndex("frm_ytel"));
   // map_fr->addMapping(lB_resim, mdl_fr->fieldIndex("frm_resim"));

    map_fr->toFirst ();
    mdl_fr->select();
    tV_fr->setCurrentIndex(mdl_fr->index(0,0));
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
    int rowidx =   tV_fr->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray =   tV_fr->
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
{

}


