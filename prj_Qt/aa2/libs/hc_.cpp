//#include "hc_.h"
#include "main/globals.h"

hC_::hC_()
{

}

// /////////////////////////////////////////////////////////////////////////////////
//    T A B L E V I E W   -----> hC_Tv
// /////////////////////////////////////////////////////////////////////////////////

/// 3- hC_Tv     - menu eklenmiş tableview

hC_Tv::hC_Tv (QSqlRelationalTableModel *tb_model,
              QDataWidgetMapper *tb_mapper ,
              QWidget *win_Wdgt)
{

    // //////////////////////////////////////////////
    QIcon icon;
    int x=20, y=20;

    cB_map = new QCheckBox;
    cB_map->setMaximumSize (x,y);
    cB_map->setTristate (true);
    cB_map->setCheckState (Qt::Checked);

    pB_ekle = new QPushButton;
    pB_ekle->setMaximumSize (x,y);
    icon.addPixmap(QPixmap (":/rsm/nv_ekle.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ekle->setIcon(icon);
    pB_ekle->setIconSize(QSize(x,y));
    pB_ekle->setToolTip ("Yeni KAYIT ekle");

    pB_eklersm = new QPushButton;
    pB_eklersm->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_eklersm.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_eklersm->setIcon(icon);
    pB_eklersm->setIconSize(QSize(x,y));
    pB_eklersm->setToolTip ("Dosyadan RESİM Ekle-Değiştir");

    //camera
    auto pB_camera = new QPushButton;
    pB_camera->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_eklersm.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_camera->setIcon(icon);
    pB_camera->setIconSize(QSize(x,y));
    pB_camera->setToolTip ("Kameradan RESİM ekle-değiştir");

    pB_sil= new QPushButton();
    pB_sil->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/delete.png") ,
                   QIcon::Normal, QIcon::On);
    pB_sil->setIcon(icon);
    pB_sil->setIconSize(QSize(x,y));
    pB_sil->setToolTip ("Kayıt SİL");


    pB_ilk= new QPushButton();
    pB_ilk->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_first.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ilk->setIcon(icon);
    pB_ilk->setIconSize(QSize(x,y));
    pB_ilk->setToolTip ("İlk kayıda git");


    pB_ncki= new QPushButton();
    pB_ncki->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_pre.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ncki->setIcon(icon);
    pB_ncki->setIconSize(QSize(x,y));
    pB_ncki->setToolTip ("Önceki Kayıda git");

    pB_snrki= new QPushButton();
    pB_snrki->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_next.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_snrki->setIcon(icon);
    pB_snrki->setIconSize(QSize(x,y));
    pB_snrki->setToolTip ("Sonraki kayıda git");

    pB_son= new QPushButton();
    pB_son->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_last.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_son->setIcon(icon);
    pB_son->setIconSize(QSize(x,y));
    pB_son->setToolTip ("Son Kayıda git");
    /*   auto * fR_mn = new QFrame(this) ;
    //fR_mn->setStyleSheet ("background-color:green");
    fR_mn->setFrameStyle (QFrame::Box | QFrame::Raised);
    fR_mn->setLineWidth (3);
    fR_mn->setMidLineWidth (2);
    fR_mn->setGeometry (0,0,40,30);
*/
    auto *widget_buttonz = new QWidget;
    widget_buttonz->setWindowTitle ("buttonz window");
    auto *Layout_buttonz = new QVBoxLayout;
    widget_buttonz->setLayout (Layout_buttonz);

    Layout_buttonz->addWidget (pB_ekle );
    Layout_buttonz->addWidget (pB_eklersm );
    // Layout_buttonz->addWidget (pB_camera );
    //Layout_buttonz->addStretch (1);
    Layout_buttonz->addWidget (pB_sil  );
    Layout_buttonz->addWidget (pB_ilk  );
    Layout_buttonz->addWidget (pB_ncki );
    Layout_buttonz->addWidget (pB_snrki);
    Layout_buttonz->addWidget (pB_son  );
    Layout_buttonz->addWidget (cB_map  );
    Layout_buttonz->addStretch ();
    //  Layout_buttonz->addStretch (1);
    //Layout_buttonz->addWidget (pB_grscks );
    //Layout_buttonz->addStretch (4);
    // //////////////////////////////////////////////

    // //////////////////////////////////////////////
    // auto *widget_table = new QWidget;
    // widget_table->setWindowTitle ("Table window");
    // auto *Layout_table = new QVBoxLayout;
    // widget_table->setLayout (Layout_table);

    table = new QTableView;

    table->setMinimumWidth (240);
    table->setMinimumHeight (150);


    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setEditTriggers
            (QAbstractItemView::NoEditTriggers );
    /*  (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);*/
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->resizeContentsPrecision();
    table->resizeRowsToContents ();
    table->resizeColumnsToContents();


    //ayout_table->addWidget (table);
    // //////////////////////////////////////////////
    // //////////////////////////////////////////////

  //  auto *th_all = new QHBoxLayout();
   // th_all->addWidget (table     );
  //  th_all->addWidget (win_Wdgt  );
   // th_all->addStretch (2) ;


    auto *t_all = new QHBoxLayout(this);
    t_all->addWidget (widget_buttonz );
    t_all->addWidget (table         );
    t_all->addWidget (win_Wdgt       );
    t_all->addStretch (1);
    //win_Wdgt->hide ();

    connect(cB_map  , &QCheckBox ::clicked ,
                 [win_Wdgt,this]()
        {
             // hersey
            if (cB_map ->checkState () == 1 )
            {
 //               t_all->addWidget (widget_buttonz, 0, 0, 1, 1);
//                t_all->addWidget (table         , 1, 0, 1, 6 );
  //              t_all->addWidget (win_Wdgt      , 1, 7, 1, 4 );

                win_Wdgt->setVisible (true);
                table->setVisible (true);
//    this->setGeometry (20,20,600,400);
            }
            // sadece table
            else if (cB_map ->checkState () == 0 )
            {
   //             t_all->addWidget (widget_buttonz, 0, 0, 1, 1 );
    //            t_all->addWidget (table         , 1, 0, 1, 1 );
      //          t_all->removeWidget (win_Wdgt );


                win_Wdgt->setVisible (false);
                table->setVisible (true);
                //win_Wdgt->hide ();
                //table->show ();
                //table->showMaximized ();


  //              this->setGeometry (20,20,600,400);

            }
            /// sadece map
            else if (cB_map ->checkState ()== 2)
            {
        //        t_all->addWidget (widget_buttonz, 0, 0, 1, 1);
                //t_all->removeWidget (table  );
          //      t_all->addWidget (win_Wdgt      , 1, 0, 1, 1 );

                win_Wdgt->setVisible (true);
                table->setVisible (false);
//                win_Wdgt->show ();
  //              table->hide ();

            }

    });
    this->adjustSize ();


    // //////////////////////////////////////////////

    /*
    QPainter pntr();
    QLinearGradient grd(0,0,100,100);
    grd.setColorAt (0.0,QColor(QRgb(0x40434a)));
    grd.setColorAt (1.0,QColor(QRgb(0x90434a)));
    QRect rec(100,100,300,300);
    pntr.fillRect (rec,grd);
*/

    //    connect(map, &QDataWidgetMapper::currentIndexChanged,
    //            [this, map, tb_model]( )
    //    {
    //        int map_row = map->currentIndex ();
    //        this->pB_ilk->setEnabled (map_row>0);
    //        this->pB_ncki->setEnabled(map_row > 0);
    //        this->pB_snrki->setEnabled(map_row < tb_model->rowCount() - 1);
    //        this->pB_son->setEnabled(map_row < tb_model->rowCount() - 1);
    //    });

    connect(pB_ilk, &QPushButton::clicked ,
            [this,tb_model,tb_mapper]()
    {
        tb_mapper->toFirst ();
        int tb_mapper_row = tb_mapper->currentIndex ();
        this->pB_ilk->setEnabled (tb_mapper_row>0);
        this->table->setCurrentIndex( tb_model->index( 0  ,0));
    });

    connect(pB_ncki, &QPushButton::clicked ,
            [this,tb_model,tb_mapper]()
    {
        tb_mapper->toPrevious ();
        int tb_mapper_row = tb_mapper->currentIndex ();
        this->pB_ncki->setEnabled(tb_mapper_row > 0);
        this->table->setCurrentIndex( tb_model->index( tb_mapper_row  ,0));
    });

    connect(pB_snrki, &QPushButton::clicked ,
            [this,tb_model,tb_mapper]()
    {
        tb_mapper->toNext ();
        int tb_mapper_row = tb_mapper->currentIndex ();
        this->pB_snrki->setEnabled(tb_mapper_row < tb_model->rowCount() - 1);
        this->table->setCurrentIndex(tb_model->index( tb_mapper_row  ,0));
    });

    connect(pB_son, &QPushButton::clicked ,
            [this,tb_model,tb_mapper]()
    {
        tb_mapper->toLast ();
        int tb_mapper_row = tb_mapper->currentIndex ();
        this->pB_son->setEnabled(tb_mapper_row < tb_model->rowCount() - 1);
        this->table->setCurrentIndex(
                    tb_model->index( tb_model->rowCount() - 1  ,0));
    });



    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this, tb_mapper, tb_model ]( )   //tb_tb_mapper, tb_model, tb_view
    {
        int tb_mapper_row = tb_mapper->currentIndex ();
        this->pB_ilk->setEnabled (tb_mapper_row>0);
        this->pB_ncki->setEnabled(tb_mapper_row > 0);
        this->pB_snrki->setEnabled(tb_mapper_row < tb_model->rowCount() - 1);
        this->pB_son->setEnabled(tb_mapper_row < tb_model->rowCount() - 1);
    });


    //            qDebug () << "this.width  " << this->table->width ();
    //            qDebug () << "     height " << this->table->height ();
    //            qDebug () << "parent w    " << this->parentWidget ()->width ();
    //            qDebug () << "parent h    " << this->parentWidget ()->height ();
    //            qDebug () << "this        " << this ;
    //            qDebug () << "this parent " << this->parent ();
    //            qDebug () << "this p w    " << this->parentWidget ();


}



