#include "cw_per.h"
//#include "ui_cw_per.h"
#include "globals.h"

Cw_per::Cw_per(QWidget *parent) : QWidget(parent)
{
    setup_ui();             //1
    setup_modelPer();
    setup_viewPer();
    setup_map();

    (connect( pB_ara , &QPushButton::clicked,
                      this, &Cw_per::on_pB_ARA_clicked ));

    (connect( pB_yaz , &QPushButton::clicked,
                      this, &Cw_per::on_pB_YAZ_clicked ));

    (connect( pB_ekle , &QPushButton::clicked,
                      this, &Cw_per::on_pB_EKLE_clicked ));


    (connect( pB_sil , &QPushButton::clicked,
                      this, &Cw_per::on_pB_SIL_clicked ));

    ( connect(pB_ilk, &QPushButton::clicked,
                      this, &Cw_per::r_toFirst));
    ( connect(pB_oncki, &QPushButton::clicked,
                      this, &Cw_per::r_toPrevious));
    (connect(pB_snrki, &QPushButton::clicked,
                     this, &Cw_per::r_toNext));
    (connect(pB_son, &QPushButton::clicked,
                    this,  &Cw_per::r_toLast));

    (connect(map_per, &QDataWidgetMapper::currentIndexChanged,
                     this, &Cw_per::on_updateButtonsSLOT));

    (connect(  tV_per->selectionModel(),
                       SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
                       map_per, SLOT(setCurrentModelIndex(QModelIndex))));

  //  (connect(  map_per->currentIndexChanged(map_per->currentIndex ()) , &map_per::currentIndexChanged, tV_per,
    //                   &tV_per->setCurrentIndex (map_per->currentIndex ());

             (connect(  tV_per->selectionModel(),
                       SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                       map_per, SLOT(setCurrentModelIndex(QModelIndex))));

    (connect( pB_kpt , &QPushButton::clicked,
                      this, &Cw_per::on_pB_KPT_clicked ));

    /// per değiştiğnde resmide değiştirelim
    connect( tV_per->selectionModel (), &QItemSelectionModel::currentRowChanged,
             this, &Cw_per::ontV_per_resimGosterSLOT );

    connect ( pB_rsm , &QPushButton::clicked, this,
              &Cw_per::onpB_per_resimEklE_clickedSLOT );





    on_updateButtonsSLOT(0);

}


