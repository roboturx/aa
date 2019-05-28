
#include "dlgt_mkstok.h"

#include <QtWidgets>

MakinaDelegate::MakinaDelegate(QObject *parent)
    : QSqlRelationalDelegate(parent), star(QPixmap(":images/star.png"))
{
qDebug()<<"mkndelegate";
}


void MakinaDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const
{
    qDebug()<<"index column " <<index.column() ;
    if (index.column() != 11)
    {
	    QStyleOptionViewItem opt = option;
	    opt.rect.adjust(0, 0, -1, -1); // since we draw the grid ourselves
	    QSqlRelationalDelegate::paint(painter, opt, index);
    }
    else
    {
	    const QAbstractItemModel *model = index.model();
	    QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled) ?
			(option.state & QStyle::State_Active) ? QPalette::Normal : QPalette::Inactive : QPalette::Disabled;

	    if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.color(cg, QPalette::Highlight));

	    int rating = model->data(index, Qt::DisplayRole).toInt();
	    int width = star.width();
	    int height = star.height();
	    int x = option.rect.x();
	    int y = option.rect.y() + (option.rect.height() / 2) - (height / 2);
        for (int i = 0; i < rating; ++i)
        {
		    painter->drawPixmap(x, y, star);
		    x += width;
		}
	    drawFocus(painter, option, option.rect.adjusted(0, 0, -1, -1)); // since we draw the grid ourselves
	}

    QPen pen = painter->pen();
    painter->setPen(option.palette.color(QPalette::Mid));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
    painter->setPen(pen);
}

QSize MakinaDelegate::sizeHint(const QStyleOptionViewItem &option,
			       const QModelIndex &index) const
{
    if (index.column() == 11)
	return QSize(5 * star.width(), star.height()) + QSize(1, 1);

    return QSqlRelationalDelegate::sizeHint(option, index) + QSize(1, 1); // since we draw the grid ourselves
}

bool MakinaDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
				 const QStyleOptionViewItem &option,
				 const QModelIndex &index)
{
    if (index.column() == 11)
	{
	    if (event->type() == QEvent::MouseButtonPress) {
		    auto *mouseEvent = dynamic_cast<QMouseEvent*>(event);
		    int stars = qBound(0, int(0.7 + qreal(mouseEvent->pos().x()
							  - option.rect.x()) / star.width()), 5);
		    model->setData(index, QVariant(stars));
		    return false; //so that the selection can change
		}

	    return true;
	}
    
	return QSqlRelationalDelegate::editorEvent(event, model, option, index);

}


QWidget *MakinaDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
				      const QModelIndex &index) const
{
    if (index.column() == 7)   // field yil spinnbox
	{
	    // for editing the year, return a spinbox with a range from -1000 to 2100.
	    auto *sb = new QSpinBox(parent);
	    sb->setFrame(false);
        sb->setMaximum(2025);
	    sb->setMinimum(1950);

	    return sb;
	}

    
	return QSqlRelationalDelegate::createEditor(parent, option, index);


}



//////////////
