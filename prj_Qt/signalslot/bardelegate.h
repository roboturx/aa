#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QAbstractItemDelegate>


class BarDelegate : public QAbstractItemDelegate
{
public:
    explicit BarDelegate(QObject *parent = nullptr);
    void paint (QPainter * painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

#endif // BARDELEGATE_H
