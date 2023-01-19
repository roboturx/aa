#include "hc_main.h"
#include "main/dw_hesap.h"
//#include "main/cm_dlg_richtxt.h"



namespace {

const int StatusTimeout = AQP::MSecPerSecond * 10;
const QString FilenameSetting("Filename");
const QString GeometrySetting("Geometry");
const QString CurrentTaskPathSetting("CurrentTaskPath");
const int FirstFrame = 0;
const int LastFrame = 4;


QAction *createAction(const QString &icon,
                      const QString &text,
                      QMainWindow *parent,
                      const QKeySequence &shortcut=QKeySequence())
{
    QAction *action = new QAction(QIcon(icon), text, parent);
    if (!shortcut.isEmpty())
        action->setShortcut(shortcut);
    return action;
}

} // anonymous namespace


hC_main::hC_main()
    : QMainWindow()
    ,
      #ifndef CUSTOM_MODEL
      timedItem(0),
      #endif
      currentIcon(0)
{
    qDebug ()<<"        Constructor MAIN **************************";

    setAcceptDrops(true);
    this->setWindowTitle ("Muhasebe Kontrol");
    //this->setGeometry (20,20,800,500);
    //this->showMaximized();
    this->setObjectName ("obj_hC_main");

    createGui();
    createActions();
    createMenusAndToolBar();
    createDocks ();
    //createModelViewDelegate();
  //  createConnections();

    AQP::accelerateMenu(menuBar());
    setWindowTitle(tr("%1 (Hesap Dosyası)[*]")
                   .arg(QApplication::applicationName()));

    statusBar()->showMessage(tr("Uygulama Hazır"), StatusTimeout);

    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    iconTimeLine.setEasingCurve (QEasingCurve::InOutQuad);


    QCoreApplication::setOrganizationName("aaSoft");
    QCoreApplication::setOrganizationDomain("roboturx@gmail.com");
    QCoreApplication::setApplicationName("EVREN 23.1.1");


    QSettings settings;

    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();

    qDebug()<<"-----------    ::hChsp  Hesap dosyası kontrol ediliyor...";
    if (! QFile::exists(filename))
    {
        qDebug()<<"XXX "<<filename<<" :"<<QFile::exists(filename);
        qDebug()<<"-----------    ::hChsp Kayıtlı Hesap Dosyası Diskte bulunamadı !! ";
        qDebug() << "            Yeni Hesap Dosyası oluşturuluyor...";

        statusBar()->showMessage(tr("Dosya Yüklenemedi %1")
                                 .arg(filename), StatusTimeout);

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    if (filename.isEmpty()  )
    {
        qDebug()<<"-----------    ::hChsp filenew Hesap Dosya Kaydı Yok ... ";
        qDebug() << "            Yeni Dosya oluşturuluyor...";

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    else
    {
        qDebug()<<"-----------    ::hChsp XML Dosyası Diskte bulundu. ";
        qDebug() << "               Yükleniyor...";

        QMetaObject::invokeMethod(this, "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, filename),
                                  Q_ARG(QStringList, settings.value(
                                            CurrentTaskPathSetting).toStringList()));

    }
}


void hC_main::createGui()
{
    //errorMessageDialog = new QErrorMessage(this);

    qDebug ()<<"   creat gui,";
    /// 000 central widget = splitter
    wdgt_central = new QWidget(this);
    setCentralWidget(wdgt_central);

    /// 000-0  splitter = page 0 + page 1
    splitter = new QSplitter(wdgt_central);

    ///  000-0-0 page  hesaplar
  //  QWidget *page0 = new QWidget(splitter);

    ///  000-0-1 page  TABlar
    QWidget *page1 = new QWidget(splitter);
    QGridLayout *layout1 = new QGridLayout(page1);
    w_TABs = new QTabWidget(page1);
    w_TABs->setTabShape (QTabWidget::Triangular);
    w_TABs->setTabPosition (QTabWidget::North);
    layout1->setColumnStretch(1, 1);
    layout1->setColumnMinimumWidth(1, 250);
    layout1->addWidget(w_TABs             ,  0, 0, 16, 2 );
    layout1->addWidget(new QLabel("Tabs") , 17, 0, 1, 2 );

    layout1->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored,
                                     QSizePolicy::MinimumExpanding), 5, 0);


    QGridLayout *lyt_central;

    if (QGuiApplication::styleHints()->showIsFullScreen()
            || QGuiApplication::styleHints()->showIsMaximized())
    {
        QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
        QGroupBox *groupBox = new QGroupBox(
                    QGuiApplication::applicationDisplayName(), this);
        horizontalLayout->addWidget(groupBox);
        lyt_central = new QGridLayout(groupBox);

    }
    else
    {
        lyt_central = new QGridLayout(this);///?????
    }

    wdgt_central->setLayout (lyt_central);

    splitter->addWidget (page1);

    lyt_central->addWidget(splitter    ,0,1,1,1);

  //  login();

}


