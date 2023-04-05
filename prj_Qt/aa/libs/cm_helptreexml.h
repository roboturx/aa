#ifndef CM_HELPTREEXML_H
#define CM_HELPTREEXML_H

#include "libs/globals.h"
#include "libs/helpitem.h"
//#include "main/cm_dlg_cb_htur.h"

class QMimeData;

class cm_HELPTreeXML : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit cm_HELPTreeXML(QObject *parent = nullptr)
        : QAbstractItemModel(parent), timedItem(0), rootItem(0),
        cutItem(0)
    {
        pi_max_Hesap_ID = new int{};
        *pi_max_Hesap_ID = 0;
    }
    ~cm_HELPTreeXML() { delete rootItem; delete cutItem; }

    int* pi_max_Hesap_ID; // for XML file rowid
    QComboBox* cB_hesapAds;   // for hesap ad




    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index,
                  int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role=Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int=Qt::EditRole) { return false; }
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role=Qt::EditRole);
    bool insertRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());

    Qt::DropActions supportedDragActions() const
    { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const
    { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *mimeData,
                      Qt::DropAction action, int row, int column,
                      const QModelIndex &parent);

    bool isChecked(const QModelIndex &index) const;
    bool hasCutItem() const { return cutItem; }

    QModelIndex moveUp(const QModelIndex &index);
    QModelIndex moveDown(const QModelIndex &index);
    QModelIndex cut(const QModelIndex &index);
    QModelIndex paste(const QModelIndex &index);
    QModelIndex promote(const QModelIndex &index);
    QModelIndex demote(const QModelIndex &index);

    void setTimedItem(const QModelIndex &index);
    void clearTimedItem();
    bool isTimedItem(const QModelIndex &index);
    void addDateTimeToTimedItem(const QDateTime &start,
                                const QDateTime &end);
    void setIconForTimedItem(const QIcon &icon=QIcon());
    void incrementEndTimeForTimedItem(int msec);

    void clear();

    QString filename() const { return m_filename; }
    void setFilename(const QString &filename)
    { m_filename=filename; }

    void load(const QString &filename=QString());
    void save(const QString &filename=QString());
    QStringList pathForIndex(const QModelIndex &index) const;
    QModelIndex indexForPath(const QStringList &path) const;

    void setListXML(QList<HelpItem *> newListXML);
    QList<HelpItem *> getListXML() const;

signals:
    void stopTiming();

private:
    HelpItem *itemForIndex(const QModelIndex &index) const;
    void readHelps(QXmlStreamReader *reader, HelpItem *help);
    void writeHelpAndChildren(QXmlStreamWriter *writer,
                              HelpItem *help) const;
    void announceItemChanged(HelpItem *item);
    QModelIndex indexForPath(const QModelIndex &parent,
                             const QStringList &path) const;
    QModelIndex moveItem(HelpItem *parent, int oldRow, int newRow);

    QString m_filename;
    QIcon   m_icon;
    HelpItem *timedItem;
    HelpItem *rootItem;
    HelpItem *cutItem;
    QList<HelpItem*> listXML;

public slots:
    void hTurColor(QColor color);


};

#endif // CM_HELPTREEXML_H
