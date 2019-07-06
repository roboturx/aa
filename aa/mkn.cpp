#include "mkn.h"

hC_MKN::hC_MKN(QWidget *parent) : QWidget(parent)
{

    qDebug ()<<"cnstrctr MAKİNA";
    //************************************************************
    //*****************  M A K İ N A  ****************************
}

void hC_MKN::mkn_setup()
{
    qDebug ()<<"setup MKN";

    hC_MKN::mkn_VTd   () ;
    hC_MKN::mkn_model () ;
    hC_MKN::mkn_wdgt  () ;
    hC_MKN::mkn_map   () ;
    hC_MKN::mkn_ui    () ;
    hC_MKN::mkn_view  () ;
    hC_MKN::mkn_kntrl () ;

}


void hC_MKN::mkn_ui()
{
    qDebug ()  <<"mkn ui";

    winLabel = new QLabel("ARAÇ BİLGİLERİ");
    this->setWindowTitle (winLabel->text ());

    MKNtview    = new hC_Tv (MKNmodel, MKNmapper, winWdgt);

    auto *mkn_l = new QGridLayout;
    mkn_l->addWidget ( MKNtview   , 0, 0, 1, 1 );
    mkn_l->addWidget ( winWdgt  , 0, 1, 1, 1 );
    //mkn_l->addWidget(wdgt_mppr  , 3, 6, 3, 5 );

    this->setLayout (mkn_l);
    qDebug ()  <<"mkn ui sonu 1";

}

void hC_MKN::mkn_wdgt()
{

    qDebug ()  <<"  mkn_wdgt";

    auto *lB_kurumno = new QLabel("Kurum No");
    led_mknKurumno = new QLineEdit();
  //  connect( led_mknKurumno, &QLineEdit::textChanged,
    //         this,  &hC_MKN::mknKurumno_ara);
    lB_kurumno->setBuddy(led_mknKurumno);
    led_mknKurumno->setFocus();
    led_mknKurumno->setReadOnly (true);

    auto *lB_plaka = new QLabel("Plaka ");
    led_mknPlaka = new QLineEdit();
    lB_plaka->setBuddy(led_mknPlaka);

    // /////////////////////////////////////////////////////
    // cins
    auto *lB_cins = new QLabel("Cins");
    lE_cins = new hC_Le ;
    lE_cins->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(lE_cins->pushButton , &QPushButton::clicked,
            [this ]()
    {
        // seçebilmek için pencere

        auto *dia = new QDialog();
        dia->setModal (true);
        dia->setGeometry ( 50, //lE_cins->pushButton->pos ().rx (),
                          400, //lE_cins->pushButton->pos ().ry (),
                          900,200);
        dia->setWindowTitle ("Cinsi - Marka ve Modeli "+
            QString::number(lE_cins->lineEdit->pos ().rx ())+"," +
            QString::number(lE_cins->lineEdit->pos ().ry ())+" - "+
            QString::number(lE_cins->pos ().x() )+"," +
            QString::number(lE_cins->pos ().y ()));

        auto *c = new hC_MKCINS ;

        c->mkCins_setup ();



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
            lE_cins->lineEdit->setText ( *sgnText );
            lE_cins->lineEdit->setFocus();
        });

        ////////////////////////////////////////////************

        // seçebilmek için pencere
        auto *cm = new hC_MKMARK ;
        cm->mkMark_setup ();

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
            lE_mark->lineEdit->setText ( *sgnText );
            lE_mark->lineEdit->setFocus();
        });
        //cm->show ();


        // seçebilmek için pencere
        auto *cmm = new hC_MKMODL ;
        cmm->mkModl_setup ();


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
            lE_modl->lineEdit->setText (* sgnText );
            lE_modl->lineEdit->setFocus();
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
    lE_mark = new hC_Le ;
    lE_mark->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(lE_mark->pushButton , &QPushButton::clicked,
            lE_cins->pushButton, &QPushButton::click );

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
            lE_mark->lineEdit->setText ( sgnText );
            lE_mark->lineEdit->setFocus();
        });
        cmmy->show ();
    });*/
