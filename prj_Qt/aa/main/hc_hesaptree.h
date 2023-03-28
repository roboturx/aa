#ifndef hC_hesapTree_H
#define hC_hesapTree_H

//#include "main/cw_dlg_options.h"
#include "main/taskitem.h"
//#include "libs/globals.h"
#include "main/cm_treexml.h"


class hC_hesapTree : public QMainWindow
{
    Q_OBJECT

public:
    explicit hC_hesapTree(QWidget * parent=nullptr);
    ~hC_hesapTree();
    cm_dlG_cb_hTur *cbdlgt;

    cm_TreeXML *modelXML;
    QTreeView *treeViewXML;
    QWidget * wdgt_central;
    QWidget * wdgt_hesap;
    QLabel * lB_Hesap;

    QMenu *fileMenu;
    QToolBar *fileToolBar;

    TaskItem *getCurrentItem();


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
    void sgnHesap(TaskItem* currentHesapItem);

public slots:
    void stopTiming();
    void hesapdegisti();
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


///////////////////////////////////////////////////////////////
/// \brief The HesapListesi class
/// xml dosyasından hesap adları ve renklerini
/// qpair olarak veren sınıf

class cL_HesapListesi
{
public:
    typedef QPair<QString,QColor> PairHesapColor;

    cL_HesapListesi() {};
    ~cL_HesapListesi() {};
    PairHesapColor getHesapListesi (QString hangihesaplar);

private:
    PairHesapColor setHesapListesi(QString hangiListe);
    PairHesapColor qp_hesapListesi{};
};


////////////////////////////////////////////////////////
/// \brief The cL_dlG_ColmColor class
/// treeview colonda renk ayarları
///

class cL_dlG_ColmColor : public QStyledItemDelegate
{
public:
    int m_color{};
    QModelIndex m_curIndex{};
public:
    cL_dlG_ColmColor(int renk,QModelIndex currentIndex, QObject /**parent*/)
    {
        /// int değeriyle gelen değişkeni color olark kullanır

        m_color = renk;
        m_curIndex = currentIndex;

    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {


        if (index.column() == 0 /*&&
            index.row() == m_curIndex.row ()*/)
        {
            qDebug()<< "col 0 colmcolor m_color = " << m_color;
            qDebug()<< "row col " << index.row ()<<"-"<<index.column ();
            QStyleOptionViewItem s = *qstyleoption_cast<
                const QStyleOptionViewItem*>(&option);
            s.palette.setColor(QPalette::HighlightedText ,
                               QColor( Qt::cyan));
            s.palette.setColor(QPalette::Text  ,
                               QColor(m_color));

            QStyledItemDelegate::paint(painter, s, index);
        }
    }
};


#endif // hC_hesapTree_H
