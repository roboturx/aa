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


    QLabel *lB_Hesap;
    cm_dlG_cb_hTur *cbdlgt;

    quint64* pi_Hesap_Kod;
    QString* ps_Hesap_Ad;
    TaskItem* getCurrentItem();

    cm_TreeXML *modelXML;
    QTreeView *treeViewXML;

private:

    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;



    QAction *boldAction;
    QAction *italicAction;
    QAction *strikeOutAction;
    QAction *noSubOrSuperScriptAction;
    QAction *superScriptAction;
    QAction *subScriptAction;
    QAction *colorAction;

    void createModelViewDelegate();
    void createConnections();
    void setCurrentIndex(const QModelIndex &index);

    void hideOrShowDoneTask(bool hide, const QModelIndex &index);
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

    bool okToClearData();
    void editStartOrStop(bool start);
    void editHideOrShowDoneTasks(bool hide);
    void setDirty(bool dirty=true)
    {   setWindowModified(dirty);  }

    void load(const QString &filename,
              const QStringList &taskPath=QStringList());
    void timeout();
    void updateIcon(int frame);

public slots:
    void updateUi();
    void stopTiming();


protected:
    void closeEvent(QCloseEvent*);
};

#endif // DW_HESAP_H
