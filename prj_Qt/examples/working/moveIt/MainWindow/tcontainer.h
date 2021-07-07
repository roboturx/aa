
#ifndef TCONTAINER_H
#define TCONTAINER_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QtGui>
#include <QVBoxLayout>
#include <QMenu>

enum modes{
    NONE = 0,
    MOVE = 1,
    RESIZETL = 2,
    RESIZET = 3,
    RESIZETR = 4,
    RESIZER = 5,
    RESIZEBR = 6,
    RESIZEB = 7,
    RESIZEBL = 8,
    RESIZEL = 9
};

class TContainer : public QWidget {
    Q_OBJECT

public:
    TContainer(QWidget *parent, QPoint p, QWidget *cWidget = 0);
    ~TContainer();
    QWidget *childWidget;
    QMenu *menu;
    void setChildWidget(QWidget *cWidget);

protected:
    int mode;
    QPoint position;
    QVBoxLayout* vLayout;
    void setCursorShape(const QPoint &e_pos);
    bool eventFilter(QObject *obj, QEvent *evt);
    void keyPressEvent(QKeyEvent*);
    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    bool m_infocus;
    bool m_showMenu;
    bool m_isEditing;
    void popupShow(const QPoint &pt);
    QWidget *clone();

signals:
    void inFocus(bool mode);
    void outFocus(bool mode);
    void newGeometry(QRect rect);
};

#endif // TCONTAINER_H
