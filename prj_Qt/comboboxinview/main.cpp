#include "mainwindow.h"
#include <QTableWidget>
#include "comboboxitemdelegate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
    QTableWidget tw;

    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(&tw);
    // ComboBox only in column 2
    tw.setItemDelegateForColumn(1, cbid);
    tw.setColumnCount(4);
    tw.setRowCount(10);
    tw.resize(600,400);
    tw.show();



   // w.show();
    return a.exec();
}
