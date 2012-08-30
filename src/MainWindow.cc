#include <QtGui>
#include <QScrollArea>
#include <QSplitter>
#include <QDebug>
#include "MainWindow.h"

MainWindow::MainWindow() {
    this->setWindowTitle("ChartView");
    this->resize(800, 600);

    Database* db = new Database();
    db->update("/Users/thomas/Dropbox/vatsim");

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

    this->createActions();
    this->createMenus();

    setUnifiedTitleAndToolBarOnMac(true);
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
}

void MainWindow::createMenus() {
    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    viewMenu = this->menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(chartWidget->zoomInAction);
    viewMenu->addAction(chartWidget->zoomOutAction);
    viewMenu->addSeparator();
    viewMenu->addAction(chartWidget->rotateLeftAction);
    viewMenu->addAction(chartWidget->rotateRightAction);
}