hC_Tv::~hC_Tv()
= default;

hC_Nr::hC_Nr()
{

}

int hC_Nr::hC_NrMax(QString *tb_name, QString tb_id)
{
    QSqlQuery q;
    QString qry, mesaj("");
    /// yeni kayıt id bul
    /// barkod nosu _dbtb de
    /// id de en büyük sayı
    qry = "SELECT max("+ tb_id +") FROM " + *tb_name  ;
    int maxID;
    if ( !q.exec(qry) )
    {
        mesaj = mesaj + "Malzeme No bulunamadı \n"+
                "------------------------------------\n"+
                q.lastError().text ()+
                "------------------------------------\n";
        return -1;
    }
    else
    {
        q.next();
        maxID = q.value(0).toInt ();
        mesaj = mesaj + "MAX VAL = " + QString::number(maxID) ;
    }

    return maxID = maxID + 1  ;

}


bool hC_Nr::hC_NrGo(hC_Tv* tb_view,
                    QSqlRelationalTableModel* tb_model,
                    int aranan,
                    int kolon, int kolon2 )
{
    /// tb_view table view ine eklenen son kaydı,
    /// KOLON da
    /// ARANAN ı bulur
    ///
    /// aranan iedet de olduğu gibi iedet no dur ve
    /// kayıt eklenirken oluşturulur.
    /// sonra bu classa parametreler yollanır
    ///
    ///

        tb_model->select();
    bool boole = false;
    QModelIndex searchStartIndex;
    //if(!IEDETtview->table->currentIndex().isValid())
    searchStartIndex = tb_view->table->
            model()->index( 0, kolon ) ;   //root item
    //else
    //  searchStartIndex = IEDETtview->table->
    //        currentIndex();

    QModelIndexList nextMatches = tb_view->table->
            model()->match(searchStartIndex,
                           Qt::DisplayRole, aranan, 1,
                           Qt::MatchExactly |
                           Qt::MatchWrap |
                           Qt::MatchRecursive);
//qDebug () << "aranan : " <<aranan;
//qDebug () << "kolon  : " << kolon;
//qDebug () << "view   : " << tb_view;
//qDebug () << "strt   : " <<searchStartIndex ;
//qDebug () << "match s: " <<nextMatches;
//qDebug () << "size   : " << nextMatches.size();

    if(nextMatches.size() == 1)
    {
        //first result might be the currently selected item
        if(nextMatches.at(0) == tb_view->table->
                currentIndex())
        {
            nextMatches = tb_view->table->
                    model()->match(searchStartIndex,
                                   Qt::DisplayRole, aranan, 2,
                                   Qt::MatchExactly |
                                   Qt::MatchWrap |
                                   Qt::MatchRecursive);

            if(nextMatches.size() == 2)
            {
                tb_view->table->
                        setCurrentIndex ( hC_NrSetCurrentIndex(
                                   nextMatches.at(1),kolon2));
            }
            boole = true;
        }
        else
            tb_view->table->
                    setCurrentIndex ( hC_NrSetCurrentIndex(
                                          nextMatches.at(0),kolon2));
        boole = true;
    }
//    qDebug () << "current          :" <<tb_view->table->currentIndex() ;

//    qDebug () << "current aft slct :" <<tb_view->table->currentIndex() ;

    tb_view->table->setFocus ();
//    qDebug () << "current aft fcs  :" <<tb_view->table->currentIndex() ;

    return boole;
}

