#include "Airport.h"

Airport::Airport(QString icao) {
    this->icao = icao;
}

QString Airport::getICAO() {
    return this->icao;
}

void Airport::addChart(Chart* chart) {
    this->charts.append(chart);
}

QList<Chart*> Airport::getCharts() {
    return charts;
}
