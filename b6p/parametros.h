#ifndef PARAMETROS_H
#define PARAMETROS_H
#include "acollection.h"
#include <QMap>

class Parametros : public ACollection
{
    Q_OBJECT
public:
    explicit Parametros(QObject *parent = 0);

    virtual void loadData();
    virtual void saveData();

    QString getValue(QString key, QString defaultValue);
signals:
    
public slots:
private:
    QMap<QString, QString> m_Dictionary;
};

typedef boost::shared_ptr<Parametros> ParametrosPtr;
#endif // PARAMETROS_H
