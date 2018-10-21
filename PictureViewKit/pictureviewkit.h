#pragma once
#include "pictureviewkit_global.h"
#ifdef DEBUG
#define NDEBUG //#½ûÓÃassertµ÷ÓÃ
#endif
#include <assert.h>

typedef float REAL;

PICTUREVIEWKIT_EXPORT void getDpi(IN REAL* pDpix, IN REAL* pDpiy);
PICTUREVIEWKIT_EXPORT qreal dpiScaled(const qreal value);