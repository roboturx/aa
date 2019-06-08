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
    qDebug() << "setup FİRMA";

    setup_ui();

    dbase = new DBase ;

    setup_modelfr();
    setup_viewfr();
    setup_mapfr();

    qDebug() << "setup_Firma END";
}



void Cw_fr::setup_ui()
{

    qDebug() << "  setup_uiFr";

    Cw_fr::setWindowTitle ("FİRMA");
    //Cw_fr::resize(qApp->screens()[0]->size()*.8);
    Cw_fr::showMaximized ();


    // ///////////////////////////////////////////////////////
    // pButtonzzz


    lB_fr  = new QLabel (tr("Firma"));
    lB_rsm = new QLabel (tr("Resim"));


    // ///////////////////////////////////////////////////////
    // views
    int i=1;
    FRMtview = new HC_TableView(i);

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


    auto *lYG_map = new QGridLayout;

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
    //lYG_map->addWidget(lB_rsm    , 9, 1, 1, 2);
    // /////////////////////////////////////
    // main layout

    auto *lYG_per = new QGridLayout(this);

    lYG_per->addWidget ( FRMtview ,0 ,0 ,2 ,1 );
    lYG_per->addLayout ( lYG_map   ,0 ,1 ,1 ,1);
    lYG_per->addWidget ( lB_rsm   ,1 ,1 ,1 ,1);

}

void Cw_fr::setup_modelfr()
{
    qDebug()<<"setup model fr";
    FRMmodel = new QSqlRelationalTableModel ;
    FRMmodel = dbase->modelFirma() ;
}


void Cw_fr::setup_viewfr()
{
    qDebug()<<"setup view fr";

    FRMtview->table->setModel(FRMmodel);

    //   FRMselectionMdlxxx = new QItemSelectionModel( FRMmodel );
    FRMtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FRMtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    FRMselectionMdlxxx = FRMtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    FRMtview->table->setColumnHidden(FRMmodel->fieldIndex("frm_kod"), true);
    FRMtview->table->setColumnHidden(FRMmodel->fieldIndex("frm_resim"), true);

    FRMtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    FRMtview->table->horizontalHeader()->setStretchLastSection(true);
    FRMtview->table->horizontalHeader()->resizeContentsPrecision();
    FRMtview->table->resizeRowsToContents ();
    FRMtview->table->resizeColumnsToContents();

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    FRMtview->table->setCurrentIndex(
                FRMmodel->index(0, 1)
                );
    // with blue rect
    FRMtview->table->setFocus();
    //   QTimer::singleShot(0, FRMtview->table, SLOT(setFocus()));

    ///// tableview kontrol connectleri
    ///
    ///

    // yeni firma ekle
    connect(FRMtview->pB_ekle, &QPushButton::clicked ,
            [this]()
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
            qDebug() << "HATA - Firma kaydı eklenemedi ";
        }
        else
            qDebug() << "Firma Kaydı eklendi ";
        FRMmodel->select();
    });


    connect(FRMtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        //firma resim ekle
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
            QModelIndex index = FRMtview->table->currentIndex();
            int row = index.row() ;
            // o row daki bilgelere ulaşalım
            FRMmodel->setData(FRMmodel->
                              index(row, FRMmodel->fieldIndex
                                    ("frm_resim")),inByteArray);
            FRMmodel->submitAll();
        }
    });


    /// firm  değiştiğnde resmide değiştirelim
    connect(  FRMselectionMdlxxx , &QItemSelectionModel::currentRowChanged,
              [this]()
    {

        int rowidx = FRMselectionMdlxxx->currentIndex().row();
        QByteArray outByteArray = FRMtview->table->
                model()->index( rowidx,
                                FRMmodel->fieldIndex ("frm_resim") ).data().toByteArray();

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
    });





    connect(FRMtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   FRMtview->table->currentIndex();
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
    });


    connect(FRMtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FRMmapper->toFirst ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_ilk->setEnabled (map_row>0);
        FRMtview->table->setCurrentIndex(FRMmodel->index( 0  ,0));
    });


    connect(FRMtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toPrevious ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_ncki->setEnabled(map_row > 0);
        FRMtview->table->setCurrentIndex(FRMmodel->index( map_row  ,0));
    });


    connect(FRMtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toNext ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_snrki->setEnabled(map_row < FRMmodel->rowCount() - 1);
        FRMtview->table->setCurrentIndex(FRMmodel->index( map_row  ,0));
    });


    connect(FRMtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FRMmapper->toLast ();
        int map_row = FRMmapper->currentIndex ();
        FRMtview->pB_son->setEnabled(map_row < FRMmodel->rowCount() - 1);
        FRMtview->table->setCurrentIndex(FRMmodel->index( FRMmodel->rowCount() - 1  ,0));
    });


}





/* user interface */
void Cw_fr::setup_mapfr()
{
    qDebug()<<"setup mapfr";
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

    /// depo map nav tuslari kontrol
    connect(FRMmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        FRMtview->pB_ilk->setEnabled (row>0);
        FRMtview->pB_ncki->setEnabled(row > 0);
        FRMtview->pB_snrki->setEnabled(row < FRMmodel->rowCount() - 1);
        FRMtview->pB_son->setEnabled(row < FRMmodel->rowCount() - 1);

    });

    // firmada row değiştiğinde 2 şey olsun
    connect(  FRMselectionMdlxxx ,
              &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // firmada row değiştiğinde mapper index te değişsin
        FRMmapper->setCurrentModelIndex(Index);
        // firmada row değiştiğinde firma ismini etrafa yayınlayalım
        emit Cw_fr::sgnfirma(
                    FRMtview->table->
                    model()->index( Index.row() ,
                                    FRMmodel->fieldIndex ("frm_unvan") ).data().toString()
                    ) ;
    });
    /// depo da kolon değiştiğinde indexte değişsin
    connect(  FRMselectionMdlxxx ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        FRMmapper->setCurrentModelIndex(Index);
    });

    /// firma ilk kayıda
    Cw_fr::FRMmapper->toFirst ();
}



void Cw_fr::showEvent(QShowEvent *)
{
    qDebug() << "ShowEvent Firma dosyası açılıyor";
}


Cw_fr::~Cw_fr()
= default;


