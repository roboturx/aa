
#include "mw.h"
#include <QApplication>

#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mw mw;
    mw.show();


    return a.exec();
}
