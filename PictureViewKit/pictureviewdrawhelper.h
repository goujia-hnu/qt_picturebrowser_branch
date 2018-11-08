#pragma once
#include "pictureviewkit_global.h"
#include "qcolor.h"
#include "qstring.h"
#include "qpainterpath.h"

class PICTUREVIEWKIT_EXPORT PictureViewColorMap
{
public:
	static PictureViewColorMap* instance();
	QColor findColor(const QString& str);

private:
	PictureViewColorMap();
	~PictureViewColorMap();
	QMap<QString, QColor> m_colorMap;
};

namespace PictureViewDrawHelper
{
	PICTUREVIEWKIT_EXPORT QPainterPath getBoundPath(const QRect& rect);
	PICTUREVIEWKIT_EXPORT QColor getColorFromTheme(const QString& str);
	PICTUREVIEWKIT_EXPORT QIcon LoadIconFromSvg(const QString& fileName, const QSize& size);
	PICTUREVIEWKIT_EXPORT QPixmap LoadPixmapFromSvg(const QString& fileName, const QSize& size);
}
