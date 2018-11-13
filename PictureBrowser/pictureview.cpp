#include "stdafx.h"
#include "pictureview.h"
#include "qsvgrenderer.h"
#include "basewindow.h"

#define LOGO_SIZE_WIDTH dpiScaled(200)
#define LOGO_SIZE_HEIGHT dpiScaled(200)

PictureView::PictureView(QWidget* parent)
	:QWidget(parent),
	m_scaleRatio(1.0),
	m_isSvg(false),
	m_action(None),
	m_bOpenedFile(false),
	m_bPicPressed(false)
{
	m_pLogoLabel = new QLabel(this);
	m_pLogoLabel->setFixedSize(LOGO_SIZE_WIDTH, LOGO_SIZE_HEIGHT);
	m_pLogoLabel->setPixmap(DrawHelper::LoadPixmapFromSvg("icons/mainicon.svg", QSize(LOGO_SIZE_WIDTH, LOGO_SIZE_HEIGHT)));

	m_pOpenFileButton = new PictureViewToolButton(this);
	m_pOpenFileButton->setFixedSize(dpiScaled(170), dpiScaled(45));
	m_pOpenFileButton->setText(QStringLiteral("打开图片"));
	m_pOpenFileButton->setFont(QFont("Microsoft YaHei", dpiScaled(15)));
	m_pOpenFileButton->setFlat(true);
	m_pOpenFileButton->setStyleSheet("color:rgb(255, 255, 255)");
	connect(m_pOpenFileButton, SIGNAL(clicked()), this, SLOT(onOpenFile()));

	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->addStretch();
	QHBoxLayout* layout = new QHBoxLayout(this);
	{
		layout->addStretch();
		layout->addSpacing(dpiScaled(10));
		layout->addWidget(m_pLogoLabel);
		layout->addStretch();
	}
	m_pVLayout->addLayout(layout);
	QHBoxLayout* layout2 = new QHBoxLayout(this);
	{
		layout2->addStretch();
		layout2->addWidget(m_pOpenFileButton);
		layout2->addStretch();
	}
	m_pVLayout->addLayout(layout2);
	m_pVLayout->addStretch();
	m_pVLayout->setSpacing(0);

	m_pHLayout = new QHBoxLayout(this);
	m_pHLayout->addStretch();
	m_pHLayout->addLayout(m_pVLayout);
	m_pHLayout->addStretch();

	setLayout(m_pHLayout);
}

PictureView::~PictureView()
{

}

void PictureView::setShowLogo(BOOL visible)
{
	m_pLogoLabel->setVisible(visible);
	m_pOpenFileButton->setVisible(visible);
	m_bOpenedFile = !visible;
}

void PictureView::setTitleBar(TitleBar* titlebar)
{
	m_pTitleBar = titlebar;
}

void PictureView::initPictureView()
{
	//https://www.cnblogs.com/lifexy/p/9057046.html
}

QRect PictureView::calculateShowRect()
{
	float w = rect().width();
	float h = rect().height();
	float xx = w / m_pixPicture.width();
	float yy = h / m_pixPicture.height();

	float ratio = 1.0;
	if (xx < 1.0 || yy < 1.0)
		ratio = xx > yy ? yy : xx;

	m_scaleRatio = ratio;
	int x = rect().width() - m_pixPicture.width() * ratio;
	int y = rect().height() - m_pixPicture.height() * ratio;

	return QRect(x / 2, y / 2, m_pixPicture.width() * ratio, m_pixPicture.height() * ratio);
}

QString PictureView::fileSize2Str(double fileSize)
{
	int unit = 0;
	while (fileSize > 1024)
	{
		fileSize /= 1024;
		unit++;
	}

	QString unitStr = "B";
	if (unit == 1)
		unitStr = "KB";
	else if (unit == 2)
		unitStr = "MB";
	else if (unit == 3)
		unitStr = "GB";

	return QString::number(fileSize, 'f', 2) + unitStr;
}


void PictureView::updateTitleText()
{
	QFileInfo fileInfo(m_filePath);
	QSize pixSize = m_pixPicture.size();
	//12345看图 - filename - xxx像素,xxMB - 70%
	QString showName = " - " + fileInfo.fileName() +
		" - " + QString("%1x%2").arg(pixSize.width()).arg(pixSize.height()) +
		QStringLiteral("像素") + "," + fileSize2Str(QFile(m_filePath).size()) +
		" - " + QString("%1%").arg((int)(m_scaleRatio * 100));

	m_pTitleBar->setPictureName(showName);
}

void PictureView::paintEvent(QPaintEvent *event)
{
	QPainter paint(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRect(QRect(0, 0, this->width(), this->height()));
	paint.setRenderHint(QPainter::SmoothPixmapTransform, true);
	paint.fillPath(pathBack, QBrush(Qt::white));
	QPoint temp = m_paintRect.topLeft();
	if (m_action == Move)
	{
		int x = m_xyOffset.x() + temp.x();
		int y = m_xyOffset.y() + temp.y();
		temp.setX(x);
		temp.setY(y);
		m_paintRect = QRect(x,y, m_paintRect.width(), m_paintRect.height());
		m_action = None;
	}

	if (!m_filePath.isEmpty())
	{
		paint.drawPixmap(m_paintRect, m_pixPicture);
	}
}

void PictureView::resizeEvent(QResizeEvent* event)
{
	if (m_bOpenedFile)
	{
		m_paintRect = calculateShowRect();
		updateTitleText();
	}
	QWidget::resizeEvent(event);
}


void PictureView::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}


