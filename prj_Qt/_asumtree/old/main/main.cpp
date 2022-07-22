#include "globals.h"
#include "mainwindow.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName(app.translate("main", "BalcSoft"));
    app.setWindowIcon(QIcon(":/icon.png"));
    app.setOrganizationName("BalcCo");
    app.setOrganizationDomain("balcco.tr");
    QTextStream out(stdout);

       out << "Application's executable directory is "
           << AQP::applicationPathOf() << "\n";

    MainWindow window;
    window.show();

    qDebug() << "MainWindow Activated";

    return app.exec();
}

