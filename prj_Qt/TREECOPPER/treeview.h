
#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QSqlDatabase>
#include <QWidget>
#include <qcontainerfwd.h>
//#include <qstringfwd.h>


class TreeView : public QWidget
{
    Q_OBJECT

public:
    TreeView();

private:
    bool createConnection();
    void qbind(QSqlQuery q, int key, QString kname, int parent, QString ekle);
    QSqlDatabase m_db;

    struct struCat {
        int catKey;
        QString catName;
        int catParent;
        QString catEkle;
    };

    QList<struCat> getData();
    static bool sortMe(const TreeView::struCat &s1, const TreeView::struCat &s2);
};

#endif