void PictureView::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
}


void PictureView::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}

void PictureView::onOpenFile()
{
	bool result = selectFile();
	if (!result)
	{
		qDebug() << "OpenFile Failed!!";
	}
}

void PictureView::onCloseFile()
{
	if (m_bOpenedFile)
	{
		setShowLogo(true);
		m_filePath.clear();
		//m_pixmap = QPixmap();
		m_pTitleBar->setPictureName("");
		this->update();
	}
}

void PictureView::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)//放大
	{

	}
	else//缩小
	{

	}

	QWidget::wheelEvent(event);
}

bool PictureView::event(QEvent* e)
{
	//QMouseEvent *mouse = dynamic_cast<QMouseEvent*>(e);
	////if (mouse)
	////	qDebug() << "x:" << mouse->pos().x() << " y:" << mouse->pos().y();
	////qDebug() << "rect() :" << rect().topLeft().x() << " " << rect().topLeft().y() << " " << rect().width() << " " << rect().height();
	//if (m_bOpenedFile)
	//{
	//	if (e->type() == QEvent::MouseButtonPress)
	//	{
	//		if (mouse->button() == Qt::LeftButton && m_paintRect.contains(mouse->pos()))
	//		{
	//			m_bPicPressed = true;
	//			setCursor(Qt::ClosedHandCursor);
	//			m_pressedPoint = mouse->pos();
	//			return true;
	//		}

	//	}
	//	else if (e->type() == QEvent::MouseButtonRelease)
	//	{
	//		if (mouse->button() == Qt::LeftButton && m_bPicPressed)
	//		{
	//			setCursor(Qt::OpenHandCursor);
	//			m_bPicPressed = false;
	//			return true;
	//		}

	//	}
	//	else if (e->type() == QEvent::MouseMove)
	//	{
	//		if (m_paintRect.contains(mouse->pos()) && m_bPicPressed == false)
	//			setCursor(Qt::OpenHandCursor);
	//		else if (m_paintRect.contains(mouse->pos()) == false)
	//			setCursor(Qt::ArrowCursor);

	//		if (m_paintRect.contains(mouse->pos()) && m_bPicPressed)
	//		{
	//			m_xyOffset.setX(mouse->x() - m_pressedPoint.x());
	//			m_xyOffset.setY(mouse->y() - m_pressedPoint.y());
	//			m_pressedPoint = mouse->pos();
	//			m_action = Move;
	//			update();
	//		}
	//		if (m_paintRect.contains(mouse->pos()))
	//			return true;
	//	}
	//}
	return QWidget::event(e);
}

bool PictureView::eventFilter(QObject* watched, QEvent* e)
{
	QMouseEvent *mouse = dynamic_cast<QMouseEvent*>(e);
	//if (mouse)
	//	qDebug() << "x:" << mouse->pos().x() << " y:" << mouse->pos().y();
	//qDebug() << "rect() :" << rect().topLeft().x() << " " << rect().topLeft().y() << " " << rect().width() << " " << rect().height();
	if (m_bOpenedFile)
	{
		if (e->type() == QEvent::MouseButtonPress)
		{
			if (mouse->button() == Qt::LeftButton && m_paintRect.contains(mouse->pos()))
			{
				m_bPicPressed = true;
				setCursor(Qt::ClosedHandCursor);
				m_pressedPoint = mouse->pos();
				return true;
			}

		}
		else if (e->type() == QEvent::MouseButtonRelease)
		{
			if (mouse->button() == Qt::LeftButton && m_bPicPressed)
			{
				setCursor(Qt::OpenHandCursor);
				m_bPicPressed = false;
				return true;
			}

		}
		else if (e->type() == QEvent::MouseMove)
		{
			if (m_paintRect.contains(mouse->pos()) && m_bPicPressed == false)
				setCursor(Qt::OpenHandCursor);
			else if (m_paintRect.contains(mouse->pos()) == false)
				setCursor(Qt::ArrowCursor);

			if (m_paintRect.contains(mouse->pos()) && m_bPicPressed)
			{
				m_xyOffset.setX(mouse->x() - m_pressedPoint.x());
				m_xyOffset.setY(mouse->y() - m_pressedPoint.y());
				m_pressedPoint = mouse->pos();
				m_action = Move;
				update();
			}
			if (m_paintRect.contains(mouse->pos()))
				return true;
		}
	}

	return QWidget::eventFilter(watched, e);
}

bool PictureView::selectFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("打开图片"), "/",
		QStringLiteral("所支持的图片类型(*.png;*.jpg;*.jpeg;*.bmp;*.svg);;常见图片文件(*.png;*.jpg;*.jpeg;*.bmp);;矢量图文件(*.svg)"));

	if (fileName.isEmpty())
		return false;

	m_filePath = fileName;
	QFileInfo fileInfo(fileName);
	m_isSvg = (fileInfo.suffix().toLower() == "svg") ? true : false;
	if (m_isSvg)
	{
		QSvgRenderer renderer(m_filePath);
		if (!renderer.isValid())
			return false;
		QSize size = renderer.defaultSize();
		QRect viewbox = renderer.viewBox();
		QPixmap img(size);
		img.fill(Qt::transparent);
		QPainter painter(&img);
		renderer.render(&painter);
		m_pixPicture = img;
	}
	else
	{
		QImage image;
		image.load(m_filePath);
		m_pixPicture = QPixmap::fromImage(image);
	}

	setShowLogo(false);
	m_paintRect = calculateShowRect();
	updateTitleText();
	update();
	return true;
}