#include "cw_ftr.h"
#include "cw_fr.h"
#include "cw_mlzm.h"
#include "ftr_frmekle.h"

#include "globals.h"
#include "hc_tableview.h"


Cw_ftr::Cw_ftr(QWidget *parent) :  QWidget(parent)
{
    //************************************************************
    //*****************  F A T U R A  ****************************
}



void Cw_ftr::setup_fatura()
{
    qDebug() << "FATURA";
    Cw_ftr::setWindowTitle("FATURA");
    this->setMinimumSize (800,400);
    Cw_ftr::showMaximized();

    setup_uiFtr();
    dbase = new DBase;

    setup_modelFtr ();
    setup_viewFtr () ;
    setup_mapFtr ()  ;
    setup_kntrlFtr ();

    setup_modelFtrDet() ;
    setup_viewFtrDet () ;
    setup_mapFtrDet ()  ;
    setup_kntrlFtrDet ();



}


void Cw_ftr::setup_uiFtr()
{
    qDebug() << "  setup_uiFtr";
    ////////////////////////////////////////// widgets
    wd_FTR();
    wd_FTRdet();
    //////////////////////////////////// depo tableview
    FTRtview = new HC_TableView;
    FTRtview->setMinimumSize (160,60);
    //////////////////////////////////// depodet
    ///  aslında malzemedet tableview
    FTRDETtview = new HC_TableView;
    FTRDETtview->setMinimumSize (160,60);

    ////////////////////////////////////////////// layout

    auto  frame1 = new QFrame;
    frame1->setFrameStyle(QFrame::Box | QFrame::Raised);
    auto *grid1 = new QGridLayout;
    frame1->setLayout (grid1);

    grid1->addWidget (FTRtview    , 1, 0, 1, 1);
    grid1->addWidget (wdgt_mapFTR , 1, 1, 1, 1);
    //grid1->addWidget (wdgt_rsm    , 1, 2, 1, 1);

    auto frame2 = new QFrame;
    auto *grid2 = new QGridLayout;
    frame2->setLayout (grid2);
    grid2->addWidget (FTRDETtview    , 1, 0 );
    grid2->addWidget (wdgt_mapFTR_dty, 1, 1 );

    ////////////////////////////////////////////// layout
    auto *LyG_FTR = new QGridLayout(this);
    LyG_FTR->addWidget (frame1 , 0, 0, 1, 1);
    LyG_FTR->addWidget (frame2 , 1, 0, 1, 1);


}

