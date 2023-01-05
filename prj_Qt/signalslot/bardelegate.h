#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QAbstractItemDelegate>
#include <QObject>

class BarDelegate : public QAbstractItemDelegate
{
public:
    explicit BarDelegate(QObject *parent = nullptr);
};

#endif // BARDELEGATE_H
