#include "qmysql.h"
#include <QtSql>
#include <QMessageBox>


QMysql::QMysql(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("b6p");
    db.setUserName("root");
    db.setPassword("mic1492");

    if (!db.open())
        QMessageBox::critical(0, QObject::tr("Database Error"),
                      db.lastError().text());

    db.close();
}
