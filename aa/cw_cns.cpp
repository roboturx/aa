#include "cw_cns.h"

Cw_Cns::Cw_Cns()
{

}


#include "cw_mkn.h"
#include "cw_isemri.h"
#include "cw_per.h"
#include "mkevrk.h"
#include "dlgt_mkstok.h"
#include "ww_mkcins.h"
#include "globals.h"
#include "tamamla.h"


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


   // Cw_mkn::mdll_mkcins();
   // Cw_mkn::mdll_mkmark();
   // Cw_mkn::mdll_mkmodl();


    // modellerimizi view lere yerleştirelim


 //   Cw_mkn::tV_cns_view();   // mkn cins tableview
 //   Cw_mkn::tV_mrk_view();   // mkn marka tableview
 //   Cw_mkn::tV_mdl_view();   // mkn model tableview

    // ekranı kontrol edelim


    //qDebug ()  <<"mkn kontr 4";

}       ///     Cw_mkn



////////////////////////// ekranda bişeyler gösterelim
void Cw_mkn::set_uiMKN()   // centralwidget görüntüsü
{
    this->setWindowTitle ("MAKİNA");
    this->showMaximized();

    Cw_mkn::mkn_ui_tvs();    // tv leri tanımlayalım
    Cw_mkn::mkn_ui_pbs();    // pb leri tanımlayalım

    Cw_mkn::mkn_ui_rsm();            // resim
    Cw_mkn::mkn_ui_tabw();           // tab widget
}       ///     mkn_ui

void Cw_mkn::mkn_ui_tvs()
{
    // table views
    MKNtview    = new HC_TableView;
  //  tV_mkcins = new QTableView();
  //  tV_mkmark = new QTableView();
  //  tV_mkmodl = new QTableView();
}

void Cw_mkn::mkn_ui_pbs()
{
    /// ekranı düzenle
    // SOL üst
    // ekranı genişlet daralt

    pb_rsm = new QPushButton("...");
    pb_rsm->setFixedSize(42,30);

    auto *pbL =new QHBoxLayout;
    pbL->addStretch(2);
    pbL->addWidget(pb_rsm);

    wdgt_tv = new QWidget();
    auto *tV_l = new QGridLayout(wdgt_tv);

    tV_l->addLayout(pbL   , 0,0,1,0,nullptr);
    tV_l->addWidget(MKNtview, 1,0,1,2,nullptr);   //////// makina view
}

void Cw_mkn::mkn_ui_rsm()
{

    //////////////////////////////////////////////////////
    // SOL alt - üst
    lB_foto = new QLabel("Makina Resim");
    lB_foto->setFixedSize(352,198);
    // SOL alt - alt


    wdgt_rsm = new QWidget;
    auto *rsm_l = new QGridLayout(wdgt_rsm);
    rsm_l->setColumnStretch(1,100);
    wdgt_rsm->setFixedSize(385,240);

    rsm_l->addWidget(lB_foto   , 0,0,1,1,nullptr);     // foto

}

void Cw_mkn::mkn_ui_tabw()
{

    // SOL - üst - orta - alt
    // SOL çerçeve içine alalım
    wdgt_sol = new QWidget;
    auto *mkn_l = new QGridLayout(wdgt_sol);
    mkn_l->addWidget(wdgt_rsm  ,0,0,1,1,nullptr);     // foto     sol üst
    mkn_l->addWidget(wdgt_tv   ,1,0,1,1,nullptr);     // tv       sol alt
    // mkn_l->addWidget(wdgt_mppr ,0,1,1,1,nullptr);     //    sağ üst


    // //// SAĞ da tab widget içerisinde ayrı widgetler yapalım
    wtab = new QTabWidget();
    //    wtab->setStyleSheet(SS01);
    wtab->setMovable(true);
    wtab->setTabBarAutoHide(true);

    /// SOL we SAĞ ı splitter ile ayıralım ve
    /// büyüklüklrerini ister fare ile
    /// ister << ve >> cuttonları ile ayarlayalım
    qs = new QSplitter(this);
    qs->addWidget(wdgt_sol );
    qs->addWidget(wtab);
    // qs->setSizes({2,6});
    // qs->setStretchFactor(0,0);
    qs->setStretchFactor(1,10);

    auto *mkn_layg = new QGridLayout(this);
    mkn_layg->addWidget(qs  ,0,0,1,1,nullptr);



    /// wtab içerisini düzenleyelim

    //İş Emri

    // wdgt_IE = new QWidget;
    // QHBoxLayout *layout_IE = new QHBoxLayout(wdgt_IE);



    //      wdgt_mppr = new QWidget;
    //  layout_IE->addWidget(wdgt_mppr );

    // wtab->addTab( wdgt_IE ,"İş Emri");


    // //////////////////////////////////////////////////////////////
    // IEDET
    wdgt_IEdet = new QWidget;
    auto *layout_IEdet = new QGridLayout(wdgt_IEdet);

    Cwv_IsEmri = new Cw_IsEmri;

    //  QGridLayout *gLdet = new QGridLayout;
    layout_IEdet->addWidget(Cwv_IsEmri->IEtview      , 0, 0, 1, 3);
    layout_IEdet->addWidget(Cwv_IsEmri->IEDETtview   , 0, 3, 1, 1);
    layout_IEdet->addWidget(Cwv_IsEmri->TStview     , 2, 0, 5, 4);
    layout_IEdet->addWidget(Cwv_IsEmri->SCtview , 7, 0, 1, 4);

    wtab->addTab( wdgt_IEdet ,"İş Emri");

    // //////////////////////////////////////////////////////////////
    // EVRAK

    wdgt_evrk = new QWidget;
    auto *evrk_layg = new QGridLayout(wdgt_evrk);

    evrk_sgrt = new Evr_Sgrt;
    evrk_mua = new Evr_Mua;

    tbx_evrk = new QToolBox( wdgt_evrk ) ; //= new QToolBox;
    tbx_evrk->insertItem(0, evrk_sgrt ,"Trafik Sigortası - Kasko");
    tbx_evrk->insertItem(1, evrk_mua  ,"Muayene");
    tbx_evrk->insertItem(2, new QLabel(),"HGS-KGS");
    tbx_evrk->insertItem(3, new QLabel(),"Raporlar");

    evrk_layg->addWidget( tbx_evrk ,0,0,nullptr);
    //  tbx_evrk->setStyleSheet(SS02);
    wtab->addTab(wdgt_evrk,"Evrak");


    // //////////////////////////////////////////////////////////////
    //BAKIM

    void ss();
    wdgt_bkm = new QWidget;
    auto *bkm_layg = new QGridLayout(wdgt_bkm);

    tbx_bkm = new QToolBox( wdgt_bkm ) ; //= new QToolBox;
    tbx_bkm->addItem(new QLabel(),"Yakıt");
    tbx_bkm->insertItem(1, new QLabel(),"Akü");
    tbx_bkm->insertItem(2, new QLabel(),"Lastik");
    tbx_bkm->insertItem(3, new QLabel(),"Motor Yağı");
    tbx_bkm->insertItem(4, new QLabel(),"Fren Hidrolik");
    tbx_bkm->insertItem(5, new QLabel(),"Şanzuman Yağı");
    tbx_bkm->insertItem(6, new QLabel(),"Filtreler");
    tbx_bkm->insertItem(7, new QLabel(),"Ek Ekipmanlar");
    tbx_bkm->insertItem(8, new QLabel(),"Raporlar");

    bkm_layg->addWidget( tbx_bkm ,0,0,nullptr);
    //  tbx_bkm->setStyleSheet(SS02);
    wtab->addTab(wdgt_bkm,"Bakım");

    // //////////////////////////////////////////////////////////////
    /*   //ARIZA


    QWidget *wdgt_arz = new QWidget;
    QGridLayout *arz_layg = new QGridLayout(wdgt_arz);

    tbx_arz = new QToolBox( wdgt_arz ) ; //= new QToolBox;
    tbx_arz->addItem(new QLabel(),"Araç Kabul");
    tbx_arz->insertItem(1, new QLabel(),"Arıza Tespit");
    tbx_arz->insertItem(2, new QLabel(),"Atölye-Usta Atama");
    tbx_arz->insertItem(3, new QLabel(),"Malzeme Talep");

    arz_layg->addWidget( tbx_arz ,0,0,nullptr);
    // tbx_arz->setStyleSheet(SS02);
    wtab->addTab(wdgt_arz,"Arıza");
*/
    wtab->setFocusPolicy(Qt::StrongFocus);
    qDebug()<<"cw ie  04";
}




///////////////////////////////          cr ui tamam

///////////////////////////////          modelleri oluşturalım
void Cw_mkn::set_modelMKN()
{
    qDebug()<<"set model makina";
    MKNmodel = new QSqlRelationalTableModel;
    MKNmodel = dbase->modelMakina ();
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
    //   QTimer::singleShot(0, FRMtview->table, SLOT(setFocus()));
}

void Cw_mkn::set_mapMKN()
{
    qDebug()<<"set mapmkn";
    Cw_mkn::MKNmapper = new QDataWidgetMapper(this);
    Cw_mkn::MKNmapper->setModel(MKNmodel);

    // mapperdaki comboboxları çalıştır
    Cw_mkn::MKNmapper->setItemDelegate(new QSqlRelationalDelegate(this));

    led_mknKurumno = new QLineEdit();
    MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));

    led_mknPlaka = new QLineEdit();
    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));

  //  qDebug()<<"set mapmkn 1";
    QSqlRelation relCins("dbtb_mkcins", "id_mkcins", "cinsi");
    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_cinsi"),relCins);
    cbx_mknCins = new QComboBox;
    cbxCinsiModel = new QSqlTableModel ;
    cbxCinsiModel = MKNmodel->relationModel(
                MKNmodel->fieldIndex("mkn_cinsi"));
    cbx_mknCins ->setModel(cbxCinsiModel);//cbxCinsiModel);
    cbx_mknCins->setModelColumn(cbxCinsiModel->fieldIndex("cinsi"));
    MKNmapper->addMapping(cbx_mknCins, MKNmodel->fieldIndex("mkn_cinsi"));

