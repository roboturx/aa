

#include "libs/hc_helptree.h"
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrintSupport>
#endif
#endif
#include "main/dbase.h"
#include "main/mainwindow.h"
//#include "main/login.h"


MainWindow::MainWindow()

{
    qDebug ()<<"   creat gui,";
    createGui();
    createDbase ();
    //Login();

    createActions();
    createStatusBar();
    createDockWindows();
}

MainWindow::~MainWindow()
{
}


void MainWindow::createGui()
{
    setWindowTitle(tr("Evren v23.01"));
    this->showMaximized();

    w_TABs = new QTabWidget(this);
    w_TABs->setTabPosition (QTabWidget::North);

    QWidget *DBFPage = new QWidget;
    QGridLayout *ayarlayout = new QGridLayout(DBFPage);

    ayarlayout->addWidget(w_TABs             ,  0, 0, 15, 2 );
    ayarlayout->addWidget(new QLabel("TabLAR") , 16, 0, 1, 1 );

    setCentralWidget(DBFPage);

}



void MainWindow::createDbase()
{
    dbase = new DBase;
    if (! dbase->setupDBase ())
    {
        /// hata ne /// baglanti yok
        dbase->yaz("----------------------------------------");
        dbase->yaz("HATA - Veri Tabanı Bağlantısı Yapılamadı");
        return;
    }

    /// baglanti var /// uygulama yoluna devam etsin

    dbase->yaz("----------------------------------------");
    dbase->yaz("OK - Veri Tabanı Bağlantısı Yapıldı");
    qDebug() << "OK - Veri Tabanı Bağlantısı Yapıldı";


    clsn = new hC_CLSN;
    clsn->tbsetup ();

    firma = new hC_FRM;
    firma->tbsetup ();

    hspdty = new hC_HSPDTY;
    hspdty->tbsetup ();


}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->setVisible (false);
    const QIcon printIcon = QIcon::fromTheme("document-print"
                              , QIcon(":/images/print.png"));
    QAction *printAct = new QAction(printIcon, tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the current form letter"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);
    fileMenu->addAction(printAct);
    fileToolBar->addAction(printAct);

    fileMenu->addSeparator();
    QAction *quitAct = fileMenu->addAction(tr("&Quit"),
                             this, &QWidget::close);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));

    viewMenu = menuBar()->addMenu(tr("&View"));
    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dock = new QDockWidget(tr("Hesaplar"), this);

    hesapTree = new hC_hesapTree(dock);

    helpTree = new hC_helpTree(this);

    dock->setWidget(hesapTree);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());



    connect(hesapTree,
            &hC_hesapTree::sgnHesap,
            this,
            &MainWindow::w_Tabs);
}

void MainWindow::w_Tabs(TaskItem *hesapItem)
{
    mw_currentHesapItem = hesapItem;
    createTabs();
}


