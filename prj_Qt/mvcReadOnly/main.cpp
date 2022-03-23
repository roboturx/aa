#include "modelle.h"

#include <QApplication>
#include <QTableView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTableView tableView;
    Modelle myModel;

    tableView.setModel(&myModel);
    tableView.show();
    return a.exec();
}