void Cw_ftr::wd_FTR()
{
    qDebug() << "  wd_FTR";

    lB_FTR = new QLabel ("Fatura");

    QLabel *lB_faturano = new QLabel(tr("Fatura &No"));
    lE_faturano = new QLineEdit();
    lE_faturano->setReadOnly (true);
    //lE_faturano->setPlaceholderText ("Fatura No ");
    lB_faturano->setBuddy(lE_faturano);

    QLabel *lB_firma = new QLabel(tr("Firma Ünvanı "));
    lE_firma = new HC_LE ;
    lE_firma->lineEdit->setReadOnly(true);

    // firma ismini fatyraya ekle
    connect(lE_firma->pushButton , &QPushButton::clicked,
            [this]()
    {
        // firma seçebilmek için firma penceresi
        auto *ftr = new Ftr_FrmEkle;


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // firma tableviewinde gezinirken firma adımız
        // signal ediliyor onu yakalayalım
        // seçim yapılan lineedit e aktaralım
        // ----------------------------------------------------

        connect (ftr->firma, &Cw_fr::sgnfirma,
                 [ this ] (QString secfirma )
        {
            this->lE_firma->lineEdit->setText (secfirma);
            this->lE_firma->lineEdit->setFocus();
        });
        ftr->exec ();
    });

    QLabel *lB_tarih = new QLabel(tr("Fatura &Tarihi"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

    QLabel *lB_ack = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_ack->setBuddy(lE_aciklama);

    auto *lB_ftrToplam = new QLabel(tr("Fatura Toplamı"));
    lE_ftrToplam = new QLineEdit();
    lB_ftrToplam->setBuddy(lE_ftrToplam);

    auto *lB_ftrKdv = new QLabel(tr("KDV"));
    lE_ftrKdv = new QLineEdit();
    lB_ftrKdv->setBuddy(lE_ftrKdv);

    auto *lB_ftrGenelToplam = new QLabel(tr("Genel Toplam"));
    lE_ftrGenelToplam = new QLineEdit();
    lB_ftrGenelToplam->setBuddy(lE_ftrGenelToplam);

    ///////////////////////////////////////  mapper buttonz

    LyG_FTR = new QGridLayout();
    int str{};
    LyG_FTR ->addWidget (new QLabel("<b>Fatura Başlık Bilgileri</b>"),str,0);
    LyG_FTR ->addWidget(lB_faturano, ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_faturano,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_firma   , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_firma   ,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_ack     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_aciklama,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_tarih   , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_tarih   ,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_ftrToplam     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ftrToplam     ,   str, 1, 1, 2);
    LyG_FTR ->addWidget(lB_ftrKdv     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ftrKdv     ,   str, 1, 1, 2);
    LyG_FTR ->addWidget(lB_ftrGenelToplam     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ftrGenelToplam     ,   str, 1, 1, 2);

    lB_rsm = new QLabel ("Resim");
    Resim resim(lB_rsm);
    LyG_FTR ->addWidget(lB_rsm  , str-2, 3, 3, 3);

    wdgt_mapFTR = new QWidget;
    wdgt_mapFTR->setLayout(LyG_FTR);

}

void Cw_ftr::setup_modelFtr()
{
    FTRmodel = new QSqlRelationalTableModel ;
    FTRmodel = dbase->modelFatura() ;
    qDebug() << "  setupmodelfatura";
}

void Cw_ftr::setup_viewFtr()
{
    qDebug() << "  setup_viewFtr";

    FTRtview->table->setModel ( FTRmodel );
    FTRtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FTRtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    FTRselectionMdl = FTRtview->table->selectionModel ();

    //// kullanıcı bu alanları görmesin
    FTRtview->table->setColumnHidden(FTRmodel->fieldIndex("ftr_kod"), true);
    FTRtview->table->setColumnHidden(FTRmodel->fieldIndex("ftr_resim"), true);


    FTRtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    FTRtview->table->horizontalHeader()->setStretchLastSection(true);
    FTRtview->table->horizontalHeader()->resizeContentsPrecision();
    FTRtview->table->resizeRowsToContents ();
    FTRtview->table->resizeColumnsToContents();


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

void Cw_ftr::setup_mapFtr()
{
    qDebug() << "  setup_mapFtr";
    FTRmapper = new QDataWidgetMapper(this);
    FTRmapper->setModel(FTRmodel);

    FTRmapper->addMapping(lE_faturano , FTRmodel->fieldIndex("ftr_no"));
    FTRmapper->addMapping(lE_firma->lineEdit, FTRmodel->fieldIndex("ftr_firma"));
    FTRmapper->addMapping(lE_tarih, FTRmodel->fieldIndex("ftr_tarih"));
    FTRmapper->addMapping(lE_aciklama, FTRmodel->fieldIndex("ftr_aciklama"));
    /// fatura ilk kayıda
    Cw_ftr::FTRmapper->toFirst ();
}

void Cw_ftr::setup_kntrlFtr()
{
    ///// tableview kontrol connectleri
    ///
    ///
    // //////////////////////// yeni fatura ekle
    // pB 001 yeni ekle
    connect(FTRtview->pB_ekle, &QPushButton::clicked ,
            [this ]()
    {
        auto *dia_fno =new QDialog(this);
        dia_fno->setModal (true);
        dia_fno->setWindowTitle ("Fatura No Giriniz");
        auto *ly_diafno = new QHBoxLayout(dia_fno) ;

        auto *wdkod = new QWidget;
        ly_diafno->addWidget (wdkod);

        auto *wd_ly = new QHBoxLayout;
        wdkod->setLayout (wd_ly);

        auto *lE_fno = new QLineEdit{};
        //lE_fno->setPlaceholderText ("Fatura No Giriniz...");


        auto *pB_vz = new QPushButton("Vazgeç");
        connect(pB_vz, &QPushButton::clicked,
                [dia_fno] ()
        {

            dia_fno->close() ;
        });


        auto *pB_ok = new QPushButton("Kaydet");
        pB_ok->setDefault (true);



        auto *pb_ly = new QHBoxLayout;
        pb_ly->addWidget (pB_vz);
        pb_ly->addWidget (pB_ok);

        wd_ly->addWidget (lE_fno);
        wd_ly->addLayout (pb_ly);


        // fatura no önemli
        // boş geçmek olmaz

        // ///////////////// yeni fatura no ekle
        connect(pB_ok, &QPushButton::clicked ,
                [this,lE_fno, dia_fno ]()
        {

            //  qDebug()<<"fatura no boş geçilemez";
            if (lE_fno->text () == "")
            {
                lE_fno->setPlaceholderText ("fatura no boş geçilemez");
                return;
            }

            // kayıt oluşturalım
            QSqlRecord rec = FTRmodel->record();
            rec.setValue ("ftr_no"      , lE_fno->text ());
            QString date(QDate::currentDate().toString ( "dd-MM-yyyy" ));

            rec.setValue ("ftr_tarih"   , date );

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
            }
            dia_fno->close ();
        });

        dia_fno->exec ();
    });

    // ///////////////  resim ekle
    // pB 002 yeni resim ekle
    connect(FTRtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {

        Resim resim;
        resim.resimUpdate (lB_rsm, FTRtview, FTRmodel, FTRselectionMdl,
                           "ftr_resim", "ekle");
    });

    // row değiştiğnde resmide değiştirelim
    // -- 003   row değiştiğinde resmide değiştirelim
    connect( FTRselectionMdl , &QItemSelectionModel::currentRowChanged,
             [this ]()
    {
        Resim resim;
        resim.resimUpdate (lB_rsm, FTRtview, FTRmodel, FTRselectionMdl,
                           "ftr_resim");
    });


    // pB 004 yeni camera resim ekle



    // fattura sil
    // pB 005 sil
    connect(FTRtview->pB_sil, &QPushButton::clicked,
            [this]()
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
                    FTRtview->table->setFocus ();
                    FTRmodel->select ();



                    if (FTRmodel->rowCount () == 1)
                    {
                        FTRtview->table->selectRow (0);
                        FTRtview->table->setCurrentIndex (FTRmodel->index(0,0));
                    }
                    if (FTRmodel->rowCount () > 1)
                    {
                        if (ftrindex.row () == 0)
                        {
                            FTRtview->table->selectRow (0);
                            FTRtview->table->setCurrentIndex (FTRmodel->index(0,0));
                        }
                        else if (ftrindex.row () > 0)
                        {
                            FTRtview->table->selectRow (ftrindex.row()-1);
                            FTRtview->table->setCurrentIndex (FTRmodel->index(ftrindex.row ()-1,0));
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
    });

    // pB 006 ilk
    connect(FTRtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FTRmapper->toFirst ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_ilk->setEnabled (map_row>0);
        FTRtview->table->setCurrentIndex(FTRmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(FTRtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toPrevious ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_ncki->setEnabled(map_row > 0);
        FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));
    });

    // pB 008 sonraki
    connect(FTRtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toNext ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_snrki->setEnabled(map_row < FTRmodel->rowCount() - 1);
        FTRtview->table->setCurrentIndex(FTRmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(FTRtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toLast ();
        int map_row = FTRmapper->currentIndex ();
        FTRtview->pB_son->setEnabled(map_row < FTRmodel->rowCount() - 1);
        FTRtview->table->setCurrentIndex(FTRmodel->index( FTRmodel->rowCount() - 1  ,0));
    });



    /// depo map nav tuslari kontrol
    // pB 010 nav tuslari kontrol
    connect(FTRmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        FTRtview->pB_ilk->setEnabled (row>0);
        FTRtview->pB_ncki->setEnabled(row > 0);
        FTRtview->pB_snrki->setEnabled(row < FTRmodel->rowCount() - 1);
        FTRtview->pB_son->setEnabled(row < FTRmodel->rowCount() - 1);

    });







    /// row değiştiğinde
    // --- 011
    connect (FTRselectionMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index )
    {

        // 011-01 mapper indexi ayarla
        FTRmapper->setCurrentModelIndex (Index);
    });

    /// depo da kolon değiştiğinde mapper index te değişsin
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  FTRselectionMdl, &QItemSelectionModel::currentColumnChanged,
              FTRmapper, &QDataWidgetMapper::setCurrentModelIndex);
}