void MainWindow::createTabs()
{
    qDebug()<< "mw create tabs  //";
    w_TABs->clear ();
    w_TABs->setIconSize(QSize (28,28));
 //   QGridLayout *TABlayout = new QGridLayout(this);

    int frameStyle = QFrame::Sunken /*| QFrame::Panel*/;

    QString h_Turu = mw_currentHesapItem->hesapTuru();
    integerLabel = new QLabel(h_Turu);
    integerLabel->setFrameStyle(frameStyle);

    //////////////////////////////////////////////////////
    ///
    /// 00001
    ///
    /// hesapPage
    /// her hesap için DBF TABı
    ///
    QWidget *hesapPage = new QWidget(this);
    QGridLayout *layout = new QGridLayout(hesapPage);
    //layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
//    layout->setColumnStretch(1, 1);
//    layout->setColumnMinimumWidth(1, 250);
//    layout->addWidget(w_TABs, 0, 0);

    w_TABs->addTab(hesapPage, h_Turu);

    if (h_Turu == "Konum")
    {
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/globe.png"));
    }
    if (h_Turu == "Şirket")
    {
        statusBar()->showMessage(tr("Firma Bilgileri"));
        layout->addWidget(firma, 0, 0);
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/file.png"));
    }
    if (h_Turu == "Şahıs")
    {

        statusBar()->showMessage(tr("Şahıs Adres Bilgileri"));
        layout->addWidget(clsn, 0, 0);
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/person.jpeg"));
    }
    if (h_Turu == "Aktif Hesap")
    {
        integerLabel->setText (QString::number (mw_currentHesapItem->hesapKod ())) ;
        statusBar()->showMessage(tr("Aktif Hesap"));
        layout->addWidget(hspdty, 0, 0);
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,
                 QIcon(":/rsm/ico/plus-minus-green.ico"));

        hspdty->slt_hesapChanged (mw_currentHesapItem);
    }
    if (h_Turu == "Pasif Hesap")
    {
        statusBar()->showMessage(tr("Pasif Hesap"));
        layout->addWidget(hspdty, 0, 0);
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,
                 QIcon(":/rsm/ico/plus-minus-red.ico"));

        hspdty->slt_hesapChanged (mw_currentHesapItem);

    }
    if (h_Turu == "Araç")
    {
        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/ex.ico"));
    }
    if (h_Turu == "Malzeme")
    {

        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/plt.png"));
    }
    if (h_Turu == "Gayrimenkul")
    {

        layout->addWidget(integerLabel, 1, 0);


        w_TABs->setTabIcon (0,QIcon(":/rsm/ico/gm2.ico"));
    }
    if (h_Turu == "Menkul")
    {

        layout->addWidget(integerLabel, 1, 0);

        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/candlestick.png"));


    }
    //////////////////////////////////////////////////////
    ///
    /// 00002
    ///
    /// her hesap için Ayarlar TABı
    ///
    ///
    QWidget *ayarlarPage = new QWidget(this);
    QGridLayout *ayarlayout = new QGridLayout(ayarlarPage);
    QPushButton *integerButton =
         new QPushButton(tr("QInputDialog::get&Int()"));

    colorLabel = new QLabel;
    colorLabel->setFrameStyle(frameStyle);
    colorButton = new QPushButton(tr("QColorDialog::get&Color()"));




    ayarlayout->setColumnStretch(1, 1);
    ayarlayout->setColumnMinimumWidth(1, 250);
    ayarlayout->addWidget(integerButton, 0, 0);
    ayarlayout->addWidget(new QLabel("Ayarlar"), 0, 1);
    ayarlayout->addWidget(colorButton, 1, 0);
    ayarlayout->addWidget(colorLabel, 1, 1);

   // ayarlayout->addItem(new QSpacerItem(3, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
    w_TABs->addTab(ayarlarPage, tr("Ayarlar"));

    //////////////////////////////////////////////////////
    ///
    /// 00003
    ///
    /// her hesap için Help TABı
    ///
    ///
    QWidget *helpPage = new QWidget(this);
    QGridLayout *helplayout = new QGridLayout(helpPage);



    helplayout->addWidget (helpTree);

    w_TABs->addTab(helpPage, tr("Yardım"));

        //////////////////////////////////////////////////////
        /// \brief connect
        ///
        ///
    connect(integerButton, &QAbstractButton::clicked,
            this, &MainWindow::setInteger);
    connect(colorButton, &QAbstractButton::clicked,
            this, &MainWindow::setColor);
//    connect(this, &hC_main::sg_hTurColor,
//            modelXML, &cm_TreeXML::hTurColor );

}

void MainWindow::closeEvent(QCloseEvent *)
{
    qDebug()<<"-----------  MW CLOSE ---------------";
    qDebug()<<"-----------  MW CLOSE hesap close  ***********************";
    this->hesapTree->close ();
    qDebug()<<"-----------  MW CLOSE hesap closed **********************--";
    qDebug()<<"-----------  MW CLOSE help close--////////////////////////";
    this->helpTree->close ();
    qDebug()<<"-----------  MW CLOSE help closed ///////////////////////////////////--";
    qDebug()<<"-----------  MW CLOSE ---------------";

}



void MainWindow::setInteger()
{
    //! [0]
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("Percentage:"), 25, 0, 100, 1, &ok);
    if (ok)
        integerLabel->setText(tr("%1%").arg(i));
    //! [0]
}



void MainWindow::setColor()
{
//    const QColorDialog::ColorDialogOptions options =
//            QFlag(colorDialogOptionsWidget->value());
    const QColor color =
            QColorDialog::getColor(Qt::green, this,
                          "Select Color", QFlag(1));
    if (color.isValid())
    {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
}


void MainWindow::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QTextDocument *document = textEdit->document();
    QPrinter printer;

    QPrintDialog dlg(&printer, this);
    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    document->print(&printer);
    statusBar()->showMessage(tr("Ready"), 2000);
#endif
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("Evren Hakkında"),
                       tr("Yaşadığımız <b>evren nesnelerden oluşur.</b> "
                          "Bu yazılım ile <b>evrenin nesneleri</b>ni, konum-zaman belirleyerek oluşturabilirsiniz. \n"
                          "Ve buna bağlı olarak nesneler arasındaki yazılımla belirlenen ilişkileri kullanabilirsiniz. "
                          "Yazılım, Evrenimizin genişlemekte olduğu gibi devamlı gelişme halindedir. "
                          "Genel anlamda yazılım, muhasebeyi nesnel olarak takip etmeyi amaçlar. "
                          "Bununla birlikte muhasebe sisteminde gerekli olan tüm nesnelerin özelliklerinide takip etmenizi sağlar"
                          ));
}
