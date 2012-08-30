#pragma once

#include <QString>
#include <QStringList>
#include <QHash>

class Chart {
public:
    // chart type
    enum Type {
        UNKNOWN,
        GROUND,
        SID,
        STAR,
        TRANS,
        APPR,
    };

    // instrument flags
    static const int ILS  = 0x1;
    static const int LOC  = 0x2;
    static const int VOR  = 0x4;
    static const int DME  = 0x8;
    static const int RNAV = 0x10;
    static const int VIS  = 0x20;

public:
    Chart(QString path, Type type = UNKNOWN, int flags = 0);

    QString getName();

    Type getType();
    void setType(Type type);

    void setFlag(int flag);
    void removeFlag(int flag);
    int getFlags();

    QString getPath();

    void setRunway(QString runway);
    QString getRunway();

private:
    Type type;
    int flags;
    QString path;
    QString runway;
};
