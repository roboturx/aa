#ifndef hC_hsp_H
#define hC_hsp_H


#include "libs/globals.h"
#include "libs/alt_key.h"
#include "cls_dlgt_richtext.h"
#include "cls_mdl_treefromxml.h"


class QAction;
class QStandardItem;
class StandardItem;
class QModelIndex;
class QTreeView;

class cls_mdl_TreeFromXml;

class hC_hsp : public QMainWindow
{
    Q_OBJECT

public:
    explicit hC_hsp(QWidget *parent=0);

    QString* ps_Hesap_Ad;
    quint64* pi_Hesap_Kod;

    QLabel * lB_HesapKod;
    QLabel * lB_HesapAd;
    QLabel * lB_HesapKodAd;

    TaskItem *getCurrentItem();
    cls_mdl_TreeFromXml *modelXML;


private:
    void createModelAndView();
    void createActions();
    void createMenusAndToolBar();
    void createConnections();
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

    QTreeView *treeViewXML;
    QWidget *centralWdgt;



    QTimer timer;
    QTimeLine iconTimeLine;
    QTime timedTime;
    int currentIcon;

protected:
    void closeEvent(QCloseEvent*);

signals:
    void sgnHesap(quint64* m_Hesap_Kod, QString* m_Hesap_Ad);


public slots:
    void stopTiming();

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

    void loadXML(const QString &filename,
              const QStringList &taskPath=QStringList());
    void timeout();
    void updateIcon(int frame);
    void updateUi();
};

#endif // hC_hsp_H

