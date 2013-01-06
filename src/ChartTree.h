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
    void fillAirport(QTreeWidgetItem* item, Airport* airport);
    void fillCategory(QTreeWidgetItem* item, QString name, QList<Chart*> charts);

    Database* db;
};
