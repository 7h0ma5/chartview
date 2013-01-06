#include "Airport.h"

Airport::Airport(QString icao) {
    this->icao = icao;
}

Airport::~Airport() {
    qDeleteAll(charts);
}

QString Airport::getICAO() {
    return this->icao;
}

void Airport::addChart(Chart* chart) {
    this->charts.append(chart);
}

QList<Chart*> Airport::getCharts(int type) {
    QList<Chart*> chartList;

    foreach (Chart* chart, this->charts) {
        if (chart->getType() == type) {
            chartList.append(chart);
        }
    }

    return chartList;
}
