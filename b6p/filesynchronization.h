#ifndef FILESYNCHRONIZATION_H
#define FILESYNCHRONIZATION_H

#include <QObject>
#include <QFileInfo>

class FileSynchronization : public QObject
{
    Q_OBJECT
public:
    explicit FileSynchronization(QObject *parent = 0);

    void doSynchro();

signals:

public slots:

private:
    void getFile(QFileInfo& file);
    void putFile(QString& file);

};

#endif // FILESYNCHRONIZATION_H
