#include <QtWidgets>
#include <QtGui>
#include <QtCore>


class Window : public QWidget
{
public:
	Window(QWidget* parent = nullptr)
	{
		fonts = QFontDatabase().families();

		connect(&timer, &QTimer::timeout, this, &Window::updateFont);
		timer.start(10);
	}

protected:
	void paintEvent(QPaintEvent* event) override
	{
		QPainter painter(this);
		QString str = QString::number(fonts.count());
		painter.drawText(rect(), Qt::AlignCenter, str);
	}

private:
	void updateFont()
	{
		if (fonts.empty())
		{
			timer.stop();
			return;
		}

		QString font = fonts.takeFirst();
		QString family = QFontInfo(font).family();
		update();
	}

private:
	QStringList fonts;
	QTimer timer;
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Window window;
	window.show();

	return app.exec();
}