///************************************************************
///****************  F A T U R A   S  L  O  T  S  ************





void Cw_ftr::slt_ftr_hesap()
{
    qDebug() << "ftr_hesapp";

    QModelIndex ftr_indx = FTRtview->table->currentIndex ();
    if ( ftr_indx.row () >= 0 )
    {
        int fatura_row = ftr_indx.row ();
        int id = FTRmodel->
                data ( FTRmodel->
                       index(fatura_row,FTRmodel->
                             fieldIndex("ftr_no"))).toInt () ;

        QSqlQuery q_qry;
        QString s_qry;
        // fstura toplamı
        s_qry = QString ("SELECT SUM"
                         "("
                         "(mlzmdet_fiyat) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            lE_ftrToplam->setText ( q_qry.value(0).toString ()) ;
        }
        else
        {
            qDebug() << " query inactive 1"<<endl<< q_qry.lastError ().text ();
        }
        // kdv
        s_qry = QString ("SELECT SUM"
                         "("
                         "((mlzmdet_fiyat*mlzmdet_kdv/100)) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            lE_ftrKdv->setText (q_qry.value(0).toString ());
        }

        else
        {
            qDebug() << " query inactive 2"<<endl<< q_qry.lastError ().text ();
        }
        // Genel Toplam
        s_qry = QString ("SELECT SUM"
                         "("
                         "(mlzmdet_fiyat + (mlzmdet_fiyat*mlzmdet_kdv/100)) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            lE_ftrGenelToplam->setText (q_qry.value(0).toString ());
        }

        else
        {
            qDebug() << " query inactive 3 "<<endl<< q_qry.lastError ().text ();
        }
    }
}  ///**************************************** fatura hesap




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

    /// malzeme adı değiştirlemez
    /// sadece yeni kayıt ile eklenir
    /// mlzm kod birim ve barkod isme bağlı
    QLabel *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
    lE_mlzm = new QLineEdit;
    lE_mlzm->setReadOnly (true);


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

    auto *lYG_d_map = new QGridLayout();
    int str{};
    lYG_d_map->addWidget (new QLabel("<b>Fatura Detay Bilgileri</b>"),str,0);
    lYG_d_map->addWidget(lB_mlzdetbarkod  , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbarkod  ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmlzm    , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzm          ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetgc      , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetgc      ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmiktar  , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetmiktar  ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetbirim   , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbirim   ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetfiyat   , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetfiyat   ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetkdv     , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetkdv     ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetaciklama, ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetaciklama,   str, 1, 1, 1);

    wdgt_mapFTR_dty = new QWidget;
    wdgt_mapFTR_dty->setLayout(lYG_d_map);
}


