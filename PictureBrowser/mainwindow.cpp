#include "stdafx.h"
#include "mainwindow.h"
#include "qsvgrenderer.h"

BaseWindow::BaseWindow(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	m_pTitleBar = new TitleBar(this);
	installEventFilter(m_pTitleBar);

	resize(600, 400);
	setWindowTitle(QStringLiteral("12345¿´Í¼"));
	QSvgRenderer renderer(QString("icons/mainicon.svg"));
	QPixmap img(20, 20);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	setWindowIcon(QIcon(img));

	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->addWidget(m_pTitleBar);
	pLayout->addStretch();
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pLayout);
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::paintEvent(QPaintEvent* event)
{
	////ÉèÖÃ±³¾°É«;
	//QPainter painter(this);
	//QPainterPath pathBack;
	//pathBack.setFillRule(Qt::WindingFill);
	//pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
	//painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	//painter.fillPath(pathBack, QBrush(QColor(238, 223, 204)));
	return QWidget::paintEvent(event);
}