#include "dialog.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QLockFile lockFile(QDir::temp().absoluteFilePath("<uniq id>.lock"));
    QLockFile lockFile(QDir::temp().absoluteFilePath("<uniq id>.lock"));
    qDebug () << QDir::temp().absoluteFilePath("<uniq id>.lock");

    /* Trying to close the Lock File, if the attempt is unsuccessful for 100 milliseconds,
     * then there is a Lock File already created by another process.
     / Therefore, we throw a warning and close the program
     * */
    if(!lockFile.tryLock(100)){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The application is already running.\n"
                       "Allowed to run only one instance of the application.");
        msgBox.exec();
        return 1;
    }


    Dialog w;
    w.show();
    return a.exec();
}
