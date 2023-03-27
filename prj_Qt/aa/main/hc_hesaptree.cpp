#include "main/hc_hesaptree.h"
#include "hsap/hc_hspadd.h"
#include "main/cm_dlg_richtxt.h"


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


hC_hesapTree::hC_hesapTree(QWidget * parent)
    : QMainWindow()
    ,
      #ifndef CUSTOM_MODEL
      timedItem(0),
      #endif
      currentIcon(0)
{
    qDebug ()<<"        Constructor MAIN **************************";

    createModelViewDelegate();
    createGui();
    createActions();
    createMenusAndToolBar();
    createConnections();

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

hC_hesapTree::~hC_hesapTree()
{
//    qDebug()<<"----------- ~ trreee"
//             << " filename               : " << modelXML->filename()
//             << " pathforindex (curindex): " << modelXML->pathForIndex(treeViewXML->currentIndex());
    stopTiming();

        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, modelXML->filename());
        settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(treeViewXML->currentIndex()));

       qDebug() <<"   ~ trree    close -> settings.filename "<< settings.fileName();

}

TaskItem* hC_hesapTree::getCurrentItem()
{
    qDebug()<<"-----------    ::hChsp getcurrentitem";
    TaskItem* currentItem = static_cast<TaskItem*>
            (treeViewXML->currentIndex().internalPointer());
    //        if ( currentItem)
    //        {
    //            qDebug() << "               ui hsp::getcurrentItem" ;
    //            qDebug() << "               :kod:" << currentItem->hesapKod ()
    //                     << "               :ad :" << currentItem->hesapAd ()
    //                     << "               :tpl:" << QString::number(currentItem->isTopluHesap())
    //                     << "               :tur:" << currentItem->hesapTuru()
    //                     << "               :ust:" << currentItem->ustHesap()
    //                     << "               ui currentItem" ;
    //        }
    return  currentItem;


}

/// 100-01
///
void hC_hesapTree::createModelViewDelegate()
{
    qDebug()<<"-----------    ::hChsp cr mdl vwv";

    treeViewXML = new QTreeView;
    modelXML    = new cm_TreeXML(this);

    treeViewXML->setDragDropMode(QAbstractItemView::InternalMove);

#ifdef MODEL_TEST
    (void) new ModelTest(modelXML, this);
#endif

    // kod kolonunu gizle
    treeViewXML->setColumnHidden(1,true);
    treeViewXML->setAllColumnsShowFocus(false);
    treeViewXML->setAnimated (true);
    treeViewXML->setAutoExpandDelay (100);
    treeViewXML->setIndentation (16);
    treeViewXML->setSelectionBehavior (QAbstractItemView::SelectItems);
    treeViewXML->setSelectionMode (QAbstractItemView::SingleSelection);


    // xx ile gönderilen renk kodu column 0 için text rengi olur
//    int xx= {0x00ff00};
//    cL_dlG_ColmColor *clmColor =
//        new cL_dlG_ColmColor(xx,treeViewXML->currentIndex (),this);

//    treeViewXML->setItemDelegateForColumn(0, clmColor);

    treeViewXML->setItemDelegateForColumn(1, new cm_dlG_RichTxt);
    treeViewXML->setItemDelegateForColumn(3, new cm_dlG_cb_hTur);
    treeViewXML->setModel(modelXML);

    lB_Hesap = new QLabel("Kod-------");

    //pi_Hesap_Kod = new quint64{};
    //ps_Hesap_Ad = new QString{};


}



void hC_hesapTree::createGui()
{

    QWidget *page0 = new QWidget;
    QGridLayout *layout0 = new QGridLayout(page0);

    layout0->setColumnStretch(1, 1);
    layout0->setColumnMinimumWidth(1, 250);
    layout0->addWidget(treeViewXML , 0, 0, 16, 2 );
    layout0->addWidget(lB_Hesap, 17, 0, 1, 2 );


    layout0->addItem(new QSpacerItem(0, 0,
                                     QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);

    /// central widget
    wdgt_central = new QWidget;
    setCentralWidget(wdgt_central);
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
        lyt_central = new QGridLayout(this);
    }
    wdgt_central->setLayout (lyt_central);

    QSplitter *splitter = new QSplitter(wdgt_central);
    splitter->addWidget (page0);
//    splitter->addWidget (toolbox);

    lyt_central->addWidget(splitter    ,0,1,1,1);

    setCentralWidget (wdgt_central);


}




