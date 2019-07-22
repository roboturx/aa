#include "mkn.h"

hC_MKN::hC_MKN() : hC_tBcreator ()
{


    qDebug ()<<"Constructor MAKİNA **********************************";
    //************************************************************
    //*****************  M A K İ N A  ****************************


    win_Label->setText ( "ARAÇ BİLGİLERİ");
    *tb_name  = "mkn_dbtb" ;
    *tb_ndex  = "mkn_kurumno";

    tb_flds = new hC_ArrD (18, 4);
    tb_flds->setValue ( 0, "mkn_ID"     , "INTEGER", "MakineID", "0" ) ;
    tb_flds->setValue ( 1, "mkn_kurumno", "TEXT"   , "Kurum No" );
    tb_flds->setValue ( 2, "mkn_plaka"  , "TEXT"   , "Plaka No" );
    tb_flds->setValue ( 3, "mkn_cinsi"  , "TEXT"   , "Cinsi");
    tb_flds->setValue ( 4, "mkn_marka"  , "TEXT"   , "Marka"   );
    tb_flds->setValue ( 5, "mkn_modeli" , "TEXT"   , "Model"   );
    tb_flds->setValue ( 6, "mkn_myili"  , "TEXT"   , "Model Yılı"    );
    tb_flds->setValue ( 7, "mkn_sase"   , "TEXT"   , "Şase No"  );
    tb_flds->setValue ( 8, "mkn_motorno", "TEXT"   , "Motor No" );
    tb_flds->setValue ( 9, "mkn_motortipi", "TEXT" , "Motor Tipi");
    tb_flds->setValue (10, "mkn_yakit"  , "TEXT"   , "Yakıt Türü");
    tb_flds->setValue (11, "mkn_surucu" , "TEXT"   , "Sürücü"    );
    tb_flds->setValue (12, "mkn_surtar" , "TEXT"   , "İşe Başlama Tarihi");
    tb_flds->setValue (13, "mkn_birim"  , "TEXT"   , "Birimi");
    tb_flds->setValue (14, "mkn_aciklama" , "TEXT"   , "Açıklama");
    tb_flds->setValue (15, "mkn_bulyer" , "TEXT"   , "Bulunduğu Yer");
    tb_flds->setValue (16, "mkn_rating" , "TEXT"   , "Rating", "0");
    tb_flds->setValue (17, "mkn_resim"  , "BLOB"   , "Resim" , "0" );


    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( led_mknKurumno = new QLineEdit  ) ;
    tb_wdgts->append ( led_mknPlaka = new QLineEdit  ) ;
    tb_wdgts->append ( hClE_cins = new hC_Le ) ;
    tb_wdgts->append ( hClE_mark = new hC_Le    ) ;
    tb_wdgts->append ( hClE_modl = new hC_Le    ) ;
    tb_wdgts->append ( spn_mknYil = new QSpinBox     ) ;
    tb_wdgts->append ( led_mknSase = new QLineEdit   ) ;
    tb_wdgts->append ( led_mknMotor = new QLineEdit    ) ;
    tb_wdgts->append ( led_mknMtip  = new QLineEdit   ) ;
    tb_wdgts->append ( cbx_mknYkt  = new QComboBox ) ;
    tb_wdgts->append ( cbx_mknSurucu  = new QComboBox   ) ;
    tb_wdgts->append ( clndr_mknSurucutar = new QDateTimeEdit(QDate::currentDate())  ) ;
    tb_wdgts->append ( cbx_mknBirim  = new QComboBox    ) ;
    tb_wdgts->append ( ted_mknAcklm = new QTextEdit   ) ;
    tb_wdgts->append ( cbx_mknByer  = new QComboBox    ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}

void hC_MKN::tbsetup()
{
    qDebug ()<<"   mkn setup";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );
    tb_mapper->addMapping (hClE_cins->lineEdit ,
                           tb_model->fieldIndex ("mkn_cinsi"));
    tb_mapper->addMapping (hClE_mark->lineEdit ,
                           tb_model->fieldIndex ("mkn_marka"));
    tb_mapper->addMapping (hClE_modl->lineEdit ,
                           tb_model->fieldIndex ("mkn_modeli"));


    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_MKN::tbui()
{
    qDebug ()  <<"   mkn ui";
    setWindowTitle (win_Label->text());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget (tb_view       , 0, 0, 1, 5);
    win_Grid->addWidget (win_Wdgt        , 0, 5, 1, 5);

}

void hC_MKN::tbwdgt()
{

    qDebug ()  <<"   wdgt";

    auto *lB_kurumno = new QLabel("Kurum No");

  //  connect( led_mknKurumno, &QLineEdit::textChanged,
    //         this,  &hC_MKN::mknKurumno_ara);
    lB_kurumno->setBuddy(led_mknKurumno);
    led_mknKurumno->setFocus();
    led_mknKurumno->setReadOnly (true);

    auto *lB_plaka = new QLabel("Plaka ");
    lB_plaka->setBuddy(led_mknPlaka);

    // /////////////////////////////////////////////////////
    // cins
    auto *lB_cins = new QLabel("Cins");
    hClE_cins->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(hClE_cins->pushButton , &QPushButton::clicked,
            [this ]()
    {
        // seçebilmek için pencere

        auto *dia = new QDialog();
        dia->setModal (true);
        dia->setGeometry ( 50, //hClE_cins->pushButton->pos ().rx (),
                          400, //hClE_cins->pushButton->pos ().ry (),
                          900,200);
        dia->setWindowTitle ("Cinsi - Marka ve Modeli "+
            QString::number(hClE_cins->lineEdit->pos ().rx ())+"," +
            QString::number(hClE_cins->lineEdit->pos ().ry ())+" - "+
            QString::number(hClE_cins->pos ().x() )+"," +
            QString::number(hClE_cins->pos ().y ()));

        auto *c = new hC_MKCINS ;

        c->tbsetup ();



        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (c , &hC_MKCINS::sgnCmmy ,
                 [ this ] ( QString * sgnText )
        {
            hClE_cins->lineEdit->setText ( *sgnText );
            hClE_cins->lineEdit->setFocus();
        });

        ////////////////////////////////////////////************

        // seçebilmek için pencere
        auto *cm = new hC_MKMARK ;
        cm->tbsetup ();

        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (cm , &hC_MKMARK::sgnmkMark ,
                 [ this ] ( QString* sgnText )
        {
            hClE_mark->lineEdit->setText ( *sgnText );
            hClE_mark->lineEdit->setFocus();
        });
        //cm->show ();


        // seçebilmek için pencere
        auto *cmm = new hC_MKMODL ;
        cmm->tbsetup ();

        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (cmm , &hC_MKMODL::sgnmkModl ,
                 [ this ] ( QString* sgnText )
        {
            hClE_modl->lineEdit->setText (* sgnText );
            hClE_modl->lineEdit->setFocus();
        });
        //cmmy->show ();
        ////////////////////////////////////////////**************

        auto *layout = new QGridLayout;
        dia->setLayout (layout);
        layout->addWidget (c  ,0 ,0 );
        layout->addWidget (cm ,0 ,1 );
        layout->addWidget (cmm,0 ,2 );



        dia->exec ();
    });

    // /////////////////////////////////////////////////////

    auto *lB_mark = new QLabel("Marka");
    hClE_mark->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(hClE_mark->pushButton , &QPushButton::clicked,
            hClE_cins->pushButton, &QPushButton::click );

 /*           [this ]()
    {

        // seçebilmek için pencere
        auto *cmmy = new hC_MKMARK ;
        cmmy->mkmark_setup ();

        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (cmmy , &hC_MKMARK::sgnCmmy ,
                 [ this ] ( QString sgnText )
        {
            hClE_mark->lineEdit->setText ( sgnText );
            hClE_mark->lineEdit->setFocus();
        });
        cmmy->show ();
    });*/
// ///////////////////// marka
    // /////////////////////////////////////////////////////

    auto *lB_modl = new QLabel("Model");
    hClE_modl->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(hClE_modl->pushButton , &QPushButton::clicked,
            hClE_cins->pushButton, &QPushButton::click );

 /*
            [this]()
    {

        // seçebilmek için pencere
        auto *cmmy = new hC_MKMODL ;
        cmmy->mkmodl_setup ();


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (cmmy , &hC_MKMODL::sgnCmmy ,
                 [ this ] ( QString sgnText )
        {
            hClE_modl->lineEdit->setText ( sgnText );
            hClE_modl->lineEdit->setFocus();
        });
        cmmy->show ();
    });*/

    auto *lB_mknYil = new QLabel("Yıl ");
    spn_mknYil->setMinimum (1900);
    spn_mknYil->setMaximum (2023);
    spn_mknYil->setValue ( QDate::currentDate ().year ());
    lB_mknYil->setBuddy(spn_mknYil);


    // /////////////////////////////////////////////////////



    auto *lB_mknSase = new QLabel("Şase No   ");
    lB_mknSase->setBuddy(led_mknSase);

    auto *lB_mknMotor = new QLabel("Motor No ");
    lB_mknMotor->setBuddy(led_mknMotor);


    auto *lB_mknMtip = new QLabel("Motor Tipi");
    lB_mknMtip->setBuddy(led_mknMtip);

    QLabel *lB_mknYkt = new QLabel("Yakıt Türü");
    cbx_mknYkt->insertItem(1,"Benzin");
    cbx_mknYkt->insertItem(2,"Dizel");
    cbx_mknYkt->insertItem(3,"LPG");
    cbx_mknYkt->insertItem(4,"Benzin-LPG");
    cbx_mknYkt->insertItem(5,"Doğalgaz");
   // pb_mknYkt = new QPushButton;
   // connect( pb_mknYkt, &QPushButton::clicked, this, &hC_MKN::ykt);

    auto *lB_mknSurucu = new QLabel("Sürücü  ");
   // pb_mknSurucu = new QPushButton;
    //connect( pb_mknSurucu, &QPushButton::clicked, this, &hC_MKN::src);


    QLabel *lB_mknSurucutar = new QLabel("Sürücü İşe Başlama");

    clndr_mknSurucutar->setMinimumDate(QDate(1900, 1, 1));
    clndr_mknSurucutar->setMaximumDate(QDate(2023, 1, 1));
    clndr_mknSurucutar->setDisplayFormat("dd.MM.yyyy");
    clndr_mknSurucutar->setCalendarPopup(true);

    QLabel *lB_mknBirim = new QLabel("Birim   ");
    //pb_mknBirim = new QPushButton;
   // connect( pb_mknBirim, &QPushButton::clicked, this, &hC_MKN::birim);
   // lB_mknBirim->setBuddy(cbx_mknBirim);

    QLabel *lB_mknByer = new QLabel("Bulunduğu Yer ");
    //pb_mknByer = new QPushButton;
    //connect( pb_mknByer, &QPushButton::clicked, this, &hC_MKN::byer);
    lB_mknByer->setBuddy(cbx_mknByer);


    QLabel *lB_mknAcklm = new QLabel("Açıklama   ");
    lB_mknAcklm->setBuddy(ted_mknAcklm);


    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    
    win_Wdgt->adjustSize();
    auto mknGrid = new QGridLayout();
    win_Wdgt->setLayout(mknGrid);

    ///////////////////////////////////////
    led_mknPlaka->setMinimumSize (200,25);

    int satr=0;

    mknGrid->addWidget(lB_kurumno    ,  satr,0,1,1 );
    mknGrid->addWidget(led_mknKurumno,  satr,1,1,2 );

    mknGrid->addWidget(win_Rsm       ,  satr,3,4,4 );

    mknGrid->addWidget(lB_plaka      ,++satr,0,1,1 );
    mknGrid->addWidget(led_mknPlaka  ,  satr,1,1,2 );
    mknGrid->addWidget(lB_cins       ,++satr,0,1,1 );
    mknGrid->addWidget(hClE_cins       ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mark       ,++satr,0,1,1 );
    mknGrid->addWidget(hClE_mark       ,  satr,1,1,2 );
    mknGrid->addWidget(lB_modl       ,++satr,0,1,1 );
    mknGrid->addWidget(hClE_modl       ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mknYil     ,++satr,0,1,1 );
    mknGrid->addWidget(spn_mknYil    ,  satr,1,1,2 );

    mknGrid->addWidget(lB_mknSase    ,++satr,0,1,1 );
    mknGrid->addWidget(led_mknSase   ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mknMotor   ,  satr,3,1,1 );
    mknGrid->addWidget(led_mknMotor  ,  satr,4,1,2 );
    mknGrid->addWidget(lB_mknMtip    ,++satr,0,1,1 );
    mknGrid->addWidget(led_mknMtip   ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mknYkt     ,  satr,3,1,1 );
    mknGrid->addWidget(cbx_mknYkt    ,  satr,4,1,2 );
    mknGrid->addWidget(lB_mknSurucu  ,++satr,0,1,1 );
    mknGrid->addWidget(cbx_mknSurucu ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mknSurucutar   ,  satr,3,1,1 );
    mknGrid->addWidget(clndr_mknSurucutar,  satr,4,1,2 );
    mknGrid->addWidget(lB_mknBirim   ,++satr,0,1,1 );
    mknGrid->addWidget(cbx_mknBirim  ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mknByer    ,  satr,3,1,1 );
    mknGrid->addWidget(cbx_mknByer   ,  satr,4,1,2 );
    mknGrid->addWidget(lB_mknAcklm   ,++satr,0,1,1 );
    mknGrid->addWidget(ted_mknAcklm  ,  satr,1,1,5 );


}
/////////////////////////////////     ekrandaki her şeyi kontrol edelim
void hC_MKN::tbkntrl()
{
    qDebug ()  <<"   mkn kontrol ";
    /// tüm işlemler tamam kontrol edelim

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        auto *dia_kurumno =new QDialog(this);
        dia_kurumno->setModal (true);
        dia_kurumno->setWindowTitle ("Araç Kurum No Giriniz");
        auto *ly_diafno = new QHBoxLayout(dia_kurumno) ;

        auto *wdkod = new QWidget;
        ly_diafno->addWidget (wdkod);

        auto *wd_ly = new QHBoxLayout;
        wdkod->setLayout (wd_ly);

        auto *lE_krmno = new QLineEdit{};
        //lE_krmno->setPlaceholderText ("Fatura No Giriniz...");


        auto *pB_vz = new QPushButton("Vazgeç");
        connect(pB_vz, &QPushButton::clicked,
                [dia_kurumno] ()
        {
            dia_kurumno->close() ;
        });


        auto *pB_ok = new QPushButton("Kaydet");
        pB_ok->setDefault (true);



        auto *pb_ly = new QHBoxLayout;
        pb_ly->addWidget (pB_vz);
        pb_ly->addWidget (pB_ok);

        wd_ly->addWidget (lE_krmno);
        wd_ly->addLayout (pb_ly);


        // kurum no no önemli
        // boş geçmek olmaz

        // ///////////////// yeni fatura no ekle
        connect(pB_ok, &QPushButton::clicked ,
                [this,lE_krmno, dia_kurumno ]()
        {

            //  qDebug()<<"fatura no boş geçilemez";
            if (lE_krmno->text () == "")
            {
                lE_krmno->setPlaceholderText ("Kurum No boş geçilemez");
                return;
            }

            // kayıt oluşturalım
            QSqlRecord rec = tb_model->record();
            rec.setValue ("mkn_kurumno"  , lE_krmno->text ());
            rec.setValue ("mkn_yil"      , QDate::currentDate ().year ());
            rec.setValue ("mkn_cinsi"     , " " );
            rec.setValue ("mkn_marka"    , " " );
            rec.setValue ("mkn_modeli"   , " " );
// QString date(QDate::currentDate().toString ( "dd-MM-yyyy" ));

// rec.setValue ("ftr_tarih"   , date );


            ////////////////////////////////////////////////
            hC_Nr maxID;
            int* max_id = new int{};
            *max_id     = maxID.hC_NrMax ( tb_name,
                                tb_flds->value (0,0));
            ////////////////////////////////////////////////


            // insert a new record (-1)
            if ( ! tb_model->insertRecord(tb_model->rowCount (),rec))
            {
                qDebug() << " HATA - MAKİNA kaydı eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt MAKİNA ya eklendi ";
                tb_model->submitAll ();

                ////////////////////////////////////////////////
                /// son eklenen kayda git
                maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
                ////////////////////////////////////////////////
            }

            dia_kurumno->close ();
        });
        dia_kurumno->exec ();
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                           "resim","değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {

        // ambar demirbaş kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton("BU MAKİNAYA AİT TÜM KAYITLARI SİL", QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton("VAZGEÇ",QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("                   !! DİKKAT !!\n"
                       "             Makina Kaydını silerseniz;\n"
                       "bu makinaya bağlı (arıza, bakım, sigorta, muayene vb.)\n "
                       "               tüm kayıtlarda silinir\n "
                       "   \n"
                       "           Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex indx = tb_view->table->currentIndex ();
            QString ino = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("id_mkn"))).toString ();

            s_qry = QString("DELETE FROM dbtb_mkn "
                            "WHERE id_mkn = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " Demirbaş Ambar Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - MAKİNA İKMAL Kaydı Silinemedi "
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
        // 011-02 mkn row değiştiğinde kırumno etrafa yayınlayalım
        emit sgnMkn (tb_view->table->model()->index( Index.row() ,
                tb_model->fieldIndex ("mkn_kurumno") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });



    // makina view sağ tık context menusu
    // mkn sağ tık menu kontrollerini
    // bu fonksiyonun içinden kontrol edelim

    // --- 013 sağ tık menusu
    connect(tb_view->table, &QTableView::customContextMenuRequested,
            [this]()
    {

        //qDebug ()  <<"  cw mkn view sağ tuş 001";
        auto *menu = new QMenu(this);

        // sigorta kaydı ekle
        const QIcon ekleIc_sgrt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, "&Sigorta Ekle...", this);
        ekleAct_sgrt->setShortcuts (QKeySequence::New);
        ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
      //  connect (ekleAct_sgrt, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_sgrtSLOT );
        menu->addAction(ekleAct_sgrt);

        // muayene kaydı ekle
        const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mua = new QAction(ekleIc_mua, "&Muayene Ekle...", this);
        ekleAct_mua->setShortcuts (QKeySequence::New);
        ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
       // connect (ekleAct_mua, &QAction::triggered, this,
         //        &hC_MKN::onmnyeniEklE_muaSLOT );
        menu->addAction(ekleAct_mua);


        // yağ
        const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_yag = new QAction(ekleIc_yag, "&Yağ Ekle...", this);
        ekleAct_yag->setShortcuts (QKeySequence::New);
        ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
     //   connect (ekleAct_yag, &QAction::triggered, this,
   //              &hC_MKN::onmnyeniEklE_yagSLOT );
        menu->addAction(ekleAct_yag);


        // filtre
        const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_flt = new QAction(ekleIc_flt, "&Filtre Ekle...", this);
        ekleAct_flt->setShortcuts (QKeySequence::New);
        ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
       // connect (ekleAct_flt, &QAction::triggered, this,
         //        &hC_MKN::onmnyeniEklE_fltSLOT );
        menu->addAction(ekleAct_flt);

        // akü
        const QIcon ekleIc_aku = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_aku = new QAction(ekleIc_aku, "&Akü Ekle...", this);
        ekleAct_aku->setShortcuts (QKeySequence::New);
        ekleAct_aku->setStatusTip ("Akü Kaydı Ekle");
  //      connect (ekleAct_aku, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_akuSLOT );
        menu->addAction(ekleAct_aku);

        // lastik
        const QIcon ekleIc_lst = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_lst = new QAction(ekleIc_lst, "&Lastik Ekle...", this);
        ekleAct_lst->setShortcuts (QKeySequence::New);
        ekleAct_lst->setStatusTip ("Lastik Kaydı Ekle");
     //   connect (ekleAct_lst, &QAction::triggered, this,
       //          &hC_MKN::onmnyeniEklE_lstSLOT );
        menu->addAction(ekleAct_lst);

        // yakıt
        const QIcon ekleIc_mknYkt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mknYkt = new QAction(ekleIc_mknYkt, "&Yakıt Ekle...", this);
        ekleAct_mknYkt->setShortcuts (QKeySequence::New);
        ekleAct_mknYkt->setStatusTip ("Yakıt Kaydı Ekle");
  //      connect (ekleAct_mknYkt, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_mknYktSLOT );
        menu->addAction(ekleAct_mknYkt);

        // antifiriz
        const QIcon ekleIc_afz = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_afz = new QAction(ekleIc_afz, "&Antifiriz Ekle...", this);
        ekleAct_afz->setShortcuts (QKeySequence::New);
        ekleAct_afz->setStatusTip ("Antifiriz Kaydı Ekle");
   //     connect (ekleAct_afz, &QAction::triggered, this,
     //            &hC_MKN::onmnyeniEklE_afzSLOT );
        menu->addAction(ekleAct_afz);

        // zincir
        const QIcon ekleIc_zcr = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_zcr = new QAction(ekleIc_zcr, "&Zincir Ekle...", this);
        ekleAct_zcr->setShortcuts (QKeySequence::New);
        ekleAct_zcr->setStatusTip ("Zincir Kaydı Ekle");
 //       connect (ekleAct_zcr, &QAction::triggered, this,
   //              &hC_MKN::onmnyeniEklE_zcrSLOT );
        menu->addAction(ekleAct_zcr);

        // hgs
        const QIcon ekleIc_hgs = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_hgs = new QAction(ekleIc_hgs, "&HGS Ekle...", this);
        ekleAct_hgs->setShortcuts (QKeySequence::New);
        ekleAct_hgs->setStatusTip ("HGS Kaydı Ekle");
  //      connect (ekleAct_hgs, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_hgsSLOT );
        menu->addAction(ekleAct_hgs);

        menu->addSeparator();
        menu->popup(tb_view->table->viewport()->mapToGlobal(pos()));
    });


}       ///     kontrol

