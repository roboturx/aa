
#include "frmAna.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmAna w;
    w.setWindowTitle("Ürün Takip");
    w.show();
    w.hide();

    return a.exec();
}