//qDebug()<<"set mapmkn 2";

    ///qDebug()<< "combo mrk";
    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_marka"),
                          QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));
    cbx_mknMark = new QComboBox;
    cbxMarkaModel = new QSqlTableModel ;
    cbxMarkaModel = MKNmodel->relationModel(
                MKNmodel->fieldIndex("mkn_marka"));
    cbx_mknMark->setModel(cbxMarkaModel); // cbxMarkaModel);
    cbx_mknMark->setModelColumn(cbxMarkaModel->fieldIndex("marka"));
    MKNmapper->addMapping(cbx_mknMark, MKNmodel->fieldIndex("mkn_marka"));


   // qDebug()<< "combo mdl";
    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_modeli"),
                          QSqlRelation("dbtb_mkmodl", "id_mkmodl", "modeli"));
    cbx_mknModl = new QComboBox;
    cbxModeliModel = new QSqlTableModel ;
    cbxModeliModel = MKNmodel->relationModel(
                MKNmodel->fieldIndex("mkn_modeli"));
    cbx_mknModl->setModel( cbxModeliModel ); //cbxModeliModel);
    cbx_mknModl->setModelColumn(cbxModeliModel->fieldIndex("modeli"));
    MKNmapper->addMapping(cbx_mknModl, MKNmodel->fieldIndex("mkn_modeli"));

    /// MKNmapper->addMapping(cbx_mknModl, MKNmodel->fieldIndex("mkn_"));


    MKNmodel->setRelation(  MKNmodel->fieldIndex("mkn_surucu"),
                            QSqlRelation("dbtb_clsn", "kod_pr", "soyad"));
    cbx_mknSurucu = new QComboBox ;
    cbxClsnModel = new QSqlTableModel;
    cbxClsnModel = MKNmodel->relationModel(
                MKNmodel->fieldIndex("mkn_surucu"));

    cbx_mknSurucu->setModel(cbxClsnModel);
    cbx_mknSurucu->setModelColumn(cbxClsnModel->fieldIndex("soyad"));
    MKNmapper->addMapping(cbx_mknSurucu, MKNmodel->fieldIndex("mkn_surucu"));

    Cw_mkn::MKNmapper->toFirst ();
qDebug()<<"set mapmkn son";
}


/////////////////////////////////     ekrandaki her şeyi kontrol edelim
void Cw_mkn::set_kntrlMKN()
{
    qDebug ()  <<"cw mkn kontrol ";
    QModelIndex idxMKN = MKNtview->table->currentIndex();
    onMKNtview_IE_filterSLOT(idxMKN);


    /// tüm işlemler tamam kontrol edelim
    //////////////////////////////////////////////////  table views

    /// makina view sağ tık context menusu

    /// mkn sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim
    connect(MKNtview->table, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onMKNtview_sagmenuSLOT(QPoint)));

    /// mkn değiştiğnde iş emri (ie) detaylarını değiştirelim
    connect(MKNselectionMdl,
            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
            this,  SLOT( onMKNtview_IE_filterSLOT(QModelIndex) ));



    /// mkn değiştiğnde resmide değiştirelim

    connect(MKNselectionMdl,
            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
            this,  SLOT(onMKNtview_resimGosterSLOT (QModelIndex) ));

    /// mkn değiştiğinde cins e bağlı marka ve modelde değişsin    ??????
    connect(MKNselectionMdl,
            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
            this,  SLOT( onMKNtview_cmm_filterSLOT(QModelIndex) ));

    /// mkn column değiştiğinde modelindex de değişsin
    //    connect(MKNtview->selectionModel(),
    //          SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
    //        MKNmapper, SLOT(setCurrentModelIndex(QModelIndex)));




    /// mkn row değiştiğinde modelindex de değişsin
    connect(MKNselectionMdl,
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            MKNmapper, SLOT(setCurrentModelIndex(QModelIndex)));

    //QModelIndex idc = MKNtview->currentIndex();

    //connect(MKNmapper, &QDataWidgetMapper::currentIndexChanged,
    //      this, &QTableView::MKNtview, &QTableView::setCurrentIndex);
    //
    qDebug ()  <<"cw mkn kontrol 991";
    //       /// sipariş emri (ie) değiştiğnde detayları (iedet) değiştirelim
    //    connect(Cwv_IsEmri->IEtview->selectionModel(),
    //            &QItemSelectionModel::currentChanged ,this,
    //            &Cw_mkn::onMKNtview_IE_det_filterSLOT    );




    //////////////////////////////////////////////////  pushbuttons

    /// resmi pencerede gösterelim
    connect(pb_rsm , &QPushButton::clicked,
            this, &Cw_mkn::onpb_resimPencereSLOT   );


    //////////////////////////////////////////////////  comboboxes
    qDebug ()  <<"cw mkn kontrol 1112";
    MKNtview->table->setCurrentIndex(MKNmodel->index(0, 0));
    MKNtview->setFocus();



}       ///     mkn_kontrol

// ////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////
// ////////////////////  M K N   //////////////////////////////////////
// ////////////////////////////////////////////////////////////////////





void Cw_mkn::mdll_mkn()
{
    // Create the data model for dbtb_mkn
    /*  qDebug()<<"mdll mkn 01";
    MKNmodel = new QSqlRelationalTableModel(this); //MKNtview
    MKNmodel->setEditStrategy(QSqlRelationalTableModel::OnFieldChange); // :OnRowChange);
    MKNmodel->setTable("dbtb_mkn");
    MKNmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    */
    /// mapper MKN
    //    MKNmapper = new QDataWidgetMapper(this);
    //    MKNmapper->setModel(MKNmodel);

    //    // mapperdaki comboboxları çalıştır
    //    MKNmapper->setItemDelegate(new QSqlRelationalDelegate(this));


    //    led_mknKurumno = new QLineEdit();
    //    MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));
    //    led_mknPlaka = new QLineEdit();
    //    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));
    //    ///qDebug()<< "combo cins";
    //    ///
    //    /// makina ile mkcins relation

    //    QSqlRelation relCins("dbtb_mkcins", "id_mkcins", "cinsi");
    //    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_cinsi"),relCins);
    //    cbx_mknCins = new QComboBox;
    //    cbxCinsiModel = new QSqlTableModel ;
    //    cbxCinsiModel = MKNmodel->relationModel(
    //                MKNmodel->fieldIndex("mkn_cinsi"));
    //    cbx_mknCins ->setModel(cbxCinsiModel);//cbxCinsiModel);
    //    cbx_mknCins->setModelColumn(cbxCinsiModel->fieldIndex("cinsi"));
    //    MKNmapper->addMapping(cbx_mknCins, MKNmodel->fieldIndex("mkn_cinsi"));



    //    ///qDebug()<< "combo mrk";
    //    MKNmodel->setRelation(MKNmodel->fieldIndex("mkn_marka"),
    //                          QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));
    //    cbx_mknMark = new QComboBox;
    //    cbxMarkaModel = new QSqlTableModel ;
    //    cbxMarkaModel = MKNmodel->relationModel(
    //                MKNmodel->fieldIndex("mkn_marka"));
    //    cbx_mknMark->setModel(cbxMarkaModel); // cbxMarkaModel);
    //    cbx_mknMark->setModelColumn(cbxMarkaModel->fieldIndex("marka"));
    //    MKNmapper->addMapping(cbx_mknMark, MKNmodel->fieldIndex("mkn_marka"));

    //    ///qDebug()<< "combo mdl";
    //    MKNmodel->setRelation(MKNmodel->fieldIndex("MKNmodeli"),
    //                          QSqlRelation("dbtb_mkmodl", "id_mkmodl", "modeli"));
    //    cbx_mknModl = new QComboBox;
    //    cbxModeliModel = new QSqlTableModel ;
    //    cbxModeliModel = MKNmodel->relationModel(
    //                MKNmodel->fieldIndex("MKNmodeli"));

    //    cbx_mknModl->setModel( cbxModeliModel ); //cbxModeliModel);
    //    cbx_mknModl->setModelColumn(cbxModeliModel->fieldIndex("modeli"));
    //    MKNmapper->addMapping(cbx_mknModl, MKNmodel->fieldIndex("MKNmodeli"));

    //    //////////////////////////////////////////////////////////////////

    //    ///qDebug()<< "combo clsn";
    //    MKNmodel->setRelation(  MKNmodel->fieldIndex("mkn_surucu"),
    //                            QSqlRelation("dbtb_clsn", "kod_pr", "soyad"));
    //    cbx_mknSurucu = new QComboBox ;
    //    cbxClsnModel = new QSqlTableModel;
    //    cbxClsnModel = MKNmodel->relationModel(
    //                MKNmodel->fieldIndex("mkn_surucu"));

    //    cbx_mknSurucu->setModel(cbxClsnModel);
    //    cbx_mknSurucu->setModelColumn(cbxClsnModel->fieldIndex("soyad"));
    //    MKNmapper->addMapping(cbx_mknSurucu, MKNmodel->fieldIndex("mkn_surucu"));

    ////////////////////////////////////////////////////////////////

    // Set the localized header captions
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_kurumNo"),
    //                Qt::Vertical , tr("Kurum No"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_plaka"),
    //                Qt::Horizontal, tr("PLAKA"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_cinsi"),
    //                Qt::Horizontal, tr("CİNSİ"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_Marka"),
    //                Qt::Horizontal, tr("MARKA"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("MKNmodeli"),
    //                Qt::Horizontal, tr("MODELİ"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_Yil"),
    //                Qt::Horizontal, tr("YILI"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_Saseno"),
    //                Qt::Horizontal, tr("ŞASE NO"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_Motorno"),
    //                Qt::Horizontal, tr("MOTOR NO"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_Byer"),
    //                Qt::Horizontal, tr("BULUNDUĞU YER"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_yakit"),
    //                Qt::Horizontal, tr("YAKIT TÜRÜ"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_surucu"),
    //                Qt::Horizontal, tr("SÜRÜCÜ"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_surucu_tar"),
    //                Qt::Horizontal, tr("SÜRÜCÜ İŞE BAŞLAMA"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_aciklama"),
    //                Qt::Horizontal, tr("AÇIKLAMA"));
    //    MKNmodel->setHeaderData(
    //                MKNmodel->fieldIndex("mkn_mknMotortip"),
    //                Qt::Horizontal, tr("MOTOR TİPİ"));

    //    MKNmapper->toFirst ();

    //    // Populate the MKNmodel
    //    if (!MKNmodel->select())
    //    {
    //        qDebug() << " HATA - model mkn" << MKNmodel->lastError();
    //        return;
    //    }


}       ///     MKNmodel

void Cw_mkn::mdll_mkcins()
{
    //  qDebug ()  <<" ' mdl_mkcins ' - mkcins Model Başlatıldı ";
    // Create the data model for DBTB_MKCINS

    mdl_mkcins = new QSqlRelationalTableModel(tV_mkcins);
    mdl_mkcins->setEditStrategy(QSqlTableModel::OnFieldChange);
    mdl_mkcins->setTable("DBTB_MKCINS");
    mdl_mkcins->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    //// mkcins ile mkmark relation
    mdl_mkcins->setRelation(mdl_mkcins->fieldIndex("mkcins_no"),
                            QSqlRelation("dbtb_mkmark", "id_mkmark", "marka"));

    // Remember the indexes of the columns
    // combobox fields
    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

    // Set the localized header captions
    mdl_mkcins->setHeaderData(mdl_mkcins->fieldIndex("cinsi"),
                              Qt::Horizontal, tr("CİNSİ"));

    // Populate the model
    if (!mdl_mkcins->select())
    {
        qDebug () << " HATA - " << mdl_mkcins->lastError();
        return;
    }

    // Set the model and hide the ID column
    tV_mkcins->setModel(mdl_mkcins);
    tV_mkcins->setColumnHidden(mdl_mkcins->fieldIndex("id_mkcins"), true);
    tV_mkcins->setSelectionMode(QAbstractItemView::SingleSelection);

}       ///     mdl_mkcins

