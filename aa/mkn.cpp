#include "mkn.h"

hC_MKN::hC_MKN(QWidget *parent) : QWidget(parent)
{

    qDebug ()<<"cnstrctr MAKİNA";
    //************************************************************
    //*****************  M A K İ N A  ****************************
}

void hC_MKN::setup()
{
    qDebug ()<<"setup MKN";

    hC_MKN::wdgt  () ;

    hC_MKN::ui    () ;

    hC_MKN::kntrl () ;

}


void hC_MKN::ui()
{
    qDebug ()  <<"mkn ui";

    win_Label = new QLabel("ARAÇ BİLGİLERİ");
    this->setWindowTitle (win_Label->text ());

    tb_view    = new hC_Tv (tb_model, tb_mapper, win_Wdgt);

    auto *l = new QGridLayout;
    l->addWidget ( tb_view   , 0, 0, 1, 1 );
    l->addWidget ( win_Wdgt  , 0, 1, 1, 1 );
    //l->addWidget(wdgt_mppr  , 3, 6, 3, 5 );

    this->setLayout (l);
    qDebug ()  <<"mkn ui sonu 1";

}

void hC_MKN::wdgt()
{

    qDebug ()  <<"  wdgt";

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

        c->setup ();



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
        cmm->setup ();


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


    win_Rsm = new QLabel;
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto mknGrid = new QGridLayout();
    win_Wdgt->setLayout(mknGrid);

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
/*
void hC_MKN::view()
{
    qDebug()<<"  mkn view";
    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel ();

    // sağ tuş menusu
    tb_view->table->setContextMenuPolicy(Qt::CustomContextMenu);

    // tableview de comboboxları göster
    //tb_view->setItemDelegate(new MakinaDelegate(tb_view));
    tb_view->table->setItemDelegate(new QSqlRelationalDelegate(this));

    tb_view->table->setColumnHidden(tb_model->fieldIndex("id_mkn"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex("resim"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex("rating"), true);

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    tb_view->table->setCurrentIndex(
                tb_model->index(0, 1)
                );
    // with blue rect
    tb_view->table->setFocus();
    //   QTimer::singleShot(0, tb_view->table, SLOT(setFocus()));
}

void hC_MKN::map()
{
    qDebug()<<"set mapmkn";
    hC_MKN::tb_mapper = new QDataWidgetMapper(this);
    hC_MKN::tb_mapper->setModel(tb_model);

    // mapperdaki comboboxları çalıştır
    hC_MKN::tb_mapper->setItemDelegate(new QSqlRelationalDelegate(this));

    tb_mapper->addMapping(led_mknKurumno, tb_model->fieldIndex("kurumNo"));
    tb_mapper->addMapping(led_mknPlaka, tb_model->fieldIndex("plaka"));

    tb_mapper->addMapping(lE_cins->lineEdit , tb_model->fieldIndex("cinsi"));
    tb_mapper->addMapping(lE_mark->lineEdit , tb_model->fieldIndex("marka"));
    tb_mapper->addMapping(lE_modl->lineEdit , tb_model->fieldIndex("modeli"));

    tb_mapper->addMapping(spn_mknYil, tb_model->fieldIndex("yil"));
    tb_mapper->addMapping(led_mknSase, tb_model->fieldIndex("saseno"));
    tb_mapper->addMapping(led_mknMotor, tb_model->fieldIndex("motorno"));
    tb_mapper->addMapping(led_mknMtip, tb_model->fieldIndex("motortip"));
    tb_mapper->addMapping(cbx_mknYkt, tb_model->fieldIndex("yakit"));
    tb_mapper->addMapping(cbx_mknSurucu, tb_model->fieldIndex("surucu"));
    tb_mapper->addMapping(clndr_mknSurucutar, tb_model->fieldIndex("surucu_tar"));
    tb_mapper->addMapping(cbx_mknBirim, tb_model->fieldIndex("birim"));
    tb_mapper->addMapping(cbx_mknByer, tb_model->fieldIndex("byer"));
    tb_mapper->addMapping(ted_mknAcklm, tb_model->fieldIndex("aciklama"));
    //tb_mapper->addMapping(lB_resim , tb_model->fieldIndex("resim"));
    //tb_mapper->addMapping(led_rating, tb_model->fieldIndex("rating"));




    hC_MKN::tb_mapper->toFirst ();

}

*/
/////////////////////////////////     ekrandaki her şeyi kontrol edelim
void hC_MKN::kntrl()
{
    qDebug ()  <<"cw mkn kontrol ";
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
            rec.setValue ("kurumno"  , lE_krmno->text ());
            rec.setValue ("yil"      , QDate::currentDate ().year ());
            rec.setValue ("cinsi"     , " " );
            rec.setValue ("marka"    , " " );
            rec.setValue ("modeli"   , " " );
// QString date(QDate::currentDate().toString ( "dd-MM-yyyy" ));

// rec.setValue ("ftr_tarih"   , date );

            // insert a new record (-1)
            if ( ! tb_model->insertRecord(tb_model->rowCount (),rec))
            {
                qDebug() << " HATA - MAKİNA kaydı eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt MAKİNA ya eklendi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            dia_kurumno->close ();
        });
        dia_kurumno->exec ();
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "resim","değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
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

/*
    // pB 006 ilk
    connect(tb_view->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        tb_view->hC_TvPb ("ilk", tb_model, tb_mapper);
    });

    // pB 007 önceki
    connect(tb_view->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("ncki", tb_model, tb_mapper);
    });

    // pB 008 sonraki
    connect(tb_view->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("snrki", tb_model, tb_mapper);
    });

    // pB 009 son
    connect(tb_view->pB_son, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });

    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);
    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
       // emit Cw_fr::sgnfirma(tb_view->table->model()->index( Index.row() ,
         //           tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
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
        QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, tr("&Sigorta Ekle..."), this);
        ekleAct_sgrt->setShortcuts (QKeySequence::New);
        ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
      //  connect (ekleAct_sgrt, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_sgrtSLOT );
        menu->addAction(ekleAct_sgrt);

        // muayene kaydı ekle
        const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mua = new QAction(ekleIc_mua, tr("&Muayene Ekle..."), this);
        ekleAct_mua->setShortcuts (QKeySequence::New);
        ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
       // connect (ekleAct_mua, &QAction::triggered, this,
         //        &hC_MKN::onmnyeniEklE_muaSLOT );
        menu->addAction(ekleAct_mua);


        // yağ
        const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_yag = new QAction(ekleIc_yag, tr("&Yağ Ekle..."), this);
        ekleAct_yag->setShortcuts (QKeySequence::New);
        ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
     //   connect (ekleAct_yag, &QAction::triggered, this,
   //              &hC_MKN::onmnyeniEklE_yagSLOT );
        menu->addAction(ekleAct_yag);


        // filtre
        const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_flt = new QAction(ekleIc_flt, tr("&Filtre Ekle..."), this);
        ekleAct_flt->setShortcuts (QKeySequence::New);
        ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
       // connect (ekleAct_flt, &QAction::triggered, this,
         //        &hC_MKN::onmnyeniEklE_fltSLOT );
        menu->addAction(ekleAct_flt);

        // akü
        const QIcon ekleIc_aku = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_aku = new QAction(ekleIc_aku, tr("&Akü Ekle..."), this);
        ekleAct_aku->setShortcuts (QKeySequence::New);
        ekleAct_aku->setStatusTip ("Akü Kaydı Ekle");
  //      connect (ekleAct_aku, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_akuSLOT );
        menu->addAction(ekleAct_aku);

        // lastik
        const QIcon ekleIc_lst = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_lst = new QAction(ekleIc_lst, tr("&Lastik Ekle..."), this);
        ekleAct_lst->setShortcuts (QKeySequence::New);
        ekleAct_lst->setStatusTip ("Lastik Kaydı Ekle");
     //   connect (ekleAct_lst, &QAction::triggered, this,
       //          &hC_MKN::onmnyeniEklE_lstSLOT );
        menu->addAction(ekleAct_lst);

        // yakıt
        const QIcon ekleIc_mknYkt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mknYkt = new QAction(ekleIc_mknYkt, tr("&Yakıt Ekle..."), this);
        ekleAct_mknYkt->setShortcuts (QKeySequence::New);
        ekleAct_mknYkt->setStatusTip ("Yakıt Kaydı Ekle");
  //      connect (ekleAct_mknYkt, &QAction::triggered, this,
    //             &hC_MKN::onmnyeniEklE_mknYktSLOT );
        menu->addAction(ekleAct_mknYkt);

        // antifiriz
        const QIcon ekleIc_afz = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_afz = new QAction(ekleIc_afz, tr("&Antifiriz Ekle..."), this);
        ekleAct_afz->setShortcuts (QKeySequence::New);
        ekleAct_afz->setStatusTip ("Antifiriz Kaydı Ekle");
   //     connect (ekleAct_afz, &QAction::triggered, this,
     //            &hC_MKN::onmnyeniEklE_afzSLOT );
        menu->addAction(ekleAct_afz);

        // zincir
        const QIcon ekleIc_zcr = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_zcr = new QAction(ekleIc_zcr, tr("&Zincir Ekle..."), this);
        ekleAct_zcr->setShortcuts (QKeySequence::New);
        ekleAct_zcr->setStatusTip ("Zincir Kaydı Ekle");
 //       connect (ekleAct_zcr, &QAction::triggered, this,
   //              &hC_MKN::onmnyeniEklE_zcrSLOT );
        menu->addAction(ekleAct_zcr);

        // hgs
        const QIcon ekleIc_hgs = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_hgs = new QAction(ekleIc_hgs, tr("&HGS Ekle..."), this);
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
= default;       ///      ~hC_MKN


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

/*
///
/// \brief DBase::VTd_mkn
///
QString hC_MKN::VTd()
{

    /// MKSTOK create
    ///
    QString ct, mesaj = "  OK - Makina";
    QSqlQuery q;
    QString MKNtableName ( "_dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( MKNtableName ))
    {
        //kurumNo key used every table's relation

        ct =  "CREATE TABLE IF NOT EXISTS  " + MKNtableName +
              "("
              "id_mkn integer primary key, "
              "kurumno       TEXT, "
              "plaka         TEXT, "
              "cinsi         TEXT, "
              "Marka         TEXT,"
              "modeli        TEXT,"
              "Yil           INTEGER, "
              "Saseno        TEXT, "
              "Motorno       TEXT, "
              "Motortip      TEXT, "
              "yakit         TEXT, "
              "surucu        integer, "
              "surucutar     DATE, "
              "Birim         TEXT, "
              "aciklama      TEXT, "
              "Byer          TEXT, "
              "resim         BLOB, "
              "rating        INTEGER)" ;


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

            if ( q.exec("INSERT INTO " + MKNtableName + " ( kurumNo,cinsi,"
                        "marka, modeli, surucu )"
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



void hC_MKN::model ()
{
    qDebug() << " modelmkn";
    QString indexField = "kurumno";
    QString MKNtableName ("_dbtb");


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

    tb_model = new QSqlRelationalTableModel;
    hC_Rm hC_Rm (&MKNtableName,
                 tb_model,
                 &indexField ,
                 tB_FieldList) ;

}///MKN
*/
