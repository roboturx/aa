#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), completer(nullptr), lineEdit(nullptr)
{
    QWidget *centralWidget = new QWidget;


    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/wordlist.txt"));


     lineEdit = new QLineEdit;
    lineEdit->setCompleter(completer);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lineEdit, 6, 0, 1, 2);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle(tr("Completer"));
    lineEdit->setFocus();

}
QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    completer->setMaxVisibleItems(100);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
        qDebug()<<line.trimmed();
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

        return new QStringListModel(words, completer);

}
