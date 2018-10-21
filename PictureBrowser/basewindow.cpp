#include "stdafx.h"
#include "basewindow.h"
#include "qsvgrenderer.h"

#define PADDING dpiScaled(3)

BaseWindow::BaseWindow(QWidget *parent)
	: QWidget(parent)
	, m_bLeftPressDown(false)
	, m_direction(NONE)
{
	this->setObjectName("basewindow");
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);
	this->setAttribute(Qt::WA_TranslucentBackground);

	m_pTitleBar = new TitleBar(this);
	this->installEventFilter(m_pTitleBar);
	m_pTitleBar->setMouseTracking(true);

	resize(dpiScaled(800), dpiScaled(500));
	this->setWindowTitle(QStringLiteral("12345ø¥Õº"));
	QSvgRenderer renderer(QString("icons/mainicon.svg"));
	QPixmap img(dpiScaled(20), dpiScaled(20));
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	this->setWindowIcon(QIcon(img));

	m_pPictureViewWidget = new PictureViewWidget(this);
	m_pPictureViewWidget->setObjectName("pictureviewwidget");
	m_pPictureViewWidget->setMouseTracking(true);

	m_pLayout = new QVBoxLayout(this);
	m_pLayout->addWidget(m_pTitleBar);
	m_pLayout->addWidget(m_pPictureViewWidget);
	m_pLayout->setSpacing(0);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_pLayout);

	m_pPictureViewWidget->setTitleBar(m_pTitleBar);
}

BaseWindow::~BaseWindow()
{
}

TitleBar* BaseWindow::getTitleBar()
{
	return m_pTitleBar;
}

PictureViewWidget* BaseWindow::getPictureViewWidget()
{
	return m_pPictureViewWidget;
}

void BaseWindow::initWindow()
{
	m_pTitleBar->initTitlebar();
	m_pPictureViewWidget->initPictureView();
}

void BaseWindow::paintEvent(QPaintEvent* event)
{
	if (!this->window()->isMaximized())
	{
		m_pLayout->setContentsMargins(10, 0, 10, 10);
		int size = 10;                //“ı”∞øÌ∂»
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QColor color(0, 0, 0, 0);
		for (int i = 0; i <= size; i++)
		{
			color.setAlpha(i * 3);
			painter.setPen(color);
			painter.setBrush(Qt::transparent);
			painter.drawRoundedRect(i, 0, this->width() - i * 2, this->height() - i , 10, 10);
		}
	}
	else
	{
		m_pLayout->setContentsMargins(0, 0, 0, 0);
	}
	
	return QWidget::paintEvent(event);
}

void BaseWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		this->close();
		break;
	default:
		QWidget::keyPressEvent(event);
	}
}

void BaseWindow::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_bLeftPressDown = true;
		if (m_direction != NONE)
			this->mouseGrabber();
		else
			m_pressedPoint = QCursor::pos();
	}

	QWidget::mousePressEvent(e);
}

void BaseWindow::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_bLeftPressDown = false;
		releaseMouse();
		setCursor(QCursor(Qt::ArrowCursor));
	}

	QWidget::mouseReleaseEvent(e);
}

void BaseWindow::mouseMoveEvent(QMouseEvent *e)
{
	QPoint gpt = e->globalPos();
	QPoint tl = mapToGlobal(rect().topLeft());
	QPoint rb = mapToGlobal(rect().bottomRight());
	if (!m_bLeftPressDown)
		calRegion(gpt);
	else
	{
		if (m_direction != NONE)
		{
			QRect rMove(tl, rb);
			switch (m_direction)
			{
			case LEFT:
				(rb.x() - gpt.x() <= this->minimumWidth()) ? rMove.setX(tl.x()) : rMove.setX(gpt.x());
				break;
			case RIGHT:
				rMove.setWidth(gpt.x() - tl.x());
				break;
			case UP:
				(rb.y() - gpt.y() <= this->minimumHeight()) ? rMove.setY(tl.y()) : rMove.setY(gpt.y());
				break;
			case DOWN:
				rMove.setHeight(gpt.y() - tl.y());
				break;
			case LEFTTOP:
				(rb.x() - gpt.x() <= this->minimumWidth()) ? rMove.setX(tl.x()) : rMove.setX(gpt.x());
				(rb.y() - gpt.y() <= this->minimumHeight()) ? rMove.setY(tl.y()) : rMove.setY(gpt.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gpt.x() - tl.x());
				(rb.y() - gpt.y() <= this->minimumHeight()) ? rMove.setY(tl.y()) : rMove.setY(gpt.y());
				break;
			case LEFTBOTTOM:
				rMove.setHeight(gpt.y() - tl.y());
				(rb.x() - gpt.x() <= this->minimumWidth()) ? rMove.setX(tl.x()) : rMove.setX(gpt.x());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gpt.x() - tl.x());
				rMove.setHeight(gpt.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else
		{
			QPoint offset = QCursor::pos() - m_pressedPoint;
			this->move(this->pos() + offset);
			m_pressedPoint = QCursor::pos();
		}
	}
}

void BaseWindow::calRegion(const QPoint& pt)
{
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());
	int x = pt.x();
	int y = pt.y();

	if ((tl.x() + PADDING) >= x && tl.x() <= x && (tl.y() + PADDING) >= y && tl.y() <= y)// ◊Û…œΩ«
	{
		m_direction = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x >= (rb.x() - PADDING) && x <= rb.x() && y >= (rb.y() - PADDING) && y <= rb.y())// ”“œ¬Ω«
	{
		m_direction = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= (tl.x() + PADDING) && x >= tl.x() && y >= (rb.y() - PADDING) && y <= rb.y())//◊Ûœ¬Ω«
	{
		m_direction = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() && x >= (rb.x() - PADDING) && y >= tl.y() && y <= (tl.y() + PADDING))// ”“…œΩ«
	{
		m_direction = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x())// ◊Û±ﬂ
	{
		m_direction = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING)// ”“±ﬂ
	{
		m_direction = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING)// …œ±ﬂ
	{
		m_direction = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING)// œ¬±ﬂ
	{
		m_direction = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else// ƒ¨»œ
	{
		m_direction = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

bool BaseWindow::event(QEvent*e)
{
	return QWidget::event(e);
}