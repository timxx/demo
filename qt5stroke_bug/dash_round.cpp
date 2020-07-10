#include <QtWidgets>
#include <QtGui>
#include <QtCore>

class Window : public QWidget
{
public:
	Window(QWidget *parent = nullptr)
	 : QWidget(parent)
	{
	}

protected:
	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QPainterPath path;

		path.moveTo(95.26263883128254, 240.5478666666667);
		path.cubicTo(170.4208796104275, 282.11466666666666,
					 245.49135802469135, 282.11466666666666,
					 320.4740740740741, 240.5478666666667);

		QPen pen(QBrush(Qt::black), 30.0, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
		pen.setDashPattern(QVector<qreal>() << 4.0 << 3.0 << 1.0 << 3.0);
		painter.strokePath(path, pen);
	}
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Window window;
	window.show();

	return app.exec();
}
