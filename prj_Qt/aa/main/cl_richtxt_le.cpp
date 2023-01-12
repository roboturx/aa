
#include "libs/globals.h"
#include "libs/alt_key.h"
#include "main/cl_richtxt_le.h"
#include "main/dialog.h"

cL_RichTxt_LE::cL_RichTxt_LE(QWidget *parent)
    : QTextEdit(parent)
{
    setLineWrapMode(QTextEdit::NoWrap);
    setWordWrapMode(QTextOption::NoWrap);
    setAcceptRichText(true);
    setTabChangesFocus(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    createShortcuts();
    createActions();
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(customContextMenuRequested(const QPoint&)));
    // connect(this, &QTextEdit::customContextMenuRequested,
    //     this, &QTextEdit::customContextMenuRequested);
}


void cL_RichTxt_LE::createShortcuts()
{
    QShortcut *boldShortcut = new QShortcut(QKeySequence::Bold,
                                            this, SLOT(toggleBold()));
    QShortcut *italicShortcut = new QShortcut(QKeySequence::Italic,
                                              this, SLOT(toggleItalic()));

    setToolTip(tr("<p>Use %1 to toggle bold, %2 to toggle italic, "
                  "and the context menu for color and other effects.")
               .arg(boldShortcut->key().toString(
                        QKeySequence::NativeText),
                    italicShortcut->key().toString(
                        QKeySequence::NativeText)));
}


void cL_RichTxt_LE::createActions()
{
    boldAction = createAction(tr("Bold"), Bold);
    italicAction = createAction(tr("Italic"), Italic);
    strikeOutAction = createAction(tr("Strike out"), StrikeOut);
    noSubOrSuperScriptAction = createAction(
                tr("No super or subscript"), NoSuperOrSubscript);
    superScriptAction = createAction(tr("Superscript"), Superscript);
    subScriptAction = createAction(tr("Subscript"), Subscript);

    // colorAction = new QAction(tr("Color"), this);
    //  add color menu to menu
    //  colorAction->setMenu(createColorMenu());  //qt5
    colorAction = createAction(tr("Color"), Color);

    addActions(QList<QAction*>() << boldAction << italicAction
               << strikeOutAction << noSubOrSuperScriptAction
               << superScriptAction << subScriptAction << colorAction);
    AQP::accelerateActions(actions());
}


QAction *cL_RichTxt_LE::createAction(const QString &text,
                                        const QVariant &data)
{
    QAction *action = new QAction(text, this);
    action->setData(data);
    if (data == 6)
    {
        action->setChecked(false);
    }
    else
    {
        action->setCheckable(true);
     }
    connect(action, SIGNAL(triggered()), SLOT(applyTextEffect()));
    return action;
}


QMenu *cL_RichTxt_LE::createColorMenu()
{
    QMenu *colorMenu = new QMenu(this);
    QPixmap pixmap(22, 22);
    typedef QPair<QColor, QString> ColorPair;
    foreach (const ColorPair &pair, QList<ColorPair>()
             << qMakePair(QColor("#DFCFBE") , "Sand Dollar")
             << qMakePair(QColor("#EFC050"), "Mimosa")
             << qMakePair(QColor("#C3447A"), "Fushia Rose")
             << qMakePair(QColor("#7FCDCD"), "Aqua Sky")
             << qMakePair(QColor("#E15D44"), "Tigerlily")
             << qMakePair(QColor("#55B4B0"), "Blue Turguoise")
             << qMakePair(QColor("#45B8AC"), "Turguoise")
             << qMakePair(QColor("#B565A7"), "Radiand Orchid")
             << qMakePair(QColor("#92A8D1"), "Serenity")
             << qMakePair(QColor("#F7CAC9"), "Rose Quartz")
             << qMakePair(QColor("#88B04B"), "Greenery")
             << qMakePair(QColor("#FF6F61"), "Living Coral")
             << qMakePair(QColor("#79C753"), "Green Flash")
             << qMakePair(QColor("#FAE03C"), "Buttercup")
             << qMakePair(QColor("#DD4132"), "Fiesta")
             << qMakePair(QColor("#B18F6A"), "Iced Coffee")
             << qMakePair(QColor("#98DDDE"), "Limped Shell")
             << qMakePair(QColor("#F7786B"), "Peach Echo")
             << qMakePair(QColor("#B76BA3"), "Bodacious")
             << qMakePair(QColor("#D8AE47"), "Spicy Mustard")
             << qMakePair(QColor("#92B6D5"), "Airy Blue")
             << qMakePair(QColor("#AF9483"), "Warm Taupe")

             << qMakePair(QColor(Qt::yellow), tr("Sarı"))
             << qMakePair(QColor(Qt::darkYellow), tr("Koyu Sarı"))
             << qMakePair(QColor(Qt::gray), tr("Gri"))
             << qMakePair(QColor(Qt::darkGray), tr("Koyu Gri"))
             << qMakePair(QColor(Qt::blue), tr("Blue"))
             << qMakePair(QColor(Qt::darkBlue), tr("Dark Blue"))
             << qMakePair(QColor(Qt::cyan), tr("Cyan"))
             << qMakePair(QColor(Qt::darkCyan), tr("Dark Cyan"))
             << qMakePair(QColor(Qt::green), tr("Green"))
             << qMakePair(QColor(Qt::darkGreen), tr("Dark Green"))
             << qMakePair(QColor(Qt::magenta), tr("Magenta"))
             << qMakePair(QColor(Qt::darkMagenta), tr("Dark Magenta"))
             << qMakePair(QColor(Qt::red), tr("Red"))
             << qMakePair (QColor(Qt::darkRed), tr("Dark Red")))
    {
        pixmap.fill(pair.first);
        QAction *action = colorMenu->addAction(pixmap, pair.second);
        action->setData(pair.first);
    }

    ///////////////////
    //    qDebug() << "applycolor";
    //    Dialog *dialog = new Dialog;
    //    const QColorDialog::ColorDialogOptions options =
    //        QFlag(1);
    //   const QColor color = QColorDialog::getColor(Qt::green,
    //                        this, "Select Color", options);

    //   pixmap.fill(color);
    //   QAction *action = colorMenu->addAction(pixmap, pair.second);
    //   action->setData(color);


    //   qDebug()<< "colorname "<<color.name()<<" isvalid "<<color.isValid();
    //   qDebug() << "applycolor 42 color ;"<< color;



    //   setTextColor(action->data().value<QColor>() );

    //   delete dialog;

    //  setTextColor(action->data().value<QColor>());

    //////////////////////
    //   connect(colorMenu, SIGNAL(triggered(QAction*)),
    //        this, SLOT(applyColor(QAction*)));
    AQP::accelerateMenu(colorMenu);
    return colorMenu;
}


