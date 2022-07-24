

#include "hc_hsp.h"
#include "hc_hspdetay.h"
#include "richtextdelegate.h"
#ifdef CUSTOM_MODEL
#include "treemodel.h"
#else
#include "standarditem.h"
#include "standardtreemodel.h"
#endif



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

    qDebug() << "Modelling...";
    createModelAndView();
    qDebug() << "Actions...";
    createActions();
    qDebug() << "Menu & toolbar";
    createMenusAndToolBar();
    qDebug() << "Connecting slots...";
    createConnections();


    AQP::accelerateMenu(menuBar());
#ifdef CUSTOM_MODEL
    setWindowTitle(tr("%1 (Custom modelXML)[*]")
                   .arg(QApplication::applicationName()));
#else
    setWindowTitle(tr("%1 (QStandardItemModel)[*]")
                   .arg(QApplication::applicationName()));
#endif
    statusBar()->showMessage(tr("Uygulama Hazır"), StatusTimeout);
    qDebug() << "Hazır";
    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    // qt 6 OKK iconTimeLine.setCurveShape(QTimeLine::LinearCurve);
    iconTimeLine.setEasingCurve (QEasingCurve::InOutQuad);

    QSettings settings;
    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();
    if (! QFile::exists(filename))
    {
        qDebug() << " Dosya Diskte bulunamadı ";
        statusBar()->showMessage(tr("Dosya Yüklenemedi %1")
                                 .arg(filename), StatusTimeout);
        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    if (filename.isEmpty()  )
        QTimer::singleShot(0, this, SLOT(fileNew()));
    else
        QMetaObject::invokeMethod(this, "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, filename),
                                  Q_ARG(QStringList, settings.value(
                                            CurrentTaskPathSetting).toStringList()));
    qDebug() << "-----------------";
    qDebug() << "-Mw Constructed.-";
    qDebug() << "-----------------";
    qDebug() << "-Load-or-filenew-";
    qDebug() << "-----------------";
}

/// 100-01
///
void hC_hsp::createModelAndView()
{
    centralWdgt = new QWidget;
    treeViewXML = new QTreeView;
      tableViewSQL = new QTableView;
#ifdef CUSTOM_MODEL
    modelXML = new TreeModel(this);
    treeViewXML->setDragDropMode(QAbstractItemView::InternalMove);

    modelSQL = new QSqlRelationalTableModel (this);
    modelSQL->setTable("dbtb_hesap");
    tableViewSQL->setDragDropMode(QAbstractItemView::InternalMove);
    tableViewSQL->setModel(modelSQL);
#else
    modelXML = new StandardTreeModel(this);
#endif
#ifdef MODEL_TEST
    (void) new ModelTest(modelXML, this);
#endif
    treeViewXML->setAllColumnsShowFocus(true);
    treeViewXML->setItemDelegateForColumn(0,
                       new RichTextDelegate);
    treeViewXML->setModel(modelXML);
    sqlTableName = new QLabel("Boşşşş");

    /// hesapdetaylarını oluştur
    ///

    m_hspdty = new hC_HSPDTY ;



    QGridLayout* gridd = new QGridLayout( centralWdgt );
    gridd->addWidget(treeViewXML , 0, 0, 1, 1 );
    gridd->addWidget(sqlTableName, 1, 0, 1, 1 );
    gridd->addWidget(tableViewSQL , 0, 1, 1, 1);
    centralWdgt->setLayout(gridd);
    setCentralWidget(centralWdgt);
}


