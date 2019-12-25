#ifndef QT5_LAYOUT_BUG_DEMO_H

#include <QtGui>
#include <QtWidgets>

class HeaderBar;

class Window : public QWidget
{
	Q_OBJECT
public:
	Window(QWidget *parent = nullptr);
	~Window();
};

// --------------------------------------------------------------

class HeaderBar : public QWidget
{
	Q_OBJECT
public:
	HeaderBar(QWidget *parent = nullptr);
	~HeaderBar();

	void setSingleLine(bool single);

protected:
	void paintEvent(QPaintEvent *event) override;
	bool eventFilter(QObject *object, QEvent *event) override;
	QSize sizeHint() const override;

private:
	bool m_isSingleLine;
};

// --------------------------------------------------------------

class View : public QWidget
{
	Q_OBJECT
public:
	View(const QString &name, QWidget *parent = nullptr);
	~View();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QString m_name;
};

#endif // QT5_LAYOUT_BUG_DEMO_H
