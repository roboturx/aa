#include "application.h"

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv)
{
    m_dontShowMainWindow = true;
    // Set organisation and application names
    setApplicationName("Kasa");
    setApplicationVersion("06.21");
    setOrganizationName("DBL");
    setApplicationDisplayName("LaCasaDöPapel");
    setWindowIcon(QIcon(":/images/img/main.png"));


    // Show login dialog
    login = new LoginDialog();
    login->show();
    login->setAttribute(Qt::WA_DeleteOnClose);
    if(login != Q_NULLPTR)
        m_dontShowMainWindow = false;

    //connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
    connect(this,&Application::lastWindowClosed, this, &Application::quit);
}

Application::~Application()
{
    delete login;
}