// ////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////
// ////////////////////  M K N   //////////////////////////////////////
// ////////////////////////////////////////////////////////////////////





/*
void hC_MKN::onmnyeniEklE_sgrtSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // sigorta  ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mksigorta ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"SİGORTA Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - SİGORTA Yeni Kayıt Eklenemedi - " << q.lastError() ;
    evrk_sgrt->mdl_evr_sgrt->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_sgrt));
    evrk_sgrt->tV_evr_sgrt->setFocus();


}                                           ///     onmnyeniEklE_sgrt

void hC_MKN::onmnyeniEklE_muaSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // muayene ekle
      QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkmuayene ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"MUAYENE Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - MUAYENE Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_mua



void hC_MKN::onmnyeniEklE_yagSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // yag ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkyag ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"YAĞ Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - YAĞ Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_yag



void hC_MKN::onmnyeniEklE_fltSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // flt ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkfiltre ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"FİLTRE Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - FİLTRE Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_flt



void hC_MKN::onmnyeniEklE_akuSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // aku ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkaku ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"AKÜ Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - AKÜ Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_aku



void hC_MKN::onmnyeniEklE_lstSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // lastik ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mklastik ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"ASTİK Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - LASTİK Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_lst



void hC_MKN::onmnyeniEklE_mknYktSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // yakıt ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkyakit ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"YAKIT Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - YAKIT Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_mknYkt


void hC_MKN::onmnyeniEklE_afzSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // antifiriz ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkantifiriz ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"ANTİFİRİZ Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - ANTİFİRİZ Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_afz



void hC_MKN::onmnyeniEklE_zcrSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // zincir ekle1
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkzincir ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"ZİNCİR Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - ZİNCİR Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}       ///      onmnyeniEklE_zcr



void hC_MKN::onmnyeniEklE_hgsSLOT()
{
    int id=-1;
    QModelIndex index = tb_view->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = tb_model->record(index.row());
        id = record.value("id_mkn").toInt();
    }
    // hgs ekle
    QSqlQuery q;
    if (q.exec("INSERT INTO dbtb_mkhgs ( mknstk_id )"
               " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"HGS Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "HATA - HGS Yeni Kayıt Eklenemedi - " << q.lastError() ;

    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();

}

*/




////////////////////////////////////////////////////////////  others
/*void hC_MKN::ww_mkcins()
{
    auto *w = new WW_Mkcins;
    //w->setModal(true);
    w->show();
    tb_model->select();

}       ///      ww_mkcins

*/

hC_MKN::~hC_MKN()
{
    qDebug() << "*********** destructor MAKİNA ";//    delete ui;
}

////////////////////////////////////////////
///
///
///
////
///
///
///
///
///*


//////////////////////////////////////////////////////////
///
///
///
///
///     Demirbaş Ambarı makina Ekle
///
///
///
///



//
//void hC_MKN::mknKurumno_ara()
//{



    /*
    QSqlQuery q;
    QString s_q;
    s_q = "select * from dbtb_mkn "
          "where kurumNo = "+led_mknKurumno->text().trimmed() ;
    q.prepare(s_q);
    if (q.exec())


    {
        if (q.next())
        {
            led_mknKurumno->setStyleSheet({"backgroundcolor : darkred;"});
        }
        else
        {
            led_mknKurumno->setStyleSheet({"backgroundcolor : green;"});
        }
    }
    else
    {
    qDebug()<<led_mknKurumno->text()<<"\n"; //<<q.lastError().text();
    //}

}


*/



//}

