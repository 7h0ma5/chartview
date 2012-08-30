#pragma once

#include <QString>
#include <QHash>
#include "Airport.h"

class Database {
public:
    Database();

    Airport* getAirport(QString icao);
    QList<QString> getAirportList();

    void update(QString path);

private:
    QHash<QString, Airport*> airports;
};
