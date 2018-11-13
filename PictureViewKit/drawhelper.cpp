#include "stdafx.h"
#include "drawhelper.h"
#include "qsvgrenderer.h"

PictureViewColorMap* PictureViewColorMap::instance()
{
	static PictureViewColorMap colorMap;
	return &colorMap;
}

PictureViewColorMap::PictureViewColorMap()
{
	m_colorMap.insert("TitleBar_BackGround", QColor(70, 124, 212));
	m_colorMap.insert("ToolButton", QColor(70, 124, 212));
	m_colorMap.insert("ToolButton_Hover", QColor(94, 172, 255));
	m_colorMap.insert("ToolButton_Down", QColor(63, 111, 190));
	m_colorMap.insert("ToolButton_Font", Qt::white);
	m_colorMap.insert("MenuItem", QColor(250, 250, 250));
	m_colorMap.insert("MenuItem_Hover", QColor(225, 225, 225));
	m_colorMap.insert("MenuItem_Down", QColor(232, 232, 232));
	m_colorMap.insert("MenuItem_ShortCut", QColor(121, 121, 121));
	m_colorMap.insert("MenuItem_Text", QColor(61, 61, 61));
}

PictureViewColorMap::~PictureViewColorMap()
{

}

QColor PictureViewColorMap::findColor(const QString& str)
{
	QMap<QString, QColor>::iterator iter;
	iter = m_colorMap.find(str);
	if (iter != m_colorMap.end())
		return m_colorMap[str];
	else
		return QColor();
}

QPainterPath DrawHelper::getBoundPath(const QRect& rect)
{
	int nLeft = rect.left();
	int nTop = rect.top();
	int nRight = rect.right() + 1;
	int nBottom = rect.bottom() + 1;

	QPainterPath path;
	path.moveTo(nLeft, nTop + 1);
	path.lineTo(nLeft + 1, nTop + 1);
	path.lineTo(nLeft + 1, nTop);
	path.lineTo(nRight - 1, nTop);
	path.lineTo(nRight - 1, nTop + 1);
	path.lineTo(nRight, nTop + 1);
	path.lineTo(nRight, nBottom - 1);
	path.lineTo(nRight - 1, nBottom - 1);
	path.lineTo(nRight - 1, nBottom);
	path.lineTo(nLeft + 1, nBottom);
	path.lineTo(nLeft + 1, nBottom - 1);
	path.lineTo(nLeft, nBottom - 1);
	path.closeSubpath();
	return path;
}

QColor DrawHelper::getColorFromTheme(const QString& str)
{
	PictureViewColorMap *colorMap = PictureViewColorMap::instance();
	return colorMap->findColor(str);
}

PICTUREVIEWKIT_EXPORT QIcon DrawHelper::LoadIconFromSvg(const QString& fileName, const QSize& size)
{
	QSvgRenderer renderer(fileName);
	QPixmap img(size);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	return QIcon(img);
}

PICTUREVIEWKIT_EXPORT QPixmap DrawHelper::LoadPixmapFromSvg(const QString& fileName, const QSize& size)
{
	QSvgRenderer renderer(fileName);
	QPixmap img(size);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	return img;
}