void Cw_mkn::mdll_mkmark()
{
    // Create the data model for DBTB_MKCINS
    //  qDebug ()  <<" ' mdl_mkmark ' - mkmark Model Başlatıldı ";
    mdl_mkmark = new QSqlRelationalTableModel(tV_mkmark);
    mdl_mkmark->setEditStrategy(QSqlTableModel::OnFieldChange);
    mdl_mkmark->setTable("dbtb_mkmark");
    mdl_mkmark->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    //// mkmark ile mkmodel relation
    mdl_mkmark->setRelation(mdl_mkmark->fieldIndex("mkmark_no"),
                            QSqlRelation("dbtb_mkmodl", "id_mkmodl", "modeli"));


    // Remember the indexes of the columns
    // combobox fields
    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

    // Set the localized header captions
    mdl_mkmark->setHeaderData(mdl_mkmark->fieldIndex("marka"),
                              Qt::Horizontal, tr("MARKA"));

    // Populate the model
    if (!mdl_mkmark->select())
    {
        qDebug () << " HATA - " << mdl_mkmark->lastError();
        return;
    }

    // Set the model and hide the ID column
    tV_mkmark->setModel(mdl_mkmark);
    tV_mkmark->setColumnHidden(mdl_mkmark->fieldIndex("id_mkmark"), true);
    tV_mkmark->setSelectionMode(QAbstractItemView::SingleSelection);

}       ///     mdl_mkmark

void Cw_mkn::mdll_mkmodl()
{
    //    qDebug ()  <<" ' mdl_mkmodl ' - mkmodl Model Başlatıldı ";
    // Create the data model for DBTB_MKmodl

    mdl_mkmodl = new QSqlRelationalTableModel(tV_mkmodl);
    mdl_mkmodl->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdl_mkmodl->setTable("dbtb_mkmodl");

    // Set the localized header captions
    mdl_mkmodl->setHeaderData(mdl_mkmodl->fieldIndex("modeli"),
                              Qt::Horizontal, tr("MODELİ"));

    // Populate the model
    if (!mdl_mkmodl->select())
    {
        qDebug () << " HATA - " << mdl_mkmodl->lastError();
        return;
    }

    // Set the model and hide the ID column
    tV_mkmodl->setModel(mdl_mkmodl);
    tV_mkmodl->setColumnHidden(mdl_mkmodl->fieldIndex("id_mkmodl"), true);
    tV_mkmodl->setSelectionMode(QAbstractItemView::SingleSelection);

}       ///     mdl_mkmodl

/////////////////////////////////     modeli view de gösterelim
void Cw_mkn::MKNtview_view()
{
    // Set the MKNmodel and hide the ID column
    //    MKNtview->table->setModel(MKNmodel);

    //    // tableview de comboboxları göster
    //    //MKNtview->setItemDelegate(new MakinaDelegate(MKNtview));
    //    MKNtview->table->setItemDelegate(new QSqlRelationalDelegate(this));
    //    MKNtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    //    MKNtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    //    MKNtview->table->setContextMenuPolicy(Qt::CustomContextMenu);
    //    MKNtview->table->setCurrentIndex(MKNmodel->index(0,0));
    //    MKNtview->table->selectionModel()->setCurrentIndex(MKNtview->table->currentIndex (),
    //                                                QItemSelectionModel::SelectCurrent);


    //    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("id_mkn"), true);
    //    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_resim"), true);
    //    MKNtview->table->setColumnHidden(MKNmodel->fieldIndex("mkn_rating"), true);

    //    MKNmodel->select();
    //    MKNtview->setFocus();
}       ///     mkn_view

void Cw_mkn::tV_cns_view()   // mkn cins tableview
{

}       ///     tV_cns_view

void Cw_mkn::tV_mrk_view()   // mkn marka tableview
{

}       ///     tV_mrk_view

void Cw_mkn::tV_mdl_view()   // mkn model tableview
{

}       ///     tV_mdl_view

///////////////////////////////////////////////////////////////// SLOTS

