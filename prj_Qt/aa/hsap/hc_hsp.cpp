#include "hc_hsp.h"


namespace {

const int StatusTimeout = AQP::MSecPerSecond * 10;
const QString FilenameSetting("Filename");
const QString GeometrySetting("Geometry");
const QString CurrentTaskPathSetting("CurrentTaskPath");
const int FirstFrame = 0;
const int LastFrame = 4;


QAction *createAction(const QString &icon,
                      const QString &text,
                      QObject *parent,
                      const QKeySequence &shortcut=QKeySequence())
{
    QAction *action = new QAction(QIcon(icon), text, parent);
    if (!shortcut.isEmpty())
        action->setShortcut(shortcut);
    return action;
}

} // anonymous namespace


hC_hsp::hC_hsp(QWidget *parent)
    : QMainWindow(parent)
    ,
      #ifndef CUSTOM_MODEL
      timedItem(0),
      #endif
      currentIcon(0)
{
    qDebug ()<<"        Constructor HESAP **************************";

    qDebug() << "       0200 hc_hsp construction..";
    createModelAndView();
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

    QSettings settings;
    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();

    qDebug() << "           0205 Hesap dosyası kontrol ediliyor...";
    if (! QFile::exists(filename))
    {
        qDebug() << "            Kayıtlı Hesap Dosyası Diskte bulunamadı !! ";
        qDebug() << "            Yeni Hesap Dosyası oluşturuluyor...";
        qDebug() << "            0202 hsp::filenew ";
        statusBar()->showMessage(tr("Dosya Yüklenemedi %1")
                                 .arg(filename), StatusTimeout);
        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    if (filename.isEmpty()  )
    {
        qDebug() << "            Hesap Dosya Kaydı Yok ... ";
        qDebug() << "            Yeni Dosya oluşturuluyor...";
        qDebug() << "            0203 hsp::filenew ";
        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    else
    {
        qDebug() << "               Kayıtlı XML Dosyası Diskte bulundu. ";
        qDebug() << "               Yükleniyor...";

        QMetaObject::invokeMethod(this, "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, filename),
                                  Q_ARG(QStringList, settings.value(
                       CurrentTaskPathSetting).toStringList()));
       // qDebug() << "               0204 hsp::load ";
    }
}

TaskItem* hC_hsp::getCurrentItem()
{

        TaskItem* currentItem = static_cast<TaskItem*>
            (treeViewXML->currentIndex().internalPointer());
        if ( currentItem)
        {
            qDebug() << "               ui hsp::getcurrentItem" ;
            qDebug() << "               :kod:" << currentItem->hesapKod ()
                     << "               :ad :" << currentItem->hesapAd ()
                     << "               :tpl:" << QString::number(currentItem->isTopluHesap())
                     << "               :tur:" << currentItem->hesapTuru()
                     << "               :ust:" << currentItem->ustHesap()
                     << "               ui currentItem" ;
        }
        return  currentItem;


}

/// 100-01
///
void hC_hsp::createModelAndView()
{
    qDebug() << "           0201 hsp::createModelAndView Modelling Hsp XML...";
    centralWdgt = new QWidget;
    treeViewXML = new QTreeView;

    modelXML = new cls_mdl_TreeFromXml(this);
    treeViewXML->setDragDropMode(QAbstractItemView::InternalMove);

#ifdef MODEL_TEST
    (void) new ModelTest(modelXML, this);
#endif

    // kod kolonunu gizle
   // treeViewXML->setColumnHidden(5,1);

    treeViewXML->setAllColumnsShowFocus(false);
    treeViewXML->setItemDelegateForColumn(0, new cls_dlgt_RichText);
    treeViewXML->setItemDelegateForColumn(1, new cls_dlgt_RichText);
    treeViewXML->setColumnWidth(0,5000);
    treeViewXML->setColumnWidth(1,1000);
    treeViewXML->setColumnWidth(2,5000);
    //treeViewXML->setFirstColumnSpanned();
    //treeViewXML->setIndentation();
    //treeViewXML.set
    treeViewXML->resizeColumnToContents(0);
    treeViewXML->setModel(modelXML);

    lB_HesapKod = new QLabel("Kod-------");
    lB_HesapAd = new QLabel("Ad--------");
    lB_HesapKodAd = new QLabel("KodAd---------");
    pi_Hesap_Kod = new quint64{};
    ps_Hesap_Ad = new QString{};

    QGridLayout* gridd = new QGridLayout( centralWdgt );
    gridd->addWidget(treeViewXML , 0, 0, 4, 2 );
    gridd->addWidget(lB_HesapKodAd, 5, 0, 1, 1 );

   // gridd->addWidget( o_hspdty , 0, 2, 2, 3);

qDebug()<<"                 0011 hc23";
  //  gridd ->addWidget( modelXML->cB_hesapAds , 1, 2, 1, 1);
qDebug()<<"                 0011 hc3";


   // gridd->addWidget(cB_transfer , 0, 2, 2, 3);
    centralWdgt->setLayout(gridd);
    setCentralWidget(centralWdgt);
}


void hC_hsp::createActions()
{
    qDebug() << "           0202 hsp::createActions";
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


void hC_hsp::createMenusAndToolBar()
{
    qDebug() << "           0203 hsp::createMenusAndToolBar";
    setUnifiedTitleAndToolBarOnMac(true);

    QMenu *fileMenu = menuBar()->addMenu(tr("Dosya"));
    QToolBar *fileToolBar = addToolBar(tr("Dosya"));

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


void hC_hsp::createConnections()
{
    qDebug() << "           0204 hsp::createConnections";
    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this, &hC_hsp::updateUi);


    /// selection değiştiğinde hesap kod ve adını yayalım gitsin
    ///
    ///

  //  connect(this, &hC_hsp::sgnHesap,
       //     o_hspdty, &hC_HSPDTY::slt_tbx_rowChange);


    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &hC_hsp::updateUi);
qDebug() << "                   004 01";
    connect(modelXML,
                   SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
                   this, SLOT(setDirty()));
qDebug() << "                   004 02";
    connect(modelXML, SIGNAL(stopTiming()), this,
            SLOT(stopTiming()));
qDebug() << "                   004 03";

    //connect(modelXML, SIGNAL(rowsRemoved(QModelIndex&,int,int)),
     //       this, SLOT(setDirty()));

qDebug() << "                   004 04";
    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));
qDebug() << "                   004 05";
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
qDebug() << "                   004 06";
    QHashIterator<QAction*, QString> i(slotForAction);
    while (i.hasNext()) {
        i.next();
        connect(i.key(), SIGNAL(triggered()),
                this, qPrintable(i.value()));
    }
qDebug() << "                   04 07";
    connect(editStartOrStopAction, SIGNAL(triggered(bool)),
            this, SLOT(editStartOrStop(bool)));
    connect(editHideOrShowDoneTasksAction, SIGNAL(triggered(bool)),
            this, SLOT(editHideOrShowDoneTasks(bool)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon(int)));
    qDebug() << "                   004 son";
}





