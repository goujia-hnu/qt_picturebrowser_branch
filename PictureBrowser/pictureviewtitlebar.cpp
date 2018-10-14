#include "stdafx.h"
#include "pictureviewtitlebar.h"
#include "qsvgrenderer.h"

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
	, m_bPressed(false)
{
	setFixedHeight(dpiScaled(Title_Height));
	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);

	m_pTitleLabel->setFont(QFont("Microsoft YaHei", 10));
	QPalette pal;
	pal.setColor(QPalette::WindowText, Qt::white);
	m_pTitleLabel->setPalette(pal);

	m_pMenuButton = new PictureViewToolButton(this);
	m_pMinimizeButton = new PictureViewToolButton(this);
	m_pMaximizeButton = new PictureViewToolButton(this);
	m_pCloseButton = new PictureViewToolButton(this);

	m_pIconLabel->setFixedSize(dpiScaled(20), dpiScaled(20));
	m_pIconLabel->setScaledContents(true);
	m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QSvgRenderer renderer(QString("icons/menu.svg"));
	QPixmap img(Button_Height, Button_Height);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	m_pMenuButton->setContentsMargins(5, 0, 5, 0);
	m_pMenuButton->setFixedSize(Button_Width, Button_Height);
	m_pMenuButton->setIcon(QIcon(img));
	m_pMenuButton->setFlat(true);

	renderer.load(QString("icons/minus.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pMinimizeButton->setContentsMargins(5, 0, 5, 0);
	m_pMinimizeButton->setFixedSize(Button_Width, Button_Height);
	m_pMinimizeButton->setIcon(QIcon(img));
	m_pMinimizeButton->setFlat(true);

	renderer.load(QString("icons/maximize.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pMaximizeButton->setContentsMargins(5, 0, 5, 0);
	m_pMaximizeButton->setFixedSize(Button_Width, Button_Height);
	m_pMaximizeButton->setIcon(QIcon(img));
	m_pMaximizeButton->setFlat(true);

	renderer.load(QString("icons/close.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pCloseButton->setContentsMargins(5, 0, 5, 0);
	m_pCloseButton->setFixedSize(Button_Width, Button_Height);
	m_pCloseButton->setIcon(QIcon(img));
	m_pCloseButton->setFlat(true);

	m_pTitleLabel->setObjectName("whiteLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");

	m_pMenuButton->setToolTip(QStringLiteral("显示菜单"));
	m_pMinimizeButton->setToolTip(QStringLiteral("最小化"));
	m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
	m_pCloseButton->setToolTip(QStringLiteral("关闭"));

	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addSpacing(2);
	pLayout->addWidget(m_pTitleLabel);

	pLayout->addWidget(m_pMenuButton);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(5, 0, 0, 0);

	setLayout(pLayout);

	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMenuButton, SIGNAL(clicked()), this, SLOT(showMenu()));
	
	createPopMenu();
}

TitleBar::~TitleBar()
{
}

void TitleBar::setTitleIcon(QString filePath, QSize IconSize)
{
	QPixmap titleIcon(filePath);
	m_pIconLabel->setPixmap(titleIcon.scaled(IconSize));
}

void TitleBar::setTitleContent(QString titleContent)
{
	m_pTitleLabel->setText(m_titleContent + titleContent);
	m_titleContent = titleContent;
}

void TitleBar::setTitleWidth(int width)
{
	this->setFixedWidth(width);
}


void TitleBar::createPopMenu()
{
	m_pMenu = new PictureViewPopMenu(this);

	m_pOpenfileItem = new PictureViewMenuItem(this);
	QSvgRenderer renderer(QString("icons/insertpicturefromfile.svg"));
	QPixmap img(dpiScaled(16), dpiScaled(16));
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	m_pOpenfileItem->initMenuItem(img, QStringLiteral("打开文件"), QStringLiteral("Ctrl+O"));

	m_pSaveFileItem = new PictureViewMenuItem(this);
	renderer.load(QString("icons/saveas.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pSaveFileItem->initMenuItem(img, QStringLiteral("另存为"), QStringLiteral("Ctrl+S"));

	m_pPrintPictureItem= new PictureViewMenuItem(this);
	renderer.load(QString("icons/print.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pPrintPictureItem->initMenuItem(img, QStringLiteral("打印图片..."), QStringLiteral("Ctrl+P"));

	m_pClipperItem = new PictureViewMenuItem(this);
	renderer.load(QString("icons/clipper.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pClipperItem->initMenuItem(img, QStringLiteral("裁剪"), QStringLiteral("Ctrl+Alt+P"));

	m_pScreenshotItem = new PictureViewMenuItem(this);
	renderer.load(QString("icons/GrabScreenMenu.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pScreenshotItem->initMenuItem(img, QStringLiteral("截图..."), QStringLiteral("Ctrl+Alt+A"));

	m_pFilterItem = new PictureViewMenuItem(this);
	m_pFilterItem->initMenuItem(QPixmap(), QStringLiteral("图像滤波"), QStringLiteral("Alt+F"));

	m_pCameraItem = new PictureViewMenuItem(this);
	renderer.load(QString("icons/camera.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pCameraItem->initMenuItem(img, QStringLiteral("拍照"), QStringLiteral("Ctrl+Alt+C"));

	m_pCloseFileItem = new PictureViewMenuItem(this);
	renderer.load(QString("icons/exit.svg"));
	img.fill(Qt::transparent);
	renderer.render(&painter);
	m_pCloseFileItem->initMenuItem(img, QStringLiteral("关闭文件"), QStringLiteral("Ctrl+F4"));
	//模式识别

	m_pMenu->insertItem(m_pOpenfileItem);
	m_pMenu->insertItem(m_pSaveFileItem);
	m_pMenu->insertItem(m_pPrintPictureItem);
	m_pMenu->insertItem(m_pClipperItem);
	m_pMenu->insertItem(m_pScreenshotItem);
	m_pMenu->insertItem(m_pFilterItem);
	m_pMenu->insertItem(m_pCameraItem);
	m_pMenu->insertItem(m_pCloseFileItem);
}

void TitleBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRect(QRect(0, 0, this->width(), this->height()));
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(TitleBar_BackGround));
	QWidget::paintEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
	m_bPressed = true;
	QWidget::mousePressEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	m_bPressed = false;
	QWidget::mouseReleaseEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			m_titleContent = pWidget->windowTitle();
			m_pTitleLabel->setText(m_titleContent);
			return true;
		}
	}
	case QEvent::WindowIconChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			QIcon icon = pWidget->windowIcon();
			m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
			return true;
		}
	}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_pCloseButton)
		{
			pWindow->close();
		}
	}
}

void TitleBar::showMenu()
{
	QRect rect = m_pMenuButton->geometry();
	QPoint pt = mapToGlobal(rect.bottomLeft());
	m_pMenu->move(pt);
	m_pMenu->show();
}

void TitleBar::updateMaximize()
{
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized();
		QPixmap img(Button_Height, Button_Height);
		img.fill(Qt::transparent);
		QPainter painter(&img);
		if (bMaximize)
		{
			QSvgRenderer renderer(QString("icons/minimize.svg"));
			renderer.render(&painter);
			m_pMaximizeButton->setToolTip(QStringLiteral("还原"));
			m_pMaximizeButton->setIcon(QIcon(img));
		}
		else
		{
			QSvgRenderer renderer(QString("icons/maximize.svg"));
			renderer.render(&painter);
			m_pMaximizeButton->setIcon(QIcon(img));
			m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
		}

		m_pMaximizeButton->setStyle(QApplication::style());
	}
}