/////////////////////////////////////////////   mkn view sağ tuş menusu
void Cw_mkn::onMKNtview_sagmenuSLOT(QPoint pos)
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

    // mkn resmi ekle
    const QIcon rsmIc_mkn = QIcon(":/rsm/ex.ico");
    QAction* rsmAct_mkn = new QAction(rsmIc_mkn, tr("Makina &Resmi Ekle-Değiştir"), this);
    rsmAct_mkn->setShortcuts (QKeySequence::New);
    rsmAct_mkn->setStatusTip ("Makina Resmi Ekle-Değiştir");
    connect (rsmAct_mkn, &QAction::triggered, this,
             &Cw_mkn::onmnMKN_resimEklE_clickedSLOT );
    menu->addAction(rsmAct_mkn);


    // yeni iş emri kaydı ekle
    const QIcon ekleIc_sipr = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sipr = new QAction(ekleIc_sipr, tr("İş Emri Ekle..."), this);
    ekleAct_sipr->setShortcuts (QKeySequence::New);
    ekleAct_sipr->setStatusTip ("İş Emri Kaydı Ekle");
    connect (ekleAct_sipr, &QAction::triggered, this,
             &Cw_mkn::onmnMKN_IEekle );
    menu->addAction(ekleAct_sipr);



    //  mkn kaydı SİL
    const QIcon silIc_mkn = QIcon(":/rsm/Erase.ico");
    QAction* silAct_mkn = new QAction(silIc_mkn, tr("Makina &Sil..."), this);
    silAct_mkn->setShortcuts (QKeySequence::New);
    silAct_mkn->setStatusTip ("DİKKAT :: Makina Kaydını ve bu makina ile ilgili herşeyi siler...");
    connect (silAct_mkn, &QAction::triggered, this,
             &Cw_mkn::onmnMKN_arac_sil_clickedSLOT );
    menu->addAction(silAct_mkn);

    menu->addSeparator();
    // menu->setWindowTitle("ddddddddddd");





    // yeni mkn kaydı ekle
    const QIcon ekleIc_mkn = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_mkn = new QAction(ekleIc_mkn, tr("Makina &Düzenle..."), this);
    ekleAct_mkn->setShortcuts (QKeySequence::New);
    ekleAct_mkn->setStatusTip ("Yeni Makina Kaydı Ekle-Düzenle");
    connect (ekleAct_mkn, &QAction::triggered,
             [this] ()
    {

        // makina stok ekle
        //qDebug()<<"mknekle 1"<<endl<<"mkntview index"<<MKNtview->table->currentIndex ()<<endl<<
        //        "mppmkn index"<<MKNmapper->currentIndex ();

        auto *wdgt_mppr = new QDialog;
        wdgt_mppr->setWindowTitle("Demirbaş Ambarı Yeni Kayıt");
        wdgt_mppr->setVisible(false);      ////////////     MAPPER
        wdgt_mppr->show();

        //    MKNmapper->setCurrentIndex (MKNtview->currentIndex ().row ()) ;

        auto *mapperL = new QGridLayout;
        wdgt_mppr->setLayout(mapperL);
        int satr=0;

        QLabel *lB_kurumno = new QLabel("Kurum No");
        mapperL->addWidget(lB_kurumno    ,satr,0,1,1,nullptr);

        //   led_mknKurumno = new QLineEdit();
        connect( led_mknKurumno, &QLineEdit::textChanged,
                 this,  &Cw_mkn::mknKurumno_ara);
        mapperL->addWidget(led_mknKurumno   ,satr++,1,1,3,nullptr);
        lB_kurumno->setBuddy(led_mknKurumno);
        // MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));
        led_mknKurumno->setFocus();

        QLabel *lB_plaka = new QLabel("Plaka ");
        mapperL->addWidget(lB_plaka  ,satr,0,1,1,nullptr);
        //    led_mknPlaka = new QLineEdit();
        mapperL->addWidget(led_mknPlaka ,satr++,1,1,3,nullptr);
        lB_plaka->setBuddy(led_mknPlaka);
        //    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));


        QLabel *lB_cins = new QLabel("Cinsi  ");
        pb_mknCins = new QPushButton;
        mapperL->addWidget(lB_cins   ,satr,0,1,1,nullptr);
        mapperL->addWidget(cbx_mknCins  ,satr,1,1,2,nullptr);
        mapperL->addWidget(pb_mknCins   ,satr++,3,3,1,nullptr);
        connect(pb_mknCins, &QPushButton::clicked ,
                this,&Cw_mkn::ww_mkcins );

        QLabel *lB_mknMark = new QLabel("Markası");
        pb_mknMark = new QPushButton;
        mapperL->addWidget(lB_mknMark   ,satr,0,1,1,nullptr);
        mapperL->addWidget(cbx_mknMark  ,satr,1,1,2,nullptr);
        // mapperL->addWidget(pb_mknMark   ,satr++,3,1,1,nullptr);

        QLabel *lB_mknModl = new QLabel("Modeli ");
        pb_mknModl = new QPushButton;
        mapperL->addWidget(lB_mknModl   ,++satr,0,1,1,nullptr);
        mapperL->addWidget(cbx_mknModl  ,satr,1,1,2,nullptr);
        // mapperL->addWidget(pb_mknModl   ,satr++,3,1,1,nullptr);

        QLabel *lB_mknYil = new QLabel("Yıl ");
        mapperL->addWidget(lB_mknYil    ,++satr,0,1,1,nullptr);
        spn_mknYil = new QSpinBox();
        mapperL->addWidget(spn_mknYil   ,satr++,1,1,3,nullptr);
        lB_mknYil->setBuddy(spn_mknYil);
        MKNmapper->addMapping(spn_mknYil, MKNmodel->fieldIndex("mkn_yil"));

        satr=0;
        QLabel *lB_mknSase = new QLabel("Şase No   ");
        mapperL->addWidget(lB_mknSase   ,satr,4,1,1,nullptr);
        led_mknSase = new QLineEdit();
        mapperL->addWidget(led_mknSase  ,satr++,5,1,3,nullptr);
        lB_mknSase->setBuddy(led_mknSase);
        MKNmapper->addMapping(led_mknSase, MKNmodel->fieldIndex("mkn_saseno"));

        QLabel *lB_mknMotor = new QLabel("Motor No ");
        mapperL->addWidget(lB_mknMotor  ,satr,4,1,1,nullptr);
        led_mknMotor = new QLineEdit();
        mapperL->addWidget(led_mknMotor ,satr++,5,1,3,nullptr);
        lB_mknMotor->setBuddy(led_mknMotor);
        MKNmapper->addMapping(led_mknMotor, MKNmodel->fieldIndex("mkn_motorno"));

        QLabel *lB_mknMtip = new QLabel("Motor Tipi");
        mapperL->addWidget(lB_mknMtip   ,satr,4,1,1,nullptr);
        led_mknMtip = new QLineEdit();
        mapperL->addWidget(led_mknMtip  ,satr++,5,1,3,nullptr);
        lB_mknMtip->setBuddy(led_mknMtip);
        MKNmapper->addMapping(led_mknMtip, MKNmodel->fieldIndex("mkn_motortip"));

        QLabel *lB_mknYkt = new QLabel("Yakıt Türü");
        cbx_mknYkt  = new QComboBox;
        cbx_mknYkt->insertItem(1,"Benzin");
        cbx_mknYkt->insertItem(2,"Dizel");
        cbx_mknYkt->insertItem(3,"LPG");
        cbx_mknYkt->insertItem(4,"Benzin-LPG");
        cbx_mknYkt->insertItem(5,"Doğalgaz");
        pb_mknYkt = new QPushButton;
        connect( pb_mknYkt, &QPushButton::clicked, this, &Cw_mkn::ykt);
        mapperL->addWidget(lB_mknYkt    ,satr,4,1,1,nullptr);
        mapperL->addWidget(cbx_mknYkt   ,satr,5,1,2,nullptr);
        mapperL->addWidget(pb_mknYkt    ,satr++,7,1,1,nullptr);
        MKNmapper->addMapping(cbx_mknYkt, MKNmodel->fieldIndex("mkn_yakit"));


        QLabel *lB_mknSurucu = new QLabel("Sürücü  ");
        pb_mknSurucu = new QPushButton;
        connect( pb_mknSurucu, &QPushButton::clicked, this, &Cw_mkn::src);
        mapperL->addWidget(lB_mknSurucu    ,satr,4,1,1,nullptr);
        mapperL->addWidget(cbx_mknSurucu   ,satr,5,1,2,nullptr);
        mapperL->addWidget(pb_mknSurucu    ,satr++,7,1,1,nullptr);


        QLabel *lB_mknSurucutar = new QLabel("Sürücü İşe Başlama");
        mapperL->addWidget(lB_mknSurucutar  ,satr,4,1,1,nullptr);
        clndr_mknSurucutar = new QDateTimeEdit(QDate::currentDate());
        clndr_mknSurucutar->setMinimumDate(QDate(1900, 1, 1));
        clndr_mknSurucutar->setMaximumDate(QDate(2023, 1, 1));
        clndr_mknSurucutar->setDisplayFormat("dd.MM.yyyy");
        clndr_mknSurucutar->setCalendarPopup(true);
        mapperL->addWidget(clndr_mknSurucutar   ,satr++,5,1,3,nullptr);
        MKNmapper->addMapping(clndr_mknSurucutar, MKNmodel->fieldIndex("mkn_surucu_tar"));

        QLabel *lB_mknBirim = new QLabel("Birim   ");
        cbx_mknBirim  = new QComboBox;
        pb_mknBirim = new QPushButton;
        connect( pb_mknBirim, &QPushButton::clicked, this, &Cw_mkn::birim);
        mapperL->addWidget(lB_mknBirim   ,satr,4,1,1,nullptr);
        mapperL->addWidget(cbx_mknBirim  ,satr,5,1,2,nullptr);
        mapperL->addWidget(pb_mknBirim   ,satr,7,1,1,nullptr);
        lB_mknBirim->setBuddy(cbx_mknBirim);
        MKNmapper->addMapping(cbx_mknBirim, MKNmodel->fieldIndex("mkn_birim"));

        QLabel *lB_mknByer = new QLabel("Bulunduğu Yer ");
        pb_mknByer = new QPushButton;
        connect( pb_mknByer, &QPushButton::clicked, this, &Cw_mkn::byer);
        mapperL->addWidget(lB_mknByer   ,satr,0,1,1,nullptr);
        cbx_mknByer  = new QComboBox;
        mapperL->addWidget(cbx_mknByer  ,satr,1,1,2,nullptr);
        mapperL->addWidget(pb_mknByer   ,satr++,3,1,1,nullptr);
        lB_mknByer->setBuddy(cbx_mknByer);
        MKNmapper->addMapping(cbx_mknByer, MKNmodel->fieldIndex("mkn_byer"));

        QLabel *lB_mknAcklm = new QLabel("Açıklama   ");
        mapperL->addWidget(lB_mknAcklm    ,satr,0,1,1,nullptr);
        ted_mknAcklm = new QTextEdit();
        mapperL->addWidget(ted_mknAcklm   ,satr,1,1,4,nullptr);
        lB_mknAcklm->setBuddy(ted_mknAcklm);
        MKNmapper->addMapping(ted_mknAcklm, MKNmodel->fieldIndex("mkn_aciklama"));

        lB_resim = new QLabel;
        lB_resim->setFixedSize(200,110);
        mapperL->addWidget(lB_resim   ,++satr,5,1,4,nullptr);
        MKNmapper->addMapping(lB_resim , MKNmodel->fieldIndex("mkn_resim"));
        rsm_ByteArray = new QByteArray;
        *rsm_ByteArray = "";

        //        MKNmapper->addMapping(*rsm_ByteArray, MKNmodel->fieldIndex("resim"));
        //MKNmapper->addMapping(led_rating, MKNmodel->fieldIndex("rating"));


        //    /// yeni ekle penceresine girerken index ne
        //    QModelIndex mknndx = MKNtview->currentIndex ();
        //    //MKNmapper->toFirst ();
        //    MKNmapper->setCurrentIndex( mknndx.row ()) ;
        int sutn=0;
        //   satr +=2;
        // mapperL->addWidget( MKNtview   ,++satr,0,2,7,nullptr);
        //satr+=5;
        //qDebug ()<<"model yıı 222";
        QPushButton *pb_ilk = new QPushButton("İlk");
        connect( pb_ilk, &QPushButton::clicked,
                 MKNmapper, &QDataWidgetMapper::toFirst );
        mapperL->addWidget( pb_ilk   ,satr+=2,sutn++,1,1,nullptr);

        QPushButton *pb_pr = new QPushButton("Önceki");
        connect( pb_pr, &QPushButton::clicked,
                 MKNmapper, &QDataWidgetMapper::toPrevious );
        mapperL->addWidget( pb_pr   ,satr,sutn++,1,1,nullptr);

        QPushButton *pb_lr = new QPushButton("Sonraki");
        connect( pb_lr, &QPushButton::clicked,
                 MKNmapper, &QDataWidgetMapper::toNext );
        mapperL->addWidget( pb_lr   ,satr,sutn++,1,1,nullptr);

        QPushButton *pb_ls = new QPushButton("Son");
        connect( pb_ls, &QPushButton::clicked,
                 MKNmapper, &QDataWidgetMapper::toLast );
        mapperL->addWidget( pb_ls   ,satr,sutn++,1,1,nullptr);

        pb_rsmEkle = new QPushButton("Resim Ekle");
        connect( pb_rsmEkle, &QPushButton::clicked,
                 this, &Cw_mkn::resimEkle);
        mapperL->addWidget( pb_rsmEkle   ,satr,sutn++,1,1,nullptr);


        QPushButton *pb_yn = new QPushButton("Yeni Ekle");
        connect( pb_yn, &QPushButton::clicked,
                 this, &Cw_mkn::clk_boshMKN );
        mapperL->addWidget( pb_yn   ,satr,sutn+=2,1,1,nullptr);

        QPushButton *pb_vzgc = new QPushButton("Vazgeç");
        connect( pb_vzgc, &QPushButton::clicked,
                 wdgt_mppr, &QWidget::close );
        mapperL->addWidget( pb_vzgc   ,satr++,9,1,1,nullptr);


    });




    //      this,
    //    &Cw_mkn::onmnMKN_MKNekle );





    menu->addAction(ekleAct_mkn);





    menu->popup(MKNtview->table->viewport()->mapToGlobal(pos));
}       ///     onMKNtview_sagmenuSLOT



void Cw_mkn::onmnMKN_resimEklE_clickedSLOT()
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
    lB_foto->setPixmap(QPixmap::fromImage(image));

    QByteArray inByteArray;
    QFile file(  myfile ); //dosyayı açmak için al

    if ( file.open(QIODevice::ReadOnly))
    {
        //qDebug ()<<"file read";
        inByteArray = file.readAll();

        // table view de hangi rowdayız ?
        QModelIndex index = MKNtview->table->currentIndex();
        int row = index.row() ;
        // o row daki bilgilere ulaşalım
        MKNmodel->setData(MKNmodel->
                          index(row, MKNmodel->fieldIndex ("mkn_resim")),inByteArray);
        MKNmodel->submitAll();



    }

}       ///     onpb_resimEkleSLOT

void Cw_mkn::onmnMKN_arac_sil_clickedSLOT()
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

}       ///      onmnMKN_arac_sil_clickedSLOT


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
}       ///      onmnMKN_yeniEklE_hgs