QModelIndex hC_Nr::hC_NrSetCurrentIndex(QModelIndex Index, int kolon2)
{

    if (Index.column () == 0 )
    {
        Index = (Index.sibling( Index.row (),kolon2));
    }
    return Index;
}





//////////////////////////////////////////////////////////
/// \brief hC_tBcreator::hC_tBcreator
///
///   create table and others


hC_tBcreator::hC_tBcreator (QWidget *parent)
                      : QWidget(parent)
{
    //    this->_mesaj = "";

    /// create table
    win_Label = new QLabel ;
    tb_name   = new QString  ;
    tb_ndex   = new QString ();
    tb_model  = new QSqlRelationalTableModel;
    tbx_slctnMdl = new QItemSelectionModel;
    tb_mapper = new QDataWidgetMapper;
    win_Wdgt  = new QWidget;

    tb_view   = new hC_Tv (tb_model, tb_mapper, win_Wdgt);

    /*   qDebug () <<endl<<"Preparing at hC_ ..."
                 <<endl<<"   Dosya : "<< *tb_name << " - " << tb_name
                 <<endl<<"   Index : "<< *tb_ndex << " - " << tb_ndex
                 <<endl<<"   Model : "<< tb_model
                 <<endl<<"   View  : "<< tb_view
                 <<endl<<"   Map   : "<< tb_mapper ;
*/
    qDebug () <<"tbCreator Construction ...";
}

hC_tBcreator::~hC_tBcreator()
{

    delete tb_view     ;
    delete tb_model     ;
    //  delete tbx_slctnMdl ;
    delete tb_mapper   ;

    delete tb_name     ;
    // delete tb_flds     ;
    delete tb_ndex     ;
    // delete tb_wdgts    ;

    //delete win_Wdgt  ;
    //delete win_Label ;
    //delete win_Rsm   ;



}




QString hC_tBcreator::tbCreate (hC_ArrD * tb_flds)
{
    ////////////////////////////////////////////////////////
    /// table creater
    /// fields in içindeki değerlere göre table oluşturur
    ///
    //qDebug () <<"creating "<< *tb_name <<" ..." ;
    QString ct(" ");
    QSqlQuery q;

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *tb_name ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *tb_name +
                " ( ";

        for (int i=0 ; i < tb_flds->length (); i++)
        {
            if ( i == 0 ) // ilk field
            {
                ct = ct + tb_flds->value(i,0) + " "+
                        tb_flds->value(i,1) +" PRIMARY KEY, ";
            }
            else if ( i > 0  &&
                      i < tb_flds->length () - 1 ) // other fields
            {
                ct = ct + tb_flds->value(i,0) + " "+
                        tb_flds->value(i,1) + ", ";
            }
            else if ( i == tb_flds->length () - 1 ) // son field
            {
                ct = ct + tb_flds->value(i,0) + " "+
                        tb_flds->value(i,1) + " ) ";
            }


        }



        if (!q.exec( ct ))
        {
            this-> _mesaj = "xxx:xxx HATA - Dosya Oluşturulamadı : " +
                    *tb_name  +
                    "\n------------------------------------\n"+
                    q.lastError().text()+
                    "\n------------------------------------\n";

            qDebug () << "     xxx:xxx HATA - Dosya Oluşturulamadı : "
                      << *tb_name
                    << "     ------------------------------------"
                   << "     "<< q.lastError().text()
                  << "     ------------------------------------";
        }
        else /// dosya oluşturuldu
        {

            /*    qDebug ()<< "   -------------------------- " ;
            qDebug ()<< "    ct = " << ct;
            qDebug ()<< "   -------------------------- " ;*/
            this-> _mesaj = "\nOK   - YENİ Dosya Oluşturuldu : "+ *tb_name  ;
            qDebug ()<<"   OK   - YENİ Dosya Oluşturuldu : "+ *tb_name  ;
            /*if (
                    q.exec("INSERT INTO " + *tb_name +
                           "( mlzm_barkod,mlzm_malzeme )"
                           " values( '1111','KOD 1 ve 1111 barkodlu malzeme' )"  ))

            {
                _mesaj= _mesaj+"\n   İLK kayıt Eklendi";
            }
            else
            {
                _mesaj= _mesaj+"\n   İLK Malzeme kaydı eklenemedi "
                               "\n   ------------------------------------ "+
                        q.lastError().text()+
                        "\n    ------------------------------------ ";
            }*/
        }
    }

    else /// dosya var
    {
        this-> _mesaj  = "  OK          : " + *tb_name ;
    }
    //   qDebug() << this-> _mesaj ;
    ////////////////////////////////////////////////////////////

    return _mesaj;
}



void hC_tBcreator::tbModel (hC_ArrD *tb_flds)

{
    //   qDebug () <<"modelling "<< *tb_name <<" ..." ;
    tb_model->setTable( *tb_name );


    tb_model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    tb_model->setSort(tb_model->fieldIndex
                      ( *tb_ndex ),Qt::AscendingOrder );

    for(int i = 0; i < tb_flds->length (); i++)
    {

        if ( tb_model->setHeaderData(i, Qt::Horizontal,
                                     tb_flds->value (i,2)) )
        {
            // qDebug () <<"rm_List->value ("<<i<<",2)"
            //      << tb_flds->value (i,2)<<"HEADED" ;
        }
        else
        {
            //   qDebug () <<"tb_flds->value ("<<i<<",2)"
            //        << tb_flds->value (i,2)<<"not HEADED" ;

        }

    }
    QString mesaj;
    // Populate the model
    if (!tb_model->select())
    {
        qDebug ()<< ("     xxx:xxx HATA - Model Seçim   \n"
                     "class hC_tbcreator-tbmodel - \n"+
                     *tb_name + " \n  " +
                     tb_model->lastError().text() ) ;
    }
    else
    {
        qDebug ()<< "  " << *tb_name << "modelled: " << tb_model  ;
    }
    // qDebug () <<  mesaj << tb_model;

}

void hC_tBcreator::tbView(hC_ArrD *tb_flds )
{

    //////////////////////////////////////////////////////////

    tb_view->table->setModel(tb_model);
    tbx_slctnMdl = tb_view->table->selectionModel ();


    for (int i = 0 ; i < tb_flds->length () ; i++ )
    {

        if (tb_flds->value (i,3) == "1")
        {
            tb_view->table->setColumnHidden( i , false);
        }
        else if (tb_flds->value (i,3) == "0")
        {
            tb_view->table->setColumnHidden( i , true);
        }
        else
        {
            qDebug ()<<  "     xxx:xxx view colon hidden ERROR";
        }
        /*   if (tb_view->table->isColumnHidden (i))
        {
            qDebug () <<"         Hidden :" << tb_flds->value (i,0) ;
        }
        else
        {
            qDebug () <<"     NOT Hidden :" << tb_flds->value (i,0) ;
        }*/
    }
    tb_view->table->setCurrentIndex(tb_model->index(1, 1) );
    tb_view->table->setFocus();
    qDebug () <<"  "<< *tb_name << "viewed  : " <<  tb_view <<".";
}


void hC_tBcreator::tbMap(hC_ArrD *tb_flds,
                         QList <QWidget*> * tb_wdgts )
{
    //qDebug () <<"mapping "<< *tb_name <<" ..." ;
    tb_mapper->setModel(tb_model);
    for (int i=0 ;  i < tb_flds->length () ; i++ )
    {

        if ( tb_wdgts->at (i) != nullptr)
        {
            tb_mapper->addMapping ( tb_wdgts->at (i), i);
        }
    }
    tb_mapper->toFirst()  ;
    connect(  tbx_slctnMdl, &QItemSelectionModel::currentRowChanged,
              tb_mapper,       &QDataWidgetMapper::setCurrentModelIndex);


    qDebug () <<"  "<< *tb_name << "mapped  : " <<  tb_mapper <<".";
}









// /////////////////////////////////////////////////////////////////////////////////


//    L I N E D I T    -----> hC_Le

// Sağda pushbutonu olan lineedit
// /////////////////////////////////////////////////////////////////////////////////

/// 4- hC_Le            - sağda pushbutton olan lineedit

hC_Le::hC_Le( QWidget *parent ) : QWidget (parent)
{
    lineEdit    = new QLineEdit;
    pushButton  = new QPushButton(QIcon(":/rsm/ex.ico"),nullptr );
    pushButton2 = new QPushButton(QIcon(":/rsm/Erase.ico"),nullptr );

    auto *t_all = new QGridLayout(this);

    t_all->addWidget (lineEdit    , 0, 0, 1, 4);
    t_all->addWidget (pushButton , 0, 5, 1, 1);
    t_all->addWidget (pushButton2 , 0, 6, 1, 1);
    connect (pushButton2, &QPushButton::clicked,
             lineEdit,    &QLineEdit::clear );
    // //////////////////////////////////////////////

    /*
    QPainter pntr();
    QLinearGradient grd(0,0,100,100);
    grd.setColorAt (0.0,QColor(QRgb(0x40434a)));
    grd.setColorAt (1.0,QColor(QRgb(0x90434a)));
    QRect rec(100,100,300,300);
    pntr.fillRect (rec,grd);
*/



}
hC_Le::~hC_Le()
= default;





// /////////////////////////////////////////////////////////////////////////////////


//    T E X T E D I T    -----> hC_Te

// Sağ tuş butonu olan textedit
// /////////////////////////////////////////////////////////////////////////////////

/// 4- hC_Te            - sağda pushbutton olan textedit

hC_Te::hC_Te ( QWidget *parent ) : QWidget (parent)
{
    hC_txEdt   = new QTextEdit;
    hC_txEdtpB = new QPushButton(QIcon(":/rsm/ex.ico"),nullptr );
    auto *t_all = new QGridLayout(this);
    t_all->addWidget (hC_txEdt   , 0, 0, 3, 6);
    t_all->addWidget (hC_txEdtpB , 1, 6, 1, 1);
}
hC_Te::~hC_Te()
= default;



/// 2- hC_Resim         - etiket üzerine diskten resim ekler,
///                         resmi değiştirir, pencerede gösterir
///


// ////////////////////////////////////////////////////////// resim

hC_Rs::hC_Rs (  QLabel *lB_resim,
                hC_Tv *rsm_table,
                QSqlRelationalTableModel *rsm_model,
                QItemSelectionModel *rsm_selectionModel,
                QString rsm_field,
                QString rsm_new_upd
                )
{

    lB_resim->setMinimumSize (80,50);
    lB_resim->setMaximumSize (160,100);

    if (rsm_new_upd == "ekle") // yeni kayıt
    {
        // view row unu tespit et
        int rowidx = rsm_selectionModel->currentIndex().row();

        // fatura resim ekle
        QString myfile = QFileDialog::
                getOpenFileName (this,
                                 tr("Resim Aç"), "/home/mr/Resimler",
                                 tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
                                    " ;; Tüm Dosyalar (*,*)"));

        if (myfile == "")
            return ;

        QImage image(myfile);
        lB_resim->setPixmap(QPixmap::fromImage(image));
        QByteArray inByteArray;
        QFile file(  myfile ); //dosyayı açmak için al

        if (file.open(QIODevice::ReadOnly))
        {
            inByteArray = file.readAll();
            /// resmi değiştirelim
            rsm_model->setData(rsm_model->
                               index(rowidx, rsm_model->fieldIndex
                                     ( rsm_field )), inByteArray);
            /// yeni eklenenleri kaydedelim
            rsm_model->submitAll();
        }


    }
    else  if (rsm_new_upd == "değiştir")  // resim uodate
    {
        // view row unu tespit et
        int rowidx = rsm_selectionModel->currentIndex().row();

        // row, xolumn daki veriyi bytearray a at
        QByteArray outByteArray = rsm_table->table->
                model()->index( rowidx, rsm_model->
                    fieldIndex ( rsm_field ) ).data().toByteArray();

        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData( outByteArray  );
        if ( ! outByteArray.isNull ())
        {
            lB_resim->setPixmap( outPixmap );
        }
        else
        {
            lB_resim->setPixmap (QPixmap (":/rsm/rsm_yok.png"));
            // lB_resim->setPixmap (QPixmap (""));
        }

        lB_resim->setScaledContents( true );
        lB_resim->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        lB_resim->show();

    }
    else  if (rsm_new_upd == nullptr)  // resim büyük pencerede
    {

        lB_resim->setScaledContents( true );
        lB_resim->setSizePolicy( QSizePolicy::Preferred,
                                  QSizePolicy::Preferred );
        lB_resim->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(lB_resim , &QLabel::customContextMenuRequested,
                [ lB_resim]()
        {
            //QLabel *x = win_Rsm;
            QDialog xx;
            xx.setModal(true);
            xx.setSizeGripEnabled(true);
            xx.setAutoFillBackground(true);
            QLabel *x = new QLabel(&xx);
            x->resize(QGuiApplication::primaryScreen()->
                      availableSize() * 10 / 16);
            x->setScaledContents(true);
            x->setPixmap(QPixmap (lB_resim->pixmap() ) );
            xx.setWindowTitle("RESİM GÖRÜNTÜLEME");
            xx.exec();
        });

    }
}



