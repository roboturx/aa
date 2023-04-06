#include "libs/hc_helptree.h"
#include "main/cm_dlg_richtxt.h"


namespace {

const int StatusTimeout = AQP::MSecPerSecond * 10;
const QString helpFilenameSetting("helpFilename");
//const QString GeometrySetting("Geometry");
const QString CurrentHelpPathSetting("CurrentHelpPath");
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


hC_helpTree::hC_helpTree(QWidget * parent)
    : QMainWindow()
//    ,
//      #ifndef CUSTOM_MODEL
//      timedItem(0),
//      #endif
//      currentIcon(0)
{
    qDebug ()<<"        Constructor hC_helpTree **************************";

    createModelViewDelegate();
    createGui();
    createActions();
    createMenusAndToolBar();
    createConnections();

    AQP::accelerateMenu(menuBar());
    setWindowTitle(tr("%1 (Yardım Dosyası)[*]")
                   .arg(QApplication::applicationName()));

    statusBar()->showMessage(tr("Uygulama Hazır"), StatusTimeout);

    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    iconTimeLine.setEasingCurve (QEasingCurve::InOutQuad);


 //   QCoreApplication::setOrganizationName("aaSoft");
  //  QCoreApplication::setOrganizationDomain("roboturx@gmail.com");
   // QCoreApplication::setApplicationName("EVREN 23.4.1");


    QSettings settings;

    //restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString helpFilename = settings.value(helpFilenameSetting).toString();
    QString helpDBFilename = "evren.hlp";
    qDebug()<<"::hChlp  Help dosyası kontrol ediliyor...";
    if (! QFile::exists(helpDBFilename))
    {
        qDebug()<<"  "<<helpDBFilename<<" :"<<QFile::exists(helpDBFilename);
        qDebug()<<"::hChlp Kayıtlı Yardım DBF Dosyası Diskte bulunamadı !! ";
        qDebug() << "                 Yeni Yardım Dosyası oluşturuluyor...";

        statusBar()->showMessage(tr("YRDM DBF Dosya Yüklenemedi %1")
                                 .arg(helpDBFilename), StatusTimeout);

        QTimer::singleShot(0, this, SLOT(fileDBNew()));
    }
    if (! QFile::exists(helpFilename))
    {
        qDebug()<<"  "<<helpFilename<<" :"<<QFile::exists(helpFilename);
        qDebug()<<"::hChlp Kayıtlı Yardım XML Dosyası Diskte bulunamadı !! ";
        qDebug() << "                 Yeni Yardım Dosyası oluşturuluyor...";

        statusBar()->showMessage(tr("Dosya Yüklenemedi %1")
                                 .arg(helpFilename), StatusTimeout);

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    if (helpFilename.isEmpty()  )
    {
        qDebug()<<  "  ::hChlp filenew Yardım Dosya Kaydı Yok ... ";
        qDebug() << "                 Yeni Dosya oluşturuluyor...";

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    else
    {
        qDebug()<<  "  ::hChlp XML Dosyası Diskte bulundu. ";
        qDebug() << "                        Yükleniyor...";

        QMetaObject::invokeMethod(this, "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, helpFilename),
                                  Q_ARG(QStringList, settings.value(
                                            CurrentHelpPathSetting).toStringList()));

    }
}

hC_helpTree::~hC_helpTree()
{
    qDebug()<< "~~~~ helptree"
            << "     filename : " << modelHelpXML->filename()
            << "     pathindx : " << modelHelpXML->pathForIndex(treeViewXML->currentIndex());
    stopTiming();

    QSettings settings;
  //  settings.setValue(GeometrySetting, saveGeometry());
    settings.setValue(helpFilenameSetting, modelHelpXML->filename());
    settings.setValue(CurrentHelpPathSetting,
                          modelHelpXML->pathForIndex(treeViewXML->currentIndex()));
    qDebug() <<"~~~~ helptree destrctr -> settings.helpFilename :"<< settings.fileName ();

}

HelpItem* hC_helpTree::getCurrentItem()
{
    qDebug()<<":: hChlp getcurrentitem";
    HelpItem* currentYardım = static_cast<HelpItem*>
            (treeViewXML->currentIndex().internalPointer());
    return  currentYardım;
}

/// 100-01
///
void hC_helpTree::createModelViewDelegate()
{
    qDebug()<<":: hChlpTree model view";

    treeViewXML  = new QTreeView;
    modelHelpXML = new cm_HELPTreeXML(this);

    treeViewXML->setDragDropMode(QAbstractItemView::InternalMove);

#ifdef MODEL_TEST
    (void) new ModelTest(modelHelpXML, this);
#endif

    // kod kolonunu gizle
    //treeViewXML->setColumnHidden(1,true);
    treeViewXML->setAllColumnsShowFocus(false);
    treeViewXML->setAnimated (true);
    treeViewXML->setAutoExpandDelay (100);
    treeViewXML->setIndentation (46);
    treeViewXML->setSelectionBehavior (QAbstractItemView::SelectItems);
    treeViewXML->setSelectionMode (QAbstractItemView::SingleSelection);

//    treeViewXML->setItemDelegateForColumn(0, clmColor);

    treeViewXML->setItemDelegateForColumn(0, new cm_dlG_RichTxt);
    treeViewXML->setItemDelegateForColumn(1, new cm_dlG_RichTxt);
   // treeViewXML->setItemDelegateForColumn(2, new cm_dlG_cb_hTur);
    treeViewXML->setModel(modelHelpXML);



}



void hC_helpTree::createGui()
{

    QWidget *page0 = new QWidget(this);
    QVBoxLayout *layout0 = new QVBoxLayout(page0);

    lB_Help = new QLabel("Kod-------");
    tE_yrdm = new hC_TextEdit;
    layout0->addWidget(treeViewXML);
    layout0->addWidget(tE_yrdm);
    layout0->addWidget(lB_Help   );

    /// central widget
    wdgt_central = new QWidget;
    setCentralWidget(page0);

}




void hC_helpTree::createActions()
{
    qDebug()<<"-----------    ::hChlp createActions";
    fileNewAction = createAction(":/rsm/images/filenew.png",
                                 tr("Yeni Yardım Dosyası"),
                                 this, QKeySequence::New);
    fileOpenAction = createAction(":/rsm/images/fileopen.png",
                                  tr("Yardım Dosyası Aç..."),
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
                                 tr("Yardım Ekle..."),
                                 this, QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/rsm/images/editdelete.png",
                                    tr("Yardım Sil..."),
                                    this, QKeySequence::Delete);

    editCutAction = createAction(":/rsm/images/editcut.png", tr("Kes"),
                                 this, QKeySequence::Cut);
    editPasteAction = createAction(":/rsm/images/editpaste.png", tr("Yapıştır"),
                                   this, QKeySequence::Paste);
    editMoveUpAction = createAction(":/rsm/images/editup.png", tr("Yardım Yukarı"),
                                    this, QKeySequence(tr("Ctrl+Up")));
    editMoveDownAction = createAction(":/rsm/images/editdown.png",
                                      tr("Yardım Aşağı"), this, QKeySequence(tr("Ctrl+Down")));
    editPromoteAction = createAction(":/rsm/images/editpromote.png",
                                     tr("Üst Yardım Yap"), this, QKeySequence(tr("Ctrl+Left")));
    editDemoteAction = createAction(":/rsm/images/editdemote.png",
                                    tr("Alt Yardım Yap"), this, QKeySequence(tr("Ctrl+Right")));

    editStartOrStopAction = createAction(":/rsm/images/0.png", tr("S&tart"),
                                         this, QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Kapalı Yardımlaı Gizle"),
                                                this);
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}


void hC_helpTree::createMenusAndToolBar()
{
    qDebug()<<"-----------    ::hChlp createMenusAndToolBar";

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


void hC_helpTree::createConnections()
{
    qDebug()<<"-----------    ::hChlp createConnections";
    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this, &hC_helpTree::updateUi);

    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &hC_helpTree::updateUi);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customContextMenuRequested(QPoint)));

