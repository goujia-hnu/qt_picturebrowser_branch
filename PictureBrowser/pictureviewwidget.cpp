#include "stdafx.h"
#include "pictureviewwidget.h"
#include "qsvgrenderer.h"
#include "basewindow.h"

#define LOGO_SIZE_WIDTH dpiScaled(200)
#define LOGO_SIZE_HEIGHT dpiScaled(200)

PictureViewWidget::PictureViewWidget(QWidget* parent)
	:QWidget(parent),
	m_scaleRatio(1.0),
	m_isSvg(false)
{
	m_pLogoLabel = new QLabel(this);
	m_pLogoLabel->setFixedSize(LOGO_SIZE_WIDTH, LOGO_SIZE_HEIGHT);
	QSvgRenderer renderer(QString("icons/mainicon.svg"));
	QPixmap img(LOGO_SIZE_WIDTH, LOGO_SIZE_HEIGHT);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	renderer.render(&painter);
	m_pLogoLabel->setPixmap(img);

	m_pOpenFile = new PictureViewToolButton(this);
	m_pOpenFile->setFixedSize(dpiScaled(170), dpiScaled(45));
	m_pOpenFile->setText(QStringLiteral("打开图片"));
	m_pOpenFile->setFont(QFont("Microsoft YaHei", dpiScaled(15)));
	m_pOpenFile->setFlat(true);
	m_pOpenFile->setStyleSheet("color:rgb(255, 255, 255)");
	connect(m_pOpenFile, SIGNAL(clicked()), this, SLOT(onOpenPicture()));

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
		layout2->addWidget(m_pOpenFile);
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

PictureViewWidget::~PictureViewWidget()
{

}

void PictureViewWidget::setDrawLogo(BOOL visible)
{
	m_pLogoLabel->setVisible(visible);
	m_pOpenFile->setVisible(visible);
}

BOOL PictureViewWidget::logoVisible()
{
	return m_pLogoLabel->isVisible();
}

void PictureViewWidget::setTitleBar(TitleBar* titlebar)
{
	m_pTitleBar = titlebar;
}

void PictureViewWidget::initPictureView()
{

}

void PictureViewWidget::paintEvent(QPaintEvent *event)
{
	QPainter paint(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRect(QRect(0, 0, this->width(), this->height()));
	paint.setRenderHint(QPainter::SmoothPixmapTransform, true);
	paint.fillPath(pathBack, QBrush(Qt::white));

	if (!m_filePath.isEmpty())
	{
		//原始尺寸
		int x = rect().width() - m_pixPicture.width();
		int y = rect().height() - m_pixPicture.height();
		QRect rc(x / 2, y / 2, m_pixPicture.width(), m_pixPicture.height());
		paint.drawPixmap(rc, m_pixPicture);
		//处理缩放

		//处理位移

		//显示
	}
}

void PictureViewWidget::onOpenPicture()
{
	selectFile();
}

void PictureViewWidget::onCloseFile()
{
	if (!logoVisible())
	{
		setDrawLogo(true);
		m_filePath.clear();
		//m_pixmap = QPixmap();
		this->update();
	}
}

void PictureViewWidget::selectFile()
{
	QString fileName = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("打开图片"),
		"/",
		"*.png;*.jpg;*.jpeg;*.bmp;;*.svg"
	);//只能打开一张图片

	if (!fileName.isEmpty())
	{ 
		m_filePath = fileName;
		QFileInfo fileInfo(fileName);
		m_isSvg = (fileInfo.suffix().toLower() == "svg") ? true : false;
		if (m_isSvg)
		{
			QSvgRenderer renderer(m_filePath);
			if (!renderer.isValid())
				return;
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
		QString showinfo = " - " + fileInfo.fileName(); //12345看图 - filename - xxx像素,xxMB - 70%
		m_pTitleBar->setTitleContent(showinfo);			//强制刷新一下
		this->setDrawLogo(false);							//隐藏打开按钮和LOGO	
		this->update();
	}
}