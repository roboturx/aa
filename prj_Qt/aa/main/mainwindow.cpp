
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrintSupport>
#endif
#endif

#include "mainwindow.h"
//! [0]

//! [1]
MainWindow::MainWindow()
    : textEdit(new QTextEdit)
{
    qDebug ()<<"   creat gui,";

    splitter = new QSplitter(this);
    w_TABs = new QTabWidget(this);
qDebug ()<<"   creat gui,";
    QWidget *page1 = new QWidget(splitter);
    QGridLayout *layout1 = new QGridLayout(page1);
//    w_TABs = new QTabWidget(page1);
//    w_TABs->setTabShape (QTabWidget::Triangular);
//    w_TABs->setTabPosition (QTabWidget::North);
    layout1->setColumnStretch(1, 1);
    layout1->setColumnMinimumWidth(1, 250);
    layout1->addWidget(w_TABs             ,  0, 0, 16, 2 );
    layout1->addWidget(new QLabel("Tabs") , 17, 0, 1, 2 );

//    layout1->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored,
//                                     QSizePolicy::MinimumExpanding), 5, 0);

    splitter->addWidget(page1);
    setCentralWidget(splitter);


    //  login();




    createActions();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Evren v23.01"));

    newLetter();
    setUnifiedTitleAndToolBarOnMac(true);
}
//! [1]

//! [2]
void MainWindow::newLetter()
{
    textEdit->clear();

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);
    QTextFrame *topFrame = cursor.currentFrame();
    QTextFrameFormat topFrameFormat = topFrame->frameFormat();
    topFrameFormat.setPadding(16);
    topFrame->setFrameFormat(topFrameFormat);

    QTextCharFormat textFormat;
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(16);
    tableFormat.setAlignment(Qt::AlignRight);
    cursor.insertTable(1, 1, tableFormat);
    cursor.insertText("The Firm", boldFormat);
    cursor.insertBlock();
    cursor.insertText("321 City Street", textFormat);
    cursor.insertBlock();
    cursor.insertText("Industry Park");
    cursor.insertBlock();
    cursor.insertText("Some Country");
    cursor.setPosition(topFrame->lastPosition());
    cursor.insertText(QDate::currentDate().toString("d MMMM yyyy"), textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText("Dear ", textFormat);
    cursor.insertText("NAME", italicFormat);
    cursor.insertText(",", textFormat);
    for (int i = 0; i < 3; ++i)
        cursor.insertBlock();
    cursor.insertText(tr("Yours sincerely,"), textFormat);
    for (int i = 0; i < 3; ++i)
        cursor.insertBlock();
    cursor.insertText("The Boss", textFormat);
    cursor.insertBlock();
    cursor.insertText("ADDRESS", italicFormat);
}
//! [2]

//! [3]
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
//! [3]

//! [4]
void MainWindow::save()
{
    QMimeDatabase mimeDatabase;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Choose a file name"), ".",
                                                    mimeDatabase.mimeTypeForName("text/html").filterString());
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream out(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toHtml();
    QGuiApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}
//! [4]

//! [5]
void MainWindow::undo()
{
    QTextDocument *document = textEdit->document();
    document->undo();
}
//! [5]

//! [6]
void MainWindow::insertCustomer(const QString &customer)
{
    if (customer.isEmpty())
        return;
    QStringList customerList = customer.split(", ");
    QTextDocument *document = textEdit->document();
    QTextCursor cursor = document->find("NAME");
    if (!cursor.isNull()) {
        cursor.beginEditBlock();
        cursor.insertText(customerList.at(0));
        QTextCursor oldcursor = cursor;
        cursor = document->find("ADDRESS");
        if (!cursor.isNull()) {
            for (int i = 1; i < customerList.size(); ++i) {
                cursor.insertBlock();
                cursor.insertText(customerList.at(i));
            }
            cursor.endEditBlock();
        }
        else
            oldcursor.endEditBlock();
    }
}
//! [6]

//! [7]
void MainWindow::addParagraph(const QString &paragraph)
{
    if (paragraph.isEmpty())
        return;
    QTextDocument *document = textEdit->document();
    QTextCursor cursor = document->find(tr("Yours sincerely,"));
    if (cursor.isNull())
        return;
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor, 2);
    cursor.insertBlock();
    cursor.insertText(paragraph);
    cursor.insertBlock();
    cursor.endEditBlock();

}

//! [7]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Dock Widgets"),
                       tr("The <b>Dock Widgets</b> example demonstrates how to "
                          "use Qt's dock widgets. You can enter your own text, "
                          "click a customer to add a customer name and "
                          "address, and click standard paragraphs to add them."));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"), this);
    newLetterAct->setShortcuts(QKeySequence::New);
    newLetterAct->setStatusTip(tr("Create a new form letter"));
    connect(newLetterAct, &QAction::triggered, this, &MainWindow::newLetter);
    fileMenu->addAction(newLetterAct);
    fileToolBar->addAction(newLetterAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current form letter"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon printIcon = QIcon::fromTheme("document-print", QIcon(":/images/print.png"));
    QAction *printAct = new QAction(printIcon, tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the current form letter"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);
    fileMenu->addAction(printAct);
    fileToolBar->addAction(printAct);

    fileMenu->addSeparator();

    QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));
    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png"));
    QAction *undoAct = new QAction(undoIcon, tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
    editMenu->addAction(undoAct);
    editToolBar->addAction(undoAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

//! [8]
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//! [8]

//! [9]
void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
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


    dock = new QDockWidget(tr("Hesaplar"), this);
    hesapList = new hC_hesapTree(dock);
    dock->setWidget(hesapList);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());



    dock = new QDockWidget(tr("Paragraphs"), this);
    paragraphsList = new QListWidget(dock);
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

    connect(customerList, &QListWidget::currentTextChanged,
            this, &MainWindow::insertCustomer);
    connect(paragraphsList, &QListWidget::currentTextChanged,
            this, &MainWindow::addParagraph);

    connect(hesapList, &hC_hesapTree::sgnHesap,
            this, &MainWindow::w_Tabs);
}

void MainWindow::w_Tabs(TaskItem *hesapItem)
{

    currentHesapItem = hesapItem;
    qDebug()<< "mw wtabs////////////////////////"
            << hesapItem->hesapAd();
    createTabs();


   // layout1->addWidget(wt    ,  0, 0, 16, 2 );
   // splitter->addWidget (wt);
  //  delete hesapItem;

}


void MainWindow::createTabs()
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

    QString h_Turu = currentHesapItem->hesapTuru();

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
            this, &MainWindow::setInteger);
    connect(colorButton, &QAbstractButton::clicked,
            this, &MainWindow::setColor);
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
