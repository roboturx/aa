#ifndef DLGT_MKSTOK_H
#define DLGT_MKSTOK_H


#include "main/globals.h"



class MakinaDelegate : public QSqlRelationalDelegate
{
public:
    MakinaDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
	       const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
		     const QStyleOptionViewItem &option,
		     const QModelIndex &index) override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
					const QModelIndex &index) const override;

private:
    QPixmap star;
};
#endif // DLGT_MKSTOK_H