// ///////////////////// marka
    // /////////////////////////////////////////////////////

    auto *lB_modl = new QLabel("Model");
    lE_modl = new hC_Le ;
    lE_modl->lineEdit ->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(lE_modl->pushButton , &QPushButton::clicked,
            lE_cins->pushButton, &QPushButton::click );

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
            lE_modl->lineEdit->setText ( sgnText );
            lE_modl->lineEdit->setFocus();
        });
        cmmy->show ();
    });*/

    auto *lB_mknYil = new QLabel("Yıl ");
    spn_mknYil = new QSpinBox();
    spn_mknYil->setMinimum (1900);
    spn_mknYil->setMaximum (2023);
    spn_mknYil->setValue ( QDate::currentDate ().year ());
    lB_mknYil->setBuddy(spn_mknYil);


    // /////////////////////////////////////////////////////



    auto *lB_mknSase = new QLabel("Şase No   ");
    led_mknSase = new QLineEdit();
    lB_mknSase->setBuddy(led_mknSase);

    auto *lB_mknMotor = new QLabel("Motor No ");
    led_mknMotor = new QLineEdit();
    lB_mknMotor->setBuddy(led_mknMotor);


    auto *lB_mknMtip = new QLabel("Motor Tipi");
    led_mknMtip = new QLineEdit();
    lB_mknMtip->setBuddy(led_mknMtip);

    QLabel *lB_mknYkt = new QLabel("Yakıt Türü");
    cbx_mknYkt  = new QComboBox;
    cbx_mknYkt->insertItem(1,"Benzin");
    cbx_mknYkt->insertItem(2,"Dizel");
    cbx_mknYkt->insertItem(3,"LPG");
    cbx_mknYkt->insertItem(4,"Benzin-LPG");
    cbx_mknYkt->insertItem(5,"Doğalgaz");
   // pb_mknYkt = new QPushButton;
   // connect( pb_mknYkt, &QPushButton::clicked, this, &hC_MKN::ykt);

    auto *lB_mknSurucu = new QLabel("Sürücü  ");
    cbx_mknSurucu = new QComboBox ;
   // pb_mknSurucu = new QPushButton;
    //connect( pb_mknSurucu, &QPushButton::clicked, this, &hC_MKN::src);


    QLabel *lB_mknSurucutar = new QLabel("Sürücü İşe Başlama");

    clndr_mknSurucutar = new QDateTimeEdit(QDate::currentDate());
    clndr_mknSurucutar->setMinimumDate(QDate(1900, 1, 1));
    clndr_mknSurucutar->setMaximumDate(QDate(2023, 1, 1));
    clndr_mknSurucutar->setDisplayFormat("dd.MM.yyyy");
    clndr_mknSurucutar->setCalendarPopup(true);

    QLabel *lB_mknBirim = new QLabel("Birim   ");
    cbx_mknBirim  = new QComboBox;
    //pb_mknBirim = new QPushButton;
   // connect( pb_mknBirim, &QPushButton::clicked, this, &hC_MKN::birim);
   // lB_mknBirim->setBuddy(cbx_mknBirim);

    QLabel *lB_mknByer = new QLabel("Bulunduğu Yer ");
    //pb_mknByer = new QPushButton;
    //connect( pb_mknByer, &QPushButton::clicked, this, &hC_MKN::byer);

    cbx_mknByer  = new QComboBox;
    lB_mknByer->setBuddy(cbx_mknByer);


    QLabel *lB_mknAcklm = new QLabel("Açıklama   ");
    ted_mknAcklm = new QTextEdit();
    lB_mknAcklm->setBuddy(ted_mknAcklm);


    winRsm = new QLabel;
    hC_Rs resim(winRsm);


    ///////////////////////////////////////
    winWdgt = new QWidget;
    winWdgt->setGeometry (0,0,800,300);
    auto mknGrid = new QGridLayout();
    winWdgt->setLayout(mknGrid);

    ///////////////////////////////////////
    led_mknPlaka->setMinimumSize (200,25);

    int satr=0;

    mknGrid->addWidget(lB_kurumno    ,  satr,0,1,1 );
    mknGrid->addWidget(led_mknKurumno,  satr,1,1,2 );
    mknGrid->addWidget(lB_plaka      ,++satr,0,1,1 );
    mknGrid->addWidget(led_mknPlaka  ,  satr,1,1,2 );
    mknGrid->addWidget(lB_cins       ,++satr,0,1,1 );
    mknGrid->addWidget(lE_cins       ,  satr,1,1,2 );
    mknGrid->addWidget(lB_mark       ,++satr,0,1,1 );
    mknGrid->addWidget(lE_mark       ,  satr,1,1,2 );
    mknGrid->addWidget(lB_modl       ,++satr,0,1,1 );
    mknGrid->addWidget(lE_modl       ,  satr,1,1,2 );
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
   // mknGrid->addWidget(lB_foto      ,++satr,0,4,4 );

}