//////////////////////////////////////////////////////// SLOTS tableView
void Cw_mkn::onMKNtview_IE_filterSLOT(QModelIndex mknIndex )
{
    qDebug () <<"IE_filterSLOT";
    if (mknIndex.isValid())
    {
        qDebug () <<"IE_filterSLOT index valid" << mknIndex;
        /// makina id  si ile iş emirlerini ve diğerlerini filtrele
        QSqlRecord mknrec = MKNmodel->record(mknIndex.row());
        QString bslk = mknrec.value("mkn_kurumNo").toString()+" - "+
                mknrec.value("mkn_plaka").toString() ;
        int mknid = mknrec.value("id_mkn").toInt();
        Cwv_IsEmri->IEmodel->setFilter(QString("ie_mkn_id = %1").arg(mknid));
        Cwv_IsEmri->IEmodel->select();
qDebug () <<"IE_filterSLOT 1";

        //{   /// IE id  si ile İŞ EMRİ DETAYLARINI filtrele
        Cwv_IsEmri->IEtview->setCurrentIndex
                (Cwv_IsEmri->IEmodel->index(0,0));
        QModelIndex ieindx = Cwv_IsEmri->IEtview->currentIndex();
        Cwv_IsEmri->rowChanged_IE(ieindx);
qDebug () <<"IE_filterSLOT 2";
        /*    QSqlRecord ierec = Cwv_IsEmri->IEmodel->record(ieindx.row());
            //QString bslk = mknrec.value("mkn_kurumNo").toString()+" - "+
            //      mknrec.value("plaka").toString() ;

*/

        /// IEDET id  si ile TAŞINIR VE İŞÇİLİK filtrele
        Cwv_IsEmri->IEDETtview->setCurrentIndex
                (Cwv_IsEmri->IEDETmodel->index(0,0));
        QModelIndex iedetindx = Cwv_IsEmri->IEDETtview->currentIndex();
        Cwv_IsEmri->rowChanged_IEDET(iedetindx);

qDebug () <<"IE_filterSLOT 3";

        evrk_sgrt->mdl_evr_sgrt->setFilter(QString("mknstk_id = %1").arg(mknid));
        evrk_sgrt->mdl_evr_sgrt->select();
        evrk_mua->mdl_evrk_mua->setFilter(QString("mknstk_id = %1").arg(mknid));
        evrk_mua->mdl_evrk_mua->select();

        tbx_evrk->setItemText(0,"Trafik Sigortası - Kasko   ---   "+bslk);
        tbx_evrk->setItemText(1,"Muayene   ---   "+bslk);
        tbx_evrk->setItemText(3,"OGS-KGS   ---   "+bslk);

        // mkcins mark modl için set filter ayarları

        qDebug () <<"IE_filterSLOT 4";
        /*
        QModelIndex cinsindx = tV_mkcins->currentIndex();
        if (cinsindx.isValid())
        {
            qDebug () <<"IE_filterSLOT 5";
            QSqlRecord record = mdl_mkcins->record(cinsindx.row());
            int cinsid = record.value("id_mkcins").toInt();
            mdl_mkmark->setFilter(QString("mkcins_no = %1").arg(cinsid));
            mdl_mkmark->select();
        }
        else
        {
            qDebug () <<"IE_filterSLOT 6";
            mdl_mkmark->setFilter("id_mkcins = -1");
        }
        mdl_mkmark->select();
        //qDebug () <<"mkn row changggggedd 7";
        QModelIndex markidx = tV_mkmark->currentIndex();
        if (markidx.isValid())
        {
            qDebug () <<"IE_filterSLOT 7";
            //          qDebug () <<"mkn row changggggedd 8";
            QSqlRecord record = mdl_mkmark->record(markidx.row());
            int id = record.value("id_mkmark").toInt();

            mdl_mkmodl->setFilter(QString("mkmark_no = %1").arg(id));
            mdl_mkmodl->select();
        }
        else
        {
            qDebug () <<"IE_filterSLOT 8" ;
            mdl_mkmodl->setFilter("id_mkmark = -1");
        }

        mdl_mkmodl->select();*/
    }
    else
    {
        qDebug () <<"IE_filterSLOT index NOT valid";
        //////////////////       Cwv_IsEmri->IEmodel->setFilter("id_IE = -1");
        evrk_sgrt->mdl_evr_sgrt->setFilter("id_mkn=-1");
        evrk_mua->mdl_evrk_mua->setFilter("id_mkn=-1");
    }
    qDebug () <<"mkn row changggggedd son";
}       ///      onMKNtview_IE_filterSLOT


void Cw_mkn::onMKNtview_resimGosterSLOT(QModelIndex)
{
    // makina stok tablosundan resim gösterme

    // view row unu tespit et
    int rowidx = MKNselectionMdl->currentIndex().row();
    //int rowidx = index.row (); //MKNtview->selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = MKNtview->table->
            model()->index(rowidx, MKNmodel->fieldIndex ("mkn_resim")).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    lB_foto->setPixmap( outPixmap );
    lB_foto->setScaledContents( true );
    lB_foto->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    lB_foto->show();

    /*   //QPixmap bkgnd("/home/user/Pictures/background.png");
    outPixmap = outPixmap.scaled(this ->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, outPixmap);
       this ->setPalette(palette);
*/

}       ///     onMKNtview_resimGosterSLOT


void Cw_mkn::onMKNtview_cmm_filterSLOT(QModelIndex)
{

}       ///     onMKNtview_cmm_filterSLOT


/*
void Cw_mkn::onMKNtview_IE_det_filterSLOT(QModelIndex)
{
    //  qDebug ()  <<" ' Cw_mkn      ' - onIEtview_det_filterSLOT  ";
}       ///      onIEtview_det_filterSLOT
*/
///////////////////////////////////////////// pushbutton SLOTS
void Cw_mkn::onpb_mknclickedSLOT()
{
    //   qDebug()<<"onpb mkn clicked";
    qs->setStretchFactor(0,10);
    //  wdgt_mppr->setVisible(false);
    pb_mkn->setVisible(false);
    pb_tab->setVisible(true);
}       ///     onpb_mknclickedSLOT

void Cw_mkn::onpb_tabclickedSLOT()
{
    //  qDebug()<<"onpb mkn clicked";
    qs->setStretchFactor(1,10);
    //  wdgt_mppr->setVisible(true);
    pb_mkn->setVisible(true);
    pb_tab->setVisible(false);
}       ///      onpb_tabclickedSLOT


void Cw_mkn::onpb_resimPencereSLOT()
{
    //  qDebug()<<"onpb mkn resim pencere clicked";
    QDialog *x = new QDialog;
    x->setWindowFlags(Qt::WindowCloseButtonHint |
                      Qt::WindowMaximizeButtonHint);
    x->setWindowTitle("Makina Resmi");

    QLabel *imageLabel = new QLabel(x);
    auto *xL = new QGridLayout;
    //    QScrollArea *scrollArea = new QScrollArea(x);
    xL->addWidget(imageLabel ,0,0,1,1,nullptr);
    x->setLayout(xL);
    x->setModal(true);
    // x->setGeometry(100,100,880,495);



    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);


    //setCentralWidget(scrollArea);

    x->resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);



    //int rowidx = MKNtview->selectionModel()->currentIndex().row();
    // row, xolumn daki veriyi bytearray a at
    //QByteArray outByteArray = MKNtview->model()->index
    //      (rowidx,MKNmodel->fieldIndex("mkn_resim").data().toByteArray();

    //QByteArray outByteArray =
    //   MKNmodel->data (MKNmodel->index(rowidx ,
    //    MKNmodel->fieldIndex("mkn_resim").toByteArray());

    // MKNmodel->data (MKNmodel->index (mkn_indx.row (), MKNmodel->fieldIndex ("id_mkn"))).toString ();


    QModelIndex index = MKNtview->table->currentIndex();
    QByteArray outByteArray = "";
    if (index.isValid())
    {
        // tv index i ile model de recordu bulduk
        QSqlRecord record = MKNmodel->record(index.row());
        outByteArray = record.value("mkn_resim").toByteArray ();

    }
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    imageLabel->setPixmap(outPixmap);

    //  scrollArea->setBackgroundRole(QPalette::Dark);
    //  scrollArea->setWidget(imageLabel);
    //  scrollArea->setVisible(true);


    //imageLabel->adjustSize();
    //imageLabel->resize(imageLabel->pixmap()->size());

    x->show();
}



/*
void Cw_mkn::oncbx_mknCinsclickedSLOT(const QString&)
{
    qCritical() << "combooooooooo";
    qCritical() << mdl_mkmark->filter()<<endl;
    QModelIndex index = tV_mkcins->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = mdl_mkcins->record(index.row());
        int id = record.value("id_mkcins").toInt();

        mdl_mkmark->setFilter(QString("mkcins_no = %1").arg(id));
        mdl_mkmark->select();
        qCritical() << mdl_mkmark->filter();
    }
    else
    {
        qCritical() << "ONCBX_CİNS - Cins indeksi geçerli değil - " <<mdl_mkmark->filter();
    }
}       ///     oncbx_mknCinsclickedSLOT

*/

/*
void Cw_mkn::oncbx_mknMarkclickedSLOT()
{
    QModelIndex i_mkn = MKNtview->currentIndex();
    QModelIndex i_cns = tV_mkcins->currentIndex();
    QModelIndex i_mrk = tV_mkmark->currentIndex();
    qCritical() << " i mkn  - " << i_mkn
                << "\n i cns  - " << i_cns
                << "\n i mrk  - " <<i_mrk
                << MKNmodel->relationModel(idx_mkmark)->itemData(i_mkn);

    //cbx_mknCins->

    if (i_mkn.isValid())
    {
        QSqlRecord record = mdl_mkmark->record(i_mkn.row());
        int id = record.value("id_mkmark").toInt();

        mdl_mkmodl->setFilter(QString("mkmark_no = %1").arg(id));
        mdl_mkmodl->select();

        qCritical() << "filter " << mdl_mkmark->filter();

    }

    else
    {
        qCritical() << "ONCBX_mknMarkA - Marka indeksi geçerli değil - " <<mdl_mkmark->filter();
    }




}

*/
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




void Cw_mkn::ss()
{
    SS01 = " QTabBar::tab    "
           "{"
           "     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
           "                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
           "                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
           "     border: 2px solid #C4C4C3;"
           "     border-bottom-color: #C2C7CB; /* same as the pane color */"
           "     border-top-left-radius: 4px;"
           "     border-top-right-radius: 4px;"
           "     min-width: 8ex;"
           "     color: white;"
           "     font: bold large 'Times New Roman';"
           "     padding: 2px;"
           "     alignment: center;"
           " }"

           " QTabBar::tab:selected, QTabWidget::tab:hover "
           " {"
           "     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
           "                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
           "                                 stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
           " }"

           " QTabBar::tab:selected {"
           " background-color: qlineargradient(x1: 0, y1: 0, x2: 1.4, y2: 0.8,"
           "    stop: 0 blue , stop: 1 #FF92BB);"

            //  "     border-color: #9B9B9B;"
            //"     border-bottom-color: #C2C7CB; /* same as pane color */"
            " }"

            "  QTabBar::tab:!selected {"
            " background-color: qlineargradient(x1: 0, y1: 0, x2: 1.4, y2: 0.8,"
            "    stop: 0 green , stop: 1 yellow);"

            "      margin-top: 2px; /* make non-selected tabs look smaller */"
            "  }";

    SS02 = "QToolBox::tab "
           "{     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
           "                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
           "                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
           "     border: 2px solid #C4C4C3;"
           "     border-bottom-color: #C2C7CB; /* same as the pane color */"
           "     border-top-left-radius: 4px;"
           "     border-top-right-radius: 4px;"
           "     min-width: 8ex;"
           "     padding: 2px;"
           "font: bold large 'Times New Roman';"
           "     color: white;"

           " }"

           " QToolBox::tab:selected, QToolBox::tab:hover "
           " {"
           "     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
           "                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
           "                                 stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
           " }"

           " QToolBox::tab:selected {"
           " background-color: qlineargradient(x1: 0, y1: 0, x2: 1.0, y2: 0.5,"
           "    stop: 0 darkblue , stop: 1 #FF92BB);"

           "     border-color: #9B9B9B;"
           "     border-bottom-color: #C2C7CB; /* same as pane color */"
           " }"

           "  QToolBox::tab:!selected {"
           " background-color: qlineargradient(x1: 0, y1: 0, x2: 1.0, y2: 0.5,"
           "    stop: 0 green , stop: 1 yellow);"

           "      margin-top: 2px; /* make non-selected tabs look smaller */"
           "  }" ;


}       ///      ss



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




