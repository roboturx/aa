#ifndef hC_hsp_H
#define hC_hsp_H

#include "hsap/dialogoptionswidget.h"
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

    cls_dlgt_ComboBox *cbdlgt;

    QString* ps_Hesap_Ad;
    quint64* pi_Hesap_Kod;

    QLabel * lB_Hesap;
    QLabel *integerLabel;
    QLabel *colorLabel ;
    QPushButton *colorButton;

    QTreeView *treeViewXML;
    QWidget * wdgt_central;
    QWidget * wdgt_hesap;
    DialogOptionsWidget *colorDialogOptionsWidget;

    TaskItem *getCurrentItem();
    cls_mdl_TreeFromXml *modelXML;

private:
    void createGui();
    void createModelViewDelegate();
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
    void hesapdegisti();

private slots:

    void setColor();
    void setInteger();

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
    void updateUi();
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

};

#endif // hC_hsp_H