void Cw_per::setup_ui()
{
   // this->setGeometry (130,130,1200,400);


    /// pButtonzzz
    QGroupBox *gR_pBs = new QGroupBox ("ÇALIŞAN",this);

    //lB_per     = new QLabel     (tr("Personel" ),gR_pBs);

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

    tV_per = new QTableView();
    /*   QItemSelectionModel::SelectionFlags flags =
            QItemSelectionModel::ClearAndSelect |
            QItemSelectionModel::Rows;
    QModelIndex index = tV_per->model()->index(rowIndex, 0);
    tV_per->selectionModel()->select(index, flags);
*/
    QGroupBox *gR_lBs = new QGroupBox ("ÇALIŞAN",this);

    QLabel *lB_isim  = new QLabel(tr("İ&sim"        ),gR_lBs);
    lE_isim = new QLineEdit(gR_lBs) ;
    lE_isim->setPlaceholderText ("Personel Adı");
    lB_isim->setBuddy(lE_isim);
    QLabel *lB_soyad = new QLabel(tr("S&oyad"       ),gR_lBs); lE_soyad = new QLineEdit(gR_lBs);lB_soyad->setBuddy(lE_soyad);
    QLabel *lB_bolum = new QLabel(tr("Bölü&m"       ),gR_lBs); lE_bolum = new QLineEdit(gR_lBs);lB_bolum->setBuddy(lE_bolum);
    QLabel *lB_tc    = new QLabel(tr("TC Kimlik No" ),gR_lBs); lE_tc = new QLineEdit(gR_lBs);lB_tc->setBuddy(lE_tc);
    QLabel *lB_doyer = new QLabel(tr("Doğum Yeri "  ),gR_lBs); lE_doyer = new QLineEdit(gR_lBs);lB_doyer->setBuddy(lE_doyer);
    QLabel *lB_dotar = new QLabel(tr("Doğum Tarihi "),gR_lBs);

    dT_dotar = new QDateEdit(); //QDate::currentDate ());
    dT_dotar->setSpecialValueText ("  ");
    dT_dotar->setLocale (QLocale::Turkish);
    dT_dotar->setMinimumDate(QDate::currentDate().addYears (-65));
    dT_dotar->setMaximumDate(QDate::currentDate().addDays(365));
    dT_dotar->setDisplayFormat ("dd-MM-yyyy");
    dT_dotar->setCalendarPopup (true);
    lB_dotar->setBuddy(dT_dotar);

    QLabel *lB_baba  = new QLabel(tr("Baba Adı "  ),gR_lBs);
    lE_baba = new QLineEdit(gR_lBs);
    lB_baba->setBuddy(lE_baba);
    QLabel *lB_meslek   = new QLabel(tr("M&eslek" ),gR_lBs); auto *cb_meslek = new QComboBox(gR_lBs); lB_meslek->setBuddy(cb_meslek);
    QLabel *lB_gorev    = new QLabel(tr("Gö&rev"  ),gR_lBs); lE_gorev = new QLineEdit(gR_lBs); lB_gorev->setBuddy(lE_gorev);
    QLabel *lB_adres    = new QLabel(tr("Adre&s"  ),gR_lBs); lE_adres = new QLineEdit(gR_lBs); lB_adres->setBuddy(lE_adres);
    QLabel *lB_sehir    = new QLabel(tr("Şe&hir"  ),gR_lBs); lE_sehir = new QLineEdit(gR_lBs); lB_sehir->setBuddy(lE_sehir);
    QLabel *lB_tel_cep  = new QLabel(tr("Tel &1"  ),gR_lBs); lE_tel_cep = new QLineEdit(gR_lBs); lB_tel_cep->setBuddy(lE_tel_cep);
    QLabel *lB_tel_ev   = new QLabel(tr("Tel &2"  ),gR_lBs); lE_tel_ev = new QLineEdit(gR_lBs); lB_tel_ev->setBuddy(lE_tel_ev);
    QLabel *lB_eposta   = new QLabel(tr("E-&posta"),gR_lBs); lE_eposta = new QLineEdit(gR_lBs); lB_eposta->setBuddy(lE_eposta);
    QLabel *lB_username = new QLabel(tr("Kullanıcı A&dı"),gR_lBs); lE_username = new QLineEdit(); lB_username->setBuddy(lE_username);
    QLabel *lB_password = new QLabel(tr("Şi&fre"  ),gR_lBs); lE_password = new QLineEdit(gR_lBs); lB_password->setBuddy(lE_password);
    QLabel *lB_yetki    = new QLabel(tr("&Yetki"  ),gR_lBs); lE_yetki = new QLineEdit(gR_lBs); lB_yetki->setBuddy(lE_yetki);

    auto *lYG_map = new QGridLayout();
    gR_lBs->setLayout (lYG_map);

    lYG_map->addWidget(lB_isim      , 0, 0, 1, 1);
    lYG_map->addWidget(lE_isim      , 0, 1, 1, 2);
    lYG_map->addWidget(lB_soyad     , 1, 0, 1, 1);
    lYG_map->addWidget(lE_soyad     , 1, 1, 1, 2);
    lYG_map->addWidget(lB_tc        , 2, 0, 1, 1);
    lYG_map->addWidget(lE_tc        , 2, 1, 1, 2);
    lYG_map->addWidget(lB_doyer     , 3, 0, 1, 1);
    lYG_map->addWidget(lE_doyer     , 3, 1, 1, 2);
    lYG_map->addWidget(lB_dotar     , 4, 0, 1, 1);
    lYG_map->addWidget(dT_dotar     , 4, 1, 1, 2);
    lYG_map->addWidget(lB_baba      , 5, 0, 1, 1);
    lYG_map->addWidget(lE_baba      , 5, 1, 1, 2);
    lYG_map->addWidget(lB_meslek    , 6, 0, 1, 1);
    lYG_map->addWidget(cb_meslek    , 6, 1, 1, 2);
    lYG_map->addWidget(lB_bolum     , 7, 0, 1, 1);
    lYG_map->addWidget(lE_bolum     , 7, 1, 1, 2);
    lYG_map->addWidget(lB_gorev     , 8, 0, 1, 1);
    lYG_map->addWidget(lE_gorev     , 8, 1, 1, 2);
    lYG_map->addWidget(lB_adres     , 9, 0, 1, 1);
    lYG_map->addWidget(lE_adres     , 9, 1, 1, 2);
    lYG_map->addWidget(lB_sehir     , 0, 3, 1, 1);
    lYG_map->addWidget(lE_sehir     , 0, 4, 1, 2);
    lYG_map->addWidget(lB_tel_cep   , 1, 3, 1, 1);
    lYG_map->addWidget(lE_tel_cep   , 1, 4, 1, 2);
    lYG_map->addWidget(lB_tel_ev    , 2, 3, 1, 1);
    lYG_map->addWidget(lE_tel_ev    , 2, 4, 1, 2);
    lYG_map->addWidget(lB_eposta    , 3, 3, 1, 1);
    lYG_map->addWidget(lE_eposta    , 3, 4, 1, 2);
    lYG_map->addWidget(lB_username  , 4, 3, 1, 1);
    lYG_map->addWidget(lE_username  , 4, 4, 1, 2);
    lYG_map->addWidget(lB_password  , 5, 3, 1, 1);
    lYG_map->addWidget(lE_password  , 5, 4, 1, 2);
    lYG_map->addWidget(lB_yetki     , 6, 3, 1, 1);
    lYG_map->addWidget(lE_yetki     , 6, 4, 1, 2);

    auto *lYG_per = new QGridLayout(this);

    lYG_per->addWidget (tV_per     , 0, 0, 1, 2);
    lYG_per->addWidget (gR_lBs     , 1, 0, 1, 1);
    lYG_per->addWidget (gR_pBs     , 1, 1, 2, 1);

}

