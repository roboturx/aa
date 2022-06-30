#include "globals.h"
#include "mainwindow.hpp"

QString GLB_yetki = "İlk" ;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(app.translate("main", "Timelog"));
    app.setWindowIcon(QIcon(":/icon.png"));
    app.setOrganizationName("QBalc Co.");
    app.setOrganizationDomain("qbalc.tr");
    QTextStream out(stdout);

       out << "Application's executable directory is "
           << AQP::applicationPathOf() << "\n";




#ifdef MAIN
    MainWindow window;
    window.show();
    window.login();
    qDebug() << "MainWindow Activated";
#else
    qDebug() << "MainWindow Not Activated";
#endif
    return app.exec();
}

