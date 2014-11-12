#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication::setGraphicsSystem("raster");
    QApplication a(argc, argv);
    MainWindow w;
#if QT_VERSION < 0x040000
  a.setMainWidget(&w);
#endif
    w.show();
    return a.exec();
}