QSize cL_RichTxt_LE::sizeHint() const
{
    QFontMetrics fm(font());
    return QSize(document()->idealWidth() + fm.horizontalAdvance("W"),
                 fm.height() + 5);
}


QSize cL_RichTxt_LE::minimumSizeHint() const
{
    QFontMetrics fm(font());
    return QSize(fm.horizontalAdvance("WWWW"), fm.height() + 5);
}


void cL_RichTxt_LE::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter ||
            event->key() == Qt::Key_Return)
    {
        emit returnPressed();
        event->accept();
    }
    else
        QTextEdit::keyPressEvent(event);
}


void cL_RichTxt_LE::customContextMenuRequested(
        const QPoint &pos)
{
    updateContextMenuActions();

    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}



void cL_RichTxt_LE::updateContextMenuActions()
{
    boldAction->setChecked(fontWeight() > QFont::Normal);
    italicAction->setChecked(fontItalic());
    const QTextCharFormat &format = currentCharFormat();
    strikeOutAction->setChecked(format.fontStrikeOut());
    noSubOrSuperScriptAction->setChecked(format.verticalAlignment() ==
                                         QTextCharFormat::AlignNormal);
    superScriptAction->setChecked(format.verticalAlignment() ==
                                  QTextCharFormat::AlignSuperScript);
    subScriptAction->setChecked(format.verticalAlignment() ==
                                QTextCharFormat::AlignSubScript);
}


void cL_RichTxt_LE::applyTextEffect()
{
    if (QAction *action = qobject_cast<QAction*>(sender()))
    {
        Style style = static_cast<Style>(action->data().toInt());
        QTextCharFormat format = currentCharFormat();
        switch (style)
        {
        case Bold: toggleBold(); return;
        case Italic: toggleItalic(); return;
        case StrikeOut:
            format.setFontStrikeOut(!format.fontStrikeOut());
            break;
        case NoSuperOrSubscript:
            format.setVerticalAlignment(
                        QTextCharFormat::AlignNormal);
            break;
        case Superscript:
            format.setVerticalAlignment(
                        QTextCharFormat::AlignSuperScript);
            break;
        case Subscript:
            format.setVerticalAlignment(
                        QTextCharFormat::AlignSubScript);
            break;
        case Color:
            applyColor (colorAction);
            return;
        }
        mergeCurrentCharFormat(format);
    }
}


void cL_RichTxt_LE::applyColor(QAction *action)
{
    qDebug() << "applycolor";
    Dialog *dialog = new Dialog;

    Q_ASSERT(action);


    const QColorDialog::ColorDialogOptions options =
            QFlag(1);
    const QColor color = QColorDialog::getColor(Qt::green,
                             this, "Select Color", options);

     action->setData(color);
    setTextColor(action->data().value<QColor>());
    delete dialog;
}


QString cL_RichTxt_LE::toSimpleHtml() const
{
    QString html;
    for (QTextBlock block = document()->begin(); block.isValid();
         block = block.next()) {
        for (QTextBlock::iterator i = block.begin(); !i.atEnd();
             ++i) {
            QTextFragment fragment = i.fragment();
            if (fragment.isValid()) {
                QTextCharFormat format = fragment.charFormat();
                QColor color = format.foreground().color();
                //QString text = Qt::escape(fragment.text());
                //deleted for Qt5
                QString text = QString(fragment.text()).toHtmlEscaped();
                //added for Qt5

                QStringList tags;
                if (format.verticalAlignment() ==
                        QTextCharFormat::AlignSubScript)
                    tags << "sub";
                else if (format.verticalAlignment() ==
                         QTextCharFormat::AlignSuperScript)
                    tags << "sup";
                if (format.fontItalic())
                    tags << "i";
                if (format.fontWeight() > QFont::Normal)
                    tags << "b";
                if (format.fontStrikeOut())
                    tags << "s";
                while (!tags.isEmpty())
                    text = QString("<%1>%2</%1>")
                            .arg(tags.takeFirst()).arg(text);
                if (color != QColor(Qt::black))
                    text = QString("<font color=\"%1\">%2</font>")
                            .arg(color.name(),text);
                html += text;
            }
        }
    }
    return html;
}