void hC_hesapTree::createActions()
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
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}


void hC_hesapTree::createMenusAndToolBar()
{
    qDebug()<<"-----------    ::hChsp createMenusAndToolBar";

    /*QMenu **/fileMenu = menuBar()->addMenu(tr("Dosya"));
    /*QToolBar **/fileToolBar = addToolBar(tr("Dosya"));
    fileToolBar->setAllowedAreas (Qt::LeftToolBarArea);

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
    editToolBar->setAllowedAreas (Qt::LeftToolBarArea);

    foreach (QAction *action, QList<QAction*>() << editAddAction
             << editDeleteAction << emptyAction
             << editCutAction << editPasteAction << emptyAction
             << editMoveUpAction << editMoveDownAction
             << editPromoteAction << editDemoteAction << emptyAction
             << editStartOrStopAction << editHideOrShowDoneTasksAction)

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


void hC_hesapTree::createConnections()
{
    qDebug()<<"-----------    ::hChsp createConnections";
    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this, &hC_hesapTree::updateUi);

    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &hC_hesapTree::updateUi);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(customContextMenuRequested(const QPoint&)));

    connect(modelXML,
            SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            this, SLOT(setDirty()));

    connect(modelXML, SIGNAL(stopTiming()), this,
            SLOT(stopTiming()));


    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));

  //  connect(modelXML, &cm_TreeXML::);

    QHash<QAction*, QString> slotForAction;
    slotForAction[fileNewAction] = SLOT(fileNew());
    slotForAction[fileOpenAction] = SLOT(fileOpen());
    slotForAction[fileSaveAction] = SLOT(fileSave());
    slotForAction[fileSaveAsAction] = SLOT(fileSaveAs());
    slotForAction[fileQuitAction] = SLOT(close());
    slotForAction[editAddAction] = SLOT(editAdd());
    slotForAction[editDeleteAction] = SLOT(editDelete());

    slotForAction[editCutAction] = SLOT(editCut());
    slotForAction[editPasteAction] = SLOT(editPaste());
    slotForAction[editMoveUpAction] = SLOT(editMoveUp());
    slotForAction[editMoveDownAction] = SLOT(editMoveDown());
    slotForAction[editPromoteAction] = SLOT(editPromote());
    slotForAction[editDemoteAction] = SLOT(editDemote());

    QHashIterator<QAction*, QString> i(slotForAction);
    while (i.hasNext()) {
        i.next();
        connect(i.key(), SIGNAL(triggered()),
                this, qPrintable(i.value()));
    }

    connect(editStartOrStopAction, SIGNAL(triggered(bool)),
            this, SLOT(editStartOrStop(bool)));
    connect(editHideOrShowDoneTasksAction, SIGNAL(triggered(bool)),
            this, SLOT(editHideOrShowDoneTasks(bool)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon(int)));
    qDebug() << "                  kntrl son";
}


void hC_hesapTree::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(fileNewAction);
    menu.addAction(fileOpenAction);
    menu.addAction(fileSaveAction);
    menu.exec(event->globalPos());
}

void hC_hesapTree::customContextMenuRequested(
        const QPoint &pos)
{
    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}



