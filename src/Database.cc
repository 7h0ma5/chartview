#include <QDir>
#include "Database.h"

Database::Database() {

}

Airport* Database::getAirport(QString icao) {
    return this->airports.value(icao);
}

QList<QString> Database::getAirportList() {
    return this->airports.keys();
}

void Database::update(QString path) {
    qDeleteAll(this->airports);
    this->airports.clear();

    QDir dir(path);
    QStringList aptdirs = dir.entryList(QDir::Dirs);

    foreach (QString aptdir, aptdirs) {
        if (aptdir.size() != 4) continue;

        QString icao = aptdir.toUpper();
        Airport* apt = this->getAirport(icao);
        if (!apt) {
            apt = new Airport(icao);
            airports.insert(icao, apt);
        }

        // search for pdf files in this dir
        dir.cd(aptdir);
        QStringList files = dir.entryList(QStringList("*.pdf"), QDir::Files);

        foreach (QString file, files) {
            QStringList parts = file.toUpper().split(QRegExp("(\\s+|_+|\\.)"));
            parts.removeLast(); // remove pdf ending

            Chart* chart = new Chart(dir.filePath(file));

            if (parts.first() == icao) {
                parts.removeFirst();
            }

            if (parts.size() == 0) continue;

            if (parts.first() == "GND") chart->setType(Chart::GROUND);
            if (parts.first() == "STAR") chart->setType(Chart::STAR);
            if (parts.first() == "SID") chart->setType(Chart::SID);
            if (parts.first() == "TRANS") chart->setType(Chart::TRANS);
            if (parts.first() == "APPR") chart->setType(Chart::APPR);

            parts.removeFirst();

            if (parts.contains("ILS")) chart->setFlag(Chart::ILS);
            if (parts.contains("LOC")) chart->setFlag(Chart::LOC);
            if (parts.contains("VOR")) chart->setFlag(Chart::VOR);
            if (parts.contains("DME")) chart->setFlag(Chart::DME);
            if (parts.contains("RNAV")) chart->setFlag(Chart::RNAV);
            if (parts.contains("VIS")) chart->setFlag(Chart::VIS);

            foreach (QString part, parts) {
                if (part.startsWith("RWY")) {
                    part.remove(0, 3);
                    chart->setRunway(part);
                }
            }

            apt->addChart(chart);
        }

        dir.cdUp();
    }
}
