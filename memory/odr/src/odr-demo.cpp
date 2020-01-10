
#include "kfilewidget.h"

#include <QMessageBox>
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	KFileWidget fileWidget;
	fileWidget.show();

	QString fileName = fileWidget.getOpenFileName();
	if (!fileName.isEmpty())
	{
		QMessageBox::information(&fileWidget,
								 QLatin1String("File Info"),
								 fileName);
	}

	return app.exec();
}
