#include "demo.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
	
	Window window;
	window.resize(800, 600);
	window.show();
	
	return app.exec();
}