///////////////////////////***************************************
void hC_hesapTree::updateUi()
{
    qDebug()<<"-----------    ::hChsp updateUi..."
           <<modelXML->rowCount();
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = treeViewXML->currentIndex().isValid();

    //modelXML->getListXML ();

    foreach (QAction *action, QList<QAction*>()
             << editDeleteAction
             << editMoveUpAction << editMoveDownAction
             << editCutAction
             << editPromoteAction << editDemoteAction)

        action->setEnabled(enable);

    editStartOrStopAction->setEnabled(rows);
    editPasteAction->setEnabled(modelXML->hasCutItem());




    TaskItem* currentItem = static_cast<TaskItem*>
            (treeViewXML->currentIndex().internalPointer());
    if ( currentItem)
    {
        ///
        ///  mevcut hesap tüm evrene yayılsın
        ///

        emit sgnHesap (currentItem );
        qDebug()<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
        qDebug()<<" hchsaptree update hesapkod: "
               << currentItem->hesapKod();

        ///
        /// hesap değiştiğinde detaylarda değişsin
        ///
        ///

        lB_Hesap->setText(QString::number(currentItem->hesapKod()) +" : "+
                          currentItem->parent()->hesapAd ()+" - "+
                          currentItem->hesapAd() +" - "+
                          currentItem->hesapAcklm ()+" : "+
                          QString::number(currentItem->isTopluHesap() ) +" : "+
                          currentItem->hesapTuru() +" : "+
                          currentItem->DBFile()
                          );
    }
}






void hC_hesapTree::setCurrentIndex(const QModelIndex &index)
{
    //qDebug()<<"-----------    ::hChsp setcurindx";
    if (index.isValid()) {
        treeViewXML->scrollTo(index);
        treeViewXML->setCurrentIndex(index);
    }
}



////////////// E D I T S //////////////////////////////////////////////
///
///



void hC_hesapTree::editAdd()
{
   qDebug()<<"-----------    ::hChsp editAdd Yeni Hesap Ekleniyor...............";

   hC_hspAdd* ekle = new hC_hspAdd;
   ekle->show ();



   QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->insertRows(0, 1, index))
    {
        index = modelXML->index(0, 0, index);
        setCurrentIndex(index);
        //treeViewXML->edit(index);

        TaskItem * yeniItem = new TaskItem;
        yeniItem = ekle->yeni();
        TaskItem * Item = getCurrentItem ();
        Item->setHesapAd (yeniItem->hesapAd ())  ;
        Item->setHesapAcklm (yeniItem->hesapAcklm ())  ;
        Item->setTopluHesap (yeniItem->isTopluHesap ())  ;
        Item->setHesapTuru (yeniItem->hesapTuru ())  ;
        Item->setUstHesap (yeniItem->ustHesap ())  ;
        Item->setDBFile (yeniItem->DBFile ())  ;
        setDirty();
        updateUi();
    }

}



void hC_hesapTree::editDelete()
{
    //qDebug()<<"-----------    ::hChsp editDelete";
    //qDebug() << "editdelete";
    QModelIndex index = treeViewXML->currentIndex();
    if (!index.isValid())
        return;

    QString name = modelXML->data(index).toString();
    int rows = modelXML->rowCount(index);
    if (modelXML->isTimedItem(index))
        stopTiming();
qDebug()<<"--edit delete 01";
    QString message;
    if (rows == 0)
        message = tr("<p>HESAP SİL '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>HESAP SİL '%1' ve alt hesabı (ve "
                     "alt hesaba bağlı hesaplar)").arg(name);
    else if (rows > 1)
        message = tr("<p>HESAP SİL '%1' ve ona bağlı %2 alt hesap "
                     "(ve alt hesaplara bağlı hesaplar)").arg(name).arg(rows);
    if (!AQP::okToDelete(this, tr("Delete"), message))
        return;
    qDebug()<<"--edit delete 02";
    modelXML->removeRow(index.row(), index.parent());
    qDebug()<<"--edit delete 03";
    setDirty();
    qDebug()<<"--edit delete 04";
    updateUi();
    qDebug()<<"--edit delete s0n";
}




void hC_hesapTree::editCut()
{
    qDebug()<<"-----------    ::hChsp editCut";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}


