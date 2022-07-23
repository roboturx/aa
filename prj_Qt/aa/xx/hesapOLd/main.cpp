#include "globals.h"
#include "hc_hsp.h"


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

    hC_hsp window;
    window.show();

    qDebug() << "hC_hsp Activated";

    return app.exec();
}

