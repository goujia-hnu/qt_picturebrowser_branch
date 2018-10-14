#pragma once
#include "stdafx.h"
#include "pictureviewkit_global.h"


class PICTUREVIEWKIT_EXPORT PictureViewColorMap
{
public:
	static PictureViewColorMap& instance();
	PictureViewColorMap();
	~PictureViewColorMap();
	QColor findColor(const QString& str);

private:
	QMap<QString, QColor> m_colorMap;
};

namespace PictureViewDrawHelper
{
	PICTUREVIEWKIT_EXPORT QPainterPath getBoundPath(const QRect& rect);
	PICTUREVIEWKIT_EXPORT QColor getColorFromTheme(const QString& str);
}