void Cw_per::setup_modelPer()
{

qDebug()<<"model per setup";
    QString tableName = "dbtb_clsn";
    QStringList fieldList;
    // fieldList.append("Kod");
    fieldList.append("İsim");
    fieldList.append("Soyad");
    fieldList.append("TC Kimlik No");
    fieldList.append("Doğum Yeri");
    fieldList.append("Doğum Tarihi");
    fieldList.append("Baba Adı");
    fieldList.append("Bölüm");
    fieldList.append("Meslek");
    fieldList.append("Gorev");
    fieldList.append("Adres");
    fieldList.append("Şehir");
    fieldList.append("Telefon Cep");
    fieldList.append("Telefon Ev");
    fieldList.append("E-Poata");
    fieldList.append("Kullanıcı Adı");
    fieldList.append("Şifre");
    fieldList.append("Yetki");
    // fieldList.append("resim");
    mdl_per = new QSqlRelationalTableModel();
    mdl_per->setTable(tableName);

    /// Set the columns names in a table with sorted data
    ///
    ///
    for(int i = 1, j = 0; i < mdl_per->columnCount()-1; i++, j++){
        mdl_per->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }

    // Set Sort Ascending steering column data
    mdl_per->setSort(2,Qt::AscendingOrder);

    // her field değişiminde dosya yazılacak
    mdl_per->setEditStrategy(QSqlTableModel::OnFieldChange);

    /*///  kolon başlıkları
      model_spre->setHeaderData(
                  model_spre->fieldIndex("isim"),
                  Qt::Horizontal, tr("İsim"));
      model_spre->setHeaderData(
                  model_spre->fieldIndex("Soyad"),
                  Qt::Horizontal, tr("Soyad"));
  */
    // Populate the model_mkstok
    if (!mdl_per->select())
    {
        qDebug () << mdl_per->lastError();
    }


}
void Cw_per::setup_viewPer()
{
    tV_per->setModel(mdl_per);

    // Hide the column id Records

    //// kullanıcı bu alanları görmesin
    tV_per->setColumnHidden(mdl_per->fieldIndex("kod_pr"), true);
    tV_per->setColumnHidden(mdl_per->fieldIndex("resim"), true);
    // Allow the selection of lines
    tV_per->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    tV_per->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    tV_per->resizeRowsToContents ();
    tV_per->resizeColumnsToContents();
    // tV_per->setStyleSheet ("background-color: darkgreen;"
    //                         "color : yellow;");
    tV_per->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    tV_per->horizontalHeader()->
            setStretchLastSection(true);
    tV_per->horizontalHeader()->
            resizeContentsPrecision();
    /*  tV_per->setColumnWidth(0, this->width()/15);
    tV_per->setColumnWidth(1, this->width()/15);
    tV_per->setColumnWidth(2, this->width()/15);
    tV_per->setColumnWidth(3, this->width()/15);
    tV_per->setColumnWidth(4, this->width()/15);
    tV_per->setColumnWidth(5, this->width()/15);
    tV_per->setColumnWidth(6, this->width()/15);
    tV_per->setColumnWidth(7, this->width()/10);
    tV_per->setColumnWidth(8, this->width()/10);
    tV_per->setColumnWidth(9, this->width()/10);
    tV_per->setColumnWidth(10, this->width()/8);
    tV_per->setColumnWidth(11, this->width()/8);
    tV_per->setColumnWidth(12, this->width()/2);

*/
    mdl_per->select();
    tV_per->setCurrentIndex(mdl_per->index(0,0));

}


