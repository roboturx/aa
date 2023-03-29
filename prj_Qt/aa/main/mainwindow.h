#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "adrs/clsn.h"
#include "hsap/hc_hspdetay.h"
#include "main/dbase.h"
#include "adrs/frm.h"
#include "libs/globals.h"
#include "main/hc_hesaptree.h"

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
    ~MainWindow();


    DBase *dbase;
    hC_CLSN *clsn;
    hC_FRM  *firma ;
    hC_HSPDTY *hspdty;
    ProxyModel *hspProxyModel;

    hC_hesapTree *hesapList;

    TaskItem* mw_currentHesapItem{};

    QTabWidget *w_TABs{};
    QSplitter *splitter{};
    //QGridLayout *layout1;

    QLabel *integerLabel{};
    QLabel *colorLabel{} ;
    QPushButton *colorButton{};



signals:
    void sgnMwHsp(TaskItem* hCTreeHsp );

private slots:
    void newLetter();
    void save();
    void print();
    void undo();
    void about();
    void insertCustomer(const QString &customer);
    void addParagraph(const QString &paragraph);

    // w tabs hchsptree deki hesaba göre oluşur
    // hesapitem connect ile geliyor
    void w_Tabs(TaskItem *hesapItem);
    void setColor();
    void setInteger();

private:
    void createActions();
    void createStatusBar();
    void createDockWindows();
    void createTabs();

    QTextEdit *textEdit;
    QListWidget *customerList;

    QListWidget *paragraphsList;



    QMenu *viewMenu;



};


#endif // MAINWINDOW_H