void hC_hsp::createActions()
{
    fileNewAction = createAction(":/rsm/images/filenew.png", tr("New"),
                                this, QKeySequence::New);
    fileOpenAction = createAction(":/rsm/images/fileopen.png", tr("Open..."),
                                this, QKeySequence::Open);
    fileSaveAction = createAction(":/rsm/images/filesave.png", tr("Save"),
                                this, QKeySequence::Save);
    fileSaveAsAction = createAction(":/rsm/images/filesave.png",
                                    tr("Save As..."), this
                                #if QT_VERSION >= 0x040500
                                    , QKeySequence::SaveAs
                                #endif
                                    );
    fileQuitAction = createAction(":/rsm/images/filequit.png", tr("Quit"), this);
#if QT_VERSION >= 0x040600
    fileQuitAction->setShortcuts(QKeySequence::Quit);
#else
    fileQuitAction->setShortcut(QKeySequence("Ctrl+Q"));
#endif
    editAddAction = createAction(":/rsm/images/editadd.png", tr("Add..."),
                                 this, QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/rsm/images/editdelete.png",
                                    tr("Delete..."), this, QKeySequence::Delete);
#ifdef CUSTOM_MODEL
    editCutAction = createAction(":/rsm/images/editcut.png", tr("Cut"),
                                 this, QKeySequence::Cut);
    editPasteAction = createAction(":/rsm/images/editpaste.png", tr("Paste"),
                                   this, QKeySequence::Paste);
    editMoveUpAction = createAction(":/rsm/images/editup.png", tr("Move Up"),
                                    this, QKeySequence(tr("Ctrl+Up")));
    editMoveDownAction = createAction(":/rsm/images/editdown.png",
                                      tr("Move Down"), this, QKeySequence(tr("Ctrl+Down")));
    editPromoteAction = createAction(":/rsm/images/editpromote.png",
                                     tr("Promote"), this, QKeySequence(tr("Ctrl+Left")));
    editDemoteAction = createAction(":/rsm/images/editdemote.png",
                                    tr("Demote"), this, QKeySequence(tr("Ctrl+Right")));
#endif
    editStartOrStopAction = createAction(":/rsm/images/0.png", tr("S&tart"),
                                         this, QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Hide Done Tasks"),
                                                this);
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}


void hC_hsp::createMenusAndToolBar()
{
    setUnifiedTitleAndToolBarOnMac(true);

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
#ifdef Q_WS_MAC
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif
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
    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));
#ifdef Q_WS_MAC
    editToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif
#ifdef CUSTOM_MODEL
    foreach (QAction *action, QList<QAction*>() << editAddAction
             << editDeleteAction << emptyAction
             << editCutAction << editPasteAction << emptyAction
             << editMoveUpAction << editMoveDownAction
             << editPromoteAction << editDemoteAction << emptyAction
             << editStartOrStopAction << editHideOrShowDoneTasksAction)
#else
    foreach (QAction *action, QList<QAction*>() << editAddAction
             << editDeleteAction << emptyAction
             << editStartOrStopAction << editHideOrShowDoneTasksAction)
#endif
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
    connect(treeViewXML->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex&,
                                  const QModelIndex&)),
            this, SLOT(updateUi()));

#ifdef CUSTOM_MODEL
    connect(modelXML,
            SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            this, SLOT(setDirty()));
    connect(modelXML, SIGNAL(stopTiming()), this, SLOT(stopTiming()));
#else
    connect(modelXML, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(setDirty()));
#endif // CUSTOM_MODEL
    connect(modelXML, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
            this, SLOT(setDirty()));
    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));

    QHash<QAction*, QString> slotForAction;
    slotForAction[fileNewAction] = SLOT(fileNew());
    slotForAction[fileOpenAction] = SLOT(fileOpen());
    slotForAction[fileSaveAction] = SLOT(fileSave());
    slotForAction[fileSaveAsAction] = SLOT(fileSaveAs());
    slotForAction[fileQuitAction] = SLOT(close());
    slotForAction[editAddAction] = SLOT(editAdd());
    slotForAction[editDeleteAction] = SLOT(editDelete());
#ifdef CUSTOM_MODEL
    slotForAction[editCutAction] = SLOT(editCut());
    slotForAction[editPasteAction] = SLOT(editPaste());
    slotForAction[editMoveUpAction] = SLOT(editMoveUp());
    slotForAction[editMoveDownAction] = SLOT(editMoveDown());
    slotForAction[editPromoteAction] = SLOT(editPromote());
    slotForAction[editDemoteAction] = SLOT(editDemote());
#endif
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
}


void hC_hsp::closeEvent(QCloseEvent *event)
{
    qDebug() << "mw close";
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, modelXML->filename());
        settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(treeViewXML->currentIndex()));

        qDebug() << settings.fileName();
        event->accept();
    }
    else
        event->ignore();
}


