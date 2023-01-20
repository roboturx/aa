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

    QWidget * wdgt_central;
    QSplitter *splitter ;
    QTabWidget *w_TABs ;
    DBase *dbase;
    QLabel * lB_Hesap;
    QLabel *integerLabel;
    QLabel *colorLabel ;
    QPushButton *colorButton;
    QMenu *viewMenu;

 //   void login();



    /////////////////////////
   //    cm_TreeXML *modelXML;
//    QTreeView *treeViewXML;

  //  QWidget * wdgt_hesap;
  //  cw_Dlg_Options *colorDialogOptionsWidget;

 //   TaskItem *getCurrentItem();



private:
    QTimer timer;
    QTimeLine iconTimeLine;

    QAction *createAction(const QString &icon,
                         const QString &text,
                         QMainWindow *parent,
                         const QKeySequence &shortcut=QKeySequence());
    void createActions();
    void createGui();
    //void createActions();
    void createMenusAndToolBar();
    void createDocks();
    void createTABs(QString h_Turu);
    void fgenelAyarlar();

    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileQuitAction;
    QAction *editAddAction;
    QAction *editDeleteAction;

    QAction *editCutAction;
    QAction *editPasteAction;
    QAction *editMoveUpAction;
    QAction *editMoveDownAction;
    QAction *editPromoteAction;
    QAction *editDemoteAction;
    QAction *editStartOrStopAction;
    QAction *editHideOrShowDoneTasksAction;
    QAction *ayarlarAction;

    ////////////////////////

//    QTime timedTime;
//    int currentIcon;

//signals:

//    void sg_hTurColor(QColor color);


private slots:

    void setColor();
    void setInteger();

    void customContextMenuRequested(const QPoint &pos);
    void contextMenuEvent(QContextMenuEvent *event);


    /////////////////////////////////

//private:
//    enum Style {Bold, Italic, StrikeOut, NoSuperOrSubscript,
//                Subscript, Superscript};

//    void createShortcuts();
//    void createActions2 ();
//    QAction *createAction2(const QString &text, const QVariant &data);
//    QMenu *createColorMenu();
//    void updateContextMenuActions();

protected:
  //  void closeEvent(QCloseEvent*);

};



#endif // hC_main_H

