#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PICTUREVIEWKIT_LIB)
#  define PICTUREVIEWKIT_EXPORT Q_DECL_EXPORT
# else
#  define PICTUREVIEWKIT_EXPORT Q_DECL_IMPORT
# endif
#else
# define PICTUREVIEWKIT_EXPORT
#endif
