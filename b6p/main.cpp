#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator appTranslator;

    if (appTranslator.load("b6p_" + QLocale::system().name(), a.applicationDirPath()))
        a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