void hC_MKN::mkn_view()
{
    qDebug()<<"  mkn view";
    MKNtview->table->setModel(MKNmodel);
    MKNslctnMdl = MKNtview->table->selectionModel ();

    // sağ tuş menusu
    MKNtview->table->setContextMenuPolicy(Qt::CustomContextMenu);

    // tableview de comboboxları göster
    //MKNtview->setItemDelegate(new MakinaDelegate(MKNtview));
    MKNtview->table->setItemDelegate(new QSqlRelationalDelegate(this));

    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("id_mkn"), true);
    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_resim"), true);
    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_rating"), true);

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    MKNtview->table->setCurrentIndex(
                MKNmodel->index(0, 1)
                );
    // with blue rect
    MKNtview->table->setFocus();
    //   QTimer::singleShot(0, MKNtview->table, SLOT(setFocus()));
}

void hC_MKN::mkn_map()
{
    qDebug()<<"set mapmkn";
    hC_MKN::MKNmapper = new QDataWidgetMapper(this);
    hC_MKN::MKNmapper->setModel(MKNmodel);

    // mapperdaki comboboxları çalıştır
    hC_MKN::MKNmapper->setItemDelegate(new QSqlRelationalDelegate(this));

    MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));
    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));

    MKNmapper->addMapping(lE_cins->lineEdit , MKNmodel->fieldIndex("mkn_cinsi"));
    MKNmapper->addMapping(lE_mark->lineEdit , MKNmodel->fieldIndex("mkn_marka"));
    MKNmapper->addMapping(lE_modl->lineEdit , MKNmodel->fieldIndex("mkn_modeli"));

    MKNmapper->addMapping(spn_mknYil, MKNmodel->fieldIndex("mkn_yil"));
    MKNmapper->addMapping(led_mknSase, MKNmodel->fieldIndex("mkn_saseno"));
    MKNmapper->addMapping(led_mknMotor, MKNmodel->fieldIndex("mkn_motorno"));
    MKNmapper->addMapping(led_mknMtip, MKNmodel->fieldIndex("mkn_motortip"));
    MKNmapper->addMapping(cbx_mknYkt, MKNmodel->fieldIndex("mkn_yakit"));
    MKNmapper->addMapping(cbx_mknSurucu, MKNmodel->fieldIndex("mkn_surucu"));
    MKNmapper->addMapping(clndr_mknSurucutar, MKNmodel->fieldIndex("mkn_surucu_tar"));
    MKNmapper->addMapping(cbx_mknBirim, MKNmodel->fieldIndex("mkn_birim"));
    MKNmapper->addMapping(cbx_mknByer, MKNmodel->fieldIndex("mkn_byer"));
    MKNmapper->addMapping(ted_mknAcklm, MKNmodel->fieldIndex("mkn_aciklama"));
    //MKNmapper->addMapping(lB_resim , MKNmodel->fieldIndex("mkn_resim"));
    //MKNmapper->addMapping(led_rating, MKNmodel->fieldIndex("rating"));




    hC_MKN::MKNmapper->toFirst ();

}


