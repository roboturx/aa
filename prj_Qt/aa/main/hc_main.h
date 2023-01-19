#ifndef hC_main_H
#define hC_main_H


#include "libs/globals.h"
#include "main/dbase.h"
//#include "main/cm_treexml.h"
//#include "libs/alt_key.h"
//#include "main/cm_dlg_richtxt.h"
//#include "cm_treexml.h"


class hC_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit hC_main();

    void login();
  //  QList<QColor> ls_hTurColor;

   // void setHesapAdColor(TaskItem *item);
//    cm_dlG_cb_hTur *cbdlgt;
    DBase *dbase;

    QLabel * lB_Hesap;
    QLabel *integerLabel;
    QLabel *colorLabel ;
    QPushButton *colorButton;

//    cm_TreeXML *modelXML;
//    QTreeView *treeViewXML;
    QWidget * wdgt_central;
  //  QWidget * wdgt_hesap;
  //  cw_Dlg_Options *colorDialogOptionsWidget;

 //   TaskItem *getCurrentItem();
    QTabWidget *w_TABs ;
    QMenu *viewMenu;

protected:

    QSplitter *splitter ;

    void createGui();
    void createTABs(QString h_Turu);
  //  void createModelViewDelegate();
    void createActions();
    void createDocks();
    void createMenusAndToolBar();
  //  void createConnections();

   // void setCurrentIndex(const QModelIndex &index);






  void fgenelAyarlar();


    QTimer timer;
    QTimeLine iconTimeLine;
    QTime timedTime;
    int currentIcon;

//protected:
//    void closeEvent(QCloseEvent*);

    // QGridLayout *layout0 ;



signals:
    void sgnHesap(quint64* m_Hesap_Kod,
                  QString* m_Hesap_Ad/*,
                  QString* m_Hesap_Turu*/);
    void sg_hTurColor(QColor color);



private slots:

    void setColor();
    void setInteger();


  //  void updateUi();
    void customContextMenuRequested(const QPoint &pos);
    void contextMenuEvent(QContextMenuEvent *event);
private:
    enum Style {Bold, Italic, StrikeOut, NoSuperOrSubscript,
                Subscript, Superscript};

    void createShortcuts();
    void createActions2 ();
    QAction *createAction2(const QString &text, const QVariant &data);
    QMenu *createColorMenu();
    void updateContextMenuActions();



};



#endif // hC_main_H