    connect(modelHelpXML,
            SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(setDirty()));

    connect(modelHelpXML, SIGNAL(stopTiming()), this,
            SLOT(stopTiming()));


    connect(modelHelpXML, SIGNAL(modelReset()), this, SLOT(setDirty()));
    connect (tE_yrdm, &hC_TextEdit::yrdmTextChanged,
             this, [ this]()
            {

        qDebug()<< tE_yrdm->getTextEdit()->toHtml();
         qDebug()<<"yrdm txt changed************************";
                /// mevcut indexi al
                QModelIndex cindex = treeViewXML->currentIndex() ;

                /// mevcut indexteki yardım içeriği 1. kolonda
                /// 1 kolon için yeni bir index oluştur.
                QModelIndex ourindex = modelHelpXML->index
                                  (cindex.row (), 1, cindex.parent ());

                /// yeni oluşturduğun indexte kolon 1 e te_yrdm içeriğini kaydet
                ///

                modelHelpXML->setData (ourindex,
                   tE_yrdm->getTextEdit ()->toHtml (),
                         Qt::EditRole);
            }

            );



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


void hC_helpTree::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(fileNewAction);
    menu.addAction(fileOpenAction);
    menu.addAction(fileSaveAction);
    menu.exec(event->globalPos());
}

void hC_helpTree::customContextMenuRequested(
        const QPoint &pos)
{
    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}



