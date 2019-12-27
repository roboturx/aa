#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QtWidgets>

class QExSafeApplication : public QApplication
{
public:
    QExSafeApplication(int& argc, char ** argv) :
        QApplication(argc, argv) { }
    virtual ~QExSafeApplication() { }

    virtual bool notify(QObject *receiver, QEvent *event)
    {
        try
        {
            return QApplication::notify(receiver, event);
        }
        catch(std::exception& e)
        {
            QString msg;
            msg.append("Exception thrown : ");
            msg.append(e.what());
            QMessageBox::critical(nullptr, "Error", msg);
            QMessageBox::critical(nullptr, "Object", receiver->objectName());
        }
        return false;
    }

};


#endif // MAIN_H
