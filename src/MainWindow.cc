#include <QtGui>
#include <QString>
#include <QScrollArea>
#include <QSplitter>
#include <QSettings>
#include "MainWindow.h"

MainWindow::MainWindow() {
    this->setWindowTitle("ChartView");
    this->resize(800, 600);

    this->db = new Database();
    chartTree = new ChartTree(db);
    connect(chartTree, SIGNAL(chartSelected(Chart*)), SLOT(chartSelected(Chart*)));

    chartWidget = new ChartWidget();
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(chartWidget);

    QSplitter* splitter = new QSplitter;
    splitter->addWidget(chartTree);
    splitter->addWidget(scrollArea);
    this->setCentralWidget(splitter);
    splitter->setSizes((QList<int>() << 200 << 600));

    this->createActions();
    this->createMenus();

    setUnifiedTitleAndToolBarOnMac(true);

    this->updateDatabase();
}

void MainWindow::setChartDir() {
    QSettings settings("ChartView", "ChartView");
    QString chartDir;

    while (chartDir.isEmpty()) {
        chartDir = QFileDialog::getExistingDirectory(this);
    }

    settings.setValue("chartDir", chartDir);
    this->updateDatabase();
}

void MainWindow::updateDatabase() {
    QSettings settings("ChartView", "ChartView");
    QString chartDir = settings.value("chartDir").toString();

    if (chartDir.isEmpty()) {
        this->setChartDir();
    }
    else {
        db->update(chartDir);
        chartTree->rebuild();
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {

}

void MainWindow::chartSelected(Chart* chart) {
    chartWidget->open(chart->getPath());
}

void MainWindow::createActions() {
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    updateDatabaseAction = new QAction(tr("&Update Database"), this);
    updateDatabaseAction->setShortcut(tr("CTRL+U"));
    connect(updateDatabaseAction, SIGNAL(triggered()),
            this, SLOT(updateDatabase()));

    setChartDirAction = new QAction(tr("Set Chart &Directory"), this);
    connect(setChartDirAction, SIGNAL(triggered()),
            this, SLOT(setChartDir()));
}

void MainWindow::createMenus() {
    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(setChartDirAction);
    fileMenu->addAction(updateDatabaseAction);
    fileMenu->addAction(exitAction);

    viewMenu = this->menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(chartWidget->zoomInAction);
    viewMenu->addAction(chartWidget->zoomOutAction);
    viewMenu->addSeparator();
    viewMenu->addAction(chartWidget->rotateLeftAction);
    viewMenu->addAction(chartWidget->rotateRightAction);

    toolbar = this->addToolBar(tr("Toolbar"));
    toolbar->addAction(chartWidget->zoomInAction);
    toolbar->addAction(chartWidget->zoomOutAction);
    toolbar->addSeparator();
    toolbar->addAction(chartWidget->rotateLeftAction);
    toolbar->addAction(chartWidget->rotateRightAction);
}
