#include "hc_hspdetay.h"
//#include "uniqueproxymodel.h"



hC_HSPDTY::hC_HSPDTY() : hC_tBcreator ()
{
    qDebug ()<<"Constructor HESAP DETAY **************************";
    //************************************************************
    //************  H E S A P  D E T A Y L A R I  ****************

    win_Label->setText ( "HESAP DETAY KAYITLARI");
    *tb_name   = "hspdty_dbtb" ;
    *tb_ndex  = "hspdty_ad";
    tb_flds = new hC_ArrD (10, 4);

    tb_flds->setValue ( 0, "f_hspdty_ID"      , "INTEGER", "hspdty_ID","0" ) ;
    // hesaplar ile hesap detay arası key
    tb_flds->setValue ( 1, "f_hspdty_hspID"   , "INTEGER", "hspdty_HesapID","0" ) ;
    tb_flds->setValue ( 2, "f_hspdty_tarih"   , "TEXT"   , "Tarih" );
    tb_flds->setValue ( 3, "f_hspdty_no"      , "TEXT"   , "Kayıt No" );
    tb_flds->setValue ( 4, "f_hspdty_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 5, "f_hspdty_transfer", "TEXT"   , "İlgili Hesap");
    tb_flds->setValue ( 6, "f_hspdty_r"       , "TEXT"   , "R");
    tb_flds->setValue ( 7, "f_hspdty_borc"    , "TEXT"   , "BORC");
    tb_flds->setValue ( 8, "f_hspdty_alacak"  , "TEXT"   , "ALACAK");
    tb_flds->setValue ( 9, "f_hspdty_resim"   , "BLOB"   , "Resim","0");

    tb_wdgts = new QList <QWidget*> ;

    tb_wdgts->append ( lE_hspdtyID  = new QLineEdit   ) ; //  id
    tb_wdgts->append ( lE_hspID  = new QLineEdit   ) ; // parent id
    tb_wdgts->append ( dE_tarih = new QDateEdit   ) ;
    tb_wdgts->append ( lE_no  = new QLineEdit   ) ;

    tb_wdgts->append ( lE_aciklama = new QLineEdit  ) ;
    // bağlantılı hesap
    tb_wdgts->append ( cB_transferHesap = new QComboBox ) ;
    // consilidate
    tb_wdgts->append ( lE_r = new QLineEdit  ) ;
    tb_wdgts->append ( lE_borc = new QLineEdit  ) ;
    tb_wdgts->append ( lE_alacak = new QLineEdit  ) ;

    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_HSPDTY::tbsetup()
{
    qDebug() << "0100 hspdty::tbsetup ------------------------- begins";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
    qDebug() << "0100 hspdty::tbsetup ------------------------- end";
}


void hC_HSPDTY::tbwdgt()
{
    qDebug() << "   0110 hspdty::tbwdgt ---- begin";



    //cls_mdl_TreeFromXml:: den hesap listesi gelecek


    auto *lB_tarih  = new QLabel("Açılış Tarihi"        );
    //  dE_tarih->setPlaceholderText ("Tarih");
    lB_tarih->setBuddy(dE_tarih);
    dE_tarih->setSpecialValueText ("  ");
    dE_tarih->setLocale (QLocale::Turkish);
    dE_tarih->setMinimumDate(QDate::currentDate().addYears (-25));
    dE_tarih->setMaximumDate(QDate::currentDate().addYears(25));
    dE_tarih->setDisplayFormat ("dd-MM-yyyy");
    dE_tarih->setCalendarPopup (true);
    lB_tarih->setBuddy(dE_tarih);

    auto *lB_no = new QLabel("Kayıt No"       );
    lB_no->setBuddy(lE_no);

    auto *lB_aciklama    = new QLabel("Açıklama" );
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_transfer    = new QLabel("Transfer Hesap" );
    auto *cB_transferHesap = new QComboBox;

    //cls_mdl_TreeFromXml:: den hesap listesi gelecek
//    win_hC_hsp = new hC_hsp;
//    proxyModel = new ProxyModel(this);
//    proxyModel->setSourceModel (win_hC_hsp->modelXML);
//    proxyModel->sort ( 0 , Qt::AscendingOrder);


//    delete cB_transferHesap->model ();
//    UniqueProxyModel *uniqueProxyModel = new UniqueProxyModel( 0 /*column*/,
//                                                              this);
//    uniqueProxyModel->setSourceModel(win_hC_hsp->modelXML);
//    cB_transferHesap->setModel (uniqueProxyModel);
//    cB_transferHesap->setModelColumn ( 0 /*column*/);

//    tb_view->table->setItemDelegateForColumn(3, cB_transferHesap );

    auto *lB_r = new QLabel("R"  );
    lB_r->setBuddy(lE_r);

    auto *lB_borc = new QLabel("BORC ");
    lB_borc->setBuddy(lE_borc);

    auto *lB_alacak  = new QLabel("ALACAK "  );
    lB_alacak->setBuddy(lE_alacak);


    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
    //   lB_ad->setMinimumSize (100,25);
    //  lE_ad->setMinimumSize (100,25);
    lB_aciklama->setMinimumSize (200,25);
    // lB_alacak->setMinimumSize (150,25);


    win_Grid->addWidget(lB_tarih      , 0, 0, 1, 1);
    win_Grid->addWidget(dE_tarih      , 0, 1, 1, 2);
    win_Grid->addWidget(lB_no     , 1, 0, 1, 1);
    win_Grid->addWidget(lE_no     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_aciklama        , 2, 0, 1, 1);
    win_Grid->addWidget(lE_aciklama        , 2, 1, 1, 2);
    win_Grid->addWidget(lB_transfer     , 3, 0, 1, 1);
    win_Grid->addWidget(cB_transferHesap     , 3, 1, 1, 2);
    win_Grid->addWidget(lB_r     , 4, 0, 1, 1);
    win_Grid->addWidget(lE_r     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_borc      , 5, 0, 1, 1);
    win_Grid->addWidget(lE_borc      , 5, 1, 1, 2);
    win_Grid->addWidget(lB_alacak    , 6, 0, 1, 1);
    win_Grid->addWidget(lE_alacak    , 6, 1, 1, 2);
    win_Grid->addWidget(cB_transferHesap    , 7, 1, 1, 2);

    //  xx2=1;
    win_Grid->addWidget(win_Rsm       , 7, 4, 3, 2);
    qDebug() << "   0110 hspdty::wdgt ---- end";
}


void hC_HSPDTY::tbui()
{

    qDebug() << "   0120 hspdty::tbui ---- begins";

    // yeni dosyada ilk kayıtta ilk yeni kodu verebilmek için
 //   *m_hesapID= Q_UINT64_C(1);

    hC_HSPDTY::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,1200,600);

    QSplitter *splitter = new QSplitter(this);
    splitter->setMinimumWidth(600);
  //  splitter->addWidget(win_hC_hsp);
    splitter->addWidget(tb_view);
    splitter->setOrientation (Qt::Vertical);

    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (splitter  , 0, 0, 1, 1);
    // win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);
    // win_grid->addWidget (win_hC_hsp   , 0, 0, 2, 1);
    qDebug() << "   0120 hspdty::tbui ---- end";
}



void hC_HSPDTY::debugger(QString num)
{
    curIndex = tb_view->table->currentIndex ();
    qDebug() << num+num+num
             << " rCnt =" <<  tb_model->rowCount()
             << "  r:" << tb_view->table->rowAt(0)
             << "  id:"<< tb_model->data(tb_model->index(curIndex.row (),
                                                         tb_model->fieldIndex ("hspdty_id")),Qt::DisplayRole).toString()
             << "  pid:"<<  tb_model->data(tb_model->index(curIndex.row (),
                                                           tb_model->fieldIndex ("hspdty_parentid")),Qt::DisplayRole).toString()
             << "  ad:"<<  tb_model->data(tb_model->index(curIndex.row (),
                                                          tb_model->fieldIndex ("hspdty_ad")),Qt::DisplayRole).toString()
             << "  lft:"<<  tb_model->data(tb_model->index(curIndex.row (),
                                                           tb_model->fieldIndex ("hspdty_lft")),Qt::DisplayRole).toString()
             << "  rgt:"<<  tb_model->data(tb_model->index(curIndex.row (),
                                                           tb_model->fieldIndex ("hspdty_rgt")),Qt::DisplayRole).toString()
             <<"  *-*\n"   ;
}


void hC_HSPDTY::tbkntrl()
{
    qDebug() << "   0130 hspdty::tbkntrl ---- begin";

//    cls_dlgt_ComboBox *cb = new cls_dlgt_ComboBox();

  //  tb_view->table->setItemDelegateForColumn(5, cb );

    qDebug() << "   0130 2" ;
    //////////////// filtering

    SGNDhesapKod = new qint64{};
    SGNDhesapAd  = new QString{};
    //// hesap kodu ve adını bulalım
//    TaskItem* current_hesap = win_hC_hsp->getCurrentItem();


//    if (current_hesap)
//        {
//            *SGNDhesapKod = current_hesap->hesapKod();
//            *SGNDhesapAd  = current_hesap->hesapAd();
//        }

    //////////////// filtering end
    tb_view->table->setFocus();

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked , this,
            [this]()
    {
        ////////////////////////////////////////////////
        /// \brief maxID
        ///
        /// Eklenecek kayıt için hdp_id oluştur.
        /// Dosyada bulunan max id yi bulur ve
        /// bir üstünü getirir
        ///
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
        ////////////////////////////////////////////////

         qDebug() << "   0130 2 ekle içi" ;

        QSqlQuery query;
        QString qStr, mesaj("");
     //   QString hesapLR = "";
qDebug() << "   0130 2 ekle içi         1" ;

        curIndex = tb_view->table->currentIndex ();
qDebug() << "   0130 2 ekle içi         2" ;
        reccount=tb_model->rowCount();
qDebug() << "   0130 2 ekle içi         3" ;
        qStr = QString("INSERT INTO "+*tb_name +
                       " ( f_hspdty_hspID) "
                       " values ( '"+
                       QString::number (*m_hesapID)+
                       "' )")  ;
qDebug() << "   0130 2 ekle içi         4" ;
        if ( !query.exec(qStr) )
        {
            mesaj = mesaj + "002x- İlk node e k l e n e m e d i ...\n/n"+
                    query.lastError().text ();
        }
        else
        {
            mesaj = mesaj + "Hesap Detay Kaydı eklendi - \n";
        }

qDebug() << "   0130 2 ekle içi submitall öncesi" ;

        if (tb_model->submitAll())
        {
            mesaj = mesaj +" -- SUBMITTED -- "    ;

            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
            ////////////////////////////////////////////////

        }
        else
        {
            mesaj = mesaj + " Hesap kaydı e k l e n e m e d i ."  ;
        }
            tb_view->table->setFocus();
        qDebug()<<mesaj ;
qDebug() << "   0130 2 ekle sonu" ;
    });// connect ekle sonu

    /////////////////////////////////////////////////////////////////////
    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked, this,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                     "resim", "ekle");
    });

    // -- 003   hspdty  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              this, [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked, this,
            [this]()
    {
        QModelIndex indx =   tb_view->table->currentIndex();
        if( indx.row() >= 0 )
        {
            qDebug()<< "Silinecek row no: "<< indx.row()+1;

            //         tb_view->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QString hspdtyID = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("hspdty_ID"))).toString ();

            QString hesapad = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("hspdty_ad"))).toString ();


            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL", hspdtyID+" - "+hesapad ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                QModelIndex indx2;
                if (tb_model->checkIndex(tb_view->table->model()->
                                         index(tb_view->table->currentIndex().row()  - 1, 0)))
                {
                    indx2= tb_view->table->model()->
                            index(tb_view->table->currentIndex().row()  - 1, 0);
                    qDebug() << "checkindex edddddddddddd";                }



                // remove the current index
                // pmodel->beginRemoveColumn();
                tb_model->removeRow(indx.row());
                //pmodel->endRemoveColumns();
                tb_model->select();
                tb_view->table->setSelectionMode (QAbstractItemView::SingleSelection);
                tb_view->table->setSelectionBehavior (QAbstractItemView::SelectRows);
                tb_view->table->scrollTo (indx2);
                tb_view->table->selectRow (indx2.row()-1);
                tb_view->table->scrollTo (indx2);
                tb_view->table->setSelectionBehavior (QAbstractItemView::SelectItems);

                //                QModelIndex indx2 = tb_view->table->model()->
                //                        index(tb_view->table->currentIndex().row()  - 1, 0);
                //                tb_view->table->selectionModel()->select(
                //                    indx2,QItemSelectionModel::ClearAndSelect);
                // tb_view->table->setCurrentIndex(indx2);
                // tb_view->table->edit(indx2);
            }
        }
    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              this, [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (!Index.isValid())
        {
            qDebug() <<"index is invalid - tb mappper setCurrentModelIndex";
        }

        //    hspdtyID = tb_model->data (tb_model->index (Index.row (),
        //       tb_model->fieldIndex ("hspdty_id"))).toInt ();
        //    hesapID = tb_model->data (tb_model->index (Index.row (),
        //   tb_model->fieldIndex ("hspdty_parentid"))).toInt ();

        // 011-02 hesap row değiştiğinde hesap id yi etrafa yayınlayalım
        //   emit hC_HSPDTY::sgnHsp(tb_view->table->model()->index( Index.row() ,
        //         tb_model->fieldIndex (hspdtyid) ).data().toInt() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged, this,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);


    });

    /// hesap tan signal ile yollanana
  //  connect(win_hC_hsp, &hC_hsp::sgnHesap,
    //        this , &hC_HSPDTY::slt_tbx_rowChange);


    qDebug() << "   0130 hspdty::tbkntrl ---- end";
}