void Cw_mkn::onmnMKN_MKNekle()
{
    //    // makina stok ekle
    //    //qDebug()<<"mknekle 1"<<endl<<"mkntview index"<<MKNtview->table->currentIndex ()<<endl<<
    //      //        "mppmkn index"<<MKNmapper->currentIndex ();

    //    wdgt_mppr = new QWidget;
    //    wdgt_mppr->setWindowTitle("Demirbaş Ambarı Yeni Kayıt");
    //    wdgt_mppr->setVisible(false);      ////////////     MAPPER
    //    wdgt_mppr->show();

    //    //    MKNmapper->setCurrentIndex (MKNtview->currentIndex ().row ()) ;

    //    auto *mapperL = new QGridLayout;
    //    wdgt_mppr->setLayout(mapperL);
    //    int satr=0;

    //    QLabel *lB_kurumno = new QLabel("Kurum No");
    //    mapperL->addWidget(lB_kurumno    ,satr,0,1,1,nullptr);

    //    //   led_mknKurumno = new QLineEdit();
    //    connect( led_mknKurumno, &QLineEdit::textChanged,
    //             this,  &Cw_mkn::mknKurumno_ara);
    //    mapperL->addWidget(led_mknKurumno   ,satr++,1,1,3,nullptr);
    //    lB_kurumno->setBuddy(led_mknKurumno);
    //    // MKNmapper->addMapping(led_mknKurumno, MKNmodel->fieldIndex("mkn_kurumNo"));
    //    led_mknKurumno->setFocus();

    //    QLabel *lB_plaka = new QLabel("Plaka ");
    //    mapperL->addWidget(lB_plaka  ,satr,0,1,1,nullptr);
    //    //    led_mknPlaka = new QLineEdit();
    //    mapperL->addWidget(led_mknPlaka ,satr++,1,1,3,nullptr);
    //    lB_plaka->setBuddy(led_mknPlaka);
    //    //    MKNmapper->addMapping(led_mknPlaka, MKNmodel->fieldIndex("mkn_plaka"));


    //    QLabel *lB_cins = new QLabel("Cinsi  ");
    //    pb_mknCins = new QPushButton;
    //    mapperL->addWidget(lB_cins   ,satr,0,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknCins  ,satr,1,1,2,nullptr);
    //    mapperL->addWidget(pb_mknCins   ,satr++,3,3,1,nullptr);
    //    connect(pb_mknCins, &QPushButton::clicked ,
    //            this,&Cw_mkn::ww_mkcins );

    //    QLabel *lB_mknMark = new QLabel("Markası");
    //    pb_mknMark = new QPushButton;
    //    mapperL->addWidget(lB_mknMark   ,satr,0,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknMark  ,satr,1,1,2,nullptr);
    //    // mapperL->addWidget(pb_mknMark   ,satr++,3,1,1,nullptr);

    //    QLabel *lB_mknModl = new QLabel("Modeli ");
    //    pb_mknModl = new QPushButton;
    //    mapperL->addWidget(lB_mknModl   ,++satr,0,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknModl  ,satr,1,1,2,nullptr);
    //    // mapperL->addWidget(pb_mknModl   ,satr++,3,1,1,nullptr);

    //    QLabel *lB_mknYil = new QLabel("Yıl ");
    //    mapperL->addWidget(lB_mknYil    ,++satr,0,1,1,nullptr);
    //    spn_mknYil = new QSpinBox();
    //    mapperL->addWidget(spn_mknYil   ,satr++,1,1,3,nullptr);
    //    lB_mknYil->setBuddy(spn_mknYil);
    //    MKNmapper->addMapping(spn_mknYil, MKNmodel->fieldIndex("mkn_yil"));

    //    satr=0;
    //    QLabel *lB_mknSase = new QLabel("Şase No   ");
    //    mapperL->addWidget(lB_mknSase   ,satr,4,1,1,nullptr);
    //    led_mknSase = new QLineEdit();
    //    mapperL->addWidget(led_mknSase  ,satr++,5,1,3,nullptr);
    //    lB_mknSase->setBuddy(led_mknSase);
    //    MKNmapper->addMapping(led_mknSase, MKNmodel->fieldIndex("mkn_saseno"));

    //    QLabel *lB_mknMotor = new QLabel("Motor No ");
    //    mapperL->addWidget(lB_mknMotor  ,satr,4,1,1,nullptr);
    //    led_mknMotor = new QLineEdit();
    //    mapperL->addWidget(led_mknMotor ,satr++,5,1,3,nullptr);
    //    lB_mknMotor->setBuddy(led_mknMotor);
    //    MKNmapper->addMapping(led_mknMotor, MKNmodel->fieldIndex("mkn_motorno"));

    //    QLabel *lB_mknMtip = new QLabel("Motor Tipi");
    //    mapperL->addWidget(lB_mknMtip   ,satr,4,1,1,nullptr);
    //    led_mknMtip = new QLineEdit();
    //    mapperL->addWidget(led_mknMtip  ,satr++,5,1,3,nullptr);
    //    lB_mknMtip->setBuddy(led_mknMtip);
    //    MKNmapper->addMapping(led_mknMtip, MKNmodel->fieldIndex("mkn_motortip"));

    //    QLabel *lB_mknYkt = new QLabel("Yakıt Türü");
    //    cbx_mknYkt  = new QComboBox;
    //    cbx_mknYkt->insertItem(1,"Benzin");
    //    cbx_mknYkt->insertItem(2,"Dizel");
    //    cbx_mknYkt->insertItem(3,"LPG");
    //    cbx_mknYkt->insertItem(4,"Benzin-LPG");
    //    cbx_mknYkt->insertItem(5,"Doğalgaz");
    //    pb_mknYkt = new QPushButton;
    //    connect( pb_mknYkt, &QPushButton::clicked, this, &Cw_mkn::ykt);
    //    mapperL->addWidget(lB_mknYkt    ,satr,4,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknYkt   ,satr,5,1,2,nullptr);
    //    mapperL->addWidget(pb_mknYkt    ,satr++,7,1,1,nullptr);
    //    MKNmapper->addMapping(cbx_mknYkt, MKNmodel->fieldIndex("mkn_yakit"));


    //    QLabel *lB_mknSurucu = new QLabel("Sürücü  ");
    //    pb_mknSurucu = new QPushButton;
    //    connect( pb_mknSurucu, &QPushButton::clicked, this, &Cw_mkn::src);
    //    mapperL->addWidget(lB_mknSurucu    ,satr,4,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknSurucu   ,satr,5,1,2,nullptr);
    //    mapperL->addWidget(pb_mknSurucu    ,satr++,7,1,1,nullptr);


    //    QLabel *lB_mknSurucutar = new QLabel("Sürücü İşe Başlama");
    //    mapperL->addWidget(lB_mknSurucutar  ,satr,4,1,1,nullptr);
    //    clndr_mknSurucutar = new QDateTimeEdit(QDate::currentDate());
    //    clndr_mknSurucutar->setMinimumDate(QDate(1900, 1, 1));
    //    clndr_mknSurucutar->setMaximumDate(QDate(2023, 1, 1));
    //    clndr_mknSurucutar->setDisplayFormat("dd.MM.yyyy");
    //    clndr_mknSurucutar->setCalendarPopup(true);
    //    mapperL->addWidget(clndr_mknSurucutar   ,satr++,5,1,3,nullptr);
    //    MKNmapper->addMapping(clndr_mknSurucutar, MKNmodel->fieldIndex("mkn_surucu_tar"));

    //    QLabel *lB_mknBirim = new QLabel("Birim   ");
    //    cbx_mknBirim  = new QComboBox;
    //    pb_mknBirim = new QPushButton;
    //    connect( pb_mknBirim, &QPushButton::clicked, this, &Cw_mkn::birim);
    //    mapperL->addWidget(lB_mknBirim   ,satr,4,1,1,nullptr);
    //    mapperL->addWidget(cbx_mknBirim  ,satr,5,1,2,nullptr);
    //    mapperL->addWidget(pb_mknBirim   ,satr,7,1,1,nullptr);
    //    lB_mknBirim->setBuddy(cbx_mknBirim);
    //    MKNmapper->addMapping(cbx_mknBirim, MKNmodel->fieldIndex("mkn_birim"));

    //    QLabel *lB_mknByer = new QLabel("Bulunduğu Yer ");
    //    pb_mknByer = new QPushButton;
    //    connect( pb_mknByer, &QPushButton::clicked, this, &Cw_mkn::byer);
    //    mapperL->addWidget(lB_mknByer   ,satr,0,1,1,nullptr);
    //    cbx_mknByer  = new QComboBox;
    //    mapperL->addWidget(cbx_mknByer  ,satr,1,1,2,nullptr);
    //    mapperL->addWidget(pb_mknByer   ,satr++,3,1,1,nullptr);
    //    lB_mknByer->setBuddy(cbx_mknByer);
    //    MKNmapper->addMapping(cbx_mknByer, MKNmodel->fieldIndex("mkn_byer"));

    //    QLabel *lB_mknAcklm = new QLabel("Açıklama   ");
    //    mapperL->addWidget(lB_mknAcklm    ,satr,0,1,1,nullptr);
    //    ted_mknAcklm = new QTextEdit();
    //    mapperL->addWidget(ted_mknAcklm   ,satr,1,1,4,nullptr);
    //    lB_mknAcklm->setBuddy(ted_mknAcklm);
    //    MKNmapper->addMapping(ted_mknAcklm, MKNmodel->fieldIndex("mkn_aciklama"));

    //    lB_resim = new QLabel;
    //    lB_resim->setFixedSize(200,110);
    //    mapperL->addWidget(lB_resim   ,++satr,5,1,4,nullptr);
    //    MKNmapper->addMapping(lB_resim , MKNmodel->fieldIndex("mkn_resim"));
    //    rsm_ByteArray = new QByteArray;
    //    *rsm_ByteArray = "";

    //    //        MKNmapper->addMapping(*rsm_ByteArray, MKNmodel->fieldIndex("resim"));
    //    //MKNmapper->addMapping(led_rating, MKNmodel->fieldIndex("rating"));


    //    //    /// yeni ekle penceresine girerken index ne
    //    //    QModelIndex mknndx = MKNtview->currentIndex ();
    //    //    //MKNmapper->toFirst ();
    //    //    MKNmapper->setCurrentIndex( mknndx.row ()) ;
    //    int sutn=0;
    //    //   satr +=2;
    //    // mapperL->addWidget( MKNtview   ,++satr,0,2,7,nullptr);
    //    //satr+=5;
    //    //qDebug ()<<"model yıı 222";
    //    QPushButton *pb_ilk = new QPushButton("İlk");
    //    connect( pb_ilk, &QPushButton::clicked,
    //             MKNmapper, &QDataWidgetMapper::toFirst );
    //    mapperL->addWidget( pb_ilk   ,satr+=2,sutn++,1,1,nullptr);

    //    QPushButton *pb_pr = new QPushButton("Önceki");
    //    connect( pb_pr, &QPushButton::clicked,
    //             MKNmapper, &QDataWidgetMapper::toPrevious );
    //    mapperL->addWidget( pb_pr   ,satr,sutn++,1,1,nullptr);

    //    QPushButton *pb_lr = new QPushButton("Sonraki");
    //    connect( pb_lr, &QPushButton::clicked,
    //             MKNmapper, &QDataWidgetMapper::toNext );
    //    mapperL->addWidget( pb_lr   ,satr,sutn++,1,1,nullptr);

    //    QPushButton *pb_ls = new QPushButton("Son");
    //    connect( pb_ls, &QPushButton::clicked,
    //             MKNmapper, &QDataWidgetMapper::toLast );
    //    mapperL->addWidget( pb_ls   ,satr,sutn++,1,1,nullptr);

    //    pb_rsmEkle = new QPushButton("Resim Ekle");
    //    connect( pb_rsmEkle, &QPushButton::clicked,
    //             this, &Cw_mkn::resimEkle);
    //    mapperL->addWidget( pb_rsmEkle   ,satr,sutn++,1,1,nullptr);


    //    QPushButton *pb_yn = new QPushButton("Yeni Ekle");
    //    connect( pb_yn, &QPushButton::clicked,
    //             this, &Cw_mkn::clk_boshMKN );
    //    mapperL->addWidget( pb_yn   ,satr,sutn+=2,1,1,nullptr);

    //    QPushButton *pb_vzgc = new QPushButton("Vazgeç");
    //    connect( pb_vzgc, &QPushButton::clicked,
    //             wdgt_mppr, &QWidget::close );
    //    mapperL->addWidget( pb_vzgc   ,satr++,9,1,1,nullptr);


}       ///      onmnMKN_MKNekle



