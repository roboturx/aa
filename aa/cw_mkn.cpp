#include "cw_mkn.h"
#include "cw_isemri.h"
#include "cw_per.h"
#include "mkevrk.h"
#include "dlgt_mkstok.h"
#include "ww_mkcins.h"
#include "globals.h"
#include "tamamla.h"
#include "ftr_frmekle.h"

Cw_mkn::Cw_mkn(QWidget *parent) : QWidget(parent)
{

    qDebug ()<<"MAKİNA";
    //************************************************************
    //*****************  F İ R m A  ****************************
}

void Cw_mkn::set_mkn()
{
    qDebug ()<<"setup MKN";

    // ekran görüntüsünü hazırlayalım
    Cw_mkn::set_uiMKN();

    dbase = new DBase ;

    Cw_mkn::set_modelMKN ();
    Cw_mkn::set_viewMKN ();
    Cw_mkn::set_mapMKN ();
    Cw_mkn::set_kntrlMKN();

}       ///     Cw_mkn



////////////////////////// ekranda bişeyler gösterelim
void Cw_mkn::set_uiMKN()   // centralwidget görüntüsü
{
    qDebug ()  <<"mkn ui";
    this->setWindowTitle ("MAKİNA");
    this->showMaximized();
    qDebug ()  <<"mkn ui sonu 1";

    lB_rsm = new QLabel;
    Resim resim(lB_rsm);
    MKNtview    = new HC_TableView;
    wd_mppr ()    ;
    auto *mkn_l = new QGridLayout;
    mkn_l->addWidget(MKNtview   , 4, 0, 6, 4 );
    mkn_l->addWidget(wdgt_mppr , 0, 5,10, 6 );
    mkn_l->addWidget(lB_rsm  , 0, 0, 4, 4 );
    this->setLayout (mkn_l);

}       ///     mkn_ui