///////////////////////////***************************************
void hC_helpTree::updateUi()
{
    qDebug()<<"-----------    ::hChlp updateUi..."
           <<modelHelpXML->rowCount();
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelHelpXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = treeViewXML->currentIndex().isValid();

    //modelHelpXML->getListXML ();

    foreach (QAction *action, QList<QAction*>()
             << editDeleteAction
             << editMoveUpAction << editMoveDownAction
             << editCutAction
             << editPromoteAction << editDemoteAction)

        action->setEnabled(enable);

    editStartOrStopAction->setEnabled(rows);
    editPasteAction->setEnabled(modelHelpXML->hasCutItem());


    qDebug()<<" upt ui HelpItem";

    HelpItem* currentItem = static_cast<HelpItem*>
            (treeViewXML->currentIndex().internalPointer());
    if ( currentItem)
    {
        ///
        ///  mevcut Yardım tüm evrene yayılsın
        ///

        emit sgnHelp (currentItem );

        ///
        /// Yardım değiştiğinde detaylarda değişsin
        ///
        ///

        lB_Help->setText(QString::number(currentItem->helpKod()) //+" : "+
                         // currentItem->parent()->helpAd ()+" - "+
                         // currentItem->helpAd() +" - "+
                         // currentItem->helpAcklm ()+" : "+
                         // currentItem->DBFile()
                          );
        tE_yrdm->setTextEdit (new QTextEdit(currentItem->helpAcklm () ));

    }
    qDebug()<<" upt ui HelpItem";
}






void hC_helpTree::setCurrentIndex(const QModelIndex &index)
{
    //qDebug()<<"-----------    ::hChlp setcurindx";
    if (index.isValid()) {
        treeViewXML->scrollTo(index);
        treeViewXML->setCurrentIndex(index);
    }
}



////////////// E D I T S //////////////////////////////////////////////
///
///



void hC_helpTree::editAdd()
{
   qDebug()<<"-----------    ::hChlp editAdd Yeni Yardım Ekleniyor...............";

 //  hC_hspAdd* ekle = new hC_hspAdd;
  // ekle->show ();

   QModelIndex index = treeViewXML->currentIndex();
    if (modelHelpXML->insertRows(0, 1, index))
    {
        index = modelHelpXML->index(0, 0, index);
        setCurrentIndex(index);
        //treeViewXML->edit(index);

        HelpItem * yeniItem = new HelpItem;
      //  yeniItem = ekle->yeni();

        HelpItem * Item = getCurrentItem ();
        Item->setHelpAd (yeniItem->helpAd ())  ;
        Item->setHelpAcklm (yeniItem->helpAcklm ())  ;
        Item->setHelpDBFile (yeniItem->DBFile ())  ;
        setDirty();
        updateUi();
   // delete yeniItem;
    }

}



