#include "ie.h"


hC_IE::hC_IE(QWidget *parent)  : hC_tBcreator (parent)
{
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
    qDebug() << "Constructor İŞ EMRİ *************************************  ";

    win_Label->setText ( "İŞ EMRİ KAYITLARI");
    *tb_name  = "ie_dbtb" ;
    *tb_ndex  = "ie_no";

    tb_flds = new hC_ArrD (11, 4);
    tb_flds->setValue ( 0, "ie_ID"    , "INTEGER", "İşEmriID", "0" ) ;
    tb_flds->setValue ( 1, "ie_no"    , "INTEGER", "İş Emri No" );
    tb_flds->setValue ( 2, "ie_mkn"   , "TEXT"   , "Kurum No" ) ;
    tb_flds->setValue ( 3, "ie_tarih" , "TEXT"   , "İş Emri Tarihi" );
    tb_flds->setValue ( 4, "ie_durum" , "TEXT"   , "Durum");
    tb_flds->setValue ( 5, "ie_girtar", "TEXT"   , "Araç Giriş Tarihi"   );
    tb_flds->setValue ( 6, "ie_ciktar", "TEXT"   , "Araç Çıkış Tarihi"   );
    tb_flds->setValue ( 7, "ie_y1"    , "TEXT"   , "Yetkili I"    );
    tb_flds->setValue ( 8, "ie_y2"    , "TEXT"   , "Yetkili II"   );
    tb_flds->setValue ( 9, "ie_resimmkn" , "BLOB"   , "ResimMkn" , "0" );
    tb_flds->setValue ( 10, "ie_resimie" , "BLOB"   , "ResimIe" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_ieno = new QLineEdit  ) ;
    tb_wdgts->append ( hClE_mkn = new hC_Le     ) ;
    tb_wdgts->append ( dE_geltar = new QDateTimeEdit(QDate::currentDate ())  ) ;
    tb_wdgts->append ( cbX_durum = new QComboBox ) ;
    tb_wdgts->append ( dE_girtar = new QDateTimeEdit(QDate::currentDate ())) ;
    tb_wdgts->append ( dE_ciktar = new QDateTimeEdit(QDate::currentDate ()) ) ;
    tb_wdgts->append ( hClE_yetkili1 = new hC_Le     ) ;
    tb_wdgts->append ( hClE_yetkili2 = new hC_Le    ) ;
    tb_wdgts->append ( new QLabel    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;


}

void hC_IE::tbsetup()
{
    qDebug() << "   ie setup ";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );
    tb_mapper->addMapping (hClE_mkn->lineEdit ,
                           tb_model->fieldIndex ("ie_mkn"));
    tb_mapper->addMapping (hClE_yetkili1->lineEdit ,
                           tb_model->fieldIndex ("ie_y1"));
    tb_mapper->addMapping (hClE_yetkili2->lineEdit ,
                           tb_model->fieldIndex ("ie_y2"));

    dragger = new DragWidget(this);

    dragger->setMinimumSize (this->width (),400);

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_IE::tbui()
{
    qDebug() << "   ui";

    hC_IE::setWindowTitle (win_Label->text());
    this->adjustSize ();
    // hC_IE::setGeometry(20,20,
    //                  qApp->screens()[0]->size ().rwidth (),
    //     qApp->screens()[0]->size ().rheight ()/4);




    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget ( tb_view  ,  0, 0, 1, 1 );
    win_Grid->addWidget ( win_Wdgt ,  0, 1, 1, 1 );
    win_Grid->addWidget ( dragger  ,  1, 0, 1, 2 );

}

void hC_IE::tbwdgt ()
{
    qDebug () << "   wdgt";

    mkn = new hC_MKN ;
    mkn->tbsetup();




    auto* lB_mk = new QLabel("Araç Kurum No");
    hClE_mkn->lineEdit->setReadOnly (true);

    connect(hClE_mkn->pushButton2 , &QPushButton::clicked,
            [this ]()
    {
        hClE_mkn->lineEdit->clear () ;
    });
    connect(hClE_mkn->pushButton , &QPushButton::clicked,
            [this ]()
    {
        // mkn seçebilmek için pencere
        auto *dia = new QDialog();
        dia->setModal (true);
        dia->setGeometry ( 50, 300, 400, 200 );
        dia->setWindowTitle ( "Araç Seçimi" );

        mkn->show ();
        // ----------------------------------------------------
        // tableviewinde gezinirken
        // mkn
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------
        connect (mkn , &hC_MKN::sgnMkn ,
                 [ this ] ( QString sgnText )
        {
            qDebug ()<<"sgn mkn";
            hClE_mkn->lineEdit->setText ( sgnText );
            hClE_mkn->lineEdit->setFocus();
        });
        ////////////////////////////////////////////************
        auto *layout = new QGridLayout;
        dia->setLayout (layout);
        layout->addWidget (mkn  ,0 ,0 );
        dia->exec ();
    });



    auto* lB_ie = new QLabel("İş Emri No");
    lE_ieno->setReadOnly (true);

    auto *lB_get = new QLabel("Araç Geliş Tarihi");
    hC_Gz(dE_geltar,"nulldate");
    lB_get->setBuddy(dE_geltar);

    auto *lB_dr = new QLabel("Araç Durumu ");
    QStringList lst{ "Sıra Bekliyor",
                     "Bakıma Alındı",
                     "Tamamlandı"};
    cbX_durum->insertItems(0,lst);

    auto lB_git = new QLabel("Atölye Giriş Tarihi");
    hC_Gz(dE_girtar,"nulldate");
    lB_git->setBuddy(dE_girtar);

    auto lB_cit = new QLabel("Atölye Çıkış Tarihi");
    hC_Gz(dE_ciktar,"nulldate");

    auto lB_y1 = new QLabel("Yetkili - I ");

    auto lB_y2 = new QLabel("Yetkili - II");

    hC_Rs resim(win_Rsm);

    //////////////////////////////////////////////
    
    win_Wdgt->adjustSize ();
    auto wdgtGrid = new QGridLayout;
    win_Wdgt->setLayout (wdgtGrid);

    wdgtGrid->addWidget (lB_ie   , 0,  0, 1, 4);
    wdgtGrid->addWidget (lE_ieno , 0,  4, 1, 6);
    wdgtGrid->addWidget (lB_mk   , 0, 10, 1, 4);
    wdgtGrid->addWidget (hClE_mkn  , 0, 14, 1, 6);

    wdgtGrid->addWidget (lB_get    , 1, 0, 1, 4);
    wdgtGrid->addWidget (dE_geltar , 1, 4, 1, 6);
    wdgtGrid->addWidget (lB_dr     , 2, 0, 1, 4);
    wdgtGrid->addWidget (cbX_durum , 2, 4, 1, 6);
    wdgtGrid->addWidget (lB_git    , 3, 0, 1, 4);
    wdgtGrid->addWidget (dE_girtar , 3, 4, 1, 6);
    wdgtGrid->addWidget (lB_cit     , 4, 0, 1, 4);
    wdgtGrid->addWidget (dE_ciktar  , 4, 4, 1, 6);
    wdgtGrid->addWidget (lB_y1       , 1, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili1 , 1, 14, 1, 6);
    wdgtGrid->addWidget (lB_y2       , 2, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili2 , 2, 14, 1, 6);
    wdgtGrid->addWidget (new QLabel("Resim") , 3, 10, 1, 4);
    wdgtGrid->addWidget (win_Rsm      , 3, 14, 2, 6);

    isEmriListele ();
}

void hC_IE::tbkntrl()
{

    qDebug()<<"   ie kntrl";

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        qDebug()<<" 1 yeni iş emri kaydı ";
        ////////////////////////////////////////////////
        /// yeni kayıt için kurum noyu mkn den alalım

        QDialog makinasec;
        QHBoxLayout xl ;
        makinasec.setLayout (&xl);
        xl.addWidget (mkn);

        //*** seçim penceresinde makina seçilir
        // yoksa yeni oluşturulur
        auto mknkrmno_sT = new QString;
        mknrsm_bA = new QByteArray ;
        qDebug()<<" 3 makina penceresi ";
        connect(mkn, &hC_MKN::sgnMkn,
                [mknkrmno_sT,this  ]
                (QString krmNo_sT,
                QByteArray byteArray) mutable
        {
            //***  1   iş emri için kurum no
            *mknkrmno_sT = krmNo_sT ;
            //*** signal dan gelen byte array
            *mknrsm_bA  =  byteArray ;
        });

        auto xxx = new QLabel;
        QPixmap op;
        qDebug ()<<"mknrsm ba size  "<< mknrsm_bA;
        qDebug ()<<"mknrsm ba size  "<< *mknrsm_bA;
        op.loadFromData ( *mknrsm_bA);
        if ( ! op.isNull ())
        {
        xxx->setPixmap (  op);
        }
        else qDebug () << "Dosya sıkıntısı";
        xxx->show ();



        makinasec.exec ();
        //*** makina seçildi yola devam
        ////////////////////////////////////////////////
        /// yeni iş emri numaasını bul
        /// iş emri nosu _dbtb de
        /// no alanındaki en büyük sayı
        qDebug()<<" 5 yeni kayıt için ie no dosyada bulunuyor";
        hC_Nr maxID;
        int* iemaxid_nT = new int{};
        *iemaxid_nT     = maxID.hC_NrMax ( tb_name,
                                           tb_flds->value (0,0));
        qDebug()<<"  51 ie_no = "<<* iemaxid_nT;


        ////////////////////////////////////////////////
        /// yeni kaydı ekle

        QSqlQuery q;
        QString qry, mesaj("");
        qry = QString("INSERT INTO %1 ( "
                      "ie_no    , "
                      "ie_mkn   , "
                      "ie_durum , "
                      "ie_tarih ) "
                      " values ( '%2', '%3', '%4', '%5' ) " )
                .arg ( *tb_name)
                .arg ( QString::number( *iemaxid_nT))
                .arg ( * mknkrmno_sT )
                .arg ( cbX_durum->itemText (0))
                .arg ( QDate::currentDate ().toString ("dd/MM/yy"));

        if ( !q.exec(qry) )
        {
            mesaj = mesaj + " İş Emri Eklenemedi"+
                    "-----"+
                    q.lastError().text ()+
                    "-----";
        }
        else
        {
            mesaj = mesaj + " İş Emri eklendi.";



            //// resmi de yazalım
            /// yeni eklenenleri kaydedelim





            hClE_mkn->lineEdit->setText ( *mknkrmno_sT );
            hC_Gz (dE_geltar , "nulldate");
            hC_Gz (dE_girtar , "nulldate");
            hC_Gz (dE_ciktar , "nulldate");
            cbX_durum->setCurrentText (" ");
            hClE_yetkili1->lineEdit->setText ("");
            hClE_yetkili2->lineEdit->setText ("");

            // iş emrinde yeni kayda git
            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *iemaxid_nT , 0);
            ////////////////////////////////////////////////

            /// yeni boş kayıt eklendi

            ///////////////////////////////////////////////////////////////////
            /// ieno nun olduğu indexteyiz
            QModelIndex iendx = tb_view->table->currentIndex ();
            int iendxrow = iendx.row ();


            /// mkn den gelen resmi ie ye yazalım
            tb_model->setData(tb_model->
                              index(iendxrow, tb_model->fieldIndex
                                    ( "ie_rsmmkn" )), *mknrsm_bA );


            tb_model->submitAll();

            QByteArray iersm_bA = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_resimie" )).data ().toByteArray ();
            QByteArray mknrsm_bA = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_resimmkn" )).data ().toByteArray ();
            ///////////////////////////////////////////////////////////////////

            QByteArray itemData;
            auto  *dataStream = new QDataStream (&itemData, QIODevice::WriteOnly);

            *dataStream << iemaxid_nT        // ieno
                        << mknkrmno_sT
                        << mknrsm_bA
                        << iersm_bA  ;
            /// objeyi oluştur

            isEmriYeni ( dataStream );

        }

        qDebug () <<mesaj;

        // iş emri detay ekle

    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                    "ie_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "ie_resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // ie  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("İŞ EMRİNİ SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "İş emrini silerseniz;\n"
                       "bu İş Emri bağlı (iş emri detay, taşınır ve işçilik)\n "
                       "tüm kayıtlarda silinir\n "
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            /// önce bu iş emrine bağlı
            /// iedet
            /// iedet kayıtlarına bağlı
            /// taşınır
            /// işçilik kayıtlarını silelim



            // şimdi iş emrini silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex indx = tb_view->table->currentIndex ();

            // iedet sil
            QString ieieno = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("ie_no"))).toString ();

            s_qry = QString("DELETE FROM iedet_dbtb "
                            "WHERE iedet_id = %1").arg( ieieno );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Detay Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - İş Emri Detay Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
            // ie sil
            QString idie = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("ie_id"))).toString ();


            s_qry = QString("DELETE FROM ie_dbtb "
                            "WHERE ie_id = %1").arg( idie );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - İş Emri Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
        }

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 setfilter
        // 011-02 filtrele

        /// iş emri no her yılbaşında birden başlar


        /*       int no = tb_model->data
                (tb_model->index
                 (Index.row (),
                  tb_model->fieldIndex ("no"))).toInt ();
*/
        // 011-03 ie de row değiştiğinde ie noyu ismini etrafa yayınlayalım
        emit hC_IE::sgnIsEmri ( tb_view->table->model()->
                                index( Index.row() ,
                                       tb_model->fieldIndex ("ie_no")
                                       ).data().toInt() );

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });

    // --- 013-01 iş durumuna göre tarihleri gizle
    connect(  cbX_durum , &QComboBox::currentTextChanged,
              [this]( QString text )
    {
        if (text == " ")
        {
            hC_Gz ( dE_geltar, "0" );
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );



        }
        else if (text == "Sıra Bekliyor")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Bakıma Alındı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Tamamlandı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "1" );
        }
    });


}

