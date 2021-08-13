/*
===================================================================================================

Algoritmalar - Post Makinesi v1.0 - 18.03.2019
Burak Tiryaki - 365377@ogr.ktu.edu.tr

===================================================================================================
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
