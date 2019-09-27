// QTextDocument printing example written by David Faure for EADS
// Compared to QTextDocument::print, it allows to add a page header and footer.

#include <QPrinter>
#include <QPainter>
#include <QProgressDialog>
#include <QApplication>
#include <QTextDocument>
#include <QTextTableCell>
#include <QTextCursor>
#include <QDebug>

static const int textMargins = 12; // in millimeters
static const int borderMargins = 10; // in millimeters

static double mmToPixels(QPrinter& printer, int mm)
{
    return mm * 0.039370147 * printer.resolution();
}

static void paintPage(QPrinter& printer, int pageNumber, int pageCount,
                      QPainter* painter, QTextDocument* doc,
                      const QRectF& textRect, qreal footerHeight)
{
    //qDebug() << "Printing page" << pageNumber;
    const QSizeF pageSize = printer.paperRect().size();
    //qDebug() << "pageSize=" << pageSize;

    const double bm = mmToPixels(printer, borderMargins);
    const QRectF borderRect(bm, bm, pageSize.width() - 2 * bm, pageSize.height() - 2 * bm);
    painter->drawRect(borderRect);

    painter->save();
    // textPageRect is the rectangle in the coordinate system of the QTextDocument, in pixels,
    // and starting at (0,0) for the first page. Second page is at y=doc->pageSize().height().
    const QRectF textPageRect(0, pageNumber * doc->pageSize().height(), doc->pageSize().width(), doc->pageSize().height());
    // Clip the drawing so that the text of the other pages doesn't appear in the margins
    painter->setClipRect(textRect);
    // Translate so that 0,0 is now the page corner
    painter->translate(0, -textPageRect.top());
    // Translate so that 0,0 is the text rect corner
    painter->translate(textRect.left(), textRect.top());
    doc->drawContents(painter);
    painter->restore();

    // Footer: page number or "end"
    QRectF footerRect = textRect;
    footerRect.setTop(textRect.bottom());
    footerRect.setHeight(footerHeight);
    if (pageNumber == pageCount - 1)
        painter->drawText(footerRect, Qt::AlignCenter, QObject::tr("Fin du Bordereau de livraison"));
    else
        painter->drawText(footerRect, Qt::AlignVCenter | Qt::AlignRight, QObject::tr("Page %1/%2").arg(pageNumber+1).arg(pageCount));
}

static void printDocument(QPrinter& printer, QTextDocument* doc, QWidget* parentWidget)
{
    QPainter painter( &printer );
    QSizeF pageSize = printer.pageRect().size(); // page size in pixels
    // Calculate the rectangle where to lay out the text
    const double tm = mmToPixels(printer, textMargins);
    const qreal footerHeight = painter.fontMetrics().height();
    const QRectF textRect(tm, tm, pageSize.width() - 2 * tm, pageSize.height() - 2 * tm - footerHeight);
    //qDebug() << "textRect=" << textRect;
    doc->setPageSize(textRect.size());

    const int pageCount = doc->pageCount();
    QProgressDialog dialog( QObject::tr( "Printing" ), QObject::tr( "Cancel" ), 0, pageCount, parentWidget );
    dialog.setWindowModality( Qt::ApplicationModal );

    bool firstPage = true;
    for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex) {
        dialog.setValue( pageIndex );
        if (dialog.wasCanceled())
             break;

        if (!firstPage)
            printer.newPage();

        paintPage( printer, pageIndex, pageCount, &painter, doc, textRect, footerHeight );
        firstPage = false;
    }
}

static void addTable(QTextCursor& cursor)
{
    const int columns = 4;
    const int rows = 1;

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount( 1 );
    QTextTable* textTable = cursor.insertTable( rows + 1,
                                                columns,
                                                tableFormat );
    QTextCharFormat tableHeaderFormat;
    tableHeaderFormat.setBackground( QColor( "#DADADA" ) );

    QStringList headers;
    headers << "Product" << "Reference" << "Price" << "Price with shipping";
    for( int column = 0; column < columns; column++ ) {
        QTextTableCell cell = textTable->cellAt( 0, column );
        Q_ASSERT( cell.isValid() );
        cell.setFormat( tableHeaderFormat );
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText( headers[column] );
    }
    int row = 0;
    for( int column = 0; column < columns; column++ ) {
        QTextTableCell cell = textTable->cellAt( row + 1, column );
        Q_ASSERT( cell.isValid() );
        QTextCursor cellCursor = cell.firstCursorPosition();
        const QString cellText = QString( "A 220.00" );
        cellCursor.insertText( cellText );
    }
    cursor.movePosition( QTextCursor::End );
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextDocument textDocument;
    QTextCursor cursor(&textDocument);
    cursor.insertText("This is the first page");

    addTable(cursor);

    QTextBlockFormat blockFormat;
    blockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysBefore);
    cursor.insertBlock(blockFormat);
    cursor.insertText("This is the second page");

    QPrinter printer;
    printer.setOutputFileName("test.pdf");
    printer.setFullPage(true);

    printDocument(printer, &textDocument, 0);

    //QTextBrowser tEdit;
    //tEdit.show();
    //return app.exec();
    return 0;
}
