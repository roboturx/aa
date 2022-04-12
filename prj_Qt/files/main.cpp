#include "files.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Files w;
    w.show();
    return a.exec();
}
