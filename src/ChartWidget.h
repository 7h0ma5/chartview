#pragma once

#include <QLabel>
#include <poppler-qt4.h>

class ChartWidget : public QLabel {
Q_OBJECT
public:
    ChartWidget();

    void open(QString path);
    void render();

public slots:
    void zoomIn();
    void zoomOut();
    void rotateLeft();
    void rotateRight();


public:
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* rotateLeftAction;
    QAction* rotateRightAction;

private:
    void scaleImage(double factor);

    double zoom;
    int rotation;
    Poppler::Document* document;
};
