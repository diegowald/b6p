#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "dlglogin.h"
#include "datastore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator appTranslator;

    if (appTranslator.load("b6p_" + QLocale::system().name(), a.applicationDirPath()))
        a.installTranslator(&appTranslator);

    DlgLogin dlg;
    int IDUser = 0;
    bool canAccessApp = false;
    if (dlg.hasUsers())
    {
        if (dlg.exec() == QDialog::Accepted)
        {
            IDUser = dlg.getIDUser();
            canAccessApp = DataStore::instance()->getAccesos()->canAccessApplication(IDUser);
        }
    }
    else
        canAccessApp = true;

    if (canAccessApp)
    {
        MainWindow w(IDUser);
        w.show();
        QFont font = a.font();
        font.setPixelSize(12);
        a.setFont(font);
        return a.exec();
    }
    else
    {
        return -1;
    }
}
