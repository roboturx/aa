#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>
#include <QString>
#include "gallery-core_global.h"

class  GALLERYCORESHARED_EXPORT Picture
{
public:
    Picture( const QString &filePath );
    Picture(const QUrl &fileUr);

    int id;
    void setId(int id);

    int albumId const;
    void setAlbumId(int albumId);

private:
    int mId;
    int mAlbumId;
    QUrl mFileUrl;

};

#endif // PICTURE_H
