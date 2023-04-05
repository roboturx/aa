#ifndef HELPITEM_H
#define HELPITEM_H


#include <QDateTime>
#include <QList>
#include <QPair>
#include <QString>

class HelpItem
{
public:
    explicit HelpItem(const QString &helpAd     = QString(),
                      const QString &helpAcklm  = QString(),
                      const int &helpKod    = 0,
                      const QString &DBFile      = QString(),
                      HelpItem *parent           = 0 );
    ~HelpItem() { qDeleteAll(lo_children); }


    /// XML:002
    /// getters and setters
    /// variables for XML file
    ///


    QString helpAd() const { return f_ms_helpAd; }
    void setHelpAd(const QString &helpAd) { f_ms_helpAd = helpAd; }

    QString helpAcklm() const { return f_ms_helpAcklm; }
    void setHelpAcklm(const QString &helpAcklm) { f_ms_helpAcklm = helpAcklm; }

    int helpKod() const
    { return f_mi_helpKod; }
    void setHelpKod(const int &helpKod)
    { f_mi_helpKod = helpKod; }

    QString DBFile() const
    { return f_ms_DBFile; }
    void setHelpDBFile(const QString &helpDBFile)
    { f_ms_DBFile = helpDBFile; }

    HelpItem *parent() const
    { return o_parent; }
    HelpItem *childAt(int row) const
    { return lo_children.value(row); }
    int rowOfChild(HelpItem *child) const
    { return lo_children.indexOf(child); }
    int childCount() const
    { return lo_children.count(); }
    bool hasChildren() const
    { return !lo_children.isEmpty(); }
    QList<HelpItem*> children() const
    { return lo_children; }

    void insertChild(int row, HelpItem *item)
    { item->o_parent = this; lo_children.insert(row, item); }
    void addChild(HelpItem *item)
    { item->o_parent = this; lo_children << item; }
    void swapChildren(int oldRow, int newRow)
    //  qt5      { m_children.swap(oldRow, newRow); }
    { lo_children.swapItemsAt (oldRow, newRow); }
    HelpItem* takeChild(int row);

private:

    /// XML:001
    /// define
    /// variables for XML file
    ///

    QString f_ms_helpAd;
    QString f_ms_helpAcklm;
    int f_mi_helpKod;
    QString f_ms_DBFile;

    HelpItem *o_parent;
    QList<HelpItem*> lo_children;
};

#endif // HELPITEM_H
