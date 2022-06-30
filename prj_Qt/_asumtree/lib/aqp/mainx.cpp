

#include "aqp.hpp"
#include <QApplication>
#include <QStringList>
#include <QTextStream>


int mainx(int argc, char *argv[])
{
    QApplication app(argc, argv, false);
    QTextStream out(stdout);
    out << "Application's executable directory is "
        << AQP::applicationPathOf() << "\n";
    out << "Application's images directory is "
        << AQP::applicationPathOf("images") << "\n";
    out << AQP::filenameFilter("HTML", QStringList() << "text/html")
        << "\n";
    out << AQP::filenameFilter("Audio", QStringList() << "audio/mpeg"
        << "audio/ogg") << "\n";
    out << AQP::filenameFilter("Video", QStringList() << "video/3gpp"
        << "video/dv" << "video/mpeg") << "\n";
    return 0;
}