void Cw_per::on_pB_ARA_clicked ()
{

}

void Cw_per::on_pB_EKLE_clicked ()
{
    QSqlRecord rec = mdl_per->record();
    // insert a new record (-1) with null date

    /// date does not take null value
    /// line 126 at QDateEdit declaration
    /// with the
    /// dT_dotar->setSpecialValueText ("  ");
    /// line
    /// an invalid date value represents " "
    ///
    dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


    if ( ! mdl_per->insertRecord(-1,rec))
    {
        qDebug() << "100111 -  HATA - kayıt eklenemedi ";
    }
    else
        qDebug() << "100111 - Kayıt personele eklendi ";
    mdl_per->select();
}

void Cw_per::on_pB_SIL_clicked ()
{
    QModelIndex sample =   tV_per->currentIndex();
    if( sample.row() >= 0 )
    {

        //         tV_per->selectionModel()->setCurrentIndex
        //             (sample,QItemSelectionModel::NoUpdate);

        QSqlRecord rec = mdl_per->record();
        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;
        dlg = QMessageBox::question(this,
              "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
               QMessageBox::Yes | QMessageBox::No);

        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            mdl_per->removeRow(sample.row());
            //pmodel->endRemoveColumns();
            mdl_per->select();
        }
    }
}

void Cw_per::on_pB_YAZ_clicked ()
{

}

void Cw_per::on_pB_KPT_clicked ()
{
    this->hide ();
}


void Cw_per::ontV_per_resimGosterSLOT(QModelIndex)
{
    // makina stok tablosundan resim gösterme
    // view row unu tespit et
    int rowidx = tV_per->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = tV_per->
            model()->index( rowidx, mdl_per->fieldIndex ("resim") ).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    lB_rsm->setPixmap( outPixmap );
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}       ///     ontV_per_resimGosterSLOT

void Cw_per::onpB_per_resimEklE_clickedSLOT()
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
        QModelIndex index = tV_per->currentIndex();
        int row = index.row() ;
        // o row daki bilgelere ulaşalım
        mdl_per->setData(mdl_per->
                         index(row, mdl_per->fieldIndex ("resim")),inByteArray);
        mdl_per->submitAll();
    }
}       ///     onpb_resimEkleSLOT





