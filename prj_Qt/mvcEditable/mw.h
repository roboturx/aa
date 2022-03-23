#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QTableView>
#include <QTreeView>


QT_BEGIN_NAMESPACE
class Mw; //forward decl
QT_END_NAMESPACE


class Mw : public QMainWindow
{
    Q_OBJECT
private:
    //QTableView * tableView;
    QTreeView *treeView;

public:
    Mw(QWidget *parent =nullptr);

public slots:
    void ShowWindowTitle(const QString &title);



};

#endif // MW_H