void Cw_mkn::wd_mppr ()
{
    qDebug ()  <<"wd mp  ";
    QLabel *lB_kurumno = new QLabel("Kurum No");
    led_mknKurumno = new QLineEdit();
    connect( led_mknKurumno, &QLineEdit::textChanged,
             this,  &Cw_mkn::mknKurumno_ara);
    lB_kurumno->setBuddy(led_mknKurumno);
    led_mknKurumno->setFocus();

    QLabel *lB_plaka = new QLabel("Plaka ");
    led_mknPlaka = new QLineEdit();
    lB_plaka->setBuddy(led_mknPlaka);


    // /////////////////////////////////////////////////////

    auto *lB_cmmy = new QLabel("Cins-Marka-Model");
    tE_cmmy = new hC_textEdit ;
    tE_cmmy->hC_txEdt->setReadOnly(true);

    // cins-marka-model-yıl makinaya ekle
    connect(tE_cmmy->hC_txEdtpB , &QPushButton::clicked,
            [this ]()
    {
        // seçebilmek için pencere
        auto *cmmy = new WW_Mkcins ;


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // cmmy tableviewinde gezinirken
        // cins - marka - moel - yıl
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------

        connect (cmmy , &WW_Mkcins::sgnCmmy ,
                 [ this ] ( QString sgnText )
        {
            tE_cmmy->hC_txEdt->setText ( sgnText );
            tE_cmmy->hC_txEdt->setFocus();
        });
        cmmy->show ();
    });



/*
    cbx_mknCins = new QComboBox;
    pb_mknCins = new QPushButton;

    connect(pb_mknCins, &QPushButton::clicked ,
            this,&Cw_mkn::ww_mkcins );

    QLabel *lB_mknMark = new QLabel("Markası");
    cbx_mknMark = new QComboBox;
    pb_mknMark = new QPushButton;

    QLabel *lB_mknModl = new QLabel("Modeli ");
    cbx_mknModl = new QComboBox;
    pb_mknModl = new QPushButton;
*/
    QLabel *lB_mknYil = new QLabel("Yıl ");
    spn_mknYil = new QSpinBox();
    spn_mknYil->setMinimum (1900);
    spn_mknYil->setMaximum (2023);
    spn_mknYil->setValue ( QDate::currentDate ().year ());
    qDebug ()  <<"wd mp yıl  "<<spn_mknYil->value ();
    lB_mknYil->setBuddy(spn_mknYil);


    // /////////////////////////////////////////////////////



    QLabel *lB_mknSase = new QLabel("Şase No   ");
    led_mknSase = new QLineEdit();
    lB_mknSase->setBuddy(led_mknSase);

    QLabel *lB_mknMotor = new QLabel("Motor No ");
    led_mknMotor = new QLineEdit();
    lB_mknMotor->setBuddy(led_mknMotor);


    QLabel *lB_mknMtip = new QLabel("Motor Tipi");
    led_mknMtip = new QLineEdit();
    lB_mknMtip->setBuddy(led_mknMtip);

    QLabel *lB_mknYkt = new QLabel("Yakıt Türü");
    cbx_mknYkt  = new QComboBox;
    cbx_mknYkt->insertItem(1,"Benzin");
    cbx_mknYkt->insertItem(2,"Dizel");
    cbx_mknYkt->insertItem(3,"LPG");
    cbx_mknYkt->insertItem(4,"Benzin-LPG");
    cbx_mknYkt->insertItem(5,"Doğalgaz");
    pb_mknYkt = new QPushButton;
    connect( pb_mknYkt, &QPushButton::clicked, this, &Cw_mkn::ykt);

    QLabel *lB_mknSurucu = new QLabel("Sürücü  ");
    cbx_mknSurucu = new QComboBox ;
    pb_mknSurucu = new QPushButton;
    connect( pb_mknSurucu, &QPushButton::clicked, this, &Cw_mkn::src);


    QLabel *lB_mknSurucutar = new QLabel("Sürücü İşe Başlama");

    clndr_mknSurucutar = new QDateTimeEdit(QDate::currentDate());
    clndr_mknSurucutar->setMinimumDate(QDate(1900, 1, 1));
    clndr_mknSurucutar->setMaximumDate(QDate(2023, 1, 1));
    clndr_mknSurucutar->setDisplayFormat("dd.MM.yyyy");
    clndr_mknSurucutar->setCalendarPopup(true);

    QLabel *lB_mknBirim = new QLabel("Birim   ");
    cbx_mknBirim  = new QComboBox;
    pb_mknBirim = new QPushButton;
    connect( pb_mknBirim, &QPushButton::clicked, this, &Cw_mkn::birim);
    lB_mknBirim->setBuddy(cbx_mknBirim);

    QLabel *lB_mknByer = new QLabel("Bulunduğu Yer ");
    pb_mknByer = new QPushButton;
    connect( pb_mknByer, &QPushButton::clicked, this, &Cw_mkn::byer);

    cbx_mknByer  = new QComboBox;
    lB_mknByer->setBuddy(cbx_mknByer);


    QLabel *lB_mknAcklm = new QLabel("Açıklama   ");
    ted_mknAcklm = new QTextEdit();
    lB_mknAcklm->setBuddy(ted_mknAcklm);



    wdgt_mppr = new QWidget;
    auto *mapperL = new QGridLayout;
    wdgt_mppr->setLayout(mapperL);
    int satr=0;


    mapperL->addWidget(lB_kurumno    ,  satr,0,1,1 );
    mapperL->addWidget(led_mknKurumno,  satr,1,1,3 );
    mapperL->addWidget(lB_plaka      ,++satr,0,1,1 );
    mapperL->addWidget(led_mknPlaka  ,  satr,1,1,3 );
    mapperL->addWidget(lB_cmmy       ,++satr,0,1,3 );
    mapperL->addWidget(tE_cmmy       ,  satr,1,1,3 );

    //    mapperL->addWidget(lB_cins       ,++satr,0,1,1 );
//    mapperL->addWidget(cbx_mknCins   ,  satr,1,1,2 );
//    mapperL->addWidget(pb_mknCins    ,  satr,3,3,1 );
//    mapperL->addWidget(lB_mknMark    ,++satr,0,1,1 );
//    mapperL->addWidget(cbx_mknMark   ,  satr,1,1,2 );
//    mapperL->addWidget(lB_mknModl    ,++satr,0,1,1 );
//    mapperL->addWidget(cbx_mknModl   ,  satr,1,1,2 );

    mapperL->addWidget(lB_mknYil     ,++satr,0,1,1 );
    mapperL->addWidget(spn_mknYil    ,  satr,1,1,3 );
    mapperL->addWidget(lB_mknSase    ,++satr,0,1,1 );
    mapperL->addWidget(led_mknSase   ,  satr,1,1,3 );
    mapperL->addWidget(lB_mknMotor   ,++satr,0,1,1 );
    mapperL->addWidget(led_mknMotor  ,  satr,1,1,3 );
    mapperL->addWidget(lB_mknMtip    ,++satr,0,1,1 );
    mapperL->addWidget(led_mknMtip   ,  satr,1,1,3 );
    mapperL->addWidget(lB_mknYkt     ,++satr,0,1,1 );
    mapperL->addWidget(cbx_mknYkt    ,  satr,1,1,2 );
    mapperL->addWidget(pb_mknYkt     ,  satr,3,1,1 );
    mapperL->addWidget(lB_mknSurucu  ,++satr,0,1,1 );
    mapperL->addWidget(cbx_mknSurucu ,  satr,1,1,2 );
    mapperL->addWidget(pb_mknSurucu  ,  satr,3,1,1 );
    mapperL->addWidget(lB_mknSurucutar   ,++satr,0,1,1 );
    mapperL->addWidget(clndr_mknSurucutar,  satr,1,1,3 );
    mapperL->addWidget(lB_mknBirim   ,++satr,0,1,1 );
    mapperL->addWidget(cbx_mknBirim  ,  satr,1,1,2 );
    mapperL->addWidget(pb_mknBirim   ,  satr,3,1,1 );
    mapperL->addWidget(lB_mknByer    ,++satr,0,1,1 );
    mapperL->addWidget(cbx_mknByer   ,  satr,1,1,2 );
    mapperL->addWidget(pb_mknByer    ,  satr,3,1,1 );
    mapperL->addWidget(lB_mknAcklm   ,++satr,0,1,1 );
    mapperL->addWidget(ted_mknAcklm  ,  satr,1,1,3 );
   // mapperL->addWidget(lB_foto      ,++satr,0,4,4 );

}


