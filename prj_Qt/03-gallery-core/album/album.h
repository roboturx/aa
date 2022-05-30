#ifndef ALBUM_H
#define ALBUM_H

#include "gallery-core_global.h"
#include <QString>


class GALLERYCORESHARED_EXPORT Album
{
public:
    explicit Album( const QString& name = "");
    int id();
    QString name;
    void setName(const QString& name);

private:
    int mId;
    QString mName;

};

#endif // ALBUM_H
