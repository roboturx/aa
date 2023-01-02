#include "myclass.h"

#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    QLineEdit *le = new QLineEdit;
    QLabel *lb = new QLabel("lblaaa");
    QLabel *lbcls = new QLabel;


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (le);
    layout->addWidget (lb);
    layout->addWidget (lbcls);
    widget.setLayout (layout);

    widget.setFocus ();
    MyClass *mc = new MyClass("myclasstext");
    lbcls->text ()= mc->text ();

    MyClass::connect(le, &QLineEdit::textEdited,
                     mc , &MyClass::setText );

    QObject::connect (mc, &MyClass::textChanged,
                     lb, &QLabel::setText);
    widget.show ();

    return a.exec();
}
