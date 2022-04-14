#include "hc_hsp.h"

hC_HSP::hC_HSP() : hC_tBcreator ()
{
    qDebug ()<<"Constructor HESAP ********************************";
    //************************************************************
    //*****************  H E S A P  ******************************

    win_Label->setText ( "HESAP KAYITLARI");
    *tb_name   = "hsp_dbtb" ;
    *tb_ndex  = "hsp_ad";

    tb_flds = new hC_ArrD (13, 4);
    tb_flds->setValue ( 0, "hsp_ID"      , "INTEGER", "HesapID", "0" ) ;
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

    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_HSP::tbsetup()
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


void hC_HSP::tbui()
{

    qDebug() << "   ui";

    hC_HSP::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,600,400);
    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}
void hC_HSP::tbwdgt()
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

void hC_HSP::debugger(QString num)
{
    qDebug() << num+num+num
             << " rCnt =" <<  tb_model->rowCount()
             << "  r:" << tb_view->table->rowAt(0)
             << "  id:"<< tb_model->data(tb_model->index(0,
                   tb_model->fieldIndex ("hsp_id")),Qt::DisplayRole).toString()
             << "  pid:"<<  tb_model->data(tb_model->index(0,
                         tb_model->fieldIndex ("hsp_parentid")),Qt::DisplayRole).toString()
             << "  ad:"<<  tb_model->data(tb_model->index(0,
                    tb_model->fieldIndex ("hsp_ad")),Qt::DisplayRole).toString()
             << "  lft:"<<  tb_model->data(tb_model->index(0,
                     tb_model->fieldIndex ("hsp_lft")),Qt::DisplayRole).toString()
             << "  rgt:"<<  tb_model->data(tb_model->index(0,
                      tb_model->fieldIndex ("hsp_rgt")),Qt::DisplayRole).toString()
             <<"  *-*\n"   ;
}


