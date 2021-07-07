#include "mw_depo.h"
#include "ui_mw_depo.h"
#include "globals.h"


MW_depo::MW_depo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MW_depo)
{
    ui->setupUi(this);

    MW_depo::cr_Depo();
    MW_depo::cr_DockWindows();
    MW_depo::cr_StatusBar();

}

void MW_depo::cr_Depo()
{


    QTabWidget *wtab = new QTabWidget();
    wtab->setMovable(true);
    wtab->setTabBarAutoHide(true);

    //CALISMA
    QWidget *clsm_wdgt = new QWidget;
    QGridLayout *clsm_layg = new QGridLayout(clsm_wdgt);

    QToolBox *clsm_tool = new QToolBox( clsm_wdgt ) ; //= new QToolBox;
    clsm_tool->addItem(new QLabel(),"Görev Emri");
    clsm_tool->insertItem(1, new QLabel(),"Görev Listesi");
    clsm_tool->insertItem(2, new QLabel(),"Çalışma Rapor");

    clsm_layg->addWidget( clsm_tool ,0,0,0);

    wtab->addTab( clsm_wdgt ,"ÇALIŞMA");

    // EVRAK

    QWidget *evrk_wdgt = new QWidget;
    QGridLayout *evrk_layg = new QGridLayout(evrk_wdgt);

    QToolBox *evrk_tool = new QToolBox( evrk_wdgt ) ; //= new QToolBox;
    evrk_tool->addItem(new QLabel(),"Trafik Sigortası");
    evrk_tool->insertItem(1, new QLabel(),"Kasko");
    evrk_tool->insertItem(2, new QLabel(),"Muayene");
    evrk_tool->insertItem(3, new QLabel(),"Egzost Muayene");
    evrk_tool->insertItem(4, new QLabel(),"OGS-KGS");

    evrk_layg->addWidget( evrk_tool ,0,0,0);
    wtab->addTab(evrk_wdgt,"EVRAK");

    //BAKIM


    QWidget *bkm_wdgt = new QWidget;
    QGridLayout *bkm_layg = new QGridLayout(bkm_wdgt);

    QToolBox *bkm_tool = new QToolBox( bkm_wdgt ) ; //= new QToolBox;
    bkm_tool->addItem(new QLabel(),"Yakıt");
    bkm_tool->insertItem(1, new QLabel(),"Akü");
    bkm_tool->insertItem(2, new QLabel(),"Lastik");
    bkm_tool->insertItem(3, new QLabel(),"Motor Yağı");
    bkm_tool->insertItem(4, new QLabel(),"Fren Hidrolik");
    bkm_tool->insertItem(5, new QLabel(),"Şanzuman Yağı");
    bkm_tool->insertItem(6, new QLabel(),"Filtreler");
    bkm_tool->insertItem(7, new QLabel(),"Ek Ekipmanlar");

    bkm_layg->addWidget( bkm_tool ,0,0,0);
    wtab->addTab(bkm_wdgt,"Bakım");

    //ARIZA


    QWidget *arz_wdgt = new QWidget;
    QGridLayout *arz_layg = new QGridLayout(arz_wdgt);

    QToolBox *arz_tool = new QToolBox( arz_wdgt ) ; //= new QToolBox;
    arz_tool->addItem(new QLabel(),"Araç Kabul");
    arz_tool->insertItem(1, new QLabel(),"Arıza Tespit");
    arz_tool->insertItem(1, new QLabel(),"Atölye-Usta Atama");
    arz_tool->insertItem(1, new QLabel(),"Malzeme Talep");

    arz_layg->addWidget( arz_tool ,0,0,0);
    wtab->addTab(arz_wdgt,"Arıza");



    //this->setCentralWidget(wtab);






}



void MW_depo::depo_()
{

}


void MW_depo::cr_DockWindows()
{
    //////////////////////////////////////  1. dock
    mw_dock1 = new QDockWidget( tr( "Makina Depo" ),this) ;
    mw_dock1->setFeatures(QDockWidget::DockWidgetClosable |
                           QDockWidget::DockWidgetFloatable |
                           QDockWidget::DockWidgetMovable );

    MW_depo:: addDockWidget(Qt::LeftDockWidgetArea, mw_dock1 );



    // dock içinde layout yapabilmek için widgety ekle
    // dock bir container, containere layout uygulanmaz
    QWidget *wd = new QWidget(  );
    mw_dock1->setWidget(wd);

    QGridLayout *mw_dc_lay = new QGridLayout();
    wd->setLayout( mw_dc_lay );

    QPushButton *pb1 = new QPushButton("Ekle"  );
    QPushButton *pb2 = new QPushButton("Sil"  );
    QPushButton *pb3 = new QPushButton("Rapor"  );
    QPushButton *pb4 = new QPushButton("Çıkış"  );
    myLabel = new QLabel( ); //resim göstermek için
    myLabel->setText("swdşkdsfsdfsdefgşlmdşfl");

    mw_dc_lay->addWidget(pb1,2,0);
    mw_dc_lay->addWidget( pb2  ,0,1);
    mw_dc_lay->addWidget(pb3,1,0);
    mw_dc_lay->addWidget(pb4,1,1);
    mw_dc_lay->addWidget( myLabel,0,0 );


    //////////////////////////////////////  2. dock
    mw_dock2 = new QDockWidget(tr("İş Listesi"), this);
    mw_dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, mw_dock2);


    QListWidget *customerList = new QListWidget(mw_dock2);
    customerList->addItems(QStringList()
                           << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                           << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                           << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                           << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                           << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                           << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");

    mw_dock2->setWidget(customerList);



}






MW_depo::~MW_depo()
{
    //delete ui;
}