void hC_main::login()
{

    /// at the beginning, first mainwindow is showed,
    ///                    after login is executed

    // fade(true);

    /// veritabanı kontrol
    qDebug() << "db control";
    dbase = new DBase(this);
    //  dbase->setGeometry (800,300,300,480);
    //  dbase->setWindowTitle("Veri Tabanı Kontrol");
    dbase->show();

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
    //  this->setCentralWidget (dbase );



    /// login için esc-enter kullanımı
    /////////////////////////////////////
    /*
     logger= new Login;

WARNING  şifre için burayı kullan

       connect(logger, &Login::logok, this, &MW_main::yetkiler);
    connect(this, &MW_main::cikis, logger, &Login::logex );
    //connect(this, &MW_main::cikis, qApp , &QApplication::quit );

    //qDebug() << "main keys set ESC";
    QShortcut * sc_ESC = new QShortcut(
                QKeySequence(Qt::Key_Escape),this,
                SLOT(logouted() ));
    sc_ESC->setAutoRepeat(false);
*/


    //    sbox = new SortingBox;
    //dbox = new DragWidget;

    /// all things okey
    /// wait on main window for a key for connect

    //mw_hC_hsp = new hC_hsp;





    //this->setCentralWidget (mw_hC_hsp );
}



void hC_main::createTABs(QString h_Turu)
{

    w_TABs->clear ();
    w_TABs->setIconSize(QSize (28,28));

    int frameStyle = QFrame::Sunken | QFrame::Panel;

    integerLabel = new QLabel("Ayarlar");
    integerLabel->setFrameStyle(frameStyle);
    QPushButton *integerButton =
         new QPushButton(tr("QInputDialog::get&Int()"));

    colorLabel = new QLabel;
    colorLabel->setFrameStyle(frameStyle);
    colorButton = new QPushButton(tr("QColorDialog::get&Color()"));



    if (h_Turu == "Konum")
    {
        integerLabel = new QLabel(h_Turu, w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/globe.png"));

    }
    if (h_Turu == "Şirket")
    {
        integerLabel = new QLabel(h_Turu, w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/file.png"));
    }
    if (h_Turu == "Şahıs")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
                       integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);
        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/person.jpeg"));

    }
    if (h_Turu == "Aktif Hesap")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,
                 QIcon(":/rsm/ico/plus-minus-green.ico"));
    }
    if (h_Turu == "Pasif Hesap")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,
                 QIcon(":/rsm/ico/plus-minus-red.ico"));
    }
    if (h_Turu == "Araç")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/ex.ico"));
    }
    if (h_Turu == "Malzeme")
    {
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/plt.png"));
    }
    if (h_Turu == "Gayrimenkul")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/ico/gm2.ico"));
    }
    if (h_Turu == "Menkul")
    {
        integerLabel = new QLabel("h_Turu", w_TABs);
        integerLabel->setFrameStyle(frameStyle);
        QWidget *page1 = new QWidget(w_TABs);
        QGridLayout *layout = new QGridLayout(page1);
        layout->setColumnStretch(1, 1);
        layout->setColumnMinimumWidth(1, 250);
        //layout->addWidget(integerButton, 0, 0);
        layout->addWidget(integerLabel, 0, 1);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
        w_TABs->addTab(page1, h_Turu);
        w_TABs->setTabIcon (0,QIcon(":/rsm/icon/candlestick.png"));



    }