void Cw_per::r_toFirst()
{
    map_per->toFirst ();
    int map_row = map_per->currentIndex ();
    pB_ilk->setEnabled (map_row>0);
    tV_per->setCurrentIndex(mdl_per->index( 0  ,0));
}

void Cw_per::r_toPrevious( )
{
    map_per->toPrevious ();
    int map_row = map_per->currentIndex ();
    pB_oncki->setEnabled(map_row > 0);
    tV_per->setCurrentIndex(mdl_per->index( map_row  ,0));
}

void Cw_per::r_toNext()
{
   map_per->toNext ();
   int map_row = map_per->currentIndex ();
   pB_snrki->setEnabled(map_row < mdl_per->rowCount() - 1);

   tV_per->setCurrentIndex(mdl_per->index( map_row  ,0));
}

void Cw_per::r_toLast()
{
    map_per->toLast ();
    int map_row = map_per->currentIndex ();
    pB_son->setEnabled(map_row < mdl_per->rowCount() - 1);
    tV_per->setCurrentIndex(mdl_per->index( mdl_per->rowCount() - 1  ,0));
}



void Cw_per::on_updateButtonsSLOT(int row)
{
   /* QModelIndex next_index = tV_per->model()->index(row + 1, 0);
    tV_per->setCurrentIndex(next_index);

    //tV_per->setSelectionModel (Qt::m);*/

    pB_ilk->setEnabled (row>0);
    pB_oncki->setEnabled(row > 0);
    pB_snrki->setEnabled(row < mdl_per->rowCount() - 1);
    pB_son->setEnabled(row < mdl_per->rowCount() - 1);



}



/* user interface */
void Cw_per::setup_map()
{
    map_per = new QDataWidgetMapper(this);
    map_per->setModel(mdl_per);

    map_per->addMapping(lE_isim , mdl_per->fieldIndex("isim"));
    map_per->addMapping(lE_soyad, mdl_per->fieldIndex("soyad"));
    map_per->addMapping(lE_tc, mdl_per->fieldIndex("tckimlik"));
    map_per->addMapping(lE_doyer, mdl_per->fieldIndex("dogumyeri"));
    map_per->addMapping(dT_dotar, mdl_per->fieldIndex("dogumtarihi"));
    map_per->addMapping(lE_baba, mdl_per->fieldIndex("babaadi"));

    map_per->addMapping(lE_bolum, mdl_per->fieldIndex("bolum"));
    //map_per->addMapping(lE_meslek, mdl_per->fieldIndex("meslek"));
    map_per->addMapping(lE_gorev, mdl_per->fieldIndex("gorev"));
    map_per->addMapping(lE_adres, mdl_per->fieldIndex("adres"));
    map_per->addMapping(lE_sehir, mdl_per->fieldIndex("sehir"));
    map_per->addMapping( lE_tel_cep, mdl_per->fieldIndex("tel_cep"));
    map_per->addMapping( lE_tel_ev, mdl_per->fieldIndex("tel_ev"));
    map_per->addMapping( lE_eposta, mdl_per->fieldIndex("eposta"));
    map_per->addMapping( lE_username, mdl_per->fieldIndex("username"));
    map_per->addMapping( lE_password, mdl_per->fieldIndex("password"));
    map_per->addMapping( lE_yetki, mdl_per->fieldIndex("yetki"));

    map_per->toFirst ();
    mdl_per->select();
    tV_per->setCurrentIndex(mdl_per->index(0,0));
}


void Cw_per::showEvent(QShowEvent *)
{
    qDebug() << "Personel dosyası açılıyor";
}

/*
void Cw_per::resim(QModelIndex)
{
    // personel tablosundan resim gösterme

    // view row unu tespit et
    int rowidx =   tV_per->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray =   tV_per->
            model()->index(rowidx,10).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );


    lB_rsm->setPixmap( outPixmap );
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_rsm->show();
}
*/
Cw_per::~Cw_per()
= default;




