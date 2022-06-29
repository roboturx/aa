#include "mainwindow.h"

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    app.setQuitOnLastWindowClosed(true);
    MainWindow* window = new MainWindow(NULL);
    window->show();
    return app.exec();
}
