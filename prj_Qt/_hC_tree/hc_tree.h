#ifndef hC_Tree_H
#define hC_Tree_H

#include <QLabel>

#include <QObject>
#include <QWidget>
#include <QTreeView>
#include <QFile>
#include <QSqlQuery>
#include <QPushButton>
#include <QSqlQuery>
#include <QApplication>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>

#include "dbase.h"
#include "treesqlitem.h"
#include "treesqlmodel.h"


class hC_Tree : public QWidget
{
    Q_OBJECT
public:
    explicit hC_Tree(QWidget *parent = nullptr);

    TreeSqlModel *modelSQL ;
    QTreeView *hC_TreeView;
    QString * m_accName;
    QString* m_accCode;
    int m_prntCode;
private:
    QPushButton *butt_Exit ;
    QPushButton *butt_Add ;
    QPushButton *butt_Act ;
    QPushButton *butt_insrow ;
    QPushButton *butt_inscol ;
    QPushButton *butt_remrow ;
    QPushButton *butt_remcol ;
    QLabel * lab_status;
    QLabel * lab_status2;
    QLabel * lab_status3;


    void view();

public slots:
    void updateActions();
private slots:
    void insertChild();
    bool insertColumn();
    void insertRow();
    bool removeColumn();
    void removeRow();

signals:

};

#endif // hC_Tree_H
