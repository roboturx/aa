#include "main/dw_hesap.h"
#include "main/cm_dlg_richtxt.h"


//namespace {

//const int StatusTimeout = AQP::MSecPerSecond * 10;
//const QString FilenameSetting("Filename");
//const QString GeometrySetting("Geometry");
//const QString CurrentTaskPathSetting("CurrentTaskPath");
//const int FirstFrame = 0;
//const int LastFrame = 4;
//}
dW_Hesap::dW_Hesap(QWidget *parent)
{
    qDebug() << "dW_Hesap Constuctor - "<<parent->objectName ();


    createModelViewDelegate ();
    createConnections ();
    QWidget *x = new QWidget;
    QGridLayout *lx = new QGridLayout(x);
    lx->addWidget (treeViewXML,0,0,1,1);


}

TaskItem* dW_Hesap::getCurrentItem()
{
    qDebug()<<"-----------    ::hChsp getcurrentitem";
    TaskItem* currentItem = static_cast<TaskItem*>
        (treeViewXML->currentIndex().internalPointer());
    return  currentItem;
}


void dW_Hesap::createModelViewDelegate()
{
    qDebug()<<"-----------    ::hChsp cr mdl vwv";

    treeViewXML = new QTreeView(this);
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

    treeViewXML->setItemDelegateForColumn(1, new cm_dlG_RichTxt);

    treeViewXML->setItemDelegateForColumn(3, new cm_dlG_cb_hTur);
    treeViewXML->setModel(modelXML);

    lB_Hesap = new QLabel("Kod-------");

    pi_Hesap_Kod = new quint64{};
    ps_Hesap_Ad = new QString{};


}

void dW_Hesap::createConnections()
{
    qDebug()<<"-----------    ::hChsp createConnections";
    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this, &dW_Hesap::updateUi);

    connect(treeViewXML->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &dW_Hesap::updateUi);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(customContextMenuRequested(const QPoint&)));

    connect(modelXML,
            SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            this, SLOT(setDirty()));

    connect(modelXML, SIGNAL(stopTiming()), this,
            SLOT(stopTiming()));


    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));



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
    slotForAction[genelAyarlar] = SLOT(fgenelAyarlar());

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
    connect(genelAyarlar, SIGNAL(triggered(bool)),
            this, SLOT(fgenelAyarlar(bool)));

    //    connect(genelAyarlar, &QAction::triggered(),
    //            this, &dW_Hesap::fgenelAyarlar);

    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon(int)));
    qDebug() << "                  kntrl son";
}

void dW_Hesap::updateUi()
{
    qDebug()<<"-----------    ::hChsp updateUi...";
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
        /// mevcut hesap kod ve ad değişkenlere
        /// hspdty kayıtlarında kullanılmak üzere
        ///

        *pi_Hesap_Kod = currentItem->hesapKod ();
        *ps_Hesap_Ad = currentItem->hesapAd ();
        //   *ps_Hesap_Turu = currentItem->hesapTuru ();
        emit sgnHesap (pi_Hesap_Kod, ps_Hesap_Ad/*, ps_Hesap_Turu*/ );
        /// hesap değiştiğinde detaylarda değişsin
        ///
        ///



        lB_Hesap->setText(QString::number(currentItem->hesapKod()) +" : "+
                          currentItem->parent()->hesapAd ()+" - "+
                          currentItem->hesapAd() +" - "+
                          currentItem->hesapAcklm ()+" : "+
                          QString::number(currentItem->isTopluHesap() ) +" : "+
                          currentItem->hesapTuru() +" : "+
                          currentItem->ustHesap()
                          );

       // createTABs (currentItem->hesapTuru ());

    }
}



void dW_Hesap::setCurrentIndex(const QModelIndex &index)
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



void dW_Hesap::editAdd()
{
   //qDebug()<<"-----------    ::hChsp editAdd Yeni Hesap Ekleniyor...............";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->insertRows(0, 1, index))
    {
        index = modelXML->index(0, 0, index);
        setCurrentIndex(index);
        treeViewXML->edit(index);

        setDirty();
        updateUi();
    }

}



void dW_Hesap::editDelete()
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




void dW_Hesap::editCut()
{
    qDebug()<<"-----------    ::hChsp editCut";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}


void dW_Hesap::editPaste()
{
    qDebug()<<"-----------    ::hChsp editpaste";
    setCurrentIndex(modelXML->paste(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void dW_Hesap::editMoveUp()
{
    qDebug()<<"-----------    ::hChsp editmoveup";
    treeViewXML->setCurrentIndex(
                modelXML->moveUp(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void dW_Hesap::editMoveDown()
{
    qDebug()<<"-----------    ::hChsp editmovedown";

    treeViewXML->setCurrentIndex(
                modelXML->moveDown(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void dW_Hesap::editPromote()
{
    qDebug()<<"-----------    ::hChsp editPromote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void dW_Hesap::editDemote()
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




bool dW_Hesap::okToClearData()
{
   // qDebug()<<"-----------    ::hChsp OkToClearData";
    if (isWindowModified())
        return AQP::okToClearData(&::dW_Hesap::fileSave, this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}



void dW_Hesap::fileNew()
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


void dW_Hesap::fileOpen()
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


void dW_Hesap::load(const QString &filename,
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

//        statusBar()->showMessage(tr("%1 yüklendi").arg(filename),
//                               15  /*StatusTimeout*/);
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



bool dW_Hesap::fileSave()
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
//            statusBar()->showMessage(tr("Saved %1")
//                                     .arg(modelXML->filename()), StatusTimeout);
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


bool dW_Hesap::fileSaveAs()
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








////////////////// T A S K S ////////////////////////////////////////////////
///
///



void dW_Hesap::stopTiming()
{
    qDebug()<<"-----------    ::hChsp stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}



void dW_Hesap::editStartOrStop(bool start)
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


void dW_Hesap::timeout()
{
    qDebug()<<"-----------    ::hChsp timeout";
    modelXML->incrementEndTimeForTimedItem(timer.remainingTime ());
    timer.start ();
}


void dW_Hesap::updateIcon(int frame)
{
    qDebug()<<"-----------    ::hChsp updateIcon";
    if (frame > 4) // lastframe
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}







void dW_Hesap::hideOrShowDoneTask(bool hide,
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

void dW_Hesap::editHideOrShowDoneTasks(bool hide)
{
    // qDebug()<<"-----------    ::hChsp edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}
