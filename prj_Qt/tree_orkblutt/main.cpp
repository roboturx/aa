#include "hc_tree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hC_Tree w;
    w.show();
    return a.exec();
}
