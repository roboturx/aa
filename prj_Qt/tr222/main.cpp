#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *w = new QMainWindow;
    w->show();
    return a.exec();
}