void Cw_mkn::clk_boshMKN()
{qDebug()<<"boşmkn 1";
    /// yeni makina kaydı için
    /// sahaları boşaltalım
    led_mknKurumno->setText("")     ;
    led_mknPlaka->setText("")   ;
    cbx_mknCins->setCurrentIndex (0) ;
    cbx_mknMark->setCurrentIndex (0) ;
    cbx_mknModl->setCurrentIndex (0) ;

    spn_mknYil->setValue(0)     ;
    led_mknSase->setText("")  ;
    led_mknMotor->setText("") ;
    led_mknMtip->setText("")  ;
    cbx_mknYkt->setCurrentIndex (0)     ;
    cbx_mknSurucu->setCurrentIndex (0)   ;
    clndr_mknSurucutar->setDate(QDate::currentDate());
    cbx_mknBirim->setCurrentIndex (0) ;
    ted_mknAcklm->setText ("")  ;
    cbx_mknByer->setCurrentIndex (0)  ;
    *rsm_ByteArray           ="";

    Cw_mkn::MKNekle();

}



void Cw_mkn::MKNekle()
{
    qDebug()<<"mknekle 1";
    QSqlQuery q;
    QString s_q;
    s_q="INSERT INTO dbtb_mkn "
        "( mkn_kurumno , mkn_plaka   , mkn_cinsi , mkn_marka     ,"
        "  MKNmodeli  , mkn_yil     , mkn_saseno, mkn_motorno   ,"
        "  mkn_motortip, mkn_yakit   , mkn_surucu, mkn_surucutar,"
        "  mkn_birim   , mkn_aciklama, mkn_byer  , mkn_resim   , "
        "  mkn_rating"
        " )"
        " values(:a,:b,:c,:d,"
        ":e,:f,:g,:h,"
        ":i,:j,:k,:l,"
        ":m,:n,:o,:p,"
        ":r "
        ")"  ;
    q.prepare(s_q);
    q.bindValue(":a", ""); //led_mknKurumno->text()   );
    q.bindValue(":b", ""); //led_mknPlaka->text() );
    q.bindValue(":c", 0); //cbx_mknCins->currentIndex () );
    q.bindValue(":d", 0); //cbx_mknMark->currentIndex () );
    q.bindValue(":e", 0); //cbx_mknModl->currentIndex () );
    q.bindValue(":f", 0); //spn_mknYil->text() );
    q.bindValue(":g", ""); //led_mknSase->text() );
    q.bindValue(":h", ""); //led_mknMotor->text() );
    q.bindValue(":i", ""); //led_mknMtip->text() );
    q.bindValue(":j", 0); //cbx_mknYkt->currentIndex ()  );
    q.bindValue(":k", 0); //cbx_mknSurucu->currentIndex () );
    q.bindValue(":l", clndr_mknSurucutar->text() );
    q.bindValue(":m", 0); //cbx_mknBirim->currentIndex () );
    q.bindValue(":n", ""); //ted_mknAcklm->toPlainText () );
    q.bindValue(":o", 0); //cbx_mknByer->currentIndex () );
    q.bindValue(":p", *rsm_ByteArray ) ;
    q.bindValue(":r", "1" ) ;

    q.exec();

    if (q.isActive())
    {
        qDebug () <<"Demirbaş Ambarı - Yeni Kayıt Eklendi";
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        msgBox.setWindowTitle("KAYIT EKLENDİ                               -");
        msgBox.setText("Demirbaş Ambarı\n"
                       "Kayıt Eklendi ...");
        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            //wdgt_mppr ->close();
        }


        MKNmodel->select();
        MKNmapper->toLast ();

    }
    else
    {
        qDebug () << "HATA - Demirbaş Ambarı - Yeni Kayıt "
                     "Eklenemedi - " << q.lastError() <<
                     q.lastQuery();

        /// help QMessageBox
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        //    QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);
        //
        //      pb_tmm->setText ("TÜM MAKİNA İKMAL KAYITLARINI SİL");
        msgBox.setText("    !! HATA !!\n"
                       "Kayıt Eklenemedi ?...\n"
                       + q.lastError().text()+"\n"+
                       q.lastQuery());
        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            //yeniekle->close();
        }
    }
}


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

void Cw_mkn::resimEkle()
{

    // makina stok resim ekle
    QString myfile = QFileDialog::
            getOpenFileName(wdgt_mppr,
                            tr("Resim Aç"), "/home/mr/Resimler",
                            tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
                               " ;; Tüm Dosyalar (*,*)"));

    if (myfile == "")
        return;

    QImage image(myfile);
    lB_resim->setPixmap(QPixmap::fromImage(image));


    QFile file(  myfile ); //dosyayı açmak için al

    if ( file.open(QIODevice::ReadOnly))
    {
        *rsm_ByteArray = file.readAll();
    }

}


////////////////////////////////////////////
///
///
///
//// EKLE_IE
///
///
///
///
///


//////////////////////////////////////////////////////////
///
///
///
///
///     İş Emri Ekle
///
///
///
///




