#include "application.h"
#include "treeviewhelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType <ExpandedNode>();
    qRegisterMetaType <ExpandedNodeList>();
    //MainWindow w;
    //w.show();
    return a.exec();
}