///////////////////////////////          modelleri oluşturalım
void Cw_mkn::set_modelMKN()
{
    qDebug()<<"set model makina";
    MKNmodel = new QSqlRelationalTableModel;
    MKNmodel = dbase->modelMakina ();



//    // cinsi combo //////////////////////////////////////////////

//    mdll_mkcins ();
//    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_cinsi"),
//            QSqlRelation ("dbtb_mkcins", "id_mkcins", "cinsi"));
//    cbxCinsiModel = new QSqlTableModel ;
//    cbxCinsiModel = MKNmodel->relationModel(
//            MKNmodel->fieldIndex("mkn_cinsi"));
//    cbx_mknCins ->setModel(cbxCinsiModel);
//    cbx_mknCins->setModelColumn(cbxCinsiModel->fieldIndex("cinsi"));


//    mdll_mkmark ();
//    // marka combo //////////////////////////////////////////////
//    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_marka"),
//            QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));
//    cbxMarkaModel = new QSqlTableModel ;
////    cbxMarkaModel  = MKNmodel->relationModel(
////                MKNmodel->fieldIndex("mkn_marka"));
////    cbx_mknMark->setModel(cbxMarkaModel); // cbxMarkaModel);
////    cbx_mknMark->setModelColumn(cbxMarkaModel->fieldIndex("marka"));



//    //    // marka combo //////////////////////////////////////////////
////    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_marka"),
////            QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));
////    cbxMarkaModel = new QSqlTableModel ;
////    cbxMarkaModel = MKNmodel->relationModel(
////                MKNmodel->fieldIndex("mkn_marka"));
////    cbx_mknMark->setModel(cbxMarkaModel); // cbxMarkaModel);
////    cbx_mknMark->setModelColumn(cbxMarkaModel->fieldIndex("marka"));




//    // model combo  /////////////////////////////////////////////
//    mdll_mkmodl ();
//    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_modeli"),
//            QSqlRelation("dbtb_mkmodl", "id_mkmodl", "modeli"));
//    cbxModeliModel = new QSqlTableModel ;
//    cbxModeliModel = MKNmodel->relationModel(
//                MKNmodel->fieldIndex("mkn_modeli"));
//    cbx_mknModl->setModel( cbxModeliModel ); //cbxModeliModel);
//    cbx_mknModl->setModelColumn(cbxModeliModel->fieldIndex("modeli"));

//    // sürücü combo ///////////////////////////////////////////////
//    MKNmodel->setRelation(  MKNmodel->fieldIndex("mkn_surucu"),
//            QSqlRelation("dbtb_clsn", "kod_pr", "soyad"));
//    cbxClsnModel = new QSqlTableModel;
//    cbxClsnModel = MKNmodel->relationModel(
//                MKNmodel->fieldIndex("mkn_surucu"));
//    cbx_mknSurucu->setModel(cbxClsnModel);
//    cbx_mknSurucu->setModelColumn(cbxClsnModel->fieldIndex("soyad"));




}

