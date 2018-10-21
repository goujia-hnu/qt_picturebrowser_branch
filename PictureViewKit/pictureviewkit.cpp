#include "stdafx.h"
#include "pictureviewkit.h"

void getDpi(IN REAL* pDpix, IN REAL* pDpiy)
{
	QDesktopWidget *pDesk = QApplication::desktop();
	assert(NULL != pDesk);
	if (pDpix)
		*pDpix = pDesk->logicalDpiX();
	if (pDpiy)
		*pDpiy = pDesk->logicalDpiY();
}


qreal dpiScaled(const qreal value)
{
	static float scaleX = 0.0;
	static float scaleY = 0.0;
	if (qFuzzyIsNull(scaleX))
	{
		getDpi(&scaleX, &scaleY);
		scaleX /= 96.0;
		scaleY /= 96.0;
	}
	return scaleX * value;
}