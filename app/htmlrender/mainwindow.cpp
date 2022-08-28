#include "mainwindow.h"
#include <QFile>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include "htmlwidget.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	initUi();

	loadDocument("index.html");
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUi()
{
	auto splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Horizontal);
	setCentralWidget(splitter);

	auto area = new QWidget(splitter);
	auto vlayout = new QVBoxLayout(area);
	auto commit = new QPushButton(tr("Commit"), area);
	vlayout->addWidget(commit);
	ui.edit = new QTextEdit(splitter);
	vlayout->addWidget(ui.edit, 1);
	splitter->addWidget(area);

	ui.html = new HtmlWidget(splitter);
	splitter->addWidget(ui.html);

	connect(commit, &QPushButton::clicked, this, [this]() {
		saveDocument("index.html");
	});
}

void MainWindow::loadDocument(const QString& path)
{
	QFile f(path);
	if (!f.open(QFile::ReadOnly)) {
		return;
	}

	QTextStream in(&f);
	in.setEncoding(QStringConverter::Utf8);
	const auto docStr = in.readAll();

	ui.edit->setPlainText(docStr);
}

void MainWindow::saveDocument(const QString& path)
{
	QFile f(path);
	if (!f.open(QFile::WriteOnly)) {
		return;
	}

	const auto html = ui.edit->toPlainText().trimmed();

	QTextStream out(&f);
	out << html;
	out.flush();
	f.close();

	ui.html->loadDocument(html);
}
