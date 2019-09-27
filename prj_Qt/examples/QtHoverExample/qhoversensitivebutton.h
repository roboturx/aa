#ifndef QHOVERSENSITIVEBUTTON_H
#define QHOVERSENSITIVEBUTTON_H

#include <QtWidgets>

class QHoverSensitiveButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QHoverSensitiveButton(QWidget *parent = 0);

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:

public slots:
};

#endif // QHOVERSENSITIVEBUTTON_H
