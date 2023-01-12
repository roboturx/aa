#ifndef CL_DLG_CBOX_H
#define CL_DLG_CBOX_H

#include <QStyledItemDelegate>
//#include <QSqlQuery>

//class cls_Hesaplar;

class cL_dlG_CBox : public QStyledItemDelegate
{
    Q_OBJECT
public:

    cL_dlG_CBox(QObject *parent = nullptr);
    ~cL_dlG_CBox();

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;


};




class cls_Hesaplar
{
public:
    cls_Hesaplar();
    ~cls_Hesaplar();

    void setHesaplar(QString *hAd,  qint64 hKod);
    QMap<QString*, qint64> getHesaplar();
private:
    QMap<QString*, qint64> map_hesapAdKod;
};

#endif // CL_DLG_CBOX_H
