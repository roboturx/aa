#include "hc_tableview.h"
#include "globals.h"

HC_TableView::HC_TableView (int renk, QTableView *parent ) :
    QTableView (parent)
{

    qDebug()<<"-hc-";


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
    auto *widget_table = new QWidget;
    widget_table->setWindowTitle ("table window");
    auto *Layout_table = new QVBoxLayout;
    widget_table->setLayout (Layout_table);

    table = new QTableView;

    Layout_table->addWidget (table);
    // //////////////////////////////////////////////

    // //////////////////////////////////////////////
    auto *allwdgts = new QWidget(this);
    allwdgts->setWindowTitle ("all window");
    auto *Layout_all = new QGridLayout();
    allwdgts->setMinimumSize (60,100);
    allwdgts->setLayout (Layout_all);
    Layout_all->addWidget (widget_buttonz,0,0 );
    Layout_all->addWidget (widget_table,0,1  );
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
HC_TableView::~HC_TableView()
= default;




/*
    connect(pB_ekle , &QPushButton::clicked , this, &HC_TableView::SLT_ekle );
    connect(pB_eklersm , &QPushButton::clicked , this, &HC_TableView::SLT_eklersm );
    connect(pB_grscks , &QPushButton::clicked , this, &HC_TableView::SLT_grscks );

    connect(pB_sil  , &QPushButton::clicked , this, &HC_TableView::SLT_sil );

    connect(pB_ilk  , &QPushButton::clicked , this, &HC_TableView::SLT_first );
    connect(pB_ncki , &QPushButton::clicked , this, &HC_TableView::SLT_previous );
    connect(pB_snrki, &QPushButton::clicked , this, &HC_TableView::SLT_next );
    connect(pB_son  , &QPushButton::clicked , this, &HC_TableView::SLT_last );




void HC_TableView::SLT_ekle ()    { emit sG_ekle();    }
void HC_TableView::SLT_eklersm () { emit sG_eklersm(); }
void HC_TableView::SLT_grscks ()  { emit sG_grscks();  }

void HC_TableView::SLT_sil ()     { emit sG_sil();     }

void HC_TableView::SLT_first ()   { emit sG_first();   }
void HC_TableView::SLT_next()     { emit sG_next();    }
void HC_TableView::SLT_previous() { emit sG_previous();}
void HC_TableView::SLT_last()     { emit sG_last();    }
*/
