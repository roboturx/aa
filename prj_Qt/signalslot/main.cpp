#include "myclass.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QObject>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
//#include <
//#include <

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    QLineEdit *le = new QLineEdit;
    QLabel *lb = new QLabel("lblaaa");
    QLabel *lbcls = new QLabel;

    widget.setFocus ();
    MyClass *mc = new MyClass("myclasstext");
    lbcls->text ()= mc->text ();

    MyClass::connect(le, &QLineEdit::textEdited,
                     mc , &MyClass::setText );

    QObject::connect (mc, &MyClass::textChanged,
                     lb, &QLabel::setText);

    QTreeView *treeview    = new QTreeView;
    QTableView * tableview = new QTableView;
    QListView * listview   = new QListView;

    QSplitter  * splitter = new QSplitter(Qt::Horizontal, &widget );
    splitter->addWidget (treeview);
    splitter->addWidget (tableview);
    splitter->addWidget (listview);
    //splitter->show ();


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (le);
    layout->addWidget (lb);
    layout->addWidget (lbcls);
    layout->addWidget (splitter);
    widget.setLayout (layout);


    QStandardItemModel model(5,5);
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<5; j++)
        {
            QStandardItem *item = new QStandardItem (
                QString("R %1 - C %2").arg(i).arg(j));

            //if ()
            {
                for (int x=0; x<=3; x++)
                {
                    item->appendRow (
                        new QStandardItem(QString("R %1").arg(x))  );

                }
            }
            model.setItem (i,j,item);
        }
    }

    treeview->setModel (&model);
    tableview->setModel (&model);
    listview->setModel (&model);

    treeview->setSelectionModel (tableview->selectionModel ());
    tableview->setSelectionModel (treeview->selectionModel ());
    listview->setSelectionModel (treeview->selectionModel ());

    model.setHorizontalHeaderItem (0, new QStandardItem("aaaaaa"));
    model.setHorizontalHeaderItem (1, new QStandardItem("bbbbbb"));




    widget.show ();





    return a.exec();
}
