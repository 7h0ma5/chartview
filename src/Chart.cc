#include "Chart.h"

Chart::Chart(QString path, Chart::Type type, int flags) {
    this->path = path;
    this->type = type;
    this->flags = flags;
}

QString Chart::getName() {
    QStringList name;

    switch (this->type) {
    case UNKNOWN:
      name << "Unknown";
      break;
    case GROUND:
      name << "Ground";
      break;
    case SID:
      name << "SID";
      break;
    case STAR:
      name << "STAR";
      break;
    case TRANS:
      name << "Transition";
      break;
    case APPR:
      name << "Approach";
      break;
    }

    if (this->flags & Chart::ILS) name << "ILS";
    if (this->flags & Chart::LOC) name << "LOC";
    if (this->flags & Chart::VOR) name << "VOR";
    if (this->flags & Chart::DME) name << "DME";
    if (this->flags & Chart::RNAV) name << "RNAV";
    if (this->flags & Chart::VIS) name << "Visual";

    if (!this->runway.isEmpty()) name << "RWY" << this->runway;

    return name.join(" ");
}

QString Chart::getPath() {
    return this->path;
}

Chart::Type Chart::getType() {
    return this->type;
}

void Chart::setType(Chart::Type type) {
    this->type = type;
}

void Chart::setFlag(int flag) {
    this->flags |= flag;
}

void Chart::removeFlag(int flag) {
    this->flags &= ~(flag);
}

int Chart::getFlags() {
    return this->flags;
}

void Chart::setRunway(QString runway) {
    this->runway = runway;
}

QString Chart::getRunway() {
    return this->runway;
}
