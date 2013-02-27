#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <QObject>

class Synchronization : public QObject
{
    Q_OBJECT
public:
    explicit Synchronization(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SYNCHRONIZATION_H