void Cw_mkn::onmnMKN_IEekle()
{

    /// ekle işemri widget
    QWidget *wdgt_IEekle = new QWidget;
    wdgt_IEekle->setWindowTitle("İş Emri Yeni Kayıt");
    wdgt_IEekle->setVisible(false);
    wdgt_IEekle->show();

    auto *IEL = new QGridLayout;
    wdgt_IEekle->setLayout(IEL);

    int satr = 0;
    QLabel *lB_IEno = new QLabel("İş Emri No     ");
    IEL->addWidget(lB_IEno        ,satr,0,1,1,nullptr);

    lE_IEno = new QLineEdit;
    lE_IEno->setReadOnly (true);
    //lE_IEno->setText (*IEno);
    IEL->addWidget(lE_IEno   ,satr++,1,1,3,nullptr);
    lB_IEno->setBuddy(lE_IEno);
    Cwv_IsEmri->IEmapper->addMapping(lE_IEno,
                                     Cwv_IsEmri->IEmodel->fieldIndex("ie_ie_no"));

    QLabel *lB_tr = new QLabel("İş Emri Tarihi");
    IEL->addWidget(lB_tr        ,satr,0,1,1,nullptr);
    dE_IEtarih = new QDateTimeEdit(QDate::currentDate());
    dE_IEtarih->setDisplayFormat("dd.MM.yyyy");
    dE_IEtarih->setMinimumDate(QDate(01, 01, 1900));
    dE_IEtarih->setMaximumDate(QDate(valiDDate));
    dE_IEtarih->setCalendarPopup(true);
    IEL->addWidget(dE_IEtarih   ,satr++,1,1,3,nullptr);
    lB_tr->setBuddy(dE_IEtarih);


    QLabel *lB_bl = new QLabel("Bölüm");
    IEL->addWidget(lB_bl        ,satr,0,1,1,nullptr);
    cbx_IEbolum = new QComboBox;
    pb_IEbolum= new QPushButton("+");
    IEL->addWidget(cbx_IEbolum  ,satr,1,1,3,nullptr);
    IEL->addWidget(pb_IEbolum   ,satr++,4,1,1,nullptr);
    lB_bl->setBuddy(cbx_IEbolum );

    QLabel *lB_dr = new QLabel("İş Emri Durum");
    IEL->addWidget(lB_dr        ,satr,0,1,1,nullptr);
    cbx_IEdurum = new QComboBox;
    cbx_IEdurum->addItem ("-");
    cbx_IEdurum->addItem ("Araç Bekliyor");
    cbx_IEdurum->addItem ("Arıza Tespiti Yapılıyor");
    cbx_IEdurum->addItem ("Usta Bekliyor");
    cbx_IEdurum->addItem ("Parça Bekliyor");
    cbx_IEdurum->addItem ("Tamamlandı");
    IEL->addWidget(cbx_IEdurum   ,satr++,1,1,3,nullptr);
    lB_dr->setBuddy(cbx_IEdurum);


    QLabel *lB_gt = new QLabel("Araç Giriş Tarihi");
    IEL->addWidget(lB_gt        ,satr,0,1,1,nullptr);
    dE_IEgirtarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEgirtarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEgirtarihi->setMinimumDate(QDate(01, 01, 1900));
    dE_IEgirtarihi->setMaximumDate(QDate(valiDDate));
    dE_IEgirtarihi->setCalendarPopup(true);
    IEL->addWidget(dE_IEgirtarihi   ,satr++,1,1,3,nullptr);
    lB_gt->setBuddy(dE_IEgirtarihi);


    QLabel *lB_ct = new QLabel("Araç Çıkış Tarihi");
    IEL->addWidget(lB_ct        ,satr,0,1,1,nullptr);
    dE_IEciktarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEciktarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEciktarihi->setMinimumDate(QDate (01, 01, 1900));
    dE_IEciktarihi->setMaximumDate(QDate ( valiDDate ));
    dE_IEciktarihi->setCalendarPopup(true);
    IEL->addWidget(dE_IEciktarihi   ,satr++,1,1,3,nullptr);
    lB_ct->setBuddy(dE_IEciktarihi);

    QLabel *lB_y1 = new QLabel("Yetkili 1");
    IEL->addWidget(lB_y1        ,satr,0,1,1,nullptr);
    cbx_IEyetkili1 = new QComboBox;                      // dbtb_clsn
    IEL->addWidget(cbx_IEyetkili1   ,satr,1,1,3,nullptr);
    lB_y1->setBuddy(cbx_IEyetkili1);
    QPushButton *pb_y1 = new QPushButton("+");
    IEL->addWidget(pb_y1   ,satr++,4,1,1,nullptr);
    connect (pb_y1, &QPushButton::clicked, this, &Cw_mkn::clk_IEclsn);

    QLabel *lB_y2 = new QLabel("Yetkili 2");
    IEL->addWidget(lB_y2        ,satr,0,1,1,nullptr);
    cbx_IEyetkili2 = new QComboBox;                        // dbtb_clsn
    IEL->addWidget(cbx_IEyetkili2   ,satr,1,1,3,nullptr);
    lB_y2->setBuddy(cbx_IEyetkili2);
    QPushButton *pb_y2 = new QPushButton("+");
    IEL->addWidget(pb_y2   ,satr++,4,1,1,nullptr);
    connect (pb_y2, &QPushButton::clicked, this, &Cw_mkn::clk_IEclsn);

    /*   QLabel *lB_yy = new QLabel("Yapıldığı Yer");
    IEL->addWidget(lB_yy        ,9,0,1,1,nullptr);
    cbx_IEyapyer = new QComboBox;                   //dbtb_yer
    cbx_IEyapyer->addItem ("-");
    cbx_IEyapyer->addItem ("Atölye");
    cbx_IEyapyer->addItem ("Arazi");
    cbx_IEyapyer->addItem ("Serbest Piyasa");
    cbx_IEyapyer->addItem ("Yetkili Servis");
    IEL->addWidget(cbx_IEyapyer   ,9,1,1,3,nullptr);
    lB_yy->setBuddy(cbx_IEyapyer);

    IEL->addWidget(cbx_IEyapyer   ,9,1,1,3,nullptr);
    QPushButton *pb_yy = new QPushButton("+");
    IEL->addWidget(pb_yy   ,9,4,1,1,nullptr);
    connect (pb_yy, &QPushButton::clicked, this, &Cw_mkn::clk_IEyyer);
*/
    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydetIE = new QPushButton("Yeni Ekle");
    connect (pb_kaydetIE, &QPushButton::clicked,
             this, &Cw_mkn::clk_boshIE );
    IEL->addWidget(pb_kaydetIE        ,satr,7,1,1,nullptr);

    QPushButton *pb_vzgcIE = new QPushButton("Vazgeç");
    connect (pb_vzgcIE, &QPushButton::clicked, wdgt_IEekle, &QWidget::close );
    IEL->addWidget(pb_vzgcIE        ,satr,6,1,1,nullptr);





    Cwv_IsEmri->IEmapper->addMapping(dE_IEtarih , Cwv_IsEmri->IEmodel->fieldIndex("ie_tarih"));
    Cwv_IsEmri->IEmapper->addMapping(cbx_IEbolum , Cwv_IsEmri->IEmodel->fieldIndex("ie_bolum"));
    Cwv_IsEmri->IEmapper->addMapping(cbx_IEdurum, Cwv_IsEmri->IEmodel->fieldIndex("ie_durum"));
    Cwv_IsEmri->IEmapper->addMapping(dE_IEgirtarihi , Cwv_IsEmri->IEmodel->fieldIndex("ie_girtar"));
    Cwv_IsEmri->IEmapper->addMapping(dE_IEciktarihi , Cwv_IsEmri->IEmodel->fieldIndex("ie_ciktar"));
    Cwv_IsEmri->IEmapper->addMapping(cbx_IEyetkili1, Cwv_IsEmri->IEmodel->fieldIndex("ie_yetkili1"));
    Cwv_IsEmri->IEmapper->addMapping(cbx_IEyetkili2, Cwv_IsEmri->IEmodel->fieldIndex("ie_yetkili2"));


    /// yeni ekle IE penceresine girerken index ne
    //        QModelIndex mknndx = MKNtview->currentIndex ();
    //      Cwv_IsEmri->IEmapper->setCurrentIndex( mknndx.row ()) ;

    QPushButton *pb_ilk = new QPushButton("İlk");
    connect( pb_ilk, &QPushButton::clicked,
             Cwv_IsEmri->IEmapper, &QDataWidgetMapper::toFirst );
    IEL->addWidget( pb_ilk   ,satr,1,1,1,nullptr);

    QPushButton *pb_pr = new QPushButton("Önceki");
    connect( pb_pr, &QPushButton::clicked,
             Cwv_IsEmri->IEmapper, &QDataWidgetMapper::toPrevious );
    IEL->addWidget( pb_pr   ,satr,2,1,1,nullptr);

    QPushButton *pb_lr = new QPushButton("Sonraki");
    connect( pb_lr, &QPushButton::clicked,
             Cwv_IsEmri->IEmapper, &QDataWidgetMapper::toNext );
    IEL->addWidget( pb_lr   ,satr,3,1,1,nullptr);

    QPushButton *pb_ls = new QPushButton("Son");
    connect( pb_ls, &QPushButton::clicked,
             Cwv_IsEmri->IEmapper, &QDataWidgetMapper::toLast );
    /*pb_ls->setStyleSheet("QPushButton {"
                             "background color: rgb(125,125,125);"
                             "color           : rgb(125,0,125); "
                             "}");

    */
    IEL->addWidget( pb_ls   ,satr,4,1,1,nullptr);




}

void Cw_mkn::IEekle()
{
    // qDebug ()<<"ie ekle 8";
    ////////////////////////////////
    QSqlQuery q;
    QString s_q;
    s_q ="INSERT INTO dbtb_ie "
         "( ie_mkn_id, ie_ie_no   , ie_tarih   , ie_bolum  ,"
         "  ie_durum , ie_girtar  , ie_ciktar , ie_yetkili1,"
         "  ie_yetkili2 "
         " )"
         " values( ?, ? ,? ,? ,? ,? ,? ,? , ?  )"  ;
    q.prepare(s_q);

    q.bindValue(0, *MKNid );
    //   qDebug ()<<*MKNid;
    q.bindValue(1, lE_IEno->text ());
    //    qDebug ()<<lE_IEno->text ();
    q.bindValue(2, dE_IEtarih->text ());
    q.bindValue(3,  cbx_IEbolum->currentText ());
    q.bindValue(4,  cbx_IEdurum->currentText ());
    q.bindValue(5,  dE_IEgirtarihi->text());
    q.bindValue(6,  dE_IEciktarihi->text());
    q.bindValue(7,  cbx_IEyetkili1->currentText ());
    q.bindValue(8,  cbx_IEyetkili2->currentText ());

    //  qDebug ()<<"ie ekle 9";


    q.exec();
    //qDebug () << q.lastError();
    if (q.isActive())
    {

        Hata hata("İş Emri Yeni Kayıt",
                  "Yeni İş Emri Kaydı Eklendi","" );

        qDebug () <<"İş Emri Yeni Kayıt Eklendi - "<< lE_IEno->text() << " -   Eklendi";
        //MKNmapper->toLast;

    }
    else
    {
        qDebug () << "İş Emri Yeni Kayıt Eklenemedi - " << q.lastError() ;
    }




    wtab->setCurrentIndex(wtab->indexOf(wdgt_IE));
    Cwv_IsEmri->IEmodel->select();
    Cwv_IsEmri->IEtview->setFocus();
    //  qDebug ()<<"ie ekle 10";

    // iş emri ekle
    ///////////////////////////////////////////////////



}

void Cw_mkn::clk_boshIE()
{

    qDebug ()<<"ie ekle";
    // makinanın id ve kurum nosunu alalım

    //   QSqlRelationalTableModel *mkn;
    //  mkn = Cw_mkn::MKNmodel();

    MKNid = new QString;
    *MKNid = -1;
    //QSqlQuery q;
    QVariant ino = " " ;
    QModelIndex index = Cw_mkn::MKNtview->table->currentIndex();

    if (index.isValid())
    {
        // index ile recordu bulduk
        QSqlRecord record = MKNmodel->record(index.row());
        *MKNid = record.value("id_mkn").toString();

        ino = record.value("mkn_kurumno") ;
        qDebug ()<<"mkn id --- " << *MKNid << "-- kurum no   -- "<< ino;

    }
    else
    {
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"),
                                               QMessageBox::ActionRole);
        msgBox.setWindowTitle("KAYIT EKLEME HATASI                               -");
        msgBox.setText("İş Emri kaydı \n"
                       "Kayıt Eklenemedi ...");
        msgBox.setInformativeText("MKNtview index is invalid");        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {

            Hata hata("HATA - Kayıt Ekleme Hatası",
                      "İş Emri Kaydı Eklenemedi",
                      "MKNtview index is invalid");


            return;
        }
    }


    // IE_no yu oluşturalım
    QDate x(QDate::currentDate());

    // mkn_kurumNo + hangi yıl + yılın kaçıncı günündeyiz
    QString IE = ino.toString();
    IE.append(":");
    IE.append(QString::number( x.year()).rightRef(2));
    IE.append("~");
    IE.append(QString::number( x.dayOfYear())) ;
    IE.append("~");
    IE = IE.simplified();
    IEno = new QString ;
    *IEno = IE ;
    int IEcount = 1;
    // how mny-- records?

    qDebug ()<<"ie ekle 2";
    QSqlQuery query;
    query.prepare("SELECT * FROM dbtb_ie ");

    if (!query.exec())
    {
        qDebug() << "SQL error: "<< query.lastError().text() << endl;
    }
    else
    {
        QString lttl ="" ;
        query.first();
        while (query.next())
        {
            lttl= query.value("ie_ie_no").toString();
            lttl.chop(2);

            if (lttl == IE)
            {
                IEcount++;
            }
        }
    }
    ///// yeni ieno son hali
    *IEno += "0"+QString::number(IEcount);


    /// yeni IE iş emri kaydı için
    /// sahaları boşaltalım


    lE_IEno-> setText( *IEno ) ;
    dE_IEtarih->setDate(QDate::currentDate());
    cbx_IEbolum->setCurrentText ("");
    cbx_IEdurum->setCurrentText ("");
    dE_IEgirtarihi->setDate(QDate::currentDate());
    dE_IEciktarihi->setDate(QDate::currentDate());
    cbx_IEyetkili1->setCurrentText ("");
    cbx_IEyetkili2->setCurrentText ("");

    Cw_mkn::IEekle();
}



void Cw_mkn::clk_IEdurum()
{}

void Cw_mkn::clk_IEyyer()
{}

void Cw_mkn::clk_IEclsn()
{}




SKGComboBox::SKGComboBox(QWidget *parent) : QComboBox (parent)
{
}

SKGComboBox::~SKGComboBox()
= default;

QString SKGComboBox::text() const
{
    return this->currentText();
}

void SKGComboBox::setText (const QString& iText)
{
    int pos=this->findText(iText);
    if (pos==-1)
    {
        pos=0;
        insertItem(pos, iText);
    }
    setCurrentIndex(pos);
}
