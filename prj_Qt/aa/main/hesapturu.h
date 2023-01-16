#ifndef HESAPTURU_H
#define HESAPTURU_H

#include "libs/globals.h"

class HesapTuru
{
public:
    HesapTuru();
public:
    explicit HesapTuru(const QString &hs_Tur   = QString(),
                       const QColor  &hs_Color = QColor(),
                       const QIcon   &hs_icon  = QIcon(),
                       const QString &hs_01    = QString(),
                       const QString &hs_02    = QString(),
                       const quint64 &hs_T_Kod = 0,
                      HesapTuru *parent        = 0 );
    ~HesapTuru() { qDeleteAll(lo_children); }

    /// XML:002
    /// getters and setters
    /// variables for XML file
    ///

    QString getHs_Tur() const { return mstr_hs_Tur; }
    void setHs_Tur(const QString &hesapTuru) { mstr_hs_Tur = hesapTuru; }

    QColor getHs_Color() const { return mcol_hs_Color; }
    void setHs_Color(const QColor &hesapColor) { mcol_hs_Color = hesapColor; }

    QIcon getHs_icon() const    { return mico_hs_Icon; }
    void setHs_Icon(const QIcon &hesapIcon) { mico_hs_Icon = hesapIcon; }

    QString getHs_01() const  { return mstr_hs_01; }
    void setHs_01(const QString &hesap01) { mstr_hs_01 = hesap01; }

    QString getHs_02() const  { return mstr_hs_02; }
    void setHs_02(const QString &hesap02) { mstr_hs_02 = hesap02; }

    quint64 getHs_T_Kod() const   { return mint_hs_T_Kod; }
    void setHs_T_Kod(const quint64 &hesapTKod)  { mint_hs_T_Kod = hesapTKod; }

    HesapTuru *parent() const     { return o_parent; }
    HesapTuru *childAt(int row) const   { return lo_children.value(row); }
    int rowOfChild(HesapTuru *child) const     { return lo_children.indexOf(child); }
    int childCount() const     { return lo_children.count(); }
    bool hasChildren() const     { return !lo_children.isEmpty(); }
    QList<HesapTuru*> children() const     { return lo_children; }

    void insertChild(int row, HesapTuru *item)
    { item->o_parent = this; lo_children.insert(row, item); }
    void addChild(HesapTuru *item)
    { item->o_parent = this; lo_children << item; }
    void swapChildren(int oldRow, int newRow)
    //  qt5      { m_children.swap(oldRow, newRow); }
    { lo_children.swapItemsAt (oldRow, newRow); }
    HesapTuru* takeChild(int row);

private:
    /// XML:001
    /// define
    /// variables for XML file
    ///


    QString mstr_hs_Tur;
    QColor  mcol_hs_Color;
    QIcon   mico_hs_Icon;
    QString mstr_hs_01;
    QString mstr_hs_02;
    quint64 mint_hs_T_Kod;


    HesapTuru *o_parent;
    QList<HesapTuru*> lo_children;
};

#endif // HESAPTURU_H