void hC_IE::isEmriYeni(QDataStream *dataStream)
{

    /// objeyi oluştur


    IEcard *boatIcon = new IEcard (dragger);

    ///objeyi olşturduk ie özelliklerini içine atalım
    boatIcon->setDefaults ( dataStream);
}

void hC_IE::isEmriListele()
{

    ///// toolbutton için
    ////////////////// iş emirlerini ekrana listele
    DragWidget::count = 0 ;
    DragWidget::row = 65 ;
    DragWidget::col = 20 ;
    QSqlQuery query("SELECT * FROM ie_dbtb "
                    "WHERE ie_durum != 'Tamamlandı'");
    if (query.isActive ())
    {
        qDebug()<< "active " ;
    }
    else {
        qDebug()<< "not active "<< query.lastError ().text ();
        return;
    }
    qDebug()<< " before while query size "<<query.size ();
    // qDebug()<<query.next();
    QByteArray itemData;
    auto dataStream = new QDataStream (&itemData, QIODevice::WriteOnly);



    while (query.next())
    {
        qDebug()<< " in while query size ----------- "<<query.isValid ();

        int ieno_nT {query.value ("ie_no").toInt () };
        QString krmno_sT {query.value ("ie_mkn").toString ()};
        ///////////////////////////////////////////////////////////////////
        /// ieno nun olduğu index i bulalım
        QSortFilterProxyModel proxy;
        proxy.setSourceModel(tb_model);
        proxy.setFilterKeyColumn(1);
        proxy.setFilterFixedString( QString::number(ieno_nT));
        // now the proxy only contains rows that match the name
        // let's take the first one and map it to the original model
        QModelIndex matchingIndex = proxy.mapToSource(proxy.index(0,0));
        if(matchingIndex.isValid()){
            tb_view->table->scrollTo(matchingIndex,QAbstractItemView::EnsureVisible);
        } else {
            QMessageBox::information(this,"Name Search:", "Match not found!");
        }
        /// index  istediğimiz yere geldi

        QModelIndex ndx = tb_view->table->currentIndex ();
        int ndxrow = ndx.row ();

        /// ie resmini table dan alalım
        QByteArray iersmie_bA = tb_view->table->model()
                ->index( ndxrow, tb_model
                         ->fieldIndex ("mkn_resim") ).data().toByteArray ();

        /// mkn resmini table dan alalım
        QByteArray iersmmkn_bA = tb_view->table->model()
                ->index( ndxrow, tb_model
                         ->fieldIndex ("mkn_resim") ).data ().toByteArray ();


        ///////////////////////////////////////////////////////////////////
        * dataStream << ieno_nT
                     << krmno_sT
                     << iersmmkn_bA ;


        /////////////////////////////////////////////////////////////////
        auto x = new QDialog ;

        QPixmap xp;
        x->setWindowTitle("mkn resim");
        auto xx = new QLabel ("3333333333333333333333");
        auto xx1 = new QLabel ("3333333333333333333333");

        QPixmap oP = QPixmap();

        if ( oP.loadFromData( iersmmkn_bA ))
        {
            qDebug()<<"resim load edildi";

            xx1->setPixmap( oP );
        }
        else
        {
            qDebug()<<"resim NOT loaded ";

            xx1->setPixmap (QPixmap (":/rsm/rsm_yok.png"));
            // lB_resim->setPixmap (QPixmap (""));
        }

        auto gr = new QVBoxLayout();
        x->setLayout (gr);
        gr->addWidget (xx1);
        gr->addWidget (xx);
        xx->setMinimumSize (QSize(160,100));

        x->exec();

        /////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////
        isEmriYeni ( dataStream );
    }

}


hC_IE::~hC_IE()
{
    qDebug() << "*********** destructor İŞ EMRİ " ;
}


