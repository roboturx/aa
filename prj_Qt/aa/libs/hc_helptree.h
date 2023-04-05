#ifndef hC_helpTree_H
#define hC_helpTree_H

//#include "main/cw_dlg_options.h"
#include "libs/cm_helptreexml.h"
#include "libs/helpitem.h"
//#include "libs/globals.h"



class hC_helpTree : public QMainWindow
{
    Q_OBJECT

public:
    explicit hC_helpTree(QWidget *parent=nullptr);
    ~hC_helpTree();
  //  cm_dlG_cb_hTur *cbdlgt;

    cm_HELPTreeXML *modelHelpXML;
    QTreeView *treeViewXML;
    QWidget *wdgt_central;
    QWidget *wdgt_help;
    QLabel *lB_Help;

    QMenu *fileMenu;
    QToolBar *fileToolBar;

    HelpItem *getCurrentItem();


private:
    void createGui();
    void createModelViewDelegate();
    void createActions();
    void createMenusAndToolBar();
    void createConnections();
    void createTabs(QString h_Turu);
    bool okToClearData();
    void setCurrentIndex(const QModelIndex &index);

    void hideOrShowDoneTask(bool hide, const QModelIndex &index);

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

    QTimer timer;
    QTimeLine iconTimeLine;
    QTime timedTime;
    int currentIcon;


signals:
    void sgnHelp(HelpItem* currentHelpItem);

public slots:
    void stopTiming();
    //void hesapdegisti();
    void updateUi();

private slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void editAdd();
    void editDelete();

    void editCut();
    void editPaste();
    void editMoveUp();
    void editMoveDown();
    void editPromote();
    void editDemote();

    void editStartOrStop(bool start);
    void editHideOrShowDoneTasks(bool hide);
    void setDirty(bool dirty=true)
    {   setWindowModified(dirty);  }

    void load(const QString &filename,
              const QStringList &taskPath=QStringList());
    void timeout();
    void updateIcon(int frame);

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

    QAction *boldAction;
    QAction *italicAction;
    QAction *strikeOutAction;
    QAction *noSubOrSuperScriptAction;
    QAction *superScriptAction;
    QAction *subScriptAction;
    QAction *colorAction;

protected:
    void closeEvent(QCloseEvent*);


};


#endif // hC_helpTree_H
