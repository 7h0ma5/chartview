#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("ChartView");

    MainWindow mainWin;
    mainWin.show();

    app.setActiveWindow(&mainWin);
    return app.exec();
}