void hC_hsp::updateUi()
{

    qDebug() << "           0250 hsp::updateUi...";
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = treeViewXML->currentIndex().isValid();


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
        qDebug() << " */*/*/*/*/*/ ui currentItem hsp::updateui" ;
        qDebug() << "    :kod:" << currentItem->hesapKod ();
        qDebug() << "    :ad :" << currentItem->hesapAd ();
        qDebug() << "    :tpl:" << QString::number(currentItem->isTopluHesap());
        qDebug() << "    :tur:" << currentItem->hesapTuru();
        qDebug() << "    :ust:" << currentItem->ustHesap();
        qDebug() << "    ui currentItem" ;



        /// mevcut hesap kod ve ad değişkenlere
        /// hspdty kayıtlarında kullanılmak üzere
        ///
        ///

        *pi_Hesap_Kod = currentItem->hesapKod ();
        *ps_Hesap_Ad = currentItem->hesapAd ();
        emit sgnHesap (pi_Hesap_Kod, ps_Hesap_Ad );
        /// hesap değiştiğinde detaylarda değişsin
        ///
        ///

    //    QString filtre ;
      //  filtre = "f_hspdty_hspID=" +  QString::number(currentItem->hesapKod () ) ;
 //       o_hspdty->tb_model->setFilter(filtre);


        lB_HesapKodAd->setText(currentItem->hesapAd() +" - "+
                      QString::number(currentItem->hesapKod() )
                          );
        lB_HesapKod->setText(QString::number(currentItem->hesapKod()) +
                             QString::number(currentItem->isTopluHesap() ) +
                             currentItem->hesapTuru() +
                             currentItem->ustHesap()
                             );

    }

}



void hC_hsp::setCurrentIndex(const QModelIndex &index)
{
  //  qDebug() << "setcurindx";
    if (index.isValid()) {
        treeViewXML->scrollTo(index);
        treeViewXML->setCurrentIndex(index);
    }
}



////////////// E D I T S //////////////////////////////////////////////
///
///



