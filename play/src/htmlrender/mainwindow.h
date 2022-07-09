#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE

class HtmlWidget;
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	void initUi();
	void loadDocument(const QString &path);
	void saveDocument(const QString &path);

private:
	struct {
		QTextEdit* edit{ nullptr };
		HtmlWidget* html{ nullptr };
	} ui;
};

#endif