void hC_helpTree::editDelete()
{
    //qDebug()<<"-----------    ::hChlp editDelete";
    //qDebug() << "editdelete";
    QModelIndex index = treeViewXML->currentIndex();
    if (!index.isValid())
        return;

    QString name = modelHelpXML->data(index).toString();
    int rows = modelHelpXML->rowCount(index);
    if (modelHelpXML->isTimedItem(index))
        stopTiming();
qDebug()<<"--edit delete 01";
    QString message;
    if (rows == 0)
        message = tr("<p>Yardım SİL '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>Yardım SİL '%1' ve alt hesabı (ve "
                     "alt hesaba bağlı Yardımlar)").arg(name);
    else if (rows > 1)
        message = tr("<p>Yardım SİL '%1' ve ona bağlı %2 alt Yardım "
                     "(ve alt Yardımlara bağlı Yardımlar)").arg(name).arg(rows);
    if (!AQP::okToDelete(this, tr("Delete"), message))
        return;
    qDebug()<<"--edit delete 02";
    modelHelpXML->removeRow(index.row(), index.parent());
    qDebug()<<"--edit delete 03";
    setDirty();
    qDebug()<<"--edit delete 04";
    updateUi();
    qDebug()<<"--edit delete s0n";
}




void hC_helpTree::editCut()
{
    qDebug()<<"-----------    ::hChlp editCut";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelHelpXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelHelpXML->cut(index));
    editPasteAction->setEnabled(modelHelpXML->hasCutItem());
}