void Cw_mkn::set_viewMKN()
{
    qDebug()<<"setup view mkn";
    MKNtview->table->setModel(MKNmodel);
    MKNtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    MKNtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    MKNselectionMdl = MKNtview->table->selectionModel ();

    // sağ tuş menusu
    MKNtview->table->setContextMenuPolicy(Qt::CustomContextMenu);

    // tableview de comboboxları göster
    //MKNtview->setItemDelegate(new MakinaDelegate(MKNtview));
    MKNtview->table->setItemDelegate(new QSqlRelationalDelegate(this));

    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("id_mkn"), true);
    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_resim"), true);
    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_rating"), true);

    MKNtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    MKNtview->table->horizontalHeader()->setStretchLastSection(true);
    MKNtview->table->horizontalHeader()->resizeContentsPrecision();
    MKNtview->table->resizeRowsToContents ();
    MKNtview->table->resizeColumnsToContents();








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

void Cw_mkn::set_mapMKN()
{
    qDebug()<<"set mapmkn";
    Cw_mkn::MKNmapper = new QDataWidgetMapper(this);
    Cw_mkn::MKNmapper->setModel(MKNmodel);

    // mapperdaki comboboxları çalıştır
    Cw_mkn::MKNmapper->setItemDelegate(new QSqlRelationalDelegate(this));

    MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));
    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));

    MKNmapper->addMapping(tE_cmmy->hC_txEdt, MKNmodel->fieldIndex("mkn_cinsi"));
//    MKNmapper->addMapping(cbx_mknMark, MKNmodel->fieldIndex("mkn_marka"));
 //   MKNmapper->addMapping(cbx_mknModl, MKNmodel->fieldIndex("mkn_modeli"));

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




    Cw_mkn::MKNmapper->toFirst ();

    qDebug()<<"set mapmkn son";
}


