#include <QtWidgets>
#include <QtGui>
#include <QtCore>


class PopupWidget : public QWidget
{
public:
	PopupWidget(QWidget *parent = nullptr)
		: QWidget(parent, Qt::Popup)
	{
		QVBoxLayout *layout = new QVBoxLayout(this);

		QLineEdit *edit = new QLineEdit(this);
		layout->addWidget(edit);
	}

	int exec()
	{
		QEventLoop loop;

		move(QCursor::pos());
		show();

		return loop.exec();
	}

protected:
	void paintEvent(QPaintEvent *event) override
	{
		QPainter painter(this);
		painter.fillRect(rect(), Qt::white);
	}
};

class Window : public QWidget
{
	Q_OBJECT
public:
	Window(QWidget *parent = nullptr)
		: QWidget(parent)
	{
		QVBoxLayout *layout = new QVBoxLayout(this);

		QLineEdit *edit = new QLineEdit(this);
		layout->addWidget(edit);

		QPushButton *button = new QPushButton("Show popup", this);
		layout->addWidget(button);

		connect(button, &QPushButton::clicked, this, &Window::onButtonClicked);
	}

protected:
	void mouseReleaseEvent(QMouseEvent *event) override
	{
		onButtonClicked();
	}

private slots:
	void onButtonClicked()
	{
		PopupWidget pop(this);
		pop.exec();
	}
};


int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Window window;
	window.show();

	return app.exec();
}

#include "ime.moc"