void Cw_ftr::setup_modelFtrDet()
{
    qDebug() << "  setup_modelFtrDet";
    FTRDETmodel = new QSqlRelationalTableModel;
    FTRDETmodel = dbase->modelMalzemeDetay ();
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


    FTRDETtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    FTRDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FTRDETtview->table->resizeRowsToContents ();
    FTRDETtview->table->resizeColumnsToContents();
    FTRDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    FTRDETtview->table->horizontalHeader()->
            setStretchLastSection(true);
    FTRDETtview->table->horizontalHeader()->
            resizeContentsPrecision();


    FTRtview->table->setCurrentIndex(
                FTRmodel->index(0,1)
                );
    FTRtview->table->setFocus();


}


void Cw_ftr::setup_mapFtrDet()
{
    qDebug() << "  setup_mapFtrDet";
    FTRDETmapper = new QDataWidgetMapper(this);
    FTRDETmapper->setModel(FTRDETmodel);

    //FTRDETmapper->addMapping(lE_d_faturano , FTRDETmodel->fieldIndex("faturano"));
    //FTRDETmapper->addMapping(lE_d_firma, FTRDETmodel->fieldIndex("firma"));
    FTRDETmapper->addMapping(lE_mlzdetbarkod, FTRDETmodel->fieldIndex("mlzmdet_barkod"));
    FTRDETmapper->addMapping(lE_mlzm, FTRDETmodel->fieldIndex("mlzmdet_malzeme"));
    FTRDETmapper->addMapping(lE_mlzdetmiktar, FTRDETmodel->fieldIndex("mlzmdet_miktar"));
    FTRDETmapper->addMapping(lE_mlzdetbirim, FTRDETmodel->fieldIndex("mlzmdet_birim"));
    FTRDETmapper->addMapping(lE_mlzdetfiyat, FTRDETmodel->fieldIndex("mlzmdet_fiyat"));
    FTRDETmapper->addMapping(lE_mlzdetkdv, FTRDETmodel->fieldIndex("mlzmdet_kdv"));
    FTRDETmapper->addMapping(lE_mlzdetaciklama, FTRDETmodel->fieldIndex("mlzmdet_aciklama"));


    /// depodetay varsa ilk kayda
    Cw_ftr::FTRDETmapper->toFirst ();

}