void hC_hsp::editAdd()
{
    qDebug() << "       hsp::editAdd Yeni Hesap Ekleniyor...............";
    QModelIndex index = treeViewXML->currentIndex();
//qDebug()<<"hc_hsp editadd ta pi-max-hesp-id " << *modelXML->pi_max_Hesap_ID;
    if (modelXML->insertRows(0, 1, index))
    {
        index = modelXML->index(0, 0, index);
        setCurrentIndex(index);
        treeViewXML->edit(index);

//        QString name = modelXML->data(index).toString();
//        QString name2 = modelXML->data(modelXML->index(0, 1, index)).toString();
//        QString name3 = modelXML->data(modelXML->index(0, 2, index)).toString();
//        QString name4 = modelXML->data(modelXML->index(0, 3, index)).toString();
//        QString name5 = modelXML->data(modelXML->index(0, 4, index)).toString();
//        qDebug() <<"--------------------------------------" ;
//        qDebug() <<"----şşşşş----------------------------------" ;
//        qDebug() << name <<" pi max hesap id "<< *modelXML->pi_max_Hesap_ID;
//        qDebug() << name2 ;
//        qDebug() << name3 ;
//        qDebug() << name4 ;
//        qDebug() << name5 ;
//        qDebug() <<"--------------------------------------" ;
// zr       qDebug() <<"--------------------------------------" ;
        setDirty();
        updateUi();
    }

}



void hC_hsp::editDelete()
{
    qDebug() << "       hsp::editDelete";
    //qDebug() << "editdelete";
    QModelIndex index = treeViewXML->currentIndex();
    if (!index.isValid())
        return;

    QString name = modelXML->data(index).toString();
    int rows = modelXML->rowCount(index);
    if (modelXML->isTimedItem(index))
        stopTiming();

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
    modelXML->removeRow(index.row(), index.parent());
    setDirty();
    updateUi();
}




void hC_hsp::editCut()
{
    qDebug() << "       hsp::editCut";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}


void hC_hsp::editPaste()
{

    qDebug() << "       hsp::editpaste";
    setCurrentIndex(modelXML->paste(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editMoveUp()
{
    qDebug() << "       hsp::editmoveup";
    treeViewXML->setCurrentIndex(
                modelXML->moveUp(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editMoveDown()
{
    qDebug() << "       hsp::editmovedown";

    treeViewXML->setCurrentIndex(
                modelXML->moveDown(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editPromote()
{
    qDebug() << "       hsp::editPromote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editDemote()
{
    qDebug() << "       hsp::editDemote";
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




bool hC_hsp::okToClearData()
{
    qDebug() << "       hsp::OkToClearData";
     if (isWindowModified())
        return AQP::okToClearData(&hC_hsp::fileSave, this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}



void hC_hsp::fileNew()
{
    qDebug() << "       hsp::filenew XML";

    if (!okToClearData())
        return;
    modelXML->clear();
    modelXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - İsimsiz hesap dosyası[*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}


void hC_hsp::fileOpen()
{
    qDebug() << "       hsp::fileOpen XML";
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


void hC_hsp::load(const QString &filename,
                  const QStringList &taskPath)
{
    qDebug() << "       210 hsp::load XML";
    qDebug() << "       loading file (filename) '" << filename
             << "       ' at path (taskPath): " << taskPath;

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
             treeViewXML->resizeColumnToContents(column);
        }
        setDirty(false);

        setWindowTitle(tr("%1 - %2[*]")
                       .arg(QApplication::applicationName(),
                            QFileInfo(filename).fileName()));

        statusBar()->showMessage(tr("%1 yüklendi").arg(filename),
                                 StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("HATA"), tr("Yüklemede Hata %1: %2")
         .arg(filename).arg(QString::fromUtf8(error.what())));
    }
    updateUi();
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
    treeViewXML->setFocus();
    QApplication::restoreOverrideCursor();

}



bool hC_hsp::fileSave()
{
    qDebug() << "       220 hsp::fileSave XML";
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


bool hC_hsp::fileSaveAs()
{
    qDebug() << "       221 hsp::fileSaveAs XML";
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

void hC_hsp::closeEvent(QCloseEvent *event)
{
    qDebug() << "       222 hsp:: ~ closeEvent";
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



void hC_hsp::stopTiming()
{
    qDebug() << "               230 stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}


void hC_hsp::editStartOrStop(bool start)
{
    qDebug() << "              231 hsp::editStartOrStop";
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


void hC_hsp::timeout()
{
    qDebug() << "              232 hsp::timeout";
    modelXML->incrementEndTimeForTimedItem(timer.remainingTime ());
    timer.start ();
}


void hC_hsp::updateIcon(int frame)
{
    qDebug() << "               233 hsp::updateIcon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}


void hC_hsp::editHideOrShowDoneTasks(bool hide)
{
    qDebug() << "            234 hsp::edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}


void hC_hsp::hideOrShowDoneTask(bool hide,
                                const QModelIndex &index)
{
    qDebug() << "            235 hsp::hideorshowdntsk";
    bool hideThisOne = hide && modelXML->isChecked(index);
    if (index.isValid())
        treeViewXML->setRowHidden(index.row(), index.parent(),
                                  hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelXML->index(row, 0, index));
    }
}



