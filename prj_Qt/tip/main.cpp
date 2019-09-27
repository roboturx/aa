#include "anapencere.h"
#include "frmAna.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmAna w;
    w.setWindowTitle("Okul Takip");
    w.show();
    w.hide();

    return a.exec();
}
