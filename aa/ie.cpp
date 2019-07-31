﻿#include "ie.h"


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
qDebug()<<" 2 seçim için makina ya giriliyor ";
        xl.addWidget (mkn);

        //*** seçim penceresinde makina seçilir
        // yoksa yeni oluşturulur
        auto mknkrmno = new QString;
        auto mknrsm = new QByteArray ;
qDebug()<<" 3 makina penceresi ";
        connect(mkn, &hC_MKN::sgnMkn,
                [mknkrmno, mknrsm  ]
                (QString krmNo,
                QByteArray byteArray) mutable
        {
            //***  1   iş emri için kurum no
            *mknkrmno = krmNo ;
            //*** signal dan gelen byte array
            *mknrsm  =  byteArray ;
            qDebug()<<"  31 makina no mkn den alındı = "<<*mknkrmno;
            qDebug()<<"  32 mknresim len-----------  = "<< mknrsm->size ();
        });
        makinasec.exec ();
        //*** makina seçildi yola devam
        qDebug()<<" **********************************************";
qDebug()<<" 4 makina seçildi ----------------------------------";
qDebug()<<"  41 makina no mkn den alındı = "<<*mknkrmno;
qDebug()<<"  42 mknresim        len      = "<< mknrsm->size ();
        ////////////////////////////////////////////////
        /// yeni iş emri numaasını bul
        /// iş emri nosu _dbtb de
        /// no alanındaki en büyük sayı
qDebug()<<" 5 yeni kayıt için ie no dosyada bulunuyor";
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id     = maxID.hC_NrMax ( tb_name,
                                       tb_flds->value (0,0));