void hC_HSPDTY::showEvent(QShowEvent *)
{
    qDebug() << "   0140 hspdty::showevent ";
}

void hC_HSPDTY::closeEvent(QCloseEvent *)
{
    //win_hC_hsp->close ();
}

void hC_HSPDTY::slt_tbx_rowChange(TaskItem *currHspItem)
{
    currentHesapItem = currHspItem;
    qDebug() << "   0150 hspdty::slt_tbx_rowChange ";
    *m_hesapID = currHspItem->hesapKod ();
    *m_hesapAd = currHspItem->hesapAd ();
   // tb_model->setFilter("f_hspdty_hspID="+ QString::number(sgnHspID));
    tb_model->setFilter(
        QString("f_hspdty_hspID = %1").arg (*m_hesapID) );
}




hC_HSPDTY::~hC_HSPDTY()
{
    //delete max_id;
    qDebug() << "   0199 hspdty:: ~ ";
    //delete
}

/*

/// left right ile tree oluşturma
///

#include "hc_hspdetay.h"
#include "libs/hc_.h"


hC_HSPDTY::hC_HSPDTY() : hC_tBcreator ()
{
    qDebug ()<<"Constructor HESAP DETAY **************************";
    //-************************************************************
    //-************  H E S A P  D E T A Y L A R I  ****************

    win_Label->setText ( "HESAP DETAY KAYITLARI");
    *tb_name   = "hsp_dbtb" ;
    *tb_ndex  = "hsp_ad";
    qDebug ()<<"C2";
    tb_flds = new hC_ArrD (13, 4);
    tb_flds->setValue ( 0, "hsp_ID"      , "INTEGER", "hspdtyID", "0" ) ;
    tb_flds->setValue ( 1, "hsp_parentID", "INTEGER", "HspParentID" ) ;
    tb_flds->setValue ( 2, "hsp_lft"     , "INTEGER"   , "LEFT");
    tb_flds->setValue ( 3, "hsp_rgt"     , "INTEGER"   , "RIGHT");
    tb_flds->setValue ( 4, "hsp_ad"      , "TEXT"   , "Hesap Adı" );
    tb_flds->setValue ( 5, "hsp_tarih"   , "TEXT"   , "Açılış Tarihi" );
    tb_flds->setValue ( 6, "hsp_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 7, "hsp_parabrm" , "TEXT"   , "Birim");
    tb_flds->setValue ( 8, "hsp_not"     , "TEXT"   , "Not");
    tb_flds->setValue ( 9, "hsp_gizli"   , "TEXT"   , "Gizli");
    tb_flds->setValue (10, "hsp_toplu"   , "TEXT"   , "Toplu");
    tb_flds->setValue (11, "hsp_turu"    , "TEXT"   , "Türü");

    tb_flds->setValue (12, "hsp_resim"   , "BLOB"   , "Resim");
qDebug ()<<"C3";
    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( lE_pid  = new QLineEdit   ) ; // parent id
    tb_wdgts->append ( lE_lft = new QLineEdit ) ;
    tb_wdgts->append ( lE_rgt = new QLineEdit ) ;

    tb_wdgts->append ( lE_ad  = new QLineEdit   ) ;
    tb_wdgts->append ( dE_tarih = new QDateEdit   ) ;
    tb_wdgts->append ( lE_aciklama = new QLineEdit  ) ;
    tb_wdgts->append ( cB_parabrm = new QComboBox ) ;
    tb_wdgts->append ( lE_not = new QLineEdit  ) ;
    tb_wdgts->append ( lE_gizli = new QLineEdit  ) ;
    tb_wdgts->append ( lE_toplu = new QLineEdit  ) ;
    tb_wdgts->append ( cB_turu = new QComboBox   ) ;
qDebug ()<<"C4";
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;
qDebug ()<<"C5";
}


void hC_HSPDTY::tbsetup()
{
    qDebug() << "   hsp setup ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );


    tbwdgt  ();

    tbui();

    tbkntrl ();

}


void hC_HSPDTY::tbui()
{

    qDebug() << "   ui";

  //  tb_treeview = new hC_tree;
 //   tb_treeview->show();

    hC_HSPDTY::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,800,400);
    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (tb_view  , 0, 2, 1, 1);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);
//    win_grid->addWidget (tb_treeview   , 0, 0, 1, 1);
}
void hC_HSPDTY::tbwdgt()
{
    qDebug() << "   wdgt";

    auto *lB_ad = new QLabel("Hesap Adı"       );
    lB_ad->setBuddy(lE_ad);

    auto *lB_tarih  = new QLabel("Açılış Tarihi"        );
    //  dE_tarih->setPlaceholderText ("Tarih");
    lB_tarih->setBuddy(dE_tarih);
    dE_tarih->setSpecialValueText ("  ");
    dE_tarih->setLocale (QLocale::Turkish);
    dE_tarih->setMinimumDate(QDate::currentDate().addYears (-25));
    dE_tarih->setMaximumDate(QDate::currentDate().addYears(25));
    dE_tarih->setDisplayFormat ("dd-MM-yyyy");
    dE_tarih->setCalendarPopup (true);
    lB_tarih->setBuddy(dE_tarih);

    auto *lB_aciklama    = new QLabel("Açıklama" );
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_parabrm = new QLabel("Para Birimi"       );

    auto *lB_not = new QLabel("Not "  );
    lB_not->setBuddy(lE_not);

    auto *lB_gizli = new QLabel("Gizli ");
    lB_gizli->setBuddy(lE_gizli);

    auto *lB_toplu  = new QLabel("Toplu "  );
    lB_toplu->setBuddy(lE_toplu);

    auto *lB_turu = new QLabel("Hesap Türü" );
    auto *lB_lft   = new QLabel("LEFT" );
    auto *lB_rgt   = new QLabel("RIGHT" );

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
    //   lB_ad->setMinimumSize (100,25);
    //  lE_ad->setMinimumSize (100,25);
    lB_aciklama->setMinimumSize (200,25);
    // lB_alacak->setMinimumSize (150,25);


    win_Grid->addWidget(lB_ad      , 0, 0, 1, 1);
    win_Grid->addWidget(lE_ad      , 0, 1, 1, 2);
    win_Grid->addWidget(lB_tarih     , 1, 0, 1, 1);
    win_Grid->addWidget(dE_tarih     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_aciklama        , 2, 0, 1, 1);
    win_Grid->addWidget(lE_aciklama        , 2, 1, 1, 2);
    win_Grid->addWidget(lB_parabrm     , 3, 0, 1, 1);
    win_Grid->addWidget(cB_parabrm     , 3, 1, 1, 2);
    win_Grid->addWidget(lB_not     , 4, 0, 1, 1);
    win_Grid->addWidget(lE_not     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_gizli      , 5, 0, 1, 1);
    win_Grid->addWidget(lE_gizli      , 5, 1, 1, 2);
    win_Grid->addWidget(lB_toplu    , 6, 0, 1, 1);
    win_Grid->addWidget(lE_toplu    , 6, 1, 1, 2);
    win_Grid->addWidget(lB_turu     , 7, 0, 1, 1);
    win_Grid->addWidget(cB_turu     , 7, 1, 1, 2);
    win_Grid->addWidget(lB_lft     , 8, 0, 1, 1);
    win_Grid->addWidget(lE_lft     , 8, 1, 1, 2);
    win_Grid->addWidget(lB_rgt     , 9, 0, 1, 1);
    win_Grid->addWidget(lE_rgt     , 9, 1, 1, 2);

    //  xx2=1;
    win_Grid->addWidget(win_Rsm       , 7, 4, 3, 2);

}

void hC_HSPDTY::debugger(QString num)
{
    curIndex = tb_view->table->currentIndex ();
    qDebug() << num+num+num
             << " rCnt =" <<  tb_model->rowCount()
             << "  r:" << tb_view->table->rowAt(0)
             << "  id:"<< tb_model->data(tb_model->index(curIndex.row (),
                   tb_model->fieldIndex ("hsp_id")),Qt::DisplayRole).toString()
             << "  pid:"<<  tb_model->data(tb_model->index(curIndex.row (),
                         tb_model->fieldIndex ("hsp_parentid")),Qt::DisplayRole).toString()
             << "  ad:"<<  tb_model->data(tb_model->index(curIndex.row (),
                    tb_model->fieldIndex ("hsp_ad")),Qt::DisplayRole).toString()
             << "  lft:"<<  tb_model->data(tb_model->index(curIndex.row (),
                     tb_model->fieldIndex ("hsp_lft")),Qt::DisplayRole).toString()
             << "  rgt:"<<  tb_model->data(tb_model->index(curIndex.row (),
                      tb_model->fieldIndex ("hsp_rgt")),Qt::DisplayRole).toString()
             <<"  *-*\n"   ;
}


void hC_HSPDTY::tbkntrl()
{

    tb_view->table->setFocus();
    //tb_slctnModel->select( tb_model->index(0,0));
    tb_view->table->setFocus();
    qDebug() << "  hsp KNTRL";
    //debugger("1");

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
                ////////////////////////////////////////////////
                /// \brief maxID
                ///
                /// Eklenecek kayıt için hdp_id oluştur.
                /// Dosyada bulunan max id yi bulur ve
                /// bir üstünü getirir
                ///
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
        ////////////////////////////////////////////////

        QSqlQuery query;
        QString qStr, mesaj("");
        QString hesapLR = "";

        // curIndex = tb_view->table->model()->index(0, 0);
        curIndex = tb_view->table->currentIndex ();
        reccount=tb_model->rowCount();

        if ( reccount == 0 ) //DOSYADA KAYIT YOK
        {
            /////////////////////////////////////////
            /// node eklerken 3 ayrı durum vardır
            ///
            /// DOSYADA KAYIT YOK İLK KAYDI EKLE
            ///
            ///         root node
            /// 01    * Dosya BOŞ ilk node oluştur
            ///         left her zaman 1 dir
            ///         right 2 dir. node eklendikçe değişir
            ///
            /// DOSYADA KAYIT VAR LEAF VEYA NODE KAYDI EKLE
            ///
            ///         leaf node
            /// 02    * altında node olmayan node
            ///         left = left + 1 dir
            /// 03    * altında leaf OLAN node
            ///         left != left + 1
            ///

            // DOSYA BOŞ İLK KAYIT EKLE
            hspdtyID = 1; // max_id ilk 1
            hesapID = 0; // root node
            hesapAd = "1-2-" ; // 1-2
            hesapLR = "1-2-" ;
            hesapLeft  = 1 ;
            hesapRight = 2 ;

            //   qDebug()<<"001 Dosyaya ilk kayıt ekleniyor...";
// Dosyaya 1. kaydı ekle
/// Dosyaya ilk kayıt durumunda lft=1 rgt=2 olacak

            qStr = QString("INSERT INTO "+*tb_name +
                          " ( hsp_id, hsp_parentid,"
                          " hsp_ad, hsp_lft, hsp_rgt ) "
                          " values ( '1', '0', "
                          " '1-2*', 1, 2 )");

            if ( !query.exec(qStr) )
            {
                mesaj = mesaj + "002x- İlk node e k l e n e m e d i ...\n/n"+
                                query.lastError().text ();
            }
            else
            {
            //    debugger("3");
                mesaj = mesaj + "002- İlk node eklendi - " + hesapLR +"\n";
            }

        }
        else // DOSYADA KAYIT VAR
        {

            hspdtyID = tb_model->data (tb_model->index (curIndex.row (),
                      tb_model->fieldIndex ("hsp_id"))).toInt ();
            hesapID = tb_model->data (tb_model->index (curIndex.row (),
                            tb_model->fieldIndex ("hsp_parentid"))).toInt ();
            hesapAd = tb_model->data (tb_model->index (curIndex.row (),
                      tb_model->fieldIndex ("hsp_ad"))).toString ();
            hesapLeft  = tb_model->data (tb_model->index (curIndex.row (),
                         tb_model->fieldIndex ("hsp_lft"))).toInt ();
            hesapRight = tb_model->data (tb_model->index (curIndex.row (),
                         tb_model->fieldIndex ("hsp_rgt"))).toInt();


           // debugger("2");


            ///////////////////////////////////////////////////////
            if (hesapRight-hesapLeft == 1 ) // LEAF EKLE
            {
                /// eklemek istediğimiz node un altında
                /// child Y O K S A
                ///

                /// diğer right ları 2 artır
                qStr = QString("UPDATE %1 SET hsp_rgt = hsp_rgt + 2 "
                               "WHERE hsp_rgt >= %2 ")
                           .arg(*tb_name).arg(hesapRight) ;
                ///        .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Rights  artırıl a m a d ı . . . \n"+
                            "-3-----------------------------------\n"+
                            query.lastError().text ()+
                            "-31-----------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + " +" ;
                }
                ////// diğer left leri 2 artır
                qStr =  QString("UPDATE %1 SET hsp_lft = hsp_lft + 2 "
                               "WHERE hsp_lft > %2 ")
                           .arg(*tb_name).arg(hesapRight) ;
                ///        .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Lefts +2 artırıl a m a d ı . . . .\n"+
                            "--02----------------------------------\n"+
                            query.lastError().text ()+
                            "--021----------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + "1 " ;

                }

                hesapLR = "'" + QString::number(hesapRight+1) +" --- "+
                          QString::number(hesapRight+2) + "'";

                //qDebug()<<"<hesapLR "<< hesapLR << ">";
                /// yeni node oluştur
                qStr = QString("INSERT INTO "+*tb_name
                               +" (hsp_id, hsp_parentid, "
                                 "hsp_ad, hsp_lft, hsp_rgt ) "
                                 "values ( "+ QString::number(*max_id) +
                               " , "+QString::number(hspdtyID)+
                               ", "+hesapLR+" , %5, %6 )")
                           .arg(hesapLeft+1)
                           .arg(hesapLeft+2) ;



                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Yeni node e k l e n e m e d i \n"+
                            "-4-----------------------------------\n"+
                            query.lastError().text ()+
                            "--41----------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + "LEAF ADDED\n";
//                    hesapID = hspdtyID;
//                    hspdtyID = *max_id ;

//                    hesapAd = "1-2-" ;
//                    hesapLR = "1-2-" ;
//                    hesapLeft  = hesapLeft+1 ;
//                    hesapRight = hesapLeft+2 ;
//                    mesaj = mesaj  + "Leaf added";
//                    debugger("4");
                }
            }
            /////////////////////////////////////////////////////////
            else // NODE EKLE
            {
                /// eklemek istediğimiz node un altında
                /// child V A R S A
                ///
 ;
                qStr = QString("UPDATE %1 SET hsp_rgt = hsp_rgt + 2 "
                               "WHERE hsp_rgt >= %2 ")
                           .arg(*tb_name).arg(hesapRight) ;
                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "HATA +2 rights at nodes\n"+
                            "-3----------------------------------\n"+
                            query.lastError().text ()+
                            "-31----------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + " + " ;
                }


                ////// diğer left leri 2 artır
                qStr =  QString("UPDATE %1 SET hsp_lft = hsp_lft + 2 "
                               "WHERE hsp_lft > %2 ")
                           .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "HATA +2 Left\n"+
                            "--02----------------------------------\n"+
                            query.lastError().text ()+
                            "--021----------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + "1 " ;
                }

                /// yeni node oluştur

                hesapLR = QString::number(hesapRight+1) +" - "+
                          QString::number(hesapRight+2);

                qStr = QString("INSERT INTO "+*tb_name
                               +" (hsp_id, hsp_parentid, "
                                 "hsp_ad, hsp_lft, hsp_rgt ) "
                                 "values ( "+ QString::number(*max_id) +
                               " , "+QString::number(hspdtyID)+
                               ", "+hesapLR+" , %5, %6 )")
                           .arg(hesapRight)
                           .arg(hesapRight+1) ;


                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Yeni node e k l e n e m e d i\n"+
                            "-4----------------------------------\n"+
                            query.lastError().text ()+
                            "--41--------------------------------\n";
                }
                else
                {
                    mesaj = mesaj + "NODE ADDED\n";
                }
            }// eklenecek kayıt hazırlandı
        }

        if (tb_model->submitAll())
        {
            mesaj = mesaj +" -- SUBMITTED -- "    ;

            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
            ////////////////////////////////////////////////

        }
        else
        {
            mesaj = mesaj + " Hesap kaydı e k l e n e m e d i ."  ;
        }

        qDebug()<<mesaj ;

    });// connect ekle sonu

    /////////////////////////////////////////////////////////////////////
    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                     "resim", "ekle");
    });

    // -- 003   hsp  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex indx =   tb_view->table->currentIndex();
        if( indx.row() >= 0 )
        {
            qDebug()<< "Silinecek row no: "<< indx.row()+1;

            //         tb_view->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QString hspdtyID = tb_model->data
                              (tb_model->index
                               (indx.row (),
                                tb_model->fieldIndex ("hsp_ID"))).toString ();

            QString hesapad = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("hsp_ad"))).toString ();


            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                    "KAYIT SİL", hspdtyID+" - "+hesapad ,
                       QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                QModelIndex indx2;
                if (tb_model->checkIndex(tb_view->table->model()->
                        index(tb_view->table->currentIndex().row()  - 1, 0)))
                {
                     indx2= tb_view->table->model()->
                        index(tb_view->table->currentIndex().row()  - 1, 0);
                     qDebug() << "checkindex edddddddddddd";                }



                // remove the current index
                // pmodel->beginRemoveColumn();
                tb_model->removeRow(indx.row());
                //pmodel->endRemoveColumns();
                tb_model->select();
                tb_view->table->setSelectionMode (QAbstractItemView::SingleSelection);
                tb_view->table->setSelectionBehavior (QAbstractItemView::SelectRows);
                tb_view->table->scrollTo (indx2);
                tb_view->table->selectRow (indx2.row()-1);
                tb_view->table->scrollTo (indx2);
                tb_view->table->setSelectionBehavior (QAbstractItemView::SelectItems);

//                QModelIndex indx2 = tb_view->table->model()->
//                        index(tb_view->table->currentIndex().row()  - 1, 0);
//                tb_view->table->selectionModel()->select(
//                    indx2,QItemSelectionModel::ClearAndSelect);
               // tb_view->table->setCurrentIndex(indx2);
               // tb_view->table->edit(indx2);
            }
        }
    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (!Index.isValid())
        {
            qDebug() <<"index is invalid - tb mappper setCurrentModelIndex";
        }

        hspdtyID = tb_model->data (tb_model->index (Index.row (),
                  tb_model->fieldIndex ("hsp_id"))).toInt ();
        hesapID = tb_model->data (tb_model->index (Index.row (),
                        tb_model->fieldIndex ("hsp_parentid"))).toInt ();
        hesapAd = tb_model->data (tb_model->index (Index.row (),
                  tb_model->fieldIndex ("hsp_ad"))).toString ();
        hesapLeft  = tb_model->data (tb_model->index (Index.row (),
                     tb_model->fieldIndex ("hsp_lft"))).toInt ();
        hesapRight = tb_model->data (tb_model->index (Index.row (),
                     tb_model->fieldIndex ("hsp_rgt"))).toInt();
        debugger("6");
        // 011-02 hesap row değiştiğinde hesap id yi etrafa yayınlayalım
        //   emit hC_HSPDTY::sgnHsp(tb_view->table->model()->index( Index.row() ,
        //         tb_model->fieldIndex (hspid) ).data().toInt() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);


    });



}


void hC_HSPDTY::showEvent(QShowEvent *)
{
    qDebug() << "Hesap dosyası açılıyor";
}

void hC_HSPDTY::slt_tbx_rowChange()
{

}




hC_HSPDTY::~hC_HSPDTY()
{
    qDebug() << "*********** destructor Hesap Detay";
    //delete
}





  */
