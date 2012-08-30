#pragma once

#include <QString>
#include <QList>
#include "Chart.h"

class Airport {
public:
    Airport(QString icao);

    QString getICAO();
    void addChart(Chart* chart);
    QList<Chart*> getCharts();

private:
    QString icao;
    QList<Chart*> charts;
};
