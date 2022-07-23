
#ifndef SORTINGBOX_H
#define SORTINGBOX_H

#include "libs/globals.h"
#include "ie/ie.h"

#include "grph/shapeitem.h"

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
    explicit SortingBox( QWidget *parent=nullptr );
  //  ~SortingBox() ;

    QSqlRecord getCurrentRecord() const;
    void setCurrentRecord(const QSqlRecord &value);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    static int count;
    static int col;
    static int row;



protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void listele ();
    void smSLOT(QPoint pos);
    void createNewSquare();
    void createIsEmri();


    //  void createNewTriangle();
//! [0]

//! [1]
private:

    hC_IE* isEmri;

    QSqlRecord currentRecord;
    QPixmap pixmap;


    int updateButtonGeometry(QToolButton *button, int x, int y);
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos,
                         const QColor &color,
                         const QSqlRecord &record,
                         const QPixmap &pixmap);
    int itemAt(const QPoint &pos);
    void moveItemTo(const QPoint &pos);
    QPoint initialItemPosition(const QPainterPath &path);
    QPoint randomItemPosition();
    QColor initialItemColor();
    QColor randomItemColor();
    QToolButton *createToolButton(const QString &toolTip,
                                  const QIcon &icon, const char *member,
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
       //void menu();
};
//! [2]

#endif