void Cw_ftr::setup_kntrlFtrDet()
{
    /////////////////
    ///
    /// CONNECT


    /// fatura detaya yeni bir kayıt ekleyelim
    /// bunu yaparken
    /// 1- faturadan fatura no, firma ve detay
    /// 2- Malzemeden fatura detaya eklenecek
    ///    mlz kod, barkod, isim ve birimi ekleyelim
    /// 3- diğer alanları mikttar fiyat vb
    ///    kullanıcıdan isteyelim

    // pB 001 yeni ekle
    connect(FTRDETtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        qDebug() << "  slt_mlz_pB_EKLE_clicked";

        // 001 faturaya malzeme detayı eklemek için dialog oluşturalım
        auto *dia_ftrmlzmekle = new QDialog(this);
        //dia_ftrmlzmekle->setModal (true);
        dia_ftrmlzmekle->setGeometry (50,50,300,300);
        dia_ftrmlzmekle->setWindowTitle ("Faturaya Malzeme Kaydı Ekle");


        // 002 fatura başlığından fatura no (malzemedetayda = gcno)
        //     ve tarihi alalım
        QModelIndex ftr_indx = FTRtview->table->currentIndex () ;
        int ftr_row = ftr_indx.row ();

        QString ftrno = FTRmodel->
                data ( FTRmodel->
                       index(ftr_row,FTRmodel->
                             fieldIndex("ftr_no"))).toString() ;
        QString ftrfrm = FTRmodel->
                data ( FTRmodel->
                       index(ftr_row,FTRmodel->
                             fieldIndex("ftr_firma"))).toString() ;

        QString ftrtarih = FTRmodel->
                data ( FTRmodel->
                       index(ftr_row,FTRmodel->
                             fieldIndex("ftr_tarih"))).toString() ;



        // 003 dialoğumuzda fatura detayında olması gerekenleri ekleyelim

        ///  malzemeden malzeme adını almak için linedit ve ekleme pB
        auto *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
        lE_mlzdetmlzm = new HC_LE;
        lE_mlzdetmlzm->lineEdit->setReadOnly (true);

        ///  malzemeden malzeme kod - barkod - birim
        // sgn ile gelen kod barkod ve birim için değişken
        auto *mlzmKod= new QString{};
        auto *mlzmBarkod= new QString{};
        auto *mlzmBirim= new QString{};
        /////////////////////////////////////////////////////////////////
        /// malzeme adını almak için class devrede
        /// class ın içinden malzeme detay bilgilerine
        /// ulaşmak mümkün (mlz->malzeme->MLZMmodel
        /// ama sinyal yoluyla alıyoruz ve classın içeriği hakkında
        /// bişey bilmemiz gerekmiyor...
        ///
        auto *mlz = new FtrDet_MlzEkle;
        mlz->hide();
        connect (lE_mlzdetmlzm->pushButton, &QPushButton::clicked,
                 [this, mlz, mlzmKod, mlzmBarkod, mlzmBirim ] ()
        {
            mlz->show();
            /// malzeme detay seçebilmek için pencere
            /// bu pencerenin açılması için
            /// malzeme adı linedeitinin yanındaki
            /// pushbuttonu tıklamak gerekir
            /// HC_LE classında lineedit + pushbutton var

            /////////////////////////////////////////////////////////////////////////////////
            /// ----------------------------------------------------
            /// malzeme tableviewinde gezinirken
            /// 1 - malzeme kodu
            /// 2 - malzeme barkodu
            /// 3 - malzeme adı
            /// 4 - birim
            /// signal ediliyor onu yakalayalım
            /// seçim yapılan lineedit e aktaralım
            /// ----------------------------------------------------

            connect (mlz->malzeme, &Cw_Mlzm::sgnMalzeme,
                     [ this, mlzmKod, mlzmBarkod, mlzmBirim ] (QString secKod,
                     QString secBarkod,
                     QString secMalzeme,
                     QString secBirim )
            {

                *mlzmKod = secKod;
                *mlzmBarkod = secBarkod;
                *mlzmBirim = secBirim;
                this->lE_mlzdetbarkod->setText(secBarkod);
                this->lE_mlzdetmlzm->lineEdit->setText (secMalzeme);
                this->lE_mlzdetmlzm->lineEdit->setFocus();
                qDebug()<<"signal cathed = "<< secMalzeme ;
            });   /// signal
            mlz->exec ();
            qDebug()<<"selected malzeme = "<< mlz->getMalzeme ();

        });  /// HC_LE pushbutton

        /// yeni kayıt ekleme içerisinde
        /// malzeme lineeditin pushbuttonu kontrol edildi
        /// pb na basıldığında malzeme penceresi açıldı
        /// malzeme ismi - kod - barkod - birim signalı alınmaya başlandı


        /// diğer alanlarıda elle dolduralım

        /// - FATURA BAŞLIĞI
        auto *lB_fno = new QLabel("Fatura No");
        auto lE_fno = new QLineEdit ;
        lE_fno->insert (ftrno);
        lE_fno->setReadOnly (true);
        auto *lB_ftr = new QLabel("Fatura Tarihi");
        auto lE_ftr = new QLineEdit ;
        lE_ftr->setText (ftrtarih);
        lE_ftr->setReadOnly (true);
        auto *lB_frm = new QLabel("Firma");
        auto lE_frm = new QLineEdit ;
        lE_frm->setText (ftrfrm);
        lE_frm->setReadOnly (true);

        /// - YENİ GİRİLMESİ GEREKEN ALANLAR
        auto *lB_miktar = new QLabel("Miktar");
        auto *lE_miktar = new QLineEdit;
        auto *lB_bfiyat = new QLabel("Birim Fiyatı");
        auto *lE_bfiyat = new QLineEdit;
        auto *lB_kdv = new QLabel("KDV oranı");
        auto *lE_kdv = new QLineEdit;
        lE_kdv->setText ("18");
        auto *lB_ckl = new QLabel("Açıklama");
        auto *lE_ckl = new QLineEdit;

        auto *lay_dia = new QGridLayout(dia_ftrmlzmekle);
        int str{};
        lay_dia->addWidget (lB_frm   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_frm   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_fno   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_fno   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_ftr   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_ftr   ,  str, 1, 1, 1);

        lay_dia->addWidget (lB_mlzdetmlzm   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_mlzdetmlzm ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_miktar,++str, 0, 1, 1);
        lay_dia->addWidget (lE_miktar,  str, 1, 1, 1);
        lay_dia->addWidget (lB_bfiyat,++str, 0, 1, 1);
        lay_dia->addWidget (lE_bfiyat,  str, 1, 1, 1);
        lay_dia->addWidget (lB_kdv   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_kdv   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_ckl   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_ckl   ,  str, 1, 1, 1);



        // yeni faturamızı ekleyelim
        QPushButton *pB_mlzekle = new QPushButton("Faturaya Malzeme Kaydı Ekle");
        QPushButton *pB_vzgc = new QPushButton("Kapat");
        lay_dia->addWidget (pB_vzgc       ,++str, 0, 1, 1 );
        lay_dia->addWidget (pB_mlzekle    ,  str, 1, 1, 2 );

        // ekle pencerelrini kapatalım
        connect (pB_vzgc, &QPushButton::clicked,
                 [dia_ftrmlzmekle, mlz ] ()
        {
            dia_ftrmlzmekle->close ();
            mlz->close ();
        });


        /// tüm bilgileri "Faturaya Malzeme Kaydı Ekle"
        /// tuşuna basılırsa fatura detaya eklelyelim
        connect (pB_mlzekle, &QPushButton::clicked,
                 [this, mlzmKod, mlzmBirim,mlzmBarkod,
                 lE_miktar, lE_bfiyat, lE_kdv, lE_ckl,
                 ftrno, ftrtarih
                 ]()
        {

            // malzeme bilgileri fatura detay için yeterli
            // boş geçilmeyecek bir alan yok

            // kayıt oluşturalım
            QSqlRecord rec = FTRDETmodel->record();

            rec.setValue ("mlzmdet_mlzm_kod" , *mlzmKod );    /// signal
            rec.setValue ("mlzmdet_barkod"   , *mlzmBarkod ); /// signal
            rec.setValue ("mlzmdet_malzeme"  , lE_mlzdetmlzm->lineEdit->text() ); /// signal
            rec.setValue ("mlzmdet_tarih"    , ftrtarih); /// faturadan
            rec.setValue ("mlzmdet_gc"       , "Faturalı Giriş");   // yeni girildi
            rec.setValue ("mlzmdet_gcno"     , ftrno);    /// faturadan
            rec.setValue ("mlzmdet_miktar"   , lE_miktar->text ()); // yeni girildi
            rec.setValue ("mlzmdet_birim"    , *mlzmBirim );   /// signal
            rec.setValue ("mlzmdet_fiyat"    , lE_bfiyat->text ()); // yeni girildi
            rec.setValue ("mlzmdet_kdv"      , lE_kdv->text ());    // yeni girildi
            rec.setValue ("mlzmdet_aciklama" , lE_ckl->text ());    // yeni girildi


            // insert a new record (-1)
            if ( ! FTRDETmodel->insertRecord(FTRDETmodel->rowCount (),rec))
            {
                qDebug() << " HATA - FATura Detaya kayıt eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt FATURA Detaya eklendi ";
                FTRDETmodel->submitAll ();
                FTRDETmodel->select ();
                // kayıt eklendi yeni kayıt için hazırlık yap
                lE_mlzdetmlzm->lineEdit->setText("");
                lE_miktar->setText ("");
                lE_bfiyat->setText ("");
                lE_kdv->setText ("18");
                lE_ckl->setText ("");



                QModelIndex ftr_ndx= FTRDETmodel->
                        index (FTRDETmodel->rowCount ()-1,0);
                FTRDETtview->table->selectRow (ftr_ndx.row ());


            }

        }); /// kaydı dosyaya kaydet pb

        dia_ftrmlzmekle->show ();

        qDebug ()<<"mlzm un 4";



    });  /// FTRDETtview yeni kayıt pushbutton

    // pB 002 yeni resim ekle

    // -- 003  row değiştiğnde resmide değiştirelim

    // pB 004 yeni camera resim ekle

    // pB 005 sil
    connect(FTRDETtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
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

    });



    // pB 006 ilk
    connect(FTRDETtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FTRDETmapper->toFirst ();
        FTRDETtview->pB_ilk->setEnabled (FTRDETmapper->currentIndex ()>0);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(FTRDETtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FTRDETmapper->toPrevious ();
        FTRDETtview->pB_ncki->setEnabled(FTRDETmapper->currentIndex () > 0);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmapper->currentIndex () ,0));
    });

    // pB 008 sonraki
    connect(FTRDETtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FTRDETmapper->toNext ();
        int map_row = FTRDETmapper->currentIndex ();
        FTRDETtview->pB_snrki->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(FTRDETtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FTRmapper->toLast ();
        int map_row = FTRDETmapper->currentIndex ();
        FTRDETtview->pB_son->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmodel->rowCount() - 1  ,0));
    });

