#ifndef MAINWINDOW_H
#define MAINWINDOW_H




#include "libs/globals.h"
#include "main/dw_hesap.h"

//    QT_BEGIN_NAMESPACE
//    class QAction;
//    class QListWidget;
//    class QMenu;
//    class QTextEdit;
//    QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

private slots:
    void newLetter();
    void save();
    void print();
    void undo();
    void about();
    void insertCustomer(const QString &customer);
    void addParagraph(const QString &paragraph);

private:
    void createActions();
    void createStatusBar();
    void createDockWindows();

    QTextEdit *textEdit;
    QListWidget *customerList;

    QListWidget *paragraphsList;

    dW_Hesap *hesapList;

    QMenu *viewMenu;
};


#endif // MAINWINDOW_H
