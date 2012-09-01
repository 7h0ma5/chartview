#pragma once

#include <QMainWindow>
#include "Database.h"
#include "ChartTree.h"
#include "ChartWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();

public slots:
    void chartSelected(Chart* chart);
    void setChartDir();
    void updateDatabase();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void createActions();
    void createMenus();

    QToolBar* toolbar;

    QMenu* fileMenu;
    QMenu* viewMenu;

    QAction* updateDatabaseAction;
    QAction* setChartDirAction;
    QAction* exitAction;

    Database* db;
    ChartTree* chartTree;
    ChartWidget* chartWidget;
};