qDebug()<<" 1 ";
    /// depodet map değiştiğinde nav tuşalrı ayarlansın
    // pB 010 nav tuslari kontrol
    connect(FTRDETmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //.row ();   //FTRDETmapper->currentIndex ();
        FTRDETtview->pB_ilk->setEnabled (row>0);
        FTRDETtview->pB_ncki->setEnabled(row > 0);
        FTRDETtview->pB_snrki->setEnabled(row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->pB_son->setEnabled(row < FTRDETmodel->rowCount() - 1);

    });
qDebug()<<" 2 ";
    // --- 011 row değiştiğinde 3 şey olsun
    connect( FTRDETselectionMdl, &QItemSelectionModel::currentRowChanged,
               [this]( QModelIndex Index )
    {
        if (Index.isValid())
        {

        qDebug()<<" 3323 ";
        // 011-01 mapper indexi ayarla
        FTRDETmapper->setCurrentModelIndex(Index);

        // 011-02 filtrele
         QSqlRecord record = FTRmodel->record(Index.row ());
            QString fatura_no = record.value("ftr_no").toString ();
            FTRDETmodel->setFilter (QString("mlzmdet_gcno = %1").arg(fatura_no) );

        }
        else
        {
            FTRDETmodel->setFilter("mlzdet_gcno=-1");
qDebug()<<" 32 ";
        }
        FTRDETmodel->select();

        qDebug()<<" 23 ";
        // 011-03 fatura hesabı yapılsın
        this->slt_ftr_hesap ();

    });
qDebug()<<" 3 ";
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(FTRDETselectionMdl, &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        FTRDETmapper->setCurrentModelIndex(Index);
    });

qDebug()<<" 4 ";
    // --- 013 tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    connect(FTRDETtview->table->model() ,
            &QSqlTableModel::dataChanged , this,
            &Cw_ftr::slt_ftr_hesap);

    // --- 014 depodet miktar değiştiğinde depo envanter hesabı
    connect (lE_mlzdetmiktar, &QLineEdit::editingFinished, this,
             &Cw_ftr::slt_ftr_hesap);
    qDebug()<<" 5 ";
}

void Cw_ftr::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Ftr dosyası açılıyor";
}

Cw_ftr::~Cw_ftr()
{
    //    delete ui;
}
