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

protected:
    void closeEvent(QCloseEvent* event);

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* viewMenu;

    QAction* exitAction;

    Database* db;
    ChartTree* chartTree;
    ChartWidget* chartWidget;
};
