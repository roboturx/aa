#ifndef GALLERY-CORE_GLOBAL_H
#define GALLERY-CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ALBUM_LIBRARY)
#  define ALBUM_EXPORT Q_DECL_EXPORT
#else
#  define ALBUM_EXPORT Q_DECL_IMPORT
#endif

#endif // GALLERY-CORE_GLOBAL_H
