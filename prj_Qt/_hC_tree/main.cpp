#include <QApplication>

#include "dbase.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(editabletreemodel);
    QApplication app(argc, argv);
    dBase db;
        db.createConnection();
        db.adding();
    MainWindow window;
    window.show();
    return app.exec();
}
