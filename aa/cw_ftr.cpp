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
    Cw_ftr::showMaximized();
    setup_uiFtr();

    dbase = new DBase;

    setup_modelFtr();
    setup_viewFtr();
    setup_mapFtr();

    setup_modelFtrDet();
    setup_viewFtrDet();
    setup_mapFtrDet();




    /// depodet miktar değiştiğinde depo envanter hesabı
    connect (lE_mlzdetmiktar, &QLineEdit::editingFinished, this,
             &Cw_ftr::slt_ftr_hesap);



}


void Cw_ftr::setup_uiFtr()
{
    qDebug() << "  setup_uiFtr";
    ////////////////////////////////////////// widgets
    wd_FTR();
    wd_FTRdet();
    //////////////////////////////////// depo tableview
    int i=1;
    FTRtview = new HC_TableView(i);
    FTRtview->setMinimumSize (60,100);
    //////////////////////////////////// depodet
    ///  aslında malzemedet tableview
    FTRDETtview = new HC_TableView(i);
    FTRDETtview->setMinimumSize (60,100);

    ////////////////////////////////////////////// layout
    auto  frame1 = new QFrame;
    frame1->setLineWidth (3);
    frame1->setFrameStyle(QFrame::Box | QFrame::Raised);
    auto *grid1 = new QGridLayout;
    frame1->setLayout (grid1);
    grid1->addWidget (FTRtview    , 0, 0, 2, 1);
    grid1->addWidget (wdgt_mapFTR , 0, 1, 1, 1);
    //grid1->addWidget (wdgt_rsm    , 1, 2, 1, 1);

    auto frame2 = new QFrame;
    auto *grid2 = new QGridLayout;
    frame2->setLayout (grid2);
    grid2->addWidget (FTRDETtview    , 0, 0 );
    grid2->addWidget (wdgt_mapFTR_dty, 0, 1 );

    ////////////////////////////////////////////// layout
    auto *LyG_FTR = new QGridLayout(this);
    LyG_FTR->addWidget (frame1 , 0, 0, 1, 1);
    LyG_FTR->addWidget (frame2 , 1, 0, 1, 1);


}

