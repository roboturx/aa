#include "hc_hspdetay.h"
#include "hsap/uniqueproxymodel.h"
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

    /// setvalue  sıralama, dosya değişkeni, TYPE, view header, viewda görünür

    tb_flds->setValue ( 0, "f_hspdty_ID"      , "INTEGER", "hspdty_ID","0" ) ;
    // hesaplar ile hesap detay arası key
    tb_flds->setValue ( 1, "f_hspdty_hspID"   , "INTEGER", "hspdty_HesapID",0) ;
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




void hC_HSPDTY::tbkntrl()
{
    qDebug() << "   0130 hspdty::tbkntrl ---- begin";

//    cls_dlgt_ComboBox *cb = new cls_dlgt_ComboBox();

  //  tb_view->table->setItemDelegateForColumn(5, cb );
     //////////////// filtering
    UniqueProxyModel *proxyModel1 = new UniqueProxyModel(1,this);
    qDebug() << "1";
    // setting proxymodel1 to view
    proxyModel1->setSourceModel (tb_model);
    tb_view->table->setModel (proxyModel1);
qDebug() << "12";
    // sorting proxy model1
    tb_view->table->setSortingEnabled (true);
qDebug() << "12";
//proxyModel->sort(0, Qt::AscendingOrder);
//qDebug() << "13"
//         << QString::number(hc_hsp_currentHesapItem->hesapKod ());
//     // filtering proxy model1
//QRegularExpression arananIfade(QString::number(hc_hsp_currentHesapItem->hesapKod ()));/*"[0-9]");*/
////QRegularExpressionMatch match = arananIfade.match (hc_hsp_currentHesapItem->hesapKod ());

//qint64 xxx = hc_hsp_currentHesapItem->hesapKod ();
//QString xx = QString::number (xxx);
//proxyModel->setFilterRegularExpression(arananIfade);
//qDebug() << "131";
//proxyModel->setFilterKeyColumn(1);

qDebug() << "14";
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

        curIndex = tb_view->table->currentIndex ();
        reccount=tb_model->rowCount();

        qStr = QString("INSERT INTO "+*tb_name +
                       " ( f_hspdty_hspID) "
                       " values ( '"+
                       QString::number (hc_hsp_currentHesapItem->hesapKod ())+
                       "' )")  ;

        if ( !query.exec(qStr) )
        {
            mesaj = mesaj + "002x- İlk node e k l e n e m e d i ...\n/n"+
                    query.lastError().text ();
        }
        else
        {
            mesaj = mesaj + "Hesap Detay Kaydı eklendi - \n";
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
            tb_view->table->setFocus();
        qDebug()<<mesaj ;

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

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged, this,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);


    });


    qDebug() << "   0130 hspdty::tbkntrl ---- end";
}


void hC_HSPDTY::showEvent(QShowEvent *)
{
    qDebug() << "   0140 hspdty::showevent ";
}

void hC_HSPDTY::closeEvent(QCloseEvent *)
{
   qDebug() << "hspdty:: close ()";
}

void hC_HSPDTY::slt_hesapChanged(TaskItem *currHspItem)
{
    /// hesap değiştiğinde filtre değişsin
    qDebug() << "   0150 hc_hspdty::slt_hesapChanged ";
    hc_hsp_currentHesapItem = currHspItem;
 //   tb_model->setFilter(
  //      QString("f_hspdty_hspID = '%1'")
     //      .arg(hc_hsp_currentHesapItem->hesapKod ()) );
   // tb_model->select ();

    qDebug() << "13"
             << QString::number(hc_hsp_currentHesapItem->hesapKod ());
    // filtering proxy model1
    QRegularExpression arananIfade("[0-9]");
    //QRegularExpressionMatch match = arananIfade.match (hc_hsp_currentHesapItem->hesapKod ());

//    qint64 xxx = hc_hsp_currentHesapItem->hesapKod ();
//    QString xx = QString::number (xxx);
    proxyModel->setFilterRegularExpression("1");
    qDebug() << "131";
    proxyModel->setFilterKeyColumn(1);




}



hC_HSPDTY::~hC_HSPDTY()
{
    qDebug() << "hspdty:: ~ destructor ";
}



//void hC_HSPDTY::debugger(QString num)
//{
//    curIndex = tb_view->table->currentIndex ();
//    qDebug() << num+num+num
//             << " rCnt =" <<  tb_model->rowCount()
//             << "  r:" << tb_view->table->rowAt(0)
//             << "  id:"<< tb_model->data(tb_model->index(curIndex.row (),
//                                                         tb_model->fieldIndex ("hspdty_id")),Qt::DisplayRole).toString()
//             << "  pid:"<<  tb_model->data(tb_model->index(curIndex.row (),
//                                                           tb_model->fieldIndex ("hspdty_parentid")),Qt::DisplayRole).toString()
//             << "  ad:"<<  tb_model->data(tb_model->index(curIndex.row (),
//                                                          tb_model->fieldIndex ("hspdty_ad")),Qt::DisplayRole).toString()
//             << "  lft:"<<  tb_model->data(tb_model->index(curIndex.row (),
//                                                           tb_model->fieldIndex ("hspdty_lft")),Qt::DisplayRole).toString()
//             << "  rgt:"<<  tb_model->data(tb_model->index(curIndex.row (),
//                                                           tb_model->fieldIndex ("hspdty_rgt")),Qt::DisplayRole).toString()
//             <<"  *-*\n"   ;
//}
