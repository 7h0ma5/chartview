#include "ChartWidget.h"
#include <QtGui>
#include <QDebug>

ChartWidget::ChartWidget() {
    document = 0;
    zoom = 1.0;
    rotation = 0;

    this->setBackgroundRole(QPalette::Dark);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->setScaledContents(true);

    zoomInAction = new QAction(tr("Zoom &In"), this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("Zoom &Out"), this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    rotateLeftAction = new QAction(tr("Rotate &Left"), this);
    rotateLeftAction->setShortcut(Qt::CTRL + Qt::Key_Left);
    connect(rotateLeftAction, SIGNAL(triggered()), this, SLOT(rotateLeft()));

    rotateRightAction = new QAction(tr("Rotate &Right"), this);
    rotateRightAction->setShortcut(Qt::CTRL + Qt::Key_Right);
    connect(rotateRightAction, SIGNAL(triggered()), this, SLOT(rotateRight()));
}

void ChartWidget::open(QString path) {
    if (document) delete document;

    rotation = 0;

    document = Poppler::Document::load(path);
    document->setRenderHint(Poppler::Document::Antialiasing);
    document->setRenderHint(Poppler::Document::TextHinting);
    document->setRenderHint(Poppler::Document::TextAntialiasing);

    this->render();
}

void ChartWidget::render() {
    if (!(document)) return;

    Poppler::Page* page = document->page(0);

    QImage image = page->renderToImage(zoom*physicalDpiX(), zoom*physicalDpiY(),
                                       -1, -1, -1, -1, (Poppler::Page::Rotation)rotation);

    this->setPixmap(QPixmap::fromImage(image));
    this->adjustSize();
    this->update();
    this->repaint();
}

void ChartWidget::zoomIn() {
    this->scaleImage(1.25);
}

void ChartWidget::zoomOut() {
    this->scaleImage(0.8);
}

void ChartWidget::scaleImage(double factor) {
    zoom *= factor;

    zoomInAction->setEnabled(zoom < 3.0);
    zoomOutAction->setEnabled(zoom > 0.333);

    this->render();
}

void ChartWidget::rotateLeft() {
    if (rotation > 0) {
        rotation = --rotation;
    }
    else {
        rotation = 3;
    }
    this->render();
}

void ChartWidget::rotateRight() {
    rotation = ++rotation % 3;
    this->render();
    qDebug() << "right!";
}
