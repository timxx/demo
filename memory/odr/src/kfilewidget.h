#ifndef ODR_K_FILE_WIDGET_H
#define ODR_K_FILE_WIDGET_H

#include <QWidget>

#if 0
#  define BEGIN_ODR_NS namespace odr {
#  define END_ODR_NS }
#  define USE_ODR_US using namespace odr;
#else
#  define BEGIN_ODR_NS
#  define END_ODR_NS
#  define USE_ODR_US
#endif

BEGIN_ODR_NS

class Q_DECL_EXPORT KFileWidget : public QWidget
{
	Q_OBJECT
public:
	KFileWidget(QWidget *parent = nullptr);
	~KFileWidget();

	QString getOpenFileName();
};

END_ODR_NS

USE_ODR_US

#endif // ODR_K_FILE_WIDGET_H