bool hC_hsp::okToClearData()
{
    qDebug() << "oktoclrdata";
    if (isWindowModified())
        return AQP::okToClearData(&hC_hsp::fileSave, this,
                                  tr("Unsaved changes"), tr("Save unsaved changes?"));
    return true;
}


void hC_hsp::fileNew()
{
    qDebug() << "New File Construction beginning...";
    if (!okToClearData())
        return;
    modelXML->clear();
    modelXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - Unnamed[*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}


void hC_hsp::updateUi()
{
    qDebug() << "user interface updating...";
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = treeViewXML->currentIndex().isValid();

#ifdef CUSTOM_MODEL
    foreach (QAction *action, QList<QAction*>()
             << editDeleteAction
             << editMoveUpAction << editMoveDownAction << editCutAction
             << editPromoteAction << editDemoteAction)
#else
    foreach (QAction *action, QList<QAction*>() << editDeleteAction
             << editStartOrStopAction)
#endif
        action->setEnabled(enable);
#ifdef CUSTOM_MODEL
    editStartOrStopAction->setEnabled(rows);
    editPasteAction->setEnabled(modelXML->hasCutItem());
#endif

    TaskItem* currentItem = static_cast<TaskItem*>
            (treeViewXML->currentIndex().internalPointer());
    if ( currentItem)
    {
        qDebug() << currentItem->hesapAd ();
        sqlTableName->setText(currentItem->hesapAd() +
                              QString::number(currentItem->isTopluHesap() ) +
                              currentItem->hesapTuru() +
                              currentItem->ustHesap()
                              );

        qDebug() << "";
    }

}


void hC_hsp::fileOpen()
{
    qDebug() << "fileopen";
    if (!okToClearData())
        return;
    QString filename = modelXML->filename();
    QString dir(filename.isEmpty() ? QString(".")
                                   : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
                                            tr("%1 - Open").arg(QApplication::applicationName()),
                                            dir, tr("Timelogs (*.tlg)"));
    if (!filename.isEmpty())
        load(filename);
}


void hC_hsp::load(const QString &filename,
                      const QStringList &taskPath)
{
    qDebug() << "loading file '" << filename << "' at path : " << taskPath;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    try {
        modelXML->load(filename);
        if (!taskPath.isEmpty()) {
#ifdef CUSTOM_MODEL
            setCurrentIndex(modelXML->indexForPath(taskPath));
#else
            if (QStandardItem *item = modelXML->itemForPath(taskPath))
                setCurrentIndex(item->index());
#endif
        }
        for (int column = 0; column < modelXML->columnCount(); ++column)
            treeViewXML->resizeColumnToContents(column);
        setDirty(false);
        setWindowTitle(tr("%1 - %2[*]")
                       .arg(QApplication::applicationName())
                       .arg(QFileInfo(filename).fileName()));
        statusBar()->showMessage(tr("Loaded %1").arg(filename),
                                 StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("Error"), tr("Failed to load %1: %2")
                     .arg(filename).arg(QString::fromUtf8(error.what())));
    }
    updateUi();
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
    treeViewXML->setFocus();
    QApplication::restoreOverrideCursor();
}


void hC_hsp::setCurrentIndex(const QModelIndex &index)
{
    qDebug() << "setcurindx";
    if (index.isValid()) {
        treeViewXML->scrollTo(index);
        treeViewXML->setCurrentIndex(index);
    }
}


bool hC_hsp::fileSave()
{
    qDebug() << "filesave";
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
    qDebug() << "filesaveas";
    QString filename = modelXML->filename();
    QString dir = filename.isEmpty() ? "."
                                     : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
                                            tr("%1 - Save As").arg(QApplication::applicationName()),
                                            dir,
                                            tr("%1 (*.tlg)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".tlg"))
        filename += ".tlg";
    modelXML->setFilename(filename);
    return fileSave();
}


#ifndef CUSTOM_MODEL
void hC_hsp::editAdd()
{
    QModelIndex index = treeViewXML->currentIndex();
    StandardTreeModel::Insert insert = StandardTreeModel::AtTopLevel;

    if (index.isValid()) {
        QStandardItem *item = modelXML->itemFromIndex(index);
#if QT_VERSION >= 0x040600
        QScopedPointer<QMessageBox> messageBox(new QMessageBox(this));
#else
        QSharedPointer<QMessageBox> messageBox(new QMessageBox(this));
#endif
        messageBox->setWindowModality(Qt::WindowModal);
        messageBox->setIcon(QMessageBox::Question);
        messageBox->setWindowTitle(tr("%1 - Add Task")
                                   .arg(QApplication::applicationName()));
        messageBox->setText(tr("<p>Add at the top level or as a "
                               "sibling or child of\n'%1'?").arg(item->text()));
        messageBox->addButton(tr("&Top Level"),
                              QMessageBox::AcceptRole);
        QAbstractButton *siblingButton = messageBox->addButton(
                    tr("&Sibling"), QMessageBox::AcceptRole);
        QAbstractButton *childButton = messageBox->addButton(
                    tr("C&hild"), QMessageBox::AcceptRole);
        messageBox->setDefaultButton(
                    qobject_cast<QPushButton*>(childButton));
        messageBox->addButton(QMessageBox::Cancel);
        messageBox->exec();
        if (messageBox->clickedButton() ==
                messageBox->button(QMessageBox::Cancel))
            return;
        if (messageBox->clickedButton() == childButton)
            insert = StandardTreeModel::AsChild;
        else if (messageBox->clickedButton() == siblingButton)
            insert = StandardTreeModel::AsSibling;
    }

    if (QStandardItem *item = modelXML->insertNewTask(insert,
                                                      tr("New Task"), index)) {
        QModelIndex index = item->index();
        setCurrentIndex(index);
        treeViewXML->edit(index);
        setDirty();
        updateUi();
    }
}

#else

void hC_hsp::editAdd()
{
    qDebug() << "Yeni Hesap Ekle";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->insertRow(0, index)) {
        index = modelXML->index(0, 0, index);
        setCurrentIndex(index);
        treeViewXML->edit(index);
        QString name = modelXML->data(index).toString();
        qDebug() <<"--------------------------------------" ;
        qDebug() <<"--------------------------------------" ;
        qDebug() << name ;
        qDebug() <<"--------------------------------------" ;
        qDebug() <<"--------------------------------------" ;
        setDirty();
        updateUi();
    }
}
#endif


void hC_hsp::editDelete()
{
    qDebug() << "editdelete";
    QModelIndex index = treeViewXML->currentIndex();
    if (!index.isValid())
        return;
#ifdef CUSTOM_MODEL
    QString name = modelXML->data(index).toString();
    int rows = modelXML->rowCount(index);
    if (modelXML->isTimedItem(index))
        stopTiming();
#else
    QStandardItem *item = modelXML->itemFromIndex(index);
    if (item == timedItem)
        stopTiming();
    QString name = item->text();
    int rows = item->rowCount();
#endif
    QString message;
    if (rows == 0)
        message = tr("<p>Delete '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>Delete '%1' and its child (and "
                     "grandchildren etc.)").arg(name);
    else if (rows > 1)
        message = tr("<p>Delete '%1' and its %2 children (and "
                     "grandchildren etc.)").arg(name).arg(rows);
    if (!AQP::okToDelete(this, tr("Delete"), message))
        return;
    modelXML->removeRow(index.row(), index.parent());
    setDirty();
    updateUi();
}


void hC_hsp::stopTiming()
{
    qDebug() << "stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}


#ifdef CUSTOM_MODEL
void hC_hsp::editCut()
{
    qDebug() << "editcut";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}


void hC_hsp::editPaste()
{
    qDebug() << "editpaste";
    setCurrentIndex(modelXML->paste(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editMoveUp()
{
    qDebug() << "editmoveup";
    treeViewXML->setCurrentIndex(
                modelXML->moveUp(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editMoveDown()
{
    qDebug() << "editmovedown";
    treeViewXML->setCurrentIndex(
                modelXML->moveDown(treeViewXML->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editPromote()
{
    qDebug() << "editpromote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hC_hsp::editDemote()
{
    qDebug() << "editdemote";
    QModelIndex index = treeViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    treeViewXML->setCurrentIndex(modelXML->demote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}
#endif // CUSTOM_MODEL


void hC_hsp::editStartOrStop(bool start)
{
    qDebug() << "editstrtstp";
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
#ifdef CUSTOM_MODEL
            modelXML->setTimedItem(index);
            modelXML->addDateTimeToTimedItem(now, now);
            modelXML->setIconForTimedItem(icon);
#else
            if (index.column() != 0) // timedItem is in column 0
                index = modelXML->index(index.row(), 0, index.parent());
            timedItem = static_cast<StandardItem*>(
                        modelXML->itemFromIndex(index));
            Q_ASSERT(timedItem);
            timedItem->addDateTime(now, now);
            timedItem->todayItem()->setIcon(icon);
#endif
            editStartOrStopAction->setIcon(icon);
#ifndef Q_WS_MAC
            setWindowIcon(icon);
#endif \
    // qt 6 timedTime.restart();
            timer.start();
            iconTimeLine.start();
        }
    }
    else { // stop the clock
        timeout(); // update to now
#ifdef CUSTOM_MODEL
        modelXML->setIconForTimedItem();
        modelXML->clearTimedItem();
#else
        if (timedItem) {
            timedItem->todayItem()->setIcon(QIcon());
            timedItem = 0;
        }
#endif
#ifndef Q_WS_MAC
        setWindowIcon(QIcon(":/rsm/images/icon.png"));
#endif
        editStartOrStopAction->setIcon(QIcon(":/rsm/images/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top")
                                         : tr("S&tart"));
    editStartOrStopAction->setIcon(QIcon(start ? tr(":/rsm/images/4.png")
                                               : tr(":/rsm/images/0.png")));
}


void hC_hsp::timeout()
{
    qDebug() << "timeout";
#ifdef CUSTOM_MODEL
    // qt 6   modelXML->incrementEndTimeForTimedItem(timedTime.elapsed());
    // qt 6  timedTime.restart();
#else
    Q_ASSERT(timedItem);
    timedItem->incrementLastEndTime(timedTime.elapsed());
    timedTime.restart();
    StandardItem *item = timedItem;
    while (item) {
        item->todayItem()->setText(item->todaysTime());
        item->totalItem()->setText(item->totalTime());
        item = static_cast<StandardItem*>(item->parent());
    }
#endif
}


void hC_hsp::updateIcon(int frame)
{
    qDebug() << "updateicon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
#ifdef CUSTOM_MODEL
    modelXML->setIconForTimedItem(icon);
#else
    Q_ASSERT(timedItem);
    timedItem->todayItem()->setIcon(icon);
#endif
    editStartOrStopAction->setIcon(icon);
#ifndef Q_WS_MAC
    setWindowIcon(icon);
#endif
}


void hC_hsp::editHideOrShowDoneTasks(bool hide)
{
    qDebug() << "edithideorshwdonetsks";
#ifdef CUSTOM_MODEL
    hideOrShowDoneTask(hide, QModelIndex());
#else
    hideOrShowDoneTask(hide, modelXML->invisibleRootItem());
#endif
}



#ifndef CUSTOM_MODEL
void hC_hsp::hideOrShowDoneTask(bool hide, QStandardItem *item)
{
    QModelIndex index = item->parent() ? item->parent()->index()
                                       : QModelIndex();
    bool hideThisOne = hide && (item->checkState() == Qt::Checked);
    treeViewXML->setRowHidden(item->row(), index, hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < item->rowCount(); ++row)
            hideOrShowDoneTask(hide, item->child(row, 0));
    }
}

#else

void hC_hsp::hideOrShowDoneTask(bool hide,
                                    const QModelIndex &index)
{
    qDebug() << "hideorshowdntsk";
    bool hideThisOne = hide && modelXML->isChecked(index);
    if (index.isValid())
        treeViewXML->setRowHidden(index.row(), index.parent(),
                                  hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelXML->index(row, 0, index));
    }
}
#endif