qDebug()<<"  51 ie_no = "<<* max_id;
        ////////////////////////////////////////////////
        /// yeni kaydı ekle
  /*
        QSqlRecord rec = tb_model->record();
        tb_model->record().setValue (QString::number( *max_id),"ie_no");
        tb_model->record().setValue (*mknkrmno,"ie_mkn");
        tb_model->record().setValue (cbX_durum->itemText (0),"ie_durum");
        tb_model->record().setValue (QDate::currentDate ().toString
                                     ("dd/MM/yy"),"ie_tarih");

        QString bA = mknrsm->toBase64();
        tb_model->record().setValue ( bA ,"ie_resimmkn");

        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        tb_model->submitAll ();
    */



        QSqlQuery q;
        QString qry, mesaj("");
    /*    qry = "INSERT INTO " +  *tb_name  +
                " ( "
                "ie_no   , "
                "ie_mkn   , "
                "ie_durum, "
                "ie_tarih, "
                "ie_resimmkn "
                " )"
                " values("
                " '"+QString::number( *max_id)+"' , "
                " '"+ * mknkrmno  +"' , "
                " '"+cbX_durum->itemText (0)  +"' , "
                " '"+QDate::currentDate ().toString ("dd/MM/yy")+"' ,"
                " '"+ mknrsm->toBase64 () +"' "
                +  " )" ; */
        qDebug()<<" 6 yeni kayıt dosyaya -------------------- ";
        qry = QString("INSERT INTO %1 ( "
                "ie_no    , "
                "ie_mkn   , "
                "ie_durum , "
                "ie_tarih ) "
                " values ( '%2', '%3', '%4', '%5' ) " )
                .arg ( *tb_name)
                .arg ( QString::number( *max_id))
                .arg ( * mknkrmno )
                .arg ( cbX_durum->itemText (0))
                .arg ( QDate::currentDate ().toString ("dd/MM/yy"));

        qDebug()<< "  66 char* len "<<  (  mknrsm)  ;

        if ( !q.exec(qry) )
        {
            qDebug ()<< "  600 kayıt yapılamadı ";
            mesaj = mesaj + " İş Emri Eklenemedi"+
                    "-----"+
                    q.lastError().text ()+
                    "-----";
        }
        else
        {
            mesaj = mesaj + " İş Emri eklendi.";
qDebug ()<< "  601 kayıt eklendi ";


qDebug ()<< " 7 kayıt tamam-------------";
QModelIndex ndx = tb_view->table->currentIndex ();
int ndxrow = ndx.row ();
qDebug ()<< "  71 kayıt indexi row  "<< ndxrow;
tb_model->setData(tb_model->
                   index(ndxrow, tb_model->fieldIndex
                         ( "ie_rsmmkn" )), *mknrsm);
/// yeni eklenenleri kaydedelim
tb_model->submitAll();




QSqlRecord dbrecor;
dbrecor = tb_model->record ( ndxrow );
qDebug ()<< "  72 model rowdaki record --------------------------------";
qDebug ()<< "  721 ---"  <<tb_model->record (ndx.row ());
qDebug ()<< "  73 dbrecor --------------------------------";
qDebug ()<< "  731--"  << dbrecor;




qDebug () <<"eklenen ieno     " << tb_model->record(ndxrow).
                                value ("ie_no").toString ();


            qDebug () <<"eklenen mkn rsm to byte array "
                     << tb_model->record(ndxrow).
                  value ("ie_resimmkn").toByteArray ().size ();

            qDebug () <<"eklenen mkn rsm to string     "
                     << tb_model->record(ndxrow).
                                value ("ie_resimmkn").Size ;


            hClE_mkn->lineEdit->setText ( *mknkrmno );
            hC_Gz (dE_geltar , "nulldate");
            hC_Gz (dE_girtar , "nulldate");
            hC_Gz (dE_ciktar , "nulldate");
            cbX_durum->setCurrentText (" ");
            hClE_yetkili1->lineEdit->setText ("");
            hClE_yetkili2->lineEdit->setText ("");

            // QLineEdit f;
            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
            ////////////////////////////////////////////////

            /// yeni boş kayıt eklendi
            /// objeyi oluştur

            qDebug ()<< " 7 kayıt tamam-------------";
         //   QModelIndex ndx = tb_view->table->currentIndex ();
         //  int ndxrow = ndx.row ();
            qDebug ()<< "  71 kayıt indexi row  "<< ndxrow;
         //   QSqlRecord dbrecor;
            dbrecor = tb_model->record ( ndxrow );
qDebug ()<< "  72 model rowdaki record --------------------------------";
qDebug ()<< "  721 ---"  <<tb_model->record (ndx.row ());
qDebug ()<< "  73 dbrecor --------------------------------";
qDebug ()<< "  731--"  << dbrecor;


            auto dbrec = new QSqlRecord;
            dbrec = &dbrecor;
            qDebug ()<< "  74 *dbrec --------------------------------";
            qDebug ()<< "  741--"  << *dbrec;

            isEmriYeni ( * dbrec );

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

void hC_IE::isEmriYeni(QSqlRecord record)
{

    /// objeyi oluştur
qDebug()<<endl;
qDebug()<< " 9 iş emri recordddddddddddddddddddddddddd   " << record;
qDebug()<< "   91 -----işemriyeni--------------------------------";
qDebug()<< "   92 rsmmkn size  " << record.value ("ie_resimmkn").toString ().size ();
qDebug()<<endl;
IEcard *boatIcon = new IEcard (dragger);

    ///objeyi olşturduk ie özelliklerini içine atalım
    /// burada table dan direk okuma yerine
    /// table recordu objenin içine yerleştirdik
    /// obje oluştuğunda table ile bağlantısı kalmıyor
    /// record zaten içinde
    boatIcon->setRecord(record);
    qDebug()<< "rec after booticon setrecord---------------" ;
    qDebug()<< "while no " << record.value ("ie_no");
    qDebug()<< "mkn no   " << record.value ("ie_mkn");
    qDebug()<< "drm      " << record.value ("ie_durum");
    qDebug()<< "trh      " << record.value ("ie_tarih");
    qDebug()<< "rsmie    " << record.value ("ie_resimie").toString ().size ();
    qDebug()<< "rsmmkn   " << record.value ("ie_resimmkn").toString ().size ();

    /// özellikleri içinden alıp objeyi oluşturalım
    boatIcon->setDefaults (/*record*/);
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
    while (query.next())
    {
qDebug()<< " in while query size ----------- "<<query.isValid ();


        auto outPixmap = new QPixmap ;
        outPixmap->loadFromData( query.value ("ie_resimmkn").toByteArray () );
        QSqlRecord record ;
        record = query.record();
        qDebug()<< " listeleme başladı "<<query.isActive ();
        qDebug()<< "db --------query.record().value------record.value---------------------------" ;
        qDebug()<< "while no " << query.record().value ("ie_no") <<" ---- "<< record.value ("ie_no");
        qDebug()<< "mkn no   " << query.record().value ("ie_mkn")<<" ---- "<< record.value ("ie_mkn");
        qDebug()<< "rsmie    " << query.record().value ("ie_resimie").toString ().size () ;
        qDebug()<< "rsmmkn 00" << query.record().value ("ie_resimmkn").toByteArray ().size () ;
        //////////////////////////////////////////////////
        /// makina resmini al
        ///
        QSqlQuery q;
        QString qry, mesaj("");

        qry = "SELECT * FROM mkn_dbtb "
              "WHERE mkn_kurumno =  '"+
                record.value("ie_mkn").toString () +"' ";



        qDebug()<< "select oldumu olmadımı  ?   " <<q.exec (qry)<<endl<<qry;
        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "Mkn krmno bulunamadı"+
                    "<br>------------------------------------<br>"+
                    q.lastError().text ()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = mesaj + "mkn rsm bulundu.";








            q.next ();

            qDebug()<<"-*-*-*-*-***-*-*-***-*-*-*-*-*-*-";
            qDebug()<<"selecteki mkn_resim uzunluğu : "<<endl
                   <<q.value ("mkn_resim").toString ().size ();
            record.value ("ie_resimmkn")=q.value ("mkn_resim");
        }

        auto x = new QDialog ;

        QPixmap xp;
        x->setWindowTitle("mkn resim");
        auto xx = new QLabel ("3333333333333333333333");
        auto xx1 = new QLabel ("3333333333333333333333");

qDebug () <<mkn->tb_view;
        int rowidx = mkn->tb_view->table->currentIndex().row();

        // row, xolumn daki veriyi bytearray a at
        //QByteArray outByteArray = mkn->tb_view->table->
          //      model()->index( rowidx, mkn->tb_model->
            //        fieldIndex ( "mkn_resim" ) ).data().toByteArray();

        QByteArray outByteArray = q.value("mkn_resim").data

        QPixmap oP = QPixmap();

        if ( oP.loadFromData( outByteArray  ))
        {
            qDebug()<<"resim load edşldi";

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

        //////////////////////////////////////////////////
        qDebug()<< "select mesaj ========    " <<mesaj ;

        qDebug()<< "rsmmkn   " << record.value ("ie_resimmkn").toString ().size ();
qDebug()<< "------------------ iişemri yeni(recoda git)";
        isEmriYeni ( record);
    }

}


hC_IE::~hC_IE()
{
    qDebug() << "*********** destructor İŞ EMRİ " ;
}


