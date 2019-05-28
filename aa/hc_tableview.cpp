#include "hc_tableview.h"
#include "globals.h"

HC_TableView::HC_TableView (int &renk, QTableView *parent ) :
    QTableView (parent)
{


    QIcon icon;
    int x=20,y=20;


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

   QFrame * fR_mn = new QFrame() ;
    fR_mn->setStyleSheet ("background-color:green");
    fR_mn->setFrameStyle (QFrame::Panel | QFrame::Raised);
    fR_mn->setLineWidth (3);
    fR_mn->setMidLineWidth (2);
    fR_mn->setGeometry (0,0,40,300);


    QVBoxLayout *LYv_nv = new QVBoxLayout;

    LYv_nv->addWidget (pB_ekle );
    LYv_nv->addWidget (pB_eklersm );
    LYv_nv->addStretch (1);
    LYv_nv->addWidget (pB_sil  );
    LYv_nv->addWidget (pB_ilk  );
    LYv_nv->addWidget (pB_ncki );
    LYv_nv->addWidget (pB_snrki);
    LYv_nv->addWidget (pB_son  );
    LYv_nv->addStretch (1);
    LYv_nv->addWidget (pB_grscks );
    LYv_nv->addStretch (4);
    table = new QTableView;

    QGridLayout *LYg_nv = new QGridLayout();
    this->setLayout (LYg_nv);
/*
    QPainter pntr();
    QLinearGradient grd(0,0,100,100);

    grd.setColorAt (0.0,QColor(QRgb(0x40434a)));
    grd.setColorAt (1.0,QColor(QRgb(0x90434a)));


    QRect rec(100,100,300,300);
    pntr.fillRect (rec,grd);
*/




    QString str = "color: rgba(155,255,155,255);"
                  " background-color : qlineargradient(spread:pad, "
                  "x1:0, y1:0, x2:1, y2:0, stop:0 "
                  "rgba(26, 84, 43, 200), stop:1 "
                  "rgba(24, 276, 148, 225));"
                  "selection-background-color: rgba(155,255,155,255);"
                  "selection-color: rgba(25,25,25,255);" ;

    //this->table->setStyleSheet (str);
    QString str2 = "color: rgba(155,255,155,255);"
                  " background-color : qlineargradient(spread:pad, "
                  "x1:0, y1:0, x2:0, y2:5, stop:0 "
                  "rgba(12, 41, 62, 10), stop:1 "
                  "rgba(22, 249, 172, 225));"
                  "selection-background-color: rgba(155,255,155,255);"
                  "selection-color: rgba(25,25,25,255);" ;
    if (renk==1)
    //this->setStyleSheet (str2);


this->setAlternatingRowColors (true);

    LYg_nv->addLayout (LYv_nv  ,0,0,1,1 );
    LYg_nv->addWidget (table   ,0,1,1,1 );
}
HC_TableView::~HC_TableView()
{

}




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
