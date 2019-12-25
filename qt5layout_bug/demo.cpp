#include "demo.h"

Window::Window(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_NativeWindow);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(QMargins());

	mainLayout->addWidget(new HeaderBar(this));

	QStackedWidget *centralArea = new QStackedWidget(this);
	centralArea->addWidget(new View(QLatin1String("View 1"), this));
	mainLayout->addWidget(centralArea);

	mainLayout->addWidget(new QStatusBar(this));
}

Window::~Window()
{
}

// --------------------------------------------------------------

HeaderBar::HeaderBar(QWidget* parent)
	: QWidget(parent)
	, m_isSingleLine(false)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	parent->installEventFilter(this);
}

HeaderBar::~HeaderBar()
{

}

void HeaderBar::setSingleLine(bool single)
{
	if (m_isSingleLine == single)
		return;

	m_isSingleLine = single;
	updateGeometry();
}

void HeaderBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::black);
}

bool HeaderBar::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange &&
		object->isWidgetType())
	{
		QWidget *w = static_cast<QWidget *>(object);
		if (w->windowState() & Qt::WindowMaximized)
			setSingleLine(true);
		else if (!(w->windowState() & Qt::WindowMinimized))
			setSingleLine(false);
	}

	return QWidget::eventFilter(object, event);
}

QSize HeaderBar::sizeHint() const
{
	return QSize(0, m_isSingleLine ? 30 : 80);
}

// --------------------------------------------------------------

View::View(const QString &name, QWidget *parent)
	: QWidget(parent)
	, m_name(name)
{
	setAttribute(Qt::WA_DontCreateNativeAncestors);
	setAttribute(Qt::WA_NativeWindow);
}

View::~View()
{

}

void View::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);

	{
		QPen pen(Qt::red, 1);
		painter.setPen(pen);

		const QRect border = rect().adjusted(0, 0, -1, -1);
		painter.drawRect(border);
	}

	if (!m_name.isEmpty())
	{
		QPen pen(Qt::black);
		painter.setPen(pen);
		QFont font = painter.font();
		font.setPointSize(30);
		font.setBold(true);
		painter.setFont(font);

		painter.drawText(rect(), Qt::AlignCenter, m_name);
	}
}
