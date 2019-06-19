#include "hc_.h"

hC_::hC_()
{

}





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
            //lB_resim->setPixmap (QPixmap (":/rsm/icon/photo_camera.png"));
            lB_resim->setPixmap (QPixmap (""));
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
            //QLabel *x = lB_rsm;
            QDialog xx;
            xx.setModal(true);
            xx.setSizeGripEnabled(true);
            xx.setAutoFillBackground(true);
            QLabel *x = new QLabel(&xx);
            x->resize(QGuiApplication::primaryScreen()->
                      availableSize() * 10 / 16);
            x->setScaledContents(true);
            x->setPixmap(QPixmap (*lB_resim->pixmap() ) );
            xx.setWindowTitle("RESİM GÖRÜNTÜLEME");
            xx.exec();
        });

    }
}






// /////////////////////////////////////////////////////////////////////////////////


//    T A B L E V I E W   -----> hC_Tv


// /////////////////////////////////////////////////////////////////////////////////

/// 3- hC_Tv     - menu eklenmiş tableview


hC_Tv::hC_Tv (int renk, QWidget *parent ) :
    QWidget (parent)
{

    // //////////////////////////////////////////////
    QIcon icon;
    int x=30*renk,y=30;

    pB_ekle = new QPushButton;
    //pB_ekle->setGeometry (0,0,x,y );
    pB_ekle->setMaximumSize (x,y);
    icon.addPixmap(QPixmap (":/rsm/nv_ekle.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ekle->setIcon(icon);
    pB_ekle->setIconSize(QSize(x,y));

    pB_eklersm = new QPushButton;
    pB_eklersm->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_eklersm.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_eklersm->setIcon(icon);
    pB_eklersm->setIconSize(QSize(x,y));

    //camera
    auto pB_camera = new QPushButton;
    pB_camera->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_eklersm.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_camera->setIcon(icon);
    pB_camera->setIconSize(QSize(x,y));


    pB_grscks = new QPushButton;
    pB_grscks->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_eklesil2.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_grscks->setIcon(icon);
    pB_grscks->setIconSize(QSize(x, y));
    pB_grscks->setAutoFillBackground (true);

    pB_sil= new QPushButton();
    pB_sil->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_sil.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_sil->setIcon(icon);
    pB_sil->setIconSize(QSize(x,y));


    pB_ilk= new QPushButton();
    pB_ilk->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_first.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ilk->setIcon(icon);
    pB_ilk->setIconSize(QSize(x,y));


    pB_ncki= new QPushButton();
    pB_ncki->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_pre.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_ncki->setIcon(icon);
    pB_ncki->setIconSize(QSize(x,y));

    pB_snrki= new QPushButton();
    pB_snrki->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_next.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_snrki->setIcon(icon);
    pB_snrki->setIconSize(QSize(x,y));

    pB_son= new QPushButton();
    pB_son->setMaximumSize (x,y );
    icon.addPixmap(QPixmap (":/rsm/nv_v_last.svg") ,
                   QIcon::Normal, QIcon::On);
    pB_son->setIcon(icon);
    pB_son->setIconSize(QSize(x,y));

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
    Layout_buttonz->addWidget (pB_camera );
    Layout_buttonz->addStretch (1);
    Layout_buttonz->addWidget (pB_sil  );
    Layout_buttonz->addWidget (pB_ilk  );
    Layout_buttonz->addWidget (pB_ncki );
    Layout_buttonz->addWidget (pB_snrki);
    Layout_buttonz->addWidget (pB_son  );
    Layout_buttonz->addStretch (1);
    Layout_buttonz->addWidget (pB_grscks );
    Layout_buttonz->addStretch (4);
    // //////////////////////////////////////////////

    // //////////////////////////////////////////////
    // auto *widget_table = new QWidget;
    // widget_table->setWindowTitle ("Table window");
    // auto *Layout_table = new QVBoxLayout;
    // widget_table->setLayout (Layout_table);

    table = new QTableView;

    //ayout_table->addWidget (table);
    // //////////////////////////////////////////////

    // //////////////////////////////////////////////
    auto *Layout_all = new QGridLayout(this);
    Layout_all->addWidget (widget_buttonz, 0, 0 );
    Layout_all->addWidget (table  , 0, 1 );
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

void hC_Tv::hC_TvPb(QString Key,
                    QSqlRelationalTableModel *model,
                    QDataWidgetMapper *map)
{
    if ( Key == "yenile")
    {
        int map_row = map->currentIndex ();
        this->pB_ilk->setEnabled (map_row>0);
        this->pB_ncki->setEnabled(map_row > 0);
        this->pB_snrki->setEnabled(map_row < model->rowCount() - 1);
        this->pB_son->setEnabled(map_row < model->rowCount() - 1);
    }
    else if ( Key == "ilk")
    {
        map->toFirst ();
        int map_row = map->currentIndex ();
        this->pB_ilk->setEnabled (map_row>0);
        this->table->setCurrentIndex( model->index( 0  ,0));
    }
    else if ( Key == "ncki")
    {
        map->toPrevious ();
        int map_row = map->currentIndex ();
        this->pB_ncki->setEnabled(map_row > 0);
        this->table->setCurrentIndex( model->index( map_row  ,0));
    }
    else if ( Key == "snrki")
    {
        map->toNext ();
        int map_row = map->currentIndex ();
        this->pB_snrki->setEnabled(map_row < model->rowCount() - 1);
        this->table->setCurrentIndex(model->index( map_row  ,0));
    }
    else if ( Key == "son")
    {
        map->toLast ();
        int map_row = map->currentIndex ();
        this->pB_son->setEnabled(map_row < model->rowCount() - 1);
        this->table->setCurrentIndex(
            model->index( model->rowCount() - 1  ,0));
    }

}
hC_Tv::~hC_Tv()
= default;








// /////////////////////////////////////////////////////////////////////////////////


//    L I N E D I T    -----> hC_Le

// Sağda pushbutonu olan lineedit
// /////////////////////////////////////////////////////////////////////////////////

/// 4- hC_Le            - sağda pushbutton olan lineedit

hC_Le::hC_Le( QWidget *parent ) : QWidget (parent)
{
    lineEdit = new QLineEdit;
    pushButton= new QPushButton(QIcon(":/rsm/ex.ico"),nullptr );
    auto *Layout_all = new QGridLayout(this);

    Layout_all->addWidget (lineEdit   , 0, 0, 1, 4);
    Layout_all->addWidget (pushButton , 0, 5, 1, 1);
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
    auto *Layout_all = new QGridLayout(this);
    Layout_all->addWidget (hC_txEdt   , 0, 0, 3, 6);
    Layout_all->addWidget (hC_txEdtpB , 1, 6, 1, 1);
}
hC_Te::~hC_Te()
= default;




// /////////////////////////////////////////////////////////////////////////////////


//    QSQLRELATIONATABLEMODEL    -----> hC_Rm

// rel model
// /////////////////////////////////////////////////////////////////////////////////

/// 4- hC_Rm            - rel model

hC_Rm::hC_Rm (QString *rm_Table,
               QSqlRelationalTableModel *rm_model,
               QString *rm_IndexField,
               QStringList *rm_List )

{
    rm_model->setTable( *rm_Table );
    rm_model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    rm_model->setSort(rm_model->fieldIndex
                      ( *rm_IndexField ),Qt::AscendingOrder );

    for(int i = 0, j = 0; i < rm_List->size (); i++, j++)
    {
        rm_model->setHeaderData(i,Qt::Horizontal, rm_List->value (j));
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