void Cw_ftr::wd_FTR()
{
    qDebug() << "  wd_FTR";

    lB_FTR     = new QLabel ("Fatura");
    lB_rsm = new QLabel (tr("Resim"));

    QLabel *lB_faturano = new QLabel(tr("Fatura &No"));
    lE_faturano = new QLineEdit();
    lE_faturano->setReadOnly (true);
    //lE_faturano->setPlaceholderText ("Fatura No ");

    lB_faturano->setBuddy(lE_faturano);

    //  lB_brkd->setText (lB_faturano->text ());

    QLabel *lB_firma = new QLabel(tr("Firma Ünvanı "));
    lE_firma = new HC_LE ;
    lE_firma->lineEdit->setReadOnly(true);
    // lB_firma->setBuddy(lE_firma);
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
            qDebug()<<"signal cathed"<< secfirma ;
        });
        ftr->exec ();
        qDebug()<<"selected firma"<< ftr->getFirma ();
    }
    );

    QLabel *lB_tarih = new QLabel(tr("Fatura &Tarihi"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

    QLabel *lB_ack = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_ack->setBuddy(lE_aciklama);

    auto *lB_ft1 = new QLabel(tr("Fatura Toplamı"));
    auto *lE_ft1 = new QLineEdit();
    lB_ft1->setBuddy(lE_ft1);

    auto *lB_ft2 = new QLabel(tr("KDV"));
    auto *lE_ft2 = new QLineEdit();
    lB_ft2->setBuddy(lE_ft2);

    auto *lB_ft3 = new QLabel(tr("Genel Toplam"));
    auto *lE_ft3 = new QLineEdit();
    lB_ft3->setBuddy(lE_ft3);

    lB_rsm = new QLabel("Resim");
    lB_rsm->setScaledContents( true );
    lB_rsm->setSizePolicy( QSizePolicy::Preferred,
                           QSizePolicy::Preferred );
    lB_rsm->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(lB_rsm , &QLabel::customContextMenuRequested,
            [ this ]()
    {
        QLabel *x = new QLabel();
        x->resize(QGuiApplication::primaryScreen()->
                  availableSize() * 3 / 5);
        x->setScaledContents(true);
        x->setPixmap(QPixmap (*lB_rsm->pixmap() ) );
        x->setWindowTitle("FATURA RESİM");
        x->show();
    });




    ///////////////////////////////////////  mapper buttonz

    LyG_FTR = new QGridLayout();
    int str{};
    LyG_FTR ->addWidget(lB_faturano,   str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_faturano,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_firma   , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_firma   ,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_ack     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_aciklama,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_tarih   , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_tarih   ,   str, 1, 1, 4);
    LyG_FTR ->addWidget(lB_ft1     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ft1     ,   str, 1, 1, 2);
    LyG_FTR ->addWidget(lB_ft2     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ft2     ,   str, 1, 1, 2);
    LyG_FTR ->addWidget(lB_ft3     , ++str, 0, 1, 1);
    LyG_FTR ->addWidget(lE_ft3     ,   str, 1, 1, 2);
    LyG_FTR ->addWidget(lB_rsm     , str-2, 3, 3, 3);

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





    ///// tableview kontrol connectleri
    ///
    ///


    // //////////////////////// yeni fatura ekle
    connect(FTRtview->pB_ekle, &QPushButton::clicked ,
            [this ]()
    {
        auto *dia_fno =new QDialog(this);
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
    connect(FTRtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {

        // fatura resim ekle
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
                              index(row, FTRmodel->fieldIndex
                                    ("ftr_resim")),inByteArray);
            /// yeni eklenenleri kaydedelim
            FTRmodel->submitAll();
        }
    });



    // row değiştiğnde resmide değiştirelim
    connect( FTRselectionMdl , &QItemSelectionModel::currentRowChanged,
             [this]()
    {

        // view row unu tespit et
        int rowidx = FTRselectionMdl->currentIndex().row();

        // row, xolumn daki veriyi bytearray a at
        QByteArray outByteArray = FTRtview->table->
                model()->index( rowidx, FTRmodel->
                                fieldIndex ("ftr_resim") ).data().toByteArray();

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


    //faturada  row değiştiğinde malzeme filtrele
    connect (FTRselectionMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index )
    {
        if (Index.isValid())
        {
            QSqlRecord record = FTRmodel->record(Index.row ());
            QString fatura_no = record.value("ftr_no").toString ();
            FTRDETmodel->setFilter (QString("mlzmdet_gcno = %1").arg(fatura_no) );

        }
        else
        {
            FTRDETmodel->setFilter("mlzdet_gcno=-1");
        }
        FTRDETmodel->select();
    });


    // fattura sil
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


    /// depo map nav tuslari kontrol
    connect(FTRmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        FTRtview->pB_ilk->setEnabled (row>0);
        FTRtview->pB_ncki->setEnabled(row > 0);
        FTRtview->pB_snrki->setEnabled(row < FTRmodel->rowCount() - 1);
        FTRtview->pB_son->setEnabled(row < FTRmodel->rowCount() - 1);

    });

    /// depo da row değiştiğinde mapper index te değişsin
    connect(  FTRselectionMdl,&QItemSelectionModel::currentRowChanged,
              FTRmapper, &QDataWidgetMapper::setCurrentModelIndex);

    /// depo da kolon değiştiğinde mapper index te değişsin
    connect(  FTRselectionMdl, &QItemSelectionModel::currentColumnChanged,
              FTRmapper, &QDataWidgetMapper::setCurrentModelIndex);

    /// fatura ilk kayıda
    Cw_ftr::FTRmapper->toFirst ();



}

///************************************************************
///****************  F A T U R A   S  L  O  T  S  ************




//void Cw_ftr::slt_ftr_pB_Eklersm_clicked()
//{
//    qDebug() << "  slt_ftr_pB_Eklersm_clicked";
//    // depo resim ekle
//    QString myfile = QFileDialog::
//            getOpenFileName(this,
//                            tr("Resim Aç"), "/home/mr/Resimler",
//                            tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
//                               " ;; Tüm Dosyalar (*,*)"));

//    if (myfile == "")
//        return;

//    QImage image(myfile);
//    lB_rsm->setPixmap(QPixmap::fromImage(image));
//    QByteArray inByteArray;
//    QFile file(  myfile ); //dosyayı açmak için al

//    if ( file.open(QIODevice::ReadOnly))
//    {
//        //qDebug ()<<"file read";
//        inByteArray = file.readAll();

//        // table view de hangi rowdayız ?
//        QModelIndex index = FTRtview->table->currentIndex();
//        int row = index.row() ;

//        /// resmi değiştirelim
//        FTRmodel->setData(FTRmodel->
//                          index(row, FTRmodel->
//                                fieldIndex ("ftr_resim")),inByteArray);
//        /// yeni eklenenleri kaydedelim
//        FTRmodel->submitAll();

//        //QByteArray outByteArray = FTRtview->table->
//        //      model()->index( row, FTRmodel->fieldIndex ("resim") ).data().toByteArray();
//        /// makina ikmalde resmi değiştirelim
//        /*        cw_mkn->MKNmodel->setData (
//                    cw_mkn->MKNmodel-> index (
//                        0 ,cw_mkn->MKNmodel-> fieldIndex ("resim")),outByteArray );

//        cw_mkn->MKNmodel-> submitAll ();
//        QModelIndex xx = cw_mkn->MKNtview->currentIndex ();
//        cw_mkn->onMKNtview_resimGosterSLOT (xx);
//*/
//    }
//}       ///     onpb_resimEkleSLOT




void Cw_ftr::slt_ftr_hesap()
{
    qDebug() << "ftr_hesapp";
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
}  ///**************************************** fatura hesap

//void Cw_ftr::slt_mlz_ara()
//{
//    qDebug()<<"malzeme araaaaaaaaaaaaaa    ";
//}

//void Cw_ftr::slt_ftr_pB_EKLE_clicked ()
//{
//    qDebug() << "  slt_ftr_pB_EKLE_clicked";
//    /*
// ///////////////////////////////////////////////////////////////////////
//    // fatura ekleme dialogu hazırlayalım
//    auto *dia_faturaekle = new QDialog(this);
//    dia_faturaekle->setGeometry (30,450,300,100);
//    dia_faturaekle->setWindowTitle ("Yeni Fatura Kaydı Ekle");

//    // içinde neler olmalı ??
//    auto *lay_dia = new QGridLayout(dia_faturaekle);

//    //auto *pB_frekle = new QPushButton("Yeni Firma Ekle");
//    auto *lft_no = new QLabel("Fatura No");
//    auto *eft_no = new QLineEdit;
//    auto *lft_fr = new QLabel("Firma");
//    auto *cbx_fr = new QComboBox;

//    // firma listesinden seçim yaptıralım
//    auto *modelcbx = new QSqlTableModel;
//    modelcbx->setTable ("frm__dbtb");
//    cbx_fr->setModel (modelcbx);
//    cbx_fr->setModelColumn (modelcbx->fieldIndex ("frm_unvan"));
//    modelcbx->select ();
/////////////////////////////////////////////////////////////////////////////
//    */
//    // /////////////////////////////////////////////////////////////////////
//    // combpobox da istenen firma yoksa
//    // yeni firma eklemek için dialog oluşturalım
//    auto *diafr = new QDialog();
//    // diafr->closeEvent (*clsevt);
//    auto layout_diafr = new QGridLayout(diafr);
//    // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
//    diafr->setGeometry (100,220,800,500);

//    diafr->setWhatsThis ("<br>"
//                         "<br> Lütfen Girişi yapılan fatura bilgilerine "
//                         "<br> Firma ünvanı girmek için seçim yapın "
//                         "<br> "
//                         "<br> Eğer aradığınız firma listede yoksa yeni  "
//                         "<br> firma girişi yaparak işlemi tamamlayın"
//                         "<br>");
//    diafr->setToolTipDuration (5000);
//    diafr->setToolTip ("<br>"
//                       "<br> Lütfen Girişi yapılan fatura bilgilerine "
//                       "<br> Firma ünvanı girmek için seçim yapın "
//                       "<br> "
//                       "<br> Eğer aradığınız firma listede yoksa yeni  "
//                       "<br> firma girişi yaparak işlemi tamamlayın"
//                       "<br>");


//    // firma class ımızı getirelim
//    auto *firma = new Cw_fr;
//    firma->setup_firma ();
//    layout_diafr->addWidget (firma ,0 ,0 ,1, 1);
//    //diafr->show();

//    /////////////////////////////////////////////////////////////////////////////////
//    // ----------------------------------------------------
//    // firma tableviewinde gezinirken firma adımız
//    // seçim yapılan lineedit e aktaralım
//    // ----------------------------------------------------

//    qDebug()<<"is signal cathed";
//    connect (firma, &Cw_fr::sgnfirma,
//             [ this ] (QString secfirma )

//    {
//        this->lE_firma->lineEdit->setText (secfirma);
//        qDebug()<<"signal cathed"<< secfirma ;
//    });
//    diafr->exec ();


//    //    connect (firma->FRMselectionMdlxxx,
//    //             &QItemSelectionModel::currentChanged  ,
//    //             [ this, firma ] (QModelIndex Index )

//    //    {
//    //        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
//    //        int fr_row = Index.row ();
//    //        this->lE_firma->lineEdit->setText (firma->FRMmodel->data(
//    //                 firma->FRMmodel->index
//    //                 (fr_row,firma->FRMmodel->fieldIndex ("frm_unvan"))
//    //                   ).toString ());
//    //    });
//    //    diafr->exec ();




//    /*
//    /////////////////////////////////////////////////////////////////////////////////
//    // ----------------------------------------------------
//    // firma tableviewinde gezinirken firma adımız
//    // seçim yapılan combobxa aktaralım
//    // ----------------------------------------------------
//    connect (firma->FRMtview->table->selectionModel (),
//             &QItemSelectionModel::currentChanged  ,
//             [ cbx_fr, firma, modelcbx ](QModelIndex Index )

//    {
//        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
//        int fr_row = Index.row ();
//        modelcbx->select();
//        cbx_fr->setCurrentText (firma->FRMmodel->data(
//                                    firma->FRMmodel->index
//                                    (fr_row,firma->FRMmodel->fieldIndex ("frm_unvan"))
//                                    ).toString ());
//    });

//    // diğer alanlarıda dolduralım
//    auto *lft_tr = new QLabel("Tarih");
//    auto *eft_tr = new QLineEdit;
//    eft_tr->setText (QDate::currentDate ().toString ("dd.MM.yyyy"));

//    auto *lft_ac = new QLabel("Açıklama");
//    auto *eft_ac = new QLineEdit;

//    lay_dia->addWidget (lft_no,0 , 0, 1, 1 );
//    lay_dia->addWidget (eft_no,0 , 1, 1, 2 );
//    lay_dia->addWidget (lft_tr,0 , 3, 1, 1 );
//    lay_dia->addWidget (eft_tr,0 , 4, 1, 2 );
//    lay_dia->addWidget (lft_ac,0 , 6, 1, 1 );
//    lay_dia->addWidget (eft_ac,0 , 7, 1, 4 );

//    lay_dia->addWidget (lft_fr,1 , 3, 1, 1 );
//    lay_dia->addWidget (cbx_fr,1 , 4, 1, 4 );
//    lay_dia->addWidget (diafr  ,4 , 0, 6, 11 );

//    //    int str{};
//    //    lay_dia->addWidget (lft_no,str  ,0,1,1);
//    //    lay_dia->addWidget (eft_no,str++,1,1,2);
//    //    lay_dia->addWidget (lft_fr,str  ,0,1,1);
//    //    lay_dia->addWidget (cbx_fr,str++,1,1,2);
//    //    lay_dia->addWidget (lft_tr,str  ,0,1,1);
//    //    lay_dia->addWidget (eft_tr,str++,1,1,2);
//    //    lay_dia->addWidget (lft_ac,str  ,0,1,1);
//    //    lay_dia->addWidget (eft_ac,str++,1,1,2);


//    // yeni faturamızı ekleyelim
//    QPushButton *pB_ftrekle = new QPushButton("Fatura Ekle");
//    QPushButton *pB_vzgc = new QPushButton("Kapat");
//    lay_dia->addWidget (pB_vzgc   , 3, 4, 1, 1 );
//    lay_dia->addWidget (pB_ftrekle, 3, 5, 1, 1 );


//    // ekle pencerelrini kapatalım
//    connect (pB_vzgc, &QPushButton::clicked,
//             [dia_faturaekle] ()
//    {

//        dia_faturaekle->close ();

//    });

///   connect (pB_frekle, &QPushButton::clicked,
//             [this,cbx_fr,modelcbx]()
//    {
//        auto *diafr = new QDialog(this);
//        diafr->setGeometry (400,0,400,600);
//        auto *firma = new Cw_fr(diafr);
//        diafr->show();
//        connect (firma->FRMtview->selectionModel (),
//                 &QItemSelectionModel::currentChanged  ,
//                 [ cbx_fr, firma, modelcbx ]()

//        {
//            QModelIndex firmandx = firma->FRMtview->currentIndex ()  ;
//            int fr_row = firmandx.row ();
//            modelcbx->select();
//            cbx_fr->setCurrentText (firma->FRMmodel->data(
//                                        firma->FRMmodel->index
//                                        (fr_row,firma->FRMmodel->fieldIndex ("frm_unvan"))
//                                        ).toString ());
//        }
//        );
//    });
///

//    // fatura başlık bilgilerimizi girdik
//    // bunu kayıt edelim

//    connect (pB_ftrekle, &QPushButton::clicked,
//             [ eft_no, eft_ac, cbx_fr, eft_tr,
//             this, dia_faturaekle ]()
//    {

//        // fatura no önemli
//        // boş geçmek olmaz
//        if ( eft_no->text () =="")
//        {
//            eft_no->setPlaceholderText ("Fatura No Giriniz...");
//            qDebug()<<"fatura no boş geçilemez";
//        }
//        else {

//            // kayıt oluşturalım
//            QSqlRecord rec = FTRmodel->record();
//            rec.setValue ("ftr_no"      , eft_no->text ());
//            rec.setValue ("ftr_firma"   , cbx_fr->currentText ());
//            rec.setValue ("ftr_tarih"   , eft_tr->text ());
//            rec.setValue ("ftr_aciklama", eft_ac->text ());

//            // insert a new record (-1)
//            if ( ! FTRmodel->insertRecord(FTRmodel->rowCount (),rec))
//            {
//                qDebug() << " HATA - FATURA ya kayıt eklenemedi ";
//            }
//            else
//            {
//                qDebug() << " - Kayıt FATURA ya eklendi ";
//                FTRmodel->submitAll ();
//                FTRmodel->select ();
//                QModelIndex ftr_ndx= FTRmodel->
//                        index (FTRmodel->rowCount ()-1,0);
//                FTRtview->table->selectRow (ftr_ndx.row ());
//            }
//            dia_faturaekle->close ();


//        }


//    });

//    dia_faturaekle->show ();

//    //////////////////////////////////////////////////////////////////////////////
//        */

//    qDebug ()<<"frm un 4";

//}

//void Cw_ftr::slt_ftr_pB_SIL_clicked ()
//{
//    qDebug() << "  slt_ftr_pB_SIL_clicked";
//    //QSqlQuery q_qry;
//    //QString s_qry;
//    QModelIndex ftrindex = FTRtview->table->currentIndex();
//    if( ftrindex.row() >= 0 )
//    {
//        QSqlRecord ftrrec = FTRmodel->record(ftrindex.row ());
//        int fatkod = ftrrec.value ("ftr_kod").toInt();
//        QString fatno = ftrrec.value("ftr_no").toString();

//        /// depo detay kayıtlarını soralım - silelim
//        QSqlQuery q_qry;
//        QString s_qry;
//        /// silinecek kayıt sayısı   mlzmdet__dbtb
//        s_qry = QString("SELECT count() FROM mlzmdet__dbtb"
//                        "where mlzmdet_gcno = %1 and "
//                        "mlzmdet_gc = 'Faturalı Giriş'").arg (fatno);
//        q_qry.exec(s_qry);
//        int xx = 0 ;

//        if ( q_qry.isActive ())
//        {
//            xx = s_qry.size () ;
//            qDebug()<< xx <<" adet kayıt silinecek ";
//        }


//        QString mess="\n";
//        mess += fatno + " nolu fatura"
//                        "\n  silinsin mi ?\n"+
//                "İşlemi onaylarsanız bu fatura kaydına ait\n " ;

//        int mlzdet_count = FTRDETmodel->rowCount () ;
//        if ( mlzdet_count > 0 )
//        {
//            mess +=QString::number (mlzdet_count) +
//                    " adet Ambar GİRİŞ kaydı da SİLİNECEK";
//        }
//        mess +="\n\nİŞLEMİ ONAYLIYORMUSUNUZ ?";


//        /// model makina kaydı var
//        QMessageBox::StandardButton dlg;
//        dlg = QMessageBox
//                ::question(this,
//                           "KAYIT SİL", mess,
//                           QMessageBox::Yes | QMessageBox::No);

//        if(dlg == QMessageBox::Yes)
//        {
//            /// ambara ait mlzm_det giriş kayıtlarını sil
//            s_qry = QString("DELETE FROM mlzmdet__dbtb "
//                            "where mlzmdet_gcno = %1").arg (fatno);
//            q_qry.exec(s_qry);
//            if (q_qry.isActive ())
//            {
//                qDebug()<<" - "<< mlzdet_count <<
//                          " - adet Faturalı Giriş Kaydı Silindi";
//            }
//            else
//            {
//                qDebug()<< "HATA - Faturalı Giriş Kayıtları Silinemedi"
//                        << q_qry.lastError() ;
//            }



//            /// depo kayıtlarını silelim
//            s_qry = QString("DELETE FROM ftr__dbtb "
//                            "where ftr_kod = %1").arg (fatkod);
//            q_qry.exec(s_qry);
//            if (q_qry.isActive ())
//            {
//                qDebug()<< "1 adet Fatura Kaydı Silindi";
//                FTRtview->table->setFocus ();
//                FTRmodel->select ();



//                if (FTRmodel->rowCount () == 1)
//                {
//                    FTRtview->table->selectRow (0);
//                    FTRtview->table->setCurrentIndex (FTRmodel->index(0,0));
//                }
//                if (FTRmodel->rowCount () > 1)
//                {
//                    if (ftrindex.row () == 0)
//                    {
//                        FTRtview->table->selectRow (0);
//                        FTRtview->table->setCurrentIndex (FTRmodel->index(0,0));
//                    }
//                    else if (ftrindex.row () > 0)
//                    {
//                        FTRtview->table->selectRow (ftrindex.row()-1);
//                        FTRtview->table->setCurrentIndex (FTRmodel->index(ftrindex.row ()-1,0));
//                    }
//                }
//            }
//            else
//            {
//                qDebug()<< "HATA - Fatura Kaydı Silinemedi"
//                        << q_qry.lastError() ;
//            }
//        }
//    }
//}



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
    lE_mlzdetmlzm = new HC_LE;
    lE_mlzdetmlzm->lineEdit->setReadOnly (true);

    connect (lE_mlzdetmlzm->pushButton, &QPushButton::clicked,
             [this]()
     {
         // firma seçebilmek için firma penceresi

         auto *mlz = new FtrDet_MlzEkle;


         /////////////////////////////////////////////////////////////////////////////////
         // ----------------------------------------------------
         // malzeme tableviewinde gezinirken malzeme adımız
         // signal ediliyor onu yakalayalım
         // seçim yapılan lineedit e aktaralım
         // ----------------------------------------------------

         connect (mlz->malzeme, &Cw_Mlzm::sgnMalzeme,
                  [ this ] (QString secMalzeme )
         {
             this->lE_mlzdetmlzm->lineEdit->setText (secMalzeme);
             this->lE_mlzdetmlzm->lineEdit->setFocus();
             qDebug()<<"signal cathed = "<< secMalzeme ;
         });
         mlz->exec ();
         qDebug()<<"selected malzeme = "<< mlz->getMalzeme ();
     });








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





    /////////////////
    ///
    /// CONNECT

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    connect(FTRDETtview->table->model() ,
            &QSqlTableModel::dataChanged , this,
            &Cw_ftr::slt_ftr_hesap);


    // fatura detaya malzeme ismi hariç diğer
    // bilgilerle yeni bir kayıt ekleyelim
    connect(FTRDETtview->pB_ekle, &QPushButton::clicked ,

             [this]()
    {

        int mlz_row = 0;
        qDebug() << "  slt_mlz_pB_EKLE_clicked";

        // 001 faturaya malzeme detayı eklemek için dialog oluşturalım
        auto *dia_ftrmlzmekle = new QDialog(this);
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


        QLabel *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
        lE_mlzdetmlzm = new HC_LE;
        lE_mlzdetmlzm->lineEdit->setReadOnly (true);

        connect (lE_mlzdetmlzm->pushButton, &QPushButton::clicked,
                 [this]()
         {
             // firma seçebilmek için firma penceresi

             auto *mlz = new FtrDet_MlzEkle;


             /////////////////////////////////////////////////////////////////////////////////
             // ----------------------------------------------------
             // malzeme tableviewinde gezinirken malzeme adımız
             // signal ediliyor onu yakalayalım
             // seçim yapılan lineedit e aktaralım
             // ----------------------------------------------------

             connect (mlz->malzeme, &Cw_Mlzm::sgnMalzeme,
                      [ this ] (QString secMalzeme )
             {
                 this->lE_mlzdetmlzm->lineEdit->setText (secMalzeme);
                 this->lE_mlzdetmlzm->lineEdit->setFocus();
                 qDebug()<<"signal cathed = "<< secMalzeme ;
             });
             mlz->exec ();
             qDebug()<<"selected malzeme = "<< mlz->getMalzeme ();
         });







  /*
        auto *lB_mlz = new QLabel("Malzeme");

        // malzeme listesini oluşturalım
        auto *cbx_mlzm = new QComboBox;
        auto *modelcbx = new QSqlTableModel;
        modelcbx->setTable ("mlzm__dbtb");
        cbx_mlzm->setModel (modelcbx);
        cbx_mlzm->setModelColumn (modelcbx->fieldIndex ("mlzm_malzeme"));
        modelcbx->select ();
*/
        // diğer alanlarıda elle dolduralım
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

        lay_dia->addWidget (lB_mlz   ,++str, 0, 1, 1);
        lay_dia->addWidget (cbx_mlzm ,  str, 1, 1, 1);
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

/*        // combpobox da istenen malzeme yoksa
        // ambara yeni malzeme eklemek için dialog oluşturalım
        auto *diamlz = new QDialog(this);
        diamlz->setWindowTitle ("Fatura Detay Bilgilerine Malzeme Ekle ");
        diamlz->setGeometry (400,0,400,600);

        diamlz->setWhatsThis ("<br> MALZEME SEÇMEK İÇİN"
                              "<br> Lütfen Girişi yapılan fatura detay bilgilerine "
                              "<br> malzeme girmek için seçim yapın "
                              "<br> "
                              "<br> Eğer aradığınız malzeme listede yoksa yeni  "
                              "<br> malzeme girişi yaparak işlemi tamamlayın"
                              "<br>");
        diamlz->setToolTipDuration (5000);
        diamlz->setToolTip ("<br> MALZEME SEÇMEK İÇİN"
                            "<br> Lütfen Girişi yapılan fatura detay bilgilerine "
                            "<br> malzeme girmek için seçim yapın "
                            "<br> "
                            "<br> Eğer aradığınız malzeme listede yoksa yeni  "
                            "<br> malzeme girişi yaparak işlemi tamamlayın"
                            "<br>");

        // ambar malzeme class ımızı getirelim
        auto *malzeme = new Cw_Mlzm ;
        malzeme->setup_mlzm ();

        auto *l_dia = new QGridLayout(diamlz);
        l_dia->addWidget (malzeme ,0,0,1,1);
        diamlz->show();


        // ----------------------------------------------------
        // malzeme tableviewinde gezinirken malzeme adımızı
        // seçim yapılan comboboxa aktaralım
        // ----------------------------------------------------


        // malzemede hangi kayıttayız ?

        connect (malzeme->MLZMselectionMdl, &QItemSelectionModel::currentRowChanged,

                 [ mlz_row, cbx_mlzm, malzeme, modelcbx] (QModelIndex Index ) mutable
        {
            //   QModelIndex mlzndx = malzeme->MLZMtview->currentIndex ()  ;
            if (Index.isValid ())
            {

                mlz_row = Index.row (); // mlzndx.row ();
                modelcbx->select();
                cbx_mlzm->setCurrentText (malzeme->MLZMmodel->data(
                                              malzeme->MLZMmodel->index
                                              (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_malzeme"))
                                              ).toString ());
            }
            else
            {
                qDebug ()<<"mlzm un 42 invalid index";
            }
        });


        // ----------------------------------------------------
        // malzeme tableviewinde gezinirken malzemedetaya
        // eklenecek gerekli alanları alalım
        // ----------------------------------------------------



        // malzeme dosyasından faturadetaya eklenecek
        // kayıtta gerekli alanları alalım
        QString mlz_kod{ malzeme->MLZMmodel->data(
                        malzeme->MLZMmodel->index
                        (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_kod"))
                        ).toString()};
        QString mlz_barkod { malzeme->MLZMmodel->data(
                        malzeme->MLZMmodel->index
                        (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_barkod"))
                        ).toString ()};
        QString mlz_birim { malzeme->MLZMmodel->data(
                        malzeme->MLZMmodel->index
                        (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_birim"))
                        ).toString ()};


        // ekle pencerelrini kapatalım
        connect (pB_vzgc, &QPushButton::clicked,
                 [dia_ftrmlzmekle ,diamlz] ()
        {
            dia_ftrmlzmekle->close ();
            diamlz->close ();
        });
*/
        // fatura başlık bilgilerimizi girdik
        // bunu kayıt edelim
        qDebug ()<<"mlz_row"<<mlz_row;
        connect (pB_mlzekle, &QPushButton::clicked,
                 [ lE_miktar, lE_bfiyat, cbx_mlzm, lE_kdv, lE_ckl,
                 malzeme , mlz_kod , mlz_barkod, mlz_birim,
                 ftrno, ftrtarih
                 ]()
        {

            // malzeme bilgileri fatura detay için yeterli
            // boş geçilmeyecek bir alan yok

            // kayıt oluşturalım
            QSqlRecord rec = malzeme->MLZMDETmodel->record();

            qDebug() << "mlz_kod = "<<mlz_kod;
            rec.setValue ("mlzmdet_mlzm_kod" , mlz_kod );
            rec.setValue ("mlzmdet_barkod"   , mlz_barkod);
            rec.setValue ("mlzmdet_malzeme"  , cbx_mlzm->currentText ());
            rec.setValue ("mlzmdet_tarih"    , ftrtarih);
            rec.setValue ("mlzmdet_gc"       , "Faturalı Giriş");
            rec.setValue ("mlzmdet_gcno"     , ftrno);
            rec.setValue ("mlzmdet_miktar"   , lE_miktar->text ());
            rec.setValue ("mlzmdet_birim"    , mlz_birim);
            rec.setValue ("mlzmdet_fiyat"    , lE_bfiyat->text ());
            rec.setValue ("mlzmdet_kdv"      , lE_kdv->text ());
            rec.setValue ("mlzmdet_aciklama" , lE_ckl->text ());


            // insert a new record (-1)
            if ( ! malzeme->MLZMDETmodel->insertRecord(malzeme->
                                                       MLZMDETmodel->rowCount (),rec))
            {
                qDebug() << " HATA - FATura Detaya kayıt eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt FATURA Detaya eklendi ";
                malzeme->MLZMDETmodel->submitAll ();
                malzeme->MLZMDETmodel->select ();
                // kayıt eklendi yeni kayıt için hazırlık yap
                lE_miktar->setText ("");
                lE_bfiyat->setText ("");
                lE_kdv->setText ("18");
                lE_ckl->setText ("");



                QModelIndex ftr_ndx= malzeme->MLZMDETmodel->
                        index (malzeme->MLZMDETmodel->rowCount ()-1,0);
                malzeme->MLZMDETtview->table->selectRow (ftr_ndx.row ());
                // qDebug() << "mlz_kod = "<<mlz_kod;

            }
            //dia_ftrmlzmekle->close ();
            //diamlz->close ();

        });
        diamlz->show ();
        dia_ftrmlzmekle->show ();

        qDebug ()<<"mlzm un 4";



    });



             // this ,  &Cw_ftr::slt_mlz_pB_EKLE_clicked  )) ;

    connect(FTRDETtview->pB_sil, &QPushButton::clicked,
            [this]()
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

    });




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
        FTRmapper->toLast ();
        int map_row = FTRDETmapper->currentIndex ();
        FTRDETtview->pB_son->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmodel->rowCount() - 1  ,0));
    });



}
///
/// \brief Cw_ftr::setup_mapFtrDet
///
void Cw_ftr::setup_mapFtrDet()
{
    qDebug() << "  setup_mapFtrDet";
    FTRDETmapper = new QDataWidgetMapper(this);
    FTRDETmapper->setModel(FTRDETmodel);

    //FTRDETmapper->addMapping(lE_d_faturano , FTRDETmodel->fieldIndex("faturano"));
    //FTRDETmapper->addMapping(lE_d_firma, FTRDETmodel->fieldIndex("firma"));
    FTRDETmapper->addMapping(lE_mlzdetbarkod, FTRDETmodel->fieldIndex("mlzmdet_barkod"));
    FTRDETmapper->addMapping(lE_mlzdetmlzm->lineEdit, FTRDETmodel->fieldIndex("mlzmdet_malzeme"));
    FTRDETmapper->addMapping(lE_mlzdetmiktar, FTRDETmodel->fieldIndex("mlzmdet_miktar"));
    FTRDETmapper->addMapping(lE_mlzdetbirim, FTRDETmodel->fieldIndex("mlzmdet_birim"));
    FTRDETmapper->addMapping(lE_mlzdetfiyat, FTRDETmodel->fieldIndex("mlzmdet_fiyat"));
    FTRDETmapper->addMapping(lE_mlzdetkdv, FTRDETmodel->fieldIndex("mlzmdet_kdv"));
    FTRDETmapper->addMapping(lE_mlzdetaciklama, FTRDETmodel->fieldIndex("mlzmdet_aciklama"));

    /// depodet map değiştiğinde nav tuşalrı ayarlansın
    connect(FTRDETmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        qDebug() << "  slt_ftrd_updButtons";
        int row = Index; //.row ();   //FTRDETmapper->currentIndex ();
        FTRDETtview->pB_ilk->setEnabled (row>0);
        FTRDETtview->pB_ncki->setEnabled(row > 0);
        FTRDETtview->pB_snrki->setEnabled(row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->pB_son->setEnabled(row < FTRDETmodel->rowCount() - 1);

    });

    /// depodet table da koon değiştiğnde index değişsin
    // connect(  FTRDETtview->table->selectionModel(),
    //          SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //        FTRDETmapper, SLOT(setCurrentModelIndex(QModelIndex))));
    /// depodet table da row değiştiğnde index değişsin
    ( connect(  FTRDETtview->table->selectionModel(),
                SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                FTRDETmapper, SLOT(setCurrentModelIndex(QModelIndex))));


    /// depodetay varsa ilk kayda
    Cw_ftr::FTRDETmapper->toFirst ();



}


