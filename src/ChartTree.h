#pragma once

#include <QTreeWidget>
#include "Database.h"

class ChartTree : public QTreeWidget {
Q_OBJECT
public:
    ChartTree(Database* db);
    void rebuild();

public slots:
    void itemSelected(QTreeWidgetItem* item, int column);

signals:
    void chartSelected(Chart* chart);

private:
    Database* db;
};