void hC_HSP::tbkntrl()
{


    tb_view->table->setFocus();
    //tb_slctnModel->select( tb_model->index(0,0));
    tb_view->table->setFocus();
    qDebug() << "  hsp KNTRL";
    debugger("1");

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
        ////////////////////////////////////////////////


        //&QItemSelectionModel::currentRowChanged() ;

        // table daki mevcut row detayları için index alalım
        // QModelIndex indx = tb_view->table->currentIndex ();
        QSqlQuery query;
        QString qStr, mesaj("");
        QString hesapLR = "";

        newIndex = tb_view->table->model()->index(0, 0);
        reccount=tb_model->rowCount();

        if ( reccount > 0 )
        {
            hesapID = tb_model->data (tb_model->index (newIndex.row (),
                     tb_model->fieldIndex ("hsp_id"))).toInt ();
            hesapParentID = tb_model->data (tb_model->index (newIndex.row (),
                      tb_model->fieldIndex ("hsp_parentid"))).toInt ();
            hesapAd = tb_model->data (tb_model->index (newIndex.row (),
                      tb_model->fieldIndex ("hsp_ad"))).toString ();
            hesapLeft  = tb_model->data (tb_model->index (newIndex.row (),
                      tb_model->fieldIndex ("hsp_lft"))).toInt ();
            hesapRight = tb_model->data (tb_model->index (newIndex.row (),
                      tb_model->fieldIndex ("hsp_rgt"))).toInt();

        }
        else
        {
            hesapID = 1;
            hesapParentID = 0;
            hesapAd = "1-2-" ;
            hesapLR = "1-2-" ;
            hesapLeft  = 1 ;
            hesapRight = 2 ;

        }

debugger("2");


        /////////////////////////////////////////
        /// node eklerken 3 ayrı durum vardır
        ///
        ///         root node
        /// 01    * Dosya BOŞ ilk node oluştur
        ///         left her zaman 1 dir
        ///         right 2 dir. node eklendikçe değişir
        ///
        ///         leaf node
        /// 02    * altında node olmayan node
        ///         left = left + 1 dir
        /// 03    * altında leaf OLAN node
        ///         left != left + 1
        ///


        if ( reccount == 0 ) // dosyadaki kayıt sayısı "0" sa
        {
            qDebug()<<"001 Dosyaya ilk kayıt ekleniyor...";
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
debugger("3");
                mesaj = mesaj + "002- İlk node eklendi - " + hesapLR;
            }
        } // 01 Dosya BOŞtu ilk node oluşturuldu
        else // 02 dosya BOŞ DEĞİL - 1 veya daha fazla kayıt var
        {


            if (hesapRight-hesapLeft == 1 ) // LEAF
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
                    mesaj = mesaj + "Rights  artırıl a m a d ı . . . "+
                            "-3-----------------------------------"+
                            query.lastError().text ()+
                            "-31-----------------------------------";
                }
                else
                {
                    mesaj = mesaj + "if h_r >= hright - h_r +2 artırıldı at leaves" ;
                }
                ////// diğer left leri 2 artır
                qStr =  QString("UPDATE %1 SET hsp_lft = hsp_lft + 2 "
                                "WHERE hsp_lft > %2 ")
                        .arg(*tb_name).arg(hesapRight) ;
                ///        .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Lefts +2 artırıl a m a d ı . . . ."+
                            "--02----------------------------------"+
                            query.lastError().text ()+
                            "--021----------------------------------";
                }
                else
                {
                    mesaj = mesaj + "if h_l >= hright - h_l +2 artırıldı at leaves" ;

                }
                /// yeni node oluştur

                ////////////////////////////////////////////////
                ///hC_Nr maxID;
                ///int* max_id = new int{};
                //*max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
                ////////////////////////////////////////////////
                hesapLR = "'" + QString::number(hesapRight+1) +" --- "+
                        QString::number(hesapRight+2) + "'";

                qDebug()<<"<hesapLR "<< hesapLR << ">";

                qStr = QString("INSERT INTO "+*tb_name
                               +" (hsp_id, hsp_parentid, "
                                 "hsp_ad, hsp_lft, hsp_rgt ) "
                        "values ( "+ QString::number(*max_id) +
                               " , "+QString::number(hesapID)+
                               ", "+hesapLR+" , %5, %6 )")
                        .arg(hesapLeft+1)
                        .arg(hesapLeft+2) ;



                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Yeni node e k l e n e m e d i "+
                            "-4-----------------------------------"+
                            query.lastError().text ()+
                            "--41----------------------------------";
                }
                else
                {
                    hesapParentID = hesapID;
                    hesapID = *max_id ;

                    hesapAd = "1-2-" ;
                    hesapLR = "1-2-" ;
                    hesapLeft  = hesapLeft+1 ;
                    hesapRight = hesapLeft+2 ;
                    mesaj = mesaj  + "Leaf added";
           debugger("4");
                }
            }
            else // NODE
            {
                /// eklemek istediğimiz node un altında
                /// child V A R S A
                ///
                qDebug()<<"<Araya node ekle> ";

                /// diğer right ları 2 artır
                qStr = QString("UPDATE %1 SET hsp_rgt = hsp_rgt + 2 "
                               "WHERE hsp_rgt > %2 ")
                        .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "HATA +2 rights at nodes"+
                            "-3----------------------------------"+
                            query.lastError().text ()+
                            "-31----------------------------------";
                }
                else
                {
                    mesaj = mesaj + "if h_r >= hright - h_r +2 artırıldı at nodes" ;
                }


                ////// diğer left leri 2 artır
                qStr =  QString("UPDATE %1 SET hsp_lft = hsp_lft + 2 "
                                "WHERE hsp_lft > %2 ")
                        .arg(*tb_name).arg(hesapRight) ;

                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "HATA +2 Left"+
                            "--02----------------------------------"+
                            query.lastError().text ()+
                            "--021----------------------------------";
                }
                else
                {
                    mesaj = mesaj + "if h_l > hright - h_l +2 artırıldı at nodes" ;
                }

                /// yeni node oluştur

                ////////////////////////////////////////////////
                ///hC_Nr maxID;
                ///int* max_id = new int{};
                //*max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
                ////////////////////////////////////////////////
                hesapLR = QString::number(hesapRight+1) +" - "+
                        QString::number(hesapRight+2);
                //QString hesapLR = QString::number(hesapRight+1) +" - "+
                //                  QString::number(hesapRight+2);

                qStr = QString("INSERT INTO "+*tb_name
                               +" (hsp_id, hsp_parentid, "
                                 "hsp_ad, hsp_lft, hsp_rgt ) "
                                 "values ( "+ QString::number(*max_id) +
                               " , "+QString::number(hesapID)+
                               ", "+hesapLR+" , %5, %6 )")
                           .arg(hesapRight+1)
                           .arg(hesapRight+2) ;



                if ( !query.exec(qStr) )
                {
                    mesaj = mesaj + "Yeni node e k l e n e m e d i"+
                            "-4----------------------------------"+
                            query.lastError().text ()+
                            "--41--------------------------------";
                }
                else
                {
                    hesapParentID = hesapID;
                    hesapID = *max_id ;

                    hesapAd = QString::number(hesapLeft+1) +"-"+QString::number(hesapLeft+2) ;
                    hesapLR = hesapAd;
                    hesapLeft  = hesapLeft+1 ;
                    hesapRight = hesapLeft+2 ;
                    mesaj = mesaj  + "Node added";
                    debugger("5");
                }
            }// eklenecek kayıt hazırlandı
        }   // 02 dosya BOŞ DEĞİL - 1 veya daha fazla kayıt var SONU

        // kayıt eklemeyi tamamla

        if (tb_model->submitAll())
        {
            mesaj = mesaj +" "+ hesapLR+ "  eklendi.  -------------------------- "    ;

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

            QString hesapad = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("hsp_ad"))).toString ();


            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL", hesapad ,
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

        hesapID = tb_model->data (tb_model->index (Index.row (),
                                                   tb_model->fieldIndex ("hsp_id"))).toInt ();
        hesapParentID = tb_model->data (tb_model->index (Index.row (),
                                                         tb_model->fieldIndex ("hsp_parentid"))).toInt ();
        hesapAd = tb_model->data (tb_model->index (Index.row (),
                                                   tb_model->fieldIndex ("hsp_ad"))).toString ();
        hesapLeft  = tb_model->data (tb_model->index (Index.row (),
                                                      tb_model->fieldIndex ("hsp_lft"))).toInt ();
        hesapRight = tb_model->data (tb_model->index (Index.row (),
                                                      tb_model->fieldIndex ("hsp_rgt"))).toInt();
        debugger("6");
        // 011-02 hesap row değiştiğinde hesap id yi etrafa yayınlayalım
        //   emit hC_HSP::sgnHsp(tb_view->table->model()->index( Index.row() ,
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


void hC_HSP::showEvent(QShowEvent *)
{
    qDebug() << "Hesap dosyası açılıyor";
}

void hC_HSP::slt_tbx_rowChange()
{

}




hC_HSP::~hC_HSP()
{
    qDebug() << "*********** destructor Hesap";
    //delete
}