void hC_helpTree::editPaste()
{
    qDebug()<<"-----------    ::hChlp editpaste";
    setCurrentIndex(modelHelpXML->paste(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_helpTree::editMoveUp()
{
    qDebug()<<"-----------    ::hChlp editmoveup";
    treeViewXML->setCurrentIndex(
                modelHelpXML->moveUp(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_helpTree::editMoveDown()
{
    qDebug()<<"-----------    ::hChlp editmovedown";

    treeViewXML->setCurrentIndex(
                modelHelpXML->moveDown(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_helpTree::editPromote()
{
    qDebug()<<"-----------    ::hChlp editPromote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelHelpXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelHelpXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_helpTree::editDemote()
{

    qDebug()<<"-----------    ::hChlp editDemote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelHelpXML->isTimedItem(index))
        stopTiming();
    treeViewXML->setCurrentIndex(modelHelpXML->demote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}




//////////// X M L  F I L E  O P E R A T I O N S ////////////////////
///
///
///




bool hC_helpTree::okToClearData()
{
   // qDebug()<<"-----------    ::hChlp OkToClearData";
    if (isWindowModified())
        return AQP::okToClearData(&hC_helpTree::fileSave, this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}



void hC_helpTree::fileNew()
{
    qDebug()<<"-----------    ::hChlp HELP  filenew XML";

    if (!okToClearData())
        return;
    modelHelpXML->clear();
    modelHelpXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - İsimsiz Yardım dosyası[*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}

// yardım dbf oluştur
void hC_helpTree::fileDBNew()
{

}


void hC_helpTree::fileOpen()
{
   // qDebug()<<"-----------    ::hChlp fileOpen XML";
    //qDebug() << "fileopen";
    if (!okToClearData())
        return;
    QString helpFilename = modelHelpXML->filename();
    QString dir(helpFilename.isEmpty() ? QString(".")
                                   : QFileInfo(helpFilename).canonicalPath());
    helpFilename = QFileDialog::getOpenFileName(this,
                                            tr("%1 - Open").arg(QApplication::applicationName()),
                                            dir, tr("konumlar (*.hlp)"));
    if (!helpFilename.isEmpty())
        load(helpFilename);
}


void hC_helpTree::load(const QString &helpFilename,
                  const QStringList &taskPath)
{
   // qDebug()<<"-----------    ::hChlp load XML";
    qDebug() << "loading file (helpFilename) '" << helpFilename
             << " ' at path (taskPath): " << taskPath;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    try {
        modelHelpXML->load(helpFilename);
        if (!taskPath.isEmpty())
        {
            setCurrentIndex(modelHelpXML->indexForPath(taskPath));
        }
        for (int column = 0;
             column < modelHelpXML->columnCount();
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
                            QFileInfo(helpFilename).fileName()));

        statusBar()->showMessage(tr("%1 yüklendi").arg(helpFilename),
                                 StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("HATA"), tr("Yüklemede Hata %1: %2\n"
                                          "yeni dosya oluşturuluyor")
                     .arg(helpFilename,QString::fromUtf8(error.what())));


    }
    updateUi();
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
    treeViewXML->setFocus();
    QApplication::restoreOverrideCursor();

}



bool hC_helpTree::fileSave()
{
    qDebug()<<"-----------    ::hChlp fileSave XML";
    // qDebug() << "filesave";
    bool saved = false;
    if (modelHelpXML->filename().isEmpty())
        saved = fileSaveAs();
    else {
        try {
            modelHelpXML->save();
            setDirty(false);
            setWindowTitle(tr("%1 - %2[*]")
                           .arg(QApplication::applicationName())
                           .arg(QFileInfo(modelHelpXML->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                                     .arg(modelHelpXML->filename()), StatusTimeout);
            saved = true;
        } catch (AQP::Error &error) {
            AQP::warning(this, tr("Error"),
                         tr("Failed to save %1: %2").arg(modelHelpXML->filename(),/*)
                         .arg(*/QString::fromUtf8(error.what())));
        }
    }
    updateUi();
    return saved;
}


bool hC_helpTree::fileSaveAs()
{
    qDebug()<<"-----------    ::hChlp fileSaveAs XML";
    // qDebug() << "filesaveas";
    QString filename = modelHelpXML->filename();
    QString dir = filename.isEmpty() ? "."
                                     : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
                                            tr("%1 - Save As").arg(QApplication::applicationName()),
                                            dir,
                                            tr("%1 (*.hlp)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".hlp"))
        filename += ".hlp";
    modelHelpXML->setFilename(filename);
    return fileSave();
}





//////////////////// O T H E R S /////////////////////////////////
///
///
///
///

void hC_helpTree::closeEvent(QCloseEvent *event)
{
    qDebug()<<"-----------    ::hChlp closeEvent *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
           << " help filename               : " << modelHelpXML->filename()
           << " pathforindex (curindex): " << modelHelpXML->pathForIndex(treeViewXML->currentIndex());
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
       // settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(helpFilenameSetting, modelHelpXML->filename());
        settings.setValue(CurrentHelpPathSetting,
                          modelHelpXML->pathForIndex(treeViewXML->currentIndex()));

        qDebug() <<"      help  close -> settings.helpFilename "<< settings.fileName ();
        event->accept();
    }
    else
        event->ignore();
}




////////////////// T A S K S ////////////////////////////////////////////////
///
///



void hC_helpTree::stopTiming()
{
    qDebug()<<"-----------    ::hChlp stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}



void hC_helpTree::editStartOrStop(bool start)
{
    qDebug()<<"-----------    ::hChlp editStartOrStop";
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

            modelHelpXML->setTimedItem(index);
            modelHelpXML->addDateTimeToTimedItem(now, now);
            modelHelpXML->setIconForTimedItem(icon);

            editStartOrStopAction->setIcon(icon);

            // qt 6 timedTime.restart();
            timer.start();
            iconTimeLine.start();
        }
    }
    else
    { // stop the clock
        timeout(); // update to now

        modelHelpXML->setIconForTimedItem();
        modelHelpXML->clearTimedItem();
        editStartOrStopAction->setIcon(QIcon(":/rsm/images/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top")
                                         : tr("S&tart"));
    editStartOrStopAction->setIcon(QIcon(start ? tr(":/rsm/images/4.png")
                                               : tr(":/rsm/images/0.png")));
}


void hC_helpTree::timeout()
{
    qDebug()<<"-----------    ::hChlp timeout";
    modelHelpXML->incrementEndTimeForTimedItem(timer.remainingTime ());
    timer.start ();
}


void hC_helpTree::updateIcon(int frame)
{
    qDebug()<<"-----------    ::hChlp updateIcon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelHelpXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}


void hC_helpTree::editHideOrShowDoneTasks(bool hide)
{
    // qDebug()<<"-----------    ::hChlp edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}


void hC_helpTree::hideOrShowDoneTask(bool hide,
                                const QModelIndex &index)
{
    // qDebug()<<"-----------    ::hChlp hideorshowdntsk";
    bool hideThisOne = hide && modelHelpXML->isChecked(index);
    if (index.isValid())
        treeViewXML->setRowHidden(index.row(), index.parent(),
                                  hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelHelpXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelHelpXML->index(row, 0, index));
    }
}