/////////////////////////////////     ekrandaki her şeyi kontrol edelim
void Cw_mkn::set_kntrlMKN()
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
        Resim resim;
        resim.resimUpdate (lB_rsm, MKNtview, MKNmodel, MKNselectionMdl,
                           "mkn_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MKNselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        Resim resim;
        resim.resimUpdate (lB_rsm, MKNtview, MKNmodel, MKNselectionMdl,
                           "mkn_resim");
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


    // pB 006 ilk
    connect(MKNtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        MKNmapper->toFirst ();
        int map_row = MKNmapper->currentIndex ();
        MKNtview->pB_ilk->setEnabled (map_row>0);
        MKNtview->table->setCurrentIndex(MKNmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(MKNtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MKNmapper->toPrevious ();
        int map_row = MKNmapper->currentIndex ();
        MKNtview->pB_ncki->setEnabled(map_row > 0);
        MKNtview->table->setCurrentIndex(MKNmodel->index( map_row  ,0));
    });

    // pB 008 sonraki
    connect(MKNtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MKNmapper->toNext ();
        int map_row = MKNmapper->currentIndex ();
        MKNtview->pB_snrki->setEnabled(map_row < MKNmodel->rowCount() - 1);
        MKNtview->table->setCurrentIndex(MKNmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(MKNtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MKNmapper->toLast ();
        int map_row = MKNmapper->currentIndex ();
        MKNtview->pB_son->setEnabled(map_row < MKNmodel->rowCount() - 1);
        MKNtview->table->setCurrentIndex(MKNmodel->index( MKNmodel->rowCount() - 1  ,0));
    });



    ///// tableview kontrol connectleri
    ///
    ///


    // pB 010 nav tuslari kontrol
    connect(MKNmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //MKNmapper->currentIndex ();
        MKNtview->pB_ilk->setEnabled (row>0);
        MKNtview->pB_ncki->setEnabled(row > 0);
        MKNtview->pB_snrki->setEnabled(row < MKNmodel->rowCount() - 1);
        MKNtview->pB_son->setEnabled(row < MKNmodel->rowCount() - 1);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  MKNselectionMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  MKNselectionMdl ,
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
        connect (ekleAct_sgrt, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_sgrtSLOT );
        menu->addAction(ekleAct_sgrt);

        // muayene kaydı ekle
        const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mua = new QAction(ekleIc_mua, tr("&Muayene Ekle..."), this);
        ekleAct_mua->setShortcuts (QKeySequence::New);
        ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
        connect (ekleAct_mua, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_muaSLOT );
        menu->addAction(ekleAct_mua);


        // yağ
        const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_yag = new QAction(ekleIc_yag, tr("&Yağ Ekle..."), this);
        ekleAct_yag->setShortcuts (QKeySequence::New);
        ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
        connect (ekleAct_yag, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_yagSLOT );
        menu->addAction(ekleAct_yag);


        // filtre
        const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_flt = new QAction(ekleIc_flt, tr("&Filtre Ekle..."), this);
        ekleAct_flt->setShortcuts (QKeySequence::New);
        ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
        connect (ekleAct_flt, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_fltSLOT );
        menu->addAction(ekleAct_flt);

        // akü
        const QIcon ekleIc_aku = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_aku = new QAction(ekleIc_aku, tr("&Akü Ekle..."), this);
        ekleAct_aku->setShortcuts (QKeySequence::New);
        ekleAct_aku->setStatusTip ("Akü Kaydı Ekle");
        connect (ekleAct_aku, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_akuSLOT );
        menu->addAction(ekleAct_aku);

        // lastik
        const QIcon ekleIc_lst = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_lst = new QAction(ekleIc_lst, tr("&Lastik Ekle..."), this);
        ekleAct_lst->setShortcuts (QKeySequence::New);
        ekleAct_lst->setStatusTip ("Lastik Kaydı Ekle");
        connect (ekleAct_lst, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_lstSLOT );
        menu->addAction(ekleAct_lst);

        // yakıt
        const QIcon ekleIc_mknYkt = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_mknYkt = new QAction(ekleIc_mknYkt, tr("&Yakıt Ekle..."), this);
        ekleAct_mknYkt->setShortcuts (QKeySequence::New);
        ekleAct_mknYkt->setStatusTip ("Yakıt Kaydı Ekle");
        connect (ekleAct_mknYkt, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_mknYktSLOT );
        menu->addAction(ekleAct_mknYkt);

        // antifiriz
        const QIcon ekleIc_afz = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_afz = new QAction(ekleIc_afz, tr("&Antifiriz Ekle..."), this);
        ekleAct_afz->setShortcuts (QKeySequence::New);
        ekleAct_afz->setStatusTip ("Antifiriz Kaydı Ekle");
        connect (ekleAct_afz, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_afzSLOT );
        menu->addAction(ekleAct_afz);

        // zincir
        const QIcon ekleIc_zcr = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_zcr = new QAction(ekleIc_zcr, tr("&Zincir Ekle..."), this);
        ekleAct_zcr->setShortcuts (QKeySequence::New);
        ekleAct_zcr->setStatusTip ("Zincir Kaydı Ekle");
        connect (ekleAct_zcr, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_zcrSLOT );
        menu->addAction(ekleAct_zcr);

        // hgs
        const QIcon ekleIc_hgs = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_hgs = new QAction(ekleIc_hgs, tr("&HGS Ekle..."), this);
        ekleAct_hgs->setShortcuts (QKeySequence::New);
        ekleAct_hgs->setStatusTip ("HGS Kaydı Ekle");
        connect (ekleAct_hgs, &QAction::triggered, this,
                 &Cw_mkn::onmnMKN_yeniEklE_hgsSLOT );
        menu->addAction(ekleAct_hgs);

        menu->addSeparator();
        menu->popup(MKNtview->table->viewport()->mapToGlobal(pos()));
    });


}       ///     mkn_kontrol

// ////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////
// ////////////////////  M K N   //////////////////////////////////////
// ////////////////////////////////////////////////////////////////////





void Cw_mkn::birim()
{

}

void Cw_mkn::byer()
{

}

void Cw_mkn::src()
{

}

void Cw_mkn::ykt()
{

}



//void Cw_mkn::mdll_mkcins()
//{
//    //  qDebug ()  <<" ' mdl_mkcins ' - mkcins Model Başlatıldı ";
//    // Create the data model for DBTB_MKCINS

//    mdl_mkcins = new QSqlRelationalTableModel(tV_mkcins);
//    mdl_mkcins->setEditStrategy(QSqlTableModel::OnFieldChange);
//    mdl_mkcins->setTable("DBTB_MKCINS");
//    mdl_mkcins->setJoinMode(QSqlRelationalTableModel::LeftJoin);

//    //// mkcins ile mkmark relation
//    //mdl_mkcins->setRelation(mdl_mkcins->fieldIndex("mkcins_no"),
//      //      QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));

//    // Remember the indexes of the columns
//    // combobox fields
//    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

//    // Set the localized header captions
//    mdl_mkcins->setHeaderData(mdl_mkcins->fieldIndex("cinsi"),
//                              Qt::Horizontal, tr("CİNSİ"));

//    // Populate the model
//    if (!mdl_mkcins->select())
//    {
//        qDebug () << " HATA - " << mdl_mkcins->lastError();
//        return;
//    }

//    // Set the model and hide the ID column
//    tV_mkcins->setModel(mdl_mkcins);
//    tV_mkcins->setColumnHidden(mdl_mkcins->fieldIndex("id_mkcins"), true);
//    tV_mkcins->setSelectionMode(QAbstractItemView::SingleSelection);

//}       ///     mdl_mkcins

//void Cw_mkn::mdll_mkmark()
//{
//    // Create the data model for DBTB_MKCINS
//    //  qDebug ()  <<" ' mdl_mkmark ' - mkmark Model Başlatıldı ";
//    mdl_mkmark = new QSqlRelationalTableModel(tV_mkmark);
//    mdl_mkmark->setEditStrategy(QSqlTableModel::OnFieldChange);
//    mdl_mkmark->setTable("dbtb_mkmark");
//    mdl_mkmark->setJoinMode(QSqlRelationalTableModel::LeftJoin);

//    //// mkmark ile mkmodel relation
//    mdl_mkmark->setRelation(mdl_mkmark->fieldIndex("mkmark_no"),
//                            QSqlRelation("dbtb_mkmodl", "id_mkmodl", "modeli"));


//    // Remember the indexes of the columns
//    // combobox fields
//    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

//    // Set the localized header captions
//    mdl_mkmark->setHeaderData(mdl_mkmark->fieldIndex("marka"),
//                              Qt::Horizontal, tr("MARKA"));

//    // Populate the model
//    if (!mdl_mkmark->select())
//    {
//        qDebug () << " HATA - " << mdl_mkmark->lastError();
//        return;
//    }

//    // Set the model and hide the ID column
//    tV_mkmark->setModel(mdl_mkmark);
//    tV_mkmark->setColumnHidden(mdl_mkmark->fieldIndex("id_mkmark"), true);
//    tV_mkmark->setSelectionMode(QAbstractItemView::SingleSelection);

//}       ///     mdl_mkmark

//void Cw_mkn::mdll_mkmodl()
//{
//    //    qDebug ()  <<" ' mdl_mkmodl ' - mkmodl Model Başlatıldı ";
//    // Create the data model for DBTB_MKmodl

//    mdl_mkmodl = new QSqlRelationalTableModel(tV_mkmodl);
//    mdl_mkmodl->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
//    mdl_mkmodl->setTable("dbtb_mkmodl");

//    // Set the localized header captions
//    mdl_mkmodl->setHeaderData(mdl_mkmodl->fieldIndex("modeli"),
//                              Qt::Horizontal, tr("MODELİ"));

//    // Populate the model
//    if (!mdl_mkmodl->select())
//    {
//        qDebug () << " HATA - " << mdl_mkmodl->lastError();
//        return;
//    }

//    // Set the model and hide the ID column
//    tV_mkmodl->setModel(mdl_mkmodl);
//    tV_mkmodl->setColumnHidden(mdl_mkmodl->fieldIndex("id_mkmodl"), true);
//    tV_mkmodl->setSelectionMode(QAbstractItemView::SingleSelection);


//    /// mkn değiştiğinde cins e bağlı marka ve modelde değişsin    ??????
//    connect(MKNselectionMdl,
//            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
//            this,  SLOT( onMKNtview_cmm_filterSLOT(QModelIndex) ));


//}       ///     mdl_mkmodl


//void Cw_mkn::onMKNtview_cmm_filterSLOT(QModelIndex Index)
//{
//    // Cins ne
//    QSqlRecord rec = MKNmodel->record(Index.row() );
//    int cinsid = rec.value("mkn_cinsi").toInt();
//    qDebug () << "cmm rec    " << endl <<
//                 "-----------" << endl <<
//                 rec <<endl <<
//                 "-----------" << endl ;
//    qDebug () << "cmm cinsid " << endl <<
//                 "-----------" << endl <<
//                 cinsid << endl <<
//                 "-----------" << endl ;
//    qDebug ()<<"filter = "<<    mdl_mkmark ;

//    mdl_mkmark->setFilter(QString("mkcins_no = %1").arg(cinsid));
//    mdl_mkmark->select();
//    cbxMarkaModel  = MKNmodel->relationModel(
//                MKNmodel->fieldIndex("mkn_marka"));
//    cbx_mknMark->setModel(cbxMarkaModel); // cbxMarkaModel);
//    cbx_mknMark->setModelColumn(cbxMarkaModel->fieldIndex("marka"));

//}       ///     filter cmm






//void Cw_mkn::tV_cns_view()   // mkn cins tableview
//{

//}       ///     tV_cns_view

//void Cw_mkn::tV_mrk_view()   // mkn marka tableview
//{

//}       ///     tV_mrk_view

//void Cw_mkn::tV_mdl_view()   // mkn model tableview
//{

//}       ///     tV_mdl_view



void Cw_mkn::onmnMKN_yeniEklE_sgrtSLOT()
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

void Cw_mkn::onmnMKN_yeniEklE_muaSLOT()
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



void Cw_mkn::onmnMKN_yeniEklE_yagSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_yag



void Cw_mkn::onmnMKN_yeniEklE_fltSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_flt



void Cw_mkn::onmnMKN_yeniEklE_akuSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_aku



void Cw_mkn::onmnMKN_yeniEklE_lstSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_lst



void Cw_mkn::onmnMKN_yeniEklE_mknYktSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_mknYkt


void Cw_mkn::onmnMKN_yeniEklE_afzSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_afz



void Cw_mkn::onmnMKN_yeniEklE_zcrSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}       ///      onmnMKN_yeniEklE_zcr



void Cw_mkn::onmnMKN_yeniEklE_hgsSLOT()
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
    /*
    evrk_mua->mdl_evrk_mua->select();
    wtab->setCurrentIndex(wtab->indexOf(wdgt_evrk));
    tbx_evrk->setCurrentIndex(tbx_evrk->indexOf(evrk_mua));
    evrk_mua->tV_evrk_mua->setFocus();
*/
}






////////////////////////////////////////////////////////////  others
void Cw_mkn::ww_mkcins()
{
    auto *w = new WW_Mkcins;
    //w->setModal(true);
    w->show();
    MKNmodel->select();

}       ///      ww_mkcins



Cw_mkn::~Cw_mkn()
= default;       ///      ~Cw_mkn


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




void Cw_mkn::mknKurumno_ara()
{



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
    {*/
    qDebug()<<led_mknKurumno->text()<<"\n"; //<<q.lastError().text();
    //}

}

