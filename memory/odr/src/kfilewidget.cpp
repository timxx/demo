#include "kfilewidget.h"
#include <QFileDialog>

BEGIN_ODR_NS

KFileWidget::KFileWidget(QWidget *parent)
	: QWidget(parent)
{

}

KFileWidget::~KFileWidget()
{

}

QString KFileWidget::getOpenFileName()
{
	return QFileDialog::getOpenFileName(this, tr("Open File"));
}

END_ODR_NS