//    if (h_Turu == "")
//    {

//    }






    connect(integerButton, &QAbstractButton::clicked,
            this, &hC_main::setInteger);
    connect(colorButton, &QAbstractButton::clicked,
            this, &hC_main::setColor);
//    connect(this, &hC_main::sg_hTurColor,
//            modelXML, &cm_TreeXML::hTurColor );

    QWidget *page10 = new QWidget;
    QGridLayout *layout = new QGridLayout(page10);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(integerButton, 0, 0);
    layout->addWidget(integerLabel, 0, 1);
    layout->addWidget(colorButton, 1, 0);
    layout->addWidget(colorLabel, 1, 1);

    layout->addItem(new QSpacerItem(3, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
    w_TABs->addTab(page10, tr("Ayarlar"));
}


void hC_main::setColor()
{

    const QColor color = QColorDialog::getColor(Qt::green, this,
                                                "Renk Seçiniz", QFlag(1));
        if (color.isValid())
    {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }

}


void hC_main::setInteger()
{
    //! [0]
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("Percentage:"), 25, 0, 100, 1, &ok);
    if (ok)
        integerLabel->setText(tr("%1%").arg(i));
    //! [0]
}




void hC_main::fgenelAyarlar()
{
    qDebug()<<"----------- ************** -------------- ";
    // return true;
}

void hC_main::createActions()
{
    qDebug()<<"-----------    ::hChsp createActions";
    fileNewAction = createAction(":/rsm/images/filenew.png",
                                 tr("Yeni Hesap Dosyası"),
                                 this, QKeySequence::New);
    fileOpenAction = createAction(":/rsm/images/fileopen.png",
                                  tr("Hesap Dosyası Aç..."),
                                  this, QKeySequence::Open);
    fileSaveAction = createAction(":/rsm/images/filesave.png",
                                  tr("Kaydet"),
                                  this, QKeySequence::Save);
    fileSaveAsAction = createAction(":/rsm/images/filesave.png",
                                    tr("Farklı Kaydet..."), this
                                #if QT_VERSION >= 0x040500
                                    , QKeySequence::SaveAs
                                #endif
                                    );
    fileQuitAction = createAction(":/rsm/images/filequit.png",
                                  tr("Çıkış"), this);
#if QT_VERSION >= 0x040600
    fileQuitAction->setShortcuts(QKeySequence::Quit);
#else
    fileQuitAction->setShortcut(QKeySequence("Ctrl+Q"));
#endif
    editAddAction = createAction(":/rsm/images/editadd.png",
                                 tr("Hesap Ekle..."),
                                 this, QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/rsm/images/editdelete.png",
                                    tr("Hesap Sil..."),
                                    this, QKeySequence::Delete);

    editCutAction = createAction(":/rsm/images/editcut.png", tr("Kes"),
                                 this, QKeySequence::Cut);
    editPasteAction = createAction(":/rsm/images/editpaste.png", tr("Yapıştır"),
                                   this, QKeySequence::Paste);
    editMoveUpAction = createAction(":/rsm/images/editup.png", tr("Hesap Yukarı"),
                                    this, QKeySequence(tr("Ctrl+Up")));
    editMoveDownAction = createAction(":/rsm/images/editdown.png",
                                      tr("Hesap Aşağı"), this, QKeySequence(tr("Ctrl+Down")));
    editPromoteAction = createAction(":/rsm/images/editpromote.png",
                                     tr("Üst Hesap Yap"), this, QKeySequence(tr("Ctrl+Left")));
    editDemoteAction = createAction(":/rsm/images/editdemote.png",
                                    tr("Alt Hesap Yap"), this, QKeySequence(tr("Ctrl+Right")));

    editStartOrStopAction = createAction(":/rsm/images/0.png", tr("S&tart"),
                                         this, QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Kapalı Hesaplaı Gizle"),
                                                this);
    genelAyarlar = new QAction(tr("Ayarlar"), this);

    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}