void hC_hesapTree::editPaste()
{
    qDebug()<<"-----------    ::hChsp editpaste";
    setCurrentIndex(modelXML->paste(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hesapTree::editMoveUp()
{
    qDebug()<<"-----------    ::hChsp editmoveup";
    treeViewXML->setCurrentIndex(
                modelXML->moveUp(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hesapTree::editMoveDown()
{
    qDebug()<<"-----------    ::hChsp editmovedown";

    treeViewXML->setCurrentIndex(
                modelXML->moveDown(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hesapTree::editPromote()
{
    qDebug()<<"-----------    ::hChsp editPromote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hesapTree::editDemote()
{

    qDebug()<<"-----------    ::hChsp editDemote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    treeViewXML->setCurrentIndex(modelXML->demote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}




//////////// X M L  F I L E  O P E R A T I O N S ////////////////////
///
///
///




bool hC_hesapTree::okToClearData()
{
   // qDebug()<<"-----------    ::hChsp OkToClearData";
    if (isWindowModified())
        return AQP::okToClearData(&hC_hesapTree::fileSave, this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}



void hC_hesapTree::fileNew()
{
   // qDebug()<<"-----------    ::hChsp filenew XML";

    if (!okToClearData())
        return;
    modelXML->clear();
    modelXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - İsimsiz hesap dosyası[*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}


void hC_hesapTree::fileOpen()
{
   // qDebug()<<"-----------    ::hChsp fileOpen XML";
    //qDebug() << "fileopen";
    if (!okToClearData())
        return;
    QString filename = modelXML->filename();
    QString dir(filename.isEmpty() ? QString(".")
                                   : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
                                            tr("%1 - Open").arg(QApplication::applicationName()),
                                            dir, tr("konumlar (*.knm)"));
    if (!filename.isEmpty())
        load(filename);
}


void hC_hesapTree::load(const QString &filename,
                  const QStringList &taskPath)
{
   // qDebug()<<"-----------    ::hChsp load XML";
    qDebug() << "loading file (filename) '" << filename
             << " ' at path (taskPath): " << taskPath;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    try {
        modelXML->load(filename);
        if (!taskPath.isEmpty())
        {
            setCurrentIndex(modelXML->indexForPath(taskPath));
        }
        for (int column = 0;
             column < modelXML->columnCount();
             ++column)
        {
            //  treeViewXML->resizeColumnToContents(column);
            treeViewXML->setColumnWidth (0,200);
            treeViewXML->setColumnWidth (1,100);
            treeViewXML->setColumnWidth (2,50);
            treeViewXML->setColumnWidth (3,100);
            treeViewXML->setColumnWidth (4,400);

        }
        treeViewXML->setMinimumWidth (50);
        treeViewXML->header()->setStretchLastSection(false);
        treeViewXML->setColumnHidden (5,true);
        treeViewXML->setAllColumnsShowFocus (false);
        treeViewXML->setIndentation (10);


        setDirty(false);

        setWindowTitle(tr("%1 - %2[*]")
                       .arg(QApplication::applicationName(),
                            QFileInfo(filename).fileName()));

        statusBar()->showMessage(tr("%1 yüklendi").arg(filename),
                                 StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("HATA"), tr("Yüklemede Hata %1: %2\n"
                                          "yeni dosya oluşturuluyor")
                     .arg(filename,QString::fromUtf8(error.what())));


    }
    updateUi();
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
    treeViewXML->setFocus();
    QApplication::restoreOverrideCursor();

}



bool hC_hesapTree::fileSave()
{
    qDebug()<<"-----------    ::hChsp fileSave XML";
    // qDebug() << "filesave";
    bool saved = false;
    if (modelXML->filename().isEmpty())
        saved = fileSaveAs();
    else {
        try {
            modelXML->save();
            setDirty(false);
            setWindowTitle(tr("%1 - %2[*]")
                           .arg(QApplication::applicationName())
                           .arg(QFileInfo(modelXML->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                                     .arg(modelXML->filename()), StatusTimeout);
            saved = true;
        } catch (AQP::Error &error) {
            AQP::warning(this, tr("Error"),
                         tr("Failed to save %1: %2").arg(modelXML->filename())
                         .arg(QString::fromUtf8(error.what())));
        }
    }
    updateUi();
    return saved;
}


bool hC_hesapTree::fileSaveAs()
{
    qDebug()<<"-----------    ::hChsp fileSaveAs XML";
    // qDebug() << "filesaveas";
    QString filename = modelXML->filename();
    QString dir = filename.isEmpty() ? "."
                                     : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
                                            tr("%1 - Save As").arg(QApplication::applicationName()),
                                            dir,
                                            tr("%1 (*.knm)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".knm"))
        filename += ".knm";
    modelXML->setFilename(filename);
    return fileSave();
}





//////////////////// O T H E R S /////////////////////////////////
///
///
///
///

void hC_hesapTree::closeEvent(QCloseEvent *event)
{
    qDebug()<<"-----------    ::hChsp closeEvent"
           << " filename               : " << modelXML->filename()
           << " pathforindex (curindex): " << modelXML->pathForIndex(treeViewXML->currentIndex());
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, modelXML->filename());
        settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(treeViewXML->currentIndex()));

        qDebug() <<"        close -> settings.filename "<< settings.fileName();
        event->accept();
    }
    else
        event->ignore();
}




////////////////// T A S K S ////////////////////////////////////////////////
///
///



void hC_hesapTree::stopTiming()
{
    qDebug()<<"-----------    ::hChsp stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}

void hC_hesapTree::hesapdegisti()
{
    qDebug()<<"-----------    hC_hesapTree::hesapdegisti() p";
}


void hC_hesapTree::editStartOrStop(bool start)
{
    qDebug()<<"-----------    ::hChsp editStartOrStop";
    timer.stop();
    iconTimeLine.stop();
    if (start) { // start the clock iff there's a current task
        QModelIndex index = treeViewXML->currentIndex();
        if (!index.isValid()) {
            editStartOrStopAction->setChecked(false);
            start = false;
        }
        else {
            QIcon icon(":/0.png");
            QDateTime now = QDateTime::currentDateTime();

            modelXML->setTimedItem(index);
            modelXML->addDateTimeToTimedItem(now, now);
            modelXML->setIconForTimedItem(icon);

            editStartOrStopAction->setIcon(icon);

            // qt 6 timedTime.restart();
            timer.start();
            iconTimeLine.start();
        }
    }
    else
    { // stop the clock
        timeout(); // update to now

        modelXML->setIconForTimedItem();
        modelXML->clearTimedItem();
        editStartOrStopAction->setIcon(QIcon(":/rsm/images/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top")
                                         : tr("S&tart"));
    editStartOrStopAction->setIcon(QIcon(start ? tr(":/rsm/images/4.png")
                                               : tr(":/rsm/images/0.png")));
}


void hC_hesapTree::timeout()
{
    qDebug()<<"-----------    ::hChsp timeout";
    modelXML->incrementEndTimeForTimedItem(timer.remainingTime ());
    timer.start ();
}


void hC_hesapTree::updateIcon(int frame)
{
    qDebug()<<"-----------    ::hChsp updateIcon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}


void hC_hesapTree::editHideOrShowDoneTasks(bool hide)
{
    // qDebug()<<"-----------    ::hChsp edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}


void hC_hesapTree::hideOrShowDoneTask(bool hide,
                                const QModelIndex &index)
{
    // qDebug()<<"-----------    ::hChsp hideorshowdntsk";
    bool hideThisOne = hide && modelXML->isChecked(index);
    if (index.isValid())
        treeViewXML->setRowHidden(index.row(), index.parent(),
                                  hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelXML->index(row, 0, index));
    }
}




///////////////////////////////////////////////////////////////
/// \brief The cL_HesapListesi class
/// xml dosyasından hesap adları ve renklerini
/// qpair olarak veren sınıf


cL_HesapListesi::PairHesapColor cL_HesapListesi::getHesapListesi(QString hangihesaplar)
{

    setHesapListesi( hangihesaplar);
    return qp_hesapListesi;
}

cL_HesapListesi::PairHesapColor cL_HesapListesi::setHesapListesi(QString hangiListe)
{
    // set
    if (hangiListe == "")
    {
    }
    else if (hangiListe == "")
    {

    }

    return qp_hesapListesi;
}
