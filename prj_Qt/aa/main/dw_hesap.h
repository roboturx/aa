#ifndef DW_HESAP_H
#define DW_HESAP_H

#include "main/cm_dlg_cb_htur.h"
#include "main/cm_treexml.h"
#include "main/taskitem.h"
//#include "hc_main.h"
//#include "libs/globals.h"


class dW_Hesap : public QWidget
{
    Q_OBJECT
public:
    dW_Hesap(QWidget *parent=nullptr);


    cm_TreeXML *modelXML;
    QTreeView *treeViewXML;
    QLabel *lB_Hesap;
    quint64* pi_Hesap_Kod;
    QString* ps_Hesap_Ad;


    TaskItem* getCurrentItem();



    ///////////////////////////////////////////////////////

  //  cm_dlG_cb_hTur *cbdlgt;





private:

    QTimer timer;
    QTimeLine iconTimeLine;

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
    QAction *genelAyarlar;



    void createModelViewDelegate();
    void createConnections();
    void setCurrentIndex(const QModelIndex &index);



    bool okToClearData();

    void load(const QString &filename,
              const QStringList &taskPath=QStringList());
    void editHideOrShowDoneTasks(bool hide);

    void editStartOrStop(bool start);

    void timeout();
    void updateIcon(int frame);
    void hideOrShowDoneTask(bool hide, const QModelIndex &index);
    //////////////////////////////////////////////////////////




//    QAction *boldAction;
//    QAction *italicAction;
//    QAction *strikeOutAction;
//    QAction *noSubOrSuperScriptAction;
//    QAction *superScriptAction;
//    QAction *subScriptAction;
//    QAction *colorAction;





signals:
        void sgnHesap(quint64* m_Hesap_Kod,
                      QString* m_Hesap_Ad/*,
                      QString* m_Hesap_Turu*/);
public slots:
    void updateUi();
    void stopTiming();
    void setDirty(bool dirty=true)     {   setWindowModified(dirty);  }
    void customContextMenuRequested(const QPoint &pos);
    void contextMenuEvent(QContextMenuEvent *event);

    void fileNew();
    void fileOpen();

    bool fileSave();
    bool fileSaveAs();
    void close();
    void editAdd();
    void editDelete();

   void  editCut();
    void editPaste();
    void editMoveUp();
    void editMoveDown();
    void editPromote();
    void editDemote();
    void fgenelAyarlar();

};

#endif // DW_HESAP_H
