
#ifndef SORTINGBOX_H
#define SORTINGBOX_H

#include <QWidget>

#include "shapeitem.h"

QT_BEGIN_NAMESPACE
class QAction;
class QPoint;
class QToolButton;
QT_END_NAMESPACE

//! [0]
class SortingBox : public QWidget
{
    Q_OBJECT

public:
    SortingBox();

protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void smSLOT(QPoint pos);
    void createNewSquare();
  //  void createNewTriangle();
//! [0]

//! [1]
private:
    int updateButtonGeometry(QToolButton *button, int x, int y);
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos,
                         const QColor &color,
                         const QString &text,
                         const QPixmap &pixmap);
    int itemAt(const QPoint &pos);
    void moveItemTo(const QPoint &pos);
    QPoint initialItemPosition(const QPainterPath &path);
    QPoint randomItemPosition();
    QColor initialItemColor();
    QColor randomItemColor();
    QToolButton *createToolButton(const QString &toolTip,
                                  const QIcon &icon,
                                  const char *member,
                                  const QPixmap &pixmap,
                                  const QString &text="2323");

    QList<ShapeItem> shapeItems;
//    QPainterPath circlePath;
    QPainterPath squarePath;
  //  QPainterPath trianglePath;

    QPoint previousPosition;
    ShapeItem *itemInMotion;

   // QToolButton *newCircleButton;
    QToolButton *newSquareButton;
    //QToolButton *newTriangleButton;
};
//! [2]

#endif