void hC_main::createDocks()
{


    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QListWidget *customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
                           << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                           << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                           << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                           << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                           << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                           << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());


    //
    //    QDockWidget *dock2 = new QDockWidget(tr("Hesaplar"), this);
    //    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //    dock2->setWidget( dockwidget );
    //    addDockWidget(Qt::RightDockWidgetArea, dock2);

    dock = new QDockWidget(tr("Hesaplar"), this);
    dW_Hesap *hesaplar = new dW_Hesap(dock);
     dock->setWidget(hesaplar);
    //addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());



    dock = new QDockWidget(tr("Paragraphs"), this);
    QListWidget *paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()
                             << "Thank you for your payment which we have received today."
                             << "Your order has been dispatched and should be with you "
                                "within 28 days."
                             << "We have dispatched those items that were in stock. The "
                                "rest of your order will be dispatched once all the "
                                "remaining items have arrived at our warehouse. No "
                                "additional shipping charges will be made."
                             << "You made a small overpayment (less than $5) which we "
                                "will keep on account for you, or return at your request."
                             << "You made a small underpayment (less than $1), but we have "
                                "sent your order anyway. We'll add this underpayment to "
                                "your next bill."
                             << "Unfortunately you did not send enough money. Please remit "
                                "an additional $. Your order will be dispatched as soon as "
                                "the complete amount has been received."
                             << "You made an overpayment (more than $5). Do you wish to "
                                "buy more items, or should we return the excess to you?");
    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

//    connect(customerList, &QListWidget::currentTextChanged,
//            this, &hC_main::insertCustomer);
//    connect(paragraphsList, &QListWidget::currentTextChanged,
//            this, &hC_main::addParagraph);


}


void hC_main::createMenusAndToolBar()
{
    qDebug()<<"-----------    ::hChsp createMenusAndToolBar";

    QMenu *fileMenu = menuBar()->addMenu(tr("Dosya"));
    viewMenu = menuBar()->addMenu(tr("&View"));
    QToolBar *fileToolBar = addToolBar(tr("Dosya"));

//    setStyleSheet ("QMenu, QToolbar {"
//                   "background-color: solid darkred;"
//                   "color: cyan;"
//                   "font: 14pt "
//                   "}");

    foreach (QAction *action, QList<QAction*>() << fileNewAction
             << fileOpenAction << fileSaveAction << fileSaveAsAction)
    {
        fileMenu->addAction(action);
        if (action != fileSaveAsAction)
            fileToolBar->addAction(action);
        if (action == fileSaveAction || action == fileSaveAsAction)
            action->setEnabled(false);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAction);

    QAction *emptyAction = 0;
    QMenu *editMenu = menuBar()->addMenu(tr("Düzen"));
    QToolBar *editToolBar = addToolBar(tr("Düzen"));


    foreach (QAction *action, QList<QAction*>() << editAddAction
             << editDeleteAction << emptyAction
             << editCutAction << editPasteAction << emptyAction
             << editMoveUpAction << editMoveDownAction
             << editPromoteAction << editDemoteAction << emptyAction
             << editStartOrStopAction << editHideOrShowDoneTasksAction
             << genelAyarlar)

    {
        if (action == emptyAction) {
            editMenu->addSeparator();
            editToolBar->addSeparator();
            continue;
        }
        if (action != editHideOrShowDoneTasksAction)
            editToolBar->addAction(action);
        else
            editMenu->addSeparator();
        editMenu->addAction(action);
    }
}


void hC_main::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(fileNewAction);
    menu.addAction(fileOpenAction);
    menu.addAction(fileSaveAction);
    menu.exec(event->globalPos());
}

void hC_main::customContextMenuRequested(
        const QPoint &pos)
{
    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}