/*
// /////////////////////////////////////////////////////////////////////////////////


//    QSQLRELATIONATABLEMODEL    -----> hC_Rm

// rel tb_model
// /////////////////////////////////////////////////////////////////////////////////

/// 4- hC_Rm            - rel tb_model

hC_Rm::hC_Rm (QString *rm_Table,
              QSqlRelationalTableModel *rm_model,
              QString *rm_IndexField,
              hC_ArrD *rm_List )

{
    rm_model->setTable( *rm_Table );
    rm_model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    rm_model->setSort(rm_model->fieldIndex
                      ( *rm_IndexField ),Qt::AscendingOrder );

    for(int i = 0, j = 0; i < rm_List->length (); i++, j++)
    {

        rm_model->setHeaderData(i,
                                Qt::Horizontal,
                                rm_List->value (i,2)) ;
    }

    // Populate the model
    if (!rm_model->select())
    {
        QString m("HATA - \n"
                  "-*- Model Seçim   \n"
                  "-*- class hC_Rm - \n"+
                  *rm_Table + "   " +
                  rm_model->lastError().text() ) ;
        qDebug () <<  m ;
    }
}

hC_Rm::~hC_Rm()
= default;

*/

hC_Gz::hC_Gz(QDateTimeEdit *tarih, QString vsbl)
{
    if (vsbl == "0" )
    {
        tarih->setVisible (false);
    }
    else if (vsbl == "1" )
    {
        tarih->setVisible (true);
    }
    else if (vsbl == "currentdate")
    {
        tarih->setDate (QDate::currentDate ());
        tarih->setVisible (true);
        tarih->setDisplayFormat("dd.MM.yyyy");
        tarih->setMinimumDate(QDate::currentDate ());
        tarih->setMaximumDate(QDate(valiDDate));
        tarih->setCalendarPopup(true);


    }
    else if (vsbl == "nulldate")
    {
        tarih->setSpecialValueText( " " );
        tarih->setDate(
                    QDate::fromString( "01/01/0001", "dd/MM/yyyy"));
        tarih->setVisible (true);
        tarih->setDisplayFormat("dd.MM.yyyy");
        tarih->setDate(QDate::currentDate () );
        tarih->setMaximumDate(QDate(valiDDate));

        tarih->setCalendarPopup(true);

    }

}


objectIsThere::objectIsThere()
{
}

objectIsThere::~objectIsThere()
{

}

bool objectIsThere::ovarmi(QString *oName)
{

    QWidgetList lst = qApp->allWidgets ();
    bool boole = false;

    foreach (QWidget *widget, QApplication::allWidgets())
    {
        if (widget->objectName () == *oName )
        {
            boole = true;
            widget->show ();
            widget->setWindowTitle (" 111111  "+widget->objectName());
            //oVar = widget;
            //oVar->show ();
            //oVar->setWindowTitle (" 111111  "+widget->objectName());
        }
    }

    return boole;
}
