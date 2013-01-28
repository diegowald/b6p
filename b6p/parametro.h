#ifndef PARAMETRO_H
#define PARAMETRO_H

#include <QObject>
class Parametro : public QObject
{
    Q_OBJECT
public:
    explicit Parametro(QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    QString m_Key;
    QString m_Value;
};

#endif // PARAMETRO_H