///************************************************************
///****************  F A T U R A  D  E  T  A  Y  ************
///*******                 S  L  O  T  S           ************
///
///




/// Fatura detayına malzeme ekle

///
/// \brief Cw_ftr::slt_mlz_pB_EKLE_clicked
///
void Cw_ftr::slt_mlz_pB_EKLE_clicked ()
{
    int mlz_row = 0;
    qDebug() << "  slt_mlz_pB_EKLE_clicked";

    // 001 faturaya malzeme detayı eklemek için dialog oluşturalım
    auto *dia_ftrmlzmekle = new QDialog(this);
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


    auto *lB_mlz = new QLabel("Malzeme");

    // malzeme listesini oluşturalım
    auto *cbx_mlzm = new QComboBox;
    auto *modelcbx = new QSqlTableModel;
    modelcbx->setTable ("mlzm__dbtb");
    cbx_mlzm->setModel (modelcbx);
    cbx_mlzm->setModelColumn (modelcbx->fieldIndex ("mlzm_malzeme"));
    modelcbx->select ();

    // diğer alanlarıda elle dolduralım
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

    lay_dia->addWidget (lB_mlz   ,++str, 0, 1, 1);
    lay_dia->addWidget (cbx_mlzm ,  str, 1, 1, 1);
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

    // combpobox da istenen malzeme yoksa
    // ambara yeni malzeme eklemek için dialog oluşturalım
    auto *diamlz = new QDialog(this);
    diamlz->setWindowTitle ("Fatura Detay Bilgilerine Malzeme Ekle ");
    diamlz->setGeometry (400,0,400,600);

    diamlz->setWhatsThis ("<br> MALZEME SEÇMEK İÇİN"
                          "<br> Lütfen Girişi yapılan fatura detay bilgilerine "
                          "<br> malzeme girmek için seçim yapın "
                          "<br> "
                          "<br> Eğer aradığınız malzeme listede yoksa yeni  "
                          "<br> malzeme girişi yaparak işlemi tamamlayın"
                          "<br>");
    diamlz->setToolTipDuration (5000);
    diamlz->setToolTip ("<br> MALZEME SEÇMEK İÇİN"
                        "<br> Lütfen Girişi yapılan fatura detay bilgilerine "
                        "<br> malzeme girmek için seçim yapın "
                        "<br> "
                        "<br> Eğer aradığınız malzeme listede yoksa yeni  "
                        "<br> malzeme girişi yaparak işlemi tamamlayın"
                        "<br>");

    // ambar malzeme class ımızı getirelim
    auto *malzeme = new Cw_Mlzm ;
    malzeme->setup_mlzm ();

    auto *l_dia = new QGridLayout(diamlz);
    l_dia->addWidget (malzeme ,0,0,1,1);
    diamlz->show();


    // ----------------------------------------------------
    // malzeme tableviewinde gezinirken malzeme adımızı
    // seçim yapılan comboboxa aktaralım
    // ----------------------------------------------------


    // malzemede hangi kayıttayız ?

    connect (malzeme->MLZMselectionMdl, &QItemSelectionModel::currentRowChanged,

             [ mlz_row, cbx_mlzm, malzeme, modelcbx] (QModelIndex Index ) mutable
    {
        //   QModelIndex mlzndx = malzeme->MLZMtview->currentIndex ()  ;
        if (Index.isValid ())
        {

            mlz_row = Index.row (); // mlzndx.row ();
            modelcbx->select();
            cbx_mlzm->setCurrentText (malzeme->MLZMmodel->data(
                                          malzeme->MLZMmodel->index
                                          (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_malzeme"))
                                          ).toString ());
        }
        else
        {
            qDebug ()<<"mlzm un 42 invalid index";
        }
    });


    // ----------------------------------------------------
    // malzeme tableviewinde gezinirken malzemedetaya
    // eklenecek gerekli alanları alalım
    // ----------------------------------------------------



    // malzeme dosyasından faturadetaya eklenecek
    // kayıtta gerekli alanları alalım
    QString mlz_kod{ malzeme->MLZMmodel->data(
                    malzeme->MLZMmodel->index
                    (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_kod"))
                    ).toString()};
    QString mlz_barkod { malzeme->MLZMmodel->data(
                    malzeme->MLZMmodel->index
                    (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_barkod"))
                    ).toString ()};
    QString mlz_birim { malzeme->MLZMmodel->data(
                    malzeme->MLZMmodel->index
                    (mlz_row,malzeme->MLZMmodel->fieldIndex ("mlzm_birim"))
                    ).toString ()};


    // ekle pencerelrini kapatalım
    connect (pB_vzgc, &QPushButton::clicked,
             [dia_ftrmlzmekle ,diamlz] ()
    {
        dia_ftrmlzmekle->close ();
        diamlz->close ();
    });

    // fatura başlık bilgilerimizi girdik
    // bunu kayıt edelim
    qDebug ()<<"mlz_row"<<mlz_row;
    connect (pB_mlzekle, &QPushButton::clicked,
             [ lE_miktar, lE_bfiyat, cbx_mlzm, lE_kdv, lE_ckl,
             malzeme , mlz_kod , mlz_barkod, mlz_birim,
             ftrno, ftrtarih
             ]()
    {

        // malzeme bilgileri fatura detay için yeterli
        // boş geçilmeyecek bir alan yok

        // kayıt oluşturalım
        QSqlRecord rec = malzeme->MLZMDETmodel->record();

        qDebug() << "mlz_kod = "<<mlz_kod;
        rec.setValue ("mlzmdet_mlzm_kod" , mlz_kod );
        rec.setValue ("mlzmdet_barkod"   , mlz_barkod);
        rec.setValue ("mlzmdet_malzeme"  , cbx_mlzm->currentText ());
        rec.setValue ("mlzmdet_tarih"    , ftrtarih);
        rec.setValue ("mlzmdet_gc"       , "Faturalı Giriş");
        rec.setValue ("mlzmdet_gcno"     , ftrno);
        rec.setValue ("mlzmdet_miktar"   , lE_miktar->text ());
        rec.setValue ("mlzmdet_birim"    , mlz_birim);
        rec.setValue ("mlzmdet_fiyat"    , lE_bfiyat->text ());
        rec.setValue ("mlzmdet_kdv"      , lE_kdv->text ());
        rec.setValue ("mlzmdet_aciklama" , lE_ckl->text ());


        // insert a new record (-1)
        if ( ! malzeme->MLZMDETmodel->insertRecord(malzeme->
                                                   MLZMDETmodel->rowCount (),rec))
        {
            qDebug() << " HATA - FATura Detaya kayıt eklenemedi ";
        }
        else
        {
            qDebug() << " - Kayıt FATURA Detaya eklendi ";
            malzeme->MLZMDETmodel->submitAll ();
            malzeme->MLZMDETmodel->select ();
            // kayıt eklendi yeni kayıt için hazırlık yap
            lE_miktar->setText ("");
            lE_bfiyat->setText ("");
            lE_kdv->setText ("18");
            lE_ckl->setText ("");



            QModelIndex ftr_ndx= malzeme->MLZMDETmodel->
                    index (malzeme->MLZMDETmodel->rowCount ()-1,0);
            malzeme->MLZMDETtview->table->selectRow (ftr_ndx.row ());
            // qDebug() << "mlz_kod = "<<mlz_kod;

        }
        //dia_ftrmlzmekle->close ();
        //diamlz->close ();

    });
    diamlz->show ();
    dia_ftrmlzmekle->show ();

    qDebug ()<<"mlzm un 4";


    //***************************
    /*
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
    qDebug ()<<"ftrno " << ftrtarih;
    QLineEdit fno;
    fno.insert (ftrno);
    fno.setReadOnly (true);
    QLineEdit ftr;
    ftr.setText (ftrtarih);
    ftr.setReadOnly (true);


    QPushButton *pB_ftrekle = new QPushButton("Faturaya Malzeme Ekle");
    QPushButton *pB_kpt = new QPushButton("Kapat");

    lay_dia->addWidget (cbx_mlzm   ,0,0,6,2);
    lay_dia->addWidget (new QLabel("Fatura No   :" + ftrno)      ,0,2,1,1);
    lay_dia->addWidget (new QLabel("Fatura Tarih:" + ftrtarih)    ,1,2,1,1);
    lay_dia->addWidget (pB_kpt    ,7,0,1,1);
    lay_dia->addWidget (pB_ftrekle,7,1,1,2);

    qDebug ()<<"ftrrrrrrr " ;
    connect (pB_kpt, &QPushButton::clicked,dia_ftrmlzmekle, &QDialog::close );
    connect (pB_ftrekle, &QPushButton::clicked,
             // [ftr_indx,ftrno,ftrtarih,this,mlz_model,mlz_view]()
             [this,ftr_indx, cbx_mlzm, modelcbx ]()
    {  /// lambda


        QModelIndex mlz_indx = cbx_mlzm->currentIndex () ;
        if ( ftr_indx.row () >= 0 )
        {

            int mlzm_row = mlz_indx.row ();
            qDebug ()<<"ftrrrrrrr 2 " ;
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
            qDebug ()<<"ftrrrrrrr 3" ;
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
                qDebug ()<<"ftrrrrrrr 4 " ;
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

    dia_ftrmlzmekle->show ();

    qDebug ()<<"ftrrrrrrr 5 " ;
*/
}








void Cw_ftr::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Ftr dosyası açılıyor";
}











Cw_ftr::~Cw_ftr()
{
    //    delete ui;
}