/////////////////////////////////     ekrandaki her şeyi kontrol edelim
void hC_MKN::mkn_kntrl()
{
    qDebug ()  <<"cw mkn kontrol ";
    /// tüm işlemler tamam kontrol edelim

    // pB 001 yeni ekle
    connect(MKNtview->pB_ekle, &QPushButton::clicked ,
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
            QSqlRecord rec = MKNmodel->record();
            rec.setValue ("mkn_kurumno"  , lE_krmno->text ());
            rec.setValue ("mkn_yil"      , QDate::currentDate ().year ());
            rec.setValue ("mkn_cinsi"     , " " );
            rec.setValue ("mkn_marka"    , " " );
            rec.setValue ("mkn_modeli"   , " " );
// QString date(QDate::currentDate().toString ( "dd-MM-yyyy" ));

// rec.setValue ("ftr_tarih"   , date );

            // insert a new record (-1)
            if ( ! MKNmodel->insertRecord(MKNmodel->rowCount (),rec))
            {
                qDebug() << " HATA - MAKİNA kaydı eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt MAKİNA ya eklendi ";
                MKNmodel->submitAll ();
                MKNmodel->select ();
            }
            dia_kurumno->close ();
        });
        dia_kurumno->exec ();
    });

    // pB 002 yeni resim ekle
    connect(MKNtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(winRsm, MKNtview, MKNmodel, MKNslctnMdl,
                           "mkn_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MKNslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( winRsm, MKNtview, MKNmodel, MKNslctnMdl,
                           "mkn_resim","değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(MKNtview->pB_sil, &QPushButton::clicked,
            [this]()
    {

        // ambar demirbaş kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("BU MAKİNAYA AİT TÜM KAYITLARI SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


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
            QModelIndex mkn_indx = MKNtview->table->currentIndex ();
            QString ino = MKNmodel->data
                    (MKNmodel->index
                     (mkn_indx.row (),
                      MKNmodel->fieldIndex ("id_mkn"))).toString ();

            s_qry = QString("DELETE FROM dbtb_mkn "
                            "WHERE id_mkn = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " Demirbaş Ambar Kaydı Silindi ";
                MKNmodel->submitAll ();
                MKNmodel->select ();
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

/*
    // pB 006 ilk
    connect(MKNtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        MKNtview->hC_TvPb ("ilk", MKNmodel, MKNmapper);
    });

    // pB 007 önceki
    connect(MKNtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MKNtview->hC_TvPb ("ncki", MKNmodel, MKNmapper);
    });

    // pB 008 sonraki
    connect(MKNtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MKNtview->hC_TvPb ("snrki", MKNmodel, MKNmapper);
    });

    // pB 009 son
    connect(MKNtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MKNtview->hC_TvPb ("son", MKNmodel, MKNmapper);
    });

    // pB 010 nav tuslari kontrol
    connect(MKNmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        MKNtview->hC_TvPb ("yenile", MKNmodel, MKNmapper);
    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  MKNslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        MKNmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
       // emit Cw_fr::sgnfirma(MKNtview->table->model()->index( Index.row() ,
         //           MKNmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  MKNslctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        MKNmapper->setCurrentModelIndex(Index);
    });



    // makina view sağ tık context menusu
    // mkn sağ tık menu kontrollerini
    // bu fonksiyonun içinden kontrol edelim

    // --- 013 sağ tık menusu
    connect(MKNtview->table, &QTableView::customContextMenuRequested,
            [this]()
    {

        //qDebug ()  <<"  cw mkn view sağ tuş 001";
        auto *menu = new QMenu(this);

        // sigorta kaydı ekle
        const QIcon ekleIc_sgrt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, tr("&Sigorta Ekle..."), this);
        ekleAct_sgrt->setShortcuts (QKeySequence::New);
        ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
      //  connect (ekleAct_sgrt, &QAction::triggered, this,
    //             &hC_MKN::onmnMKN_yeniEklE_sgrtSLOT );
        menu->addAction(ekleAct_sgrt);

        // muayene kaydı ekle
        const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mua = new QAction(ekleIc_mua, tr("&Muayene Ekle..."), this);
        ekleAct_mua->setShortcuts (QKeySequence::New);
        ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
       // connect (ekleAct_mua, &QAction::triggered, this,
         //        &hC_MKN::onmnMKN_yeniEklE_muaSLOT );
        menu->addAction(ekleAct_mua);


        // yağ
        const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_yag = new QAction(ekleIc_yag, tr("&Yağ Ekle..."), this);
        ekleAct_yag->setShortcuts (QKeySequence::New);
        ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
     //   connect (ekleAct_yag, &QAction::triggered, this,
   //              &hC_MKN::onmnMKN_yeniEklE_yagSLOT );
        menu->addAction(ekleAct_yag);


        // filtre
        const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_flt = new QAction(ekleIc_flt, tr("&Filtre Ekle..."), this);
        ekleAct_flt->setShortcuts (QKeySequence::New);
        ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
       // connect (ekleAct_flt, &QAction::triggered, this,
         //        &hC_MKN::onmnMKN_yeniEklE_fltSLOT );
        menu->addAction(ekleAct_flt);

        // akü
        const QIcon ekleIc_aku = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_aku = new QAction(ekleIc_aku, tr("&Akü Ekle..."), this);
        ekleAct_aku->setShortcuts (QKeySequence::New);
        ekleAct_aku->setStatusTip ("Akü Kaydı Ekle");
  //      connect (ekleAct_aku, &QAction::triggered, this,
    //             &hC_MKN::onmnMKN_yeniEklE_akuSLOT );
        menu->addAction(ekleAct_aku);

        // lastik
        const QIcon ekleIc_lst = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_lst = new QAction(ekleIc_lst, tr("&Lastik Ekle..."), this);
        ekleAct_lst->setShortcuts (QKeySequence::New);
        ekleAct_lst->setStatusTip ("Lastik Kaydı Ekle");
     //   connect (ekleAct_lst, &QAction::triggered, this,
       //          &hC_MKN::onmnMKN_yeniEklE_lstSLOT );
        menu->addAction(ekleAct_lst);

        // yakıt
        const QIcon ekleIc_mknYkt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mknYkt = new QAction(ekleIc_mknYkt, tr("&Yakıt Ekle..."), this);
        ekleAct_mknYkt->setShortcuts (QKeySequence::New);
        ekleAct_mknYkt->setStatusTip ("Yakıt Kaydı Ekle");
  //      connect (ekleAct_mknYkt, &QAction::triggered, this,
    //             &hC_MKN::onmnMKN_yeniEklE_mknYktSLOT );
        menu->addAction(ekleAct_mknYkt);

        // antifiriz
        const QIcon ekleIc_afz = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_afz = new QAction(ekleIc_afz, tr("&Antifiriz Ekle..."), this);
        ekleAct_afz->setShortcuts (QKeySequence::New);
        ekleAct_afz->setStatusTip ("Antifiriz Kaydı Ekle");
   //     connect (ekleAct_afz, &QAction::triggered, this,
     //            &hC_MKN::onmnMKN_yeniEklE_afzSLOT );
        menu->addAction(ekleAct_afz);

        // zincir
        const QIcon ekleIc_zcr = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_zcr = new QAction(ekleIc_zcr, tr("&Zincir Ekle..."), this);
        ekleAct_zcr->setShortcuts (QKeySequence::New);
        ekleAct_zcr->setStatusTip ("Zincir Kaydı Ekle");
 //       connect (ekleAct_zcr, &QAction::triggered, this,
   //              &hC_MKN::onmnMKN_yeniEklE_zcrSLOT );
        menu->addAction(ekleAct_zcr);

        // hgs
        const QIcon ekleIc_hgs = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_hgs = new QAction(ekleIc_hgs, tr("&HGS Ekle..."), this);
        ekleAct_hgs->setShortcuts (QKeySequence::New);
        ekleAct_hgs->setStatusTip ("HGS Kaydı Ekle");
  //      connect (ekleAct_hgs, &QAction::triggered, this,
    //             &hC_MKN::onmnMKN_yeniEklE_hgsSLOT );
        menu->addAction(ekleAct_hgs);

        menu->addSeparator();
        menu->popup(MKNtview->table->viewport()->mapToGlobal(pos()));
    });


}       ///     mkn_kontrol

// ////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////
// ////////////////////  M K N   //////////////////////////////////////
// ////////////////////////////////////////////////////////////////////





/*
void hC_MKN::onmnMKN_yeniEklE_sgrtSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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


}                                           ///     onmnMKN_yeniEklE_sgrt

void hC_MKN::onmnMKN_yeniEklE_muaSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_mua



void hC_MKN::onmnMKN_yeniEklE_yagSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_yag



void hC_MKN::onmnMKN_yeniEklE_fltSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_flt



void hC_MKN::onmnMKN_yeniEklE_akuSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_aku



void hC_MKN::onmnMKN_yeniEklE_lstSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_lst



void hC_MKN::onmnMKN_yeniEklE_mknYktSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_mknYkt


void hC_MKN::onmnMKN_yeniEklE_afzSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_afz



void hC_MKN::onmnMKN_yeniEklE_zcrSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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

}       ///      onmnMKN_yeniEklE_zcr



void hC_MKN::onmnMKN_yeniEklE_hgsSLOT()
{
    int id=-1;
    QModelIndex index = MKNtview->table->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = MKNmodel->record(index.row());
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
    MKNmodel->select();

}       ///      ww_mkcins

*/

hC_MKN::~hC_MKN()
= default;       ///      ~hC_MKN


////////////////////////////////////////////
///
///
///
//// mkn_
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
          "where mkn_kurumNo = "+led_mknKurumno->text().trimmed() ;
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


///
/// \brief DBase::VTd_mkn
///
QString hC_MKN::mkn_VTd()
{

    /// MKSTOK create
    ///
    QString ct, mesaj = "  OK - Makina";
    QSqlQuery q;
    QString MKNtableName ( "mkn__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( MKNtableName ))
    {
        //mkn_kurumNo key used every table's relation

        ct =  "CREATE TABLE IF NOT EXISTS  " + MKNtableName +
              "("
              "id_mkn integer primary key, "
              "mkn_kurumno       TEXT, "
              "mkn_plaka         TEXT, "
              "mkn_cinsi         TEXT, "
              "mkn_Marka         TEXT,"
              "mkn_modeli        TEXT,"
              "mkn_Yil           INTEGER, "
              "mkn_Saseno        TEXT, "
              "mkn_Motorno       TEXT, "
              "mkn_Motortip      TEXT, "
              "mkn_yakit         TEXT, "
              "mkn_surucu        integer, "
              "mkn_surucutar     DATE, "
              "mkn_Birim         TEXT, "
              "mkn_aciklama      TEXT, "
              "mkn_Byer          TEXT, "
              "mkn_resim         BLOB, "
              "mkn_rating        INTEGER)" ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Makina Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Malzeme Detay Dosyası YENİ Oluşturuldu";

            if ( q.exec("INSERT INTO " + MKNtableName + " ( mkn_kurumNo,mkn_cinsi,"
                        "mkn_marka, mkn_modeli, mkn_surucu )"
                        " values( '100001', 1 , 1 , 1 , 1 )"  ))
            {
                mesaj = mesaj + "<br>İLK kayıt eklendi";
            }
            else
            {
                mesaj = mesaj +"<br>İLK Kayıt EKLENEMEDİ "
                               "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;



}       /// VTdMKSTOK



void hC_MKN::mkn_model ()
{
    qDebug() << " modelmkn";
    QString indexField = "mkn_kurumno";
    QString MKNtableName ("mkn__dbtb");


    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Makina Kod");
    tB_FieldList->append("Kurum No");
    tB_FieldList->append("Plaka");
    tB_FieldList->append("Cinsi");
    tB_FieldList->append("Markası");
    tB_FieldList->append("Modeli");
    tB_FieldList->append("Model Yılı");
    tB_FieldList->append("Şase No");
    tB_FieldList->append("Motor No");
    tB_FieldList->append("Motor Tipi");
    tB_FieldList->append("Yakıt Türü");
    tB_FieldList->append("Sürücü Adı");
    tB_FieldList->append("İşe Başlama Tarihi");
    tB_FieldList->append("Birimi");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Bulunduğu Yer");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Rating");
    // tB_FieldList->append("resim");

    MKNmodel = new QSqlRelationalTableModel;
    hC_Rm hC_Rm (&MKNtableName,
                 MKNmodel,
                 &indexField ,
                 tB_FieldList) ;

}///MKN

