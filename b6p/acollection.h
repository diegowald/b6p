#ifndef ACOLLECTION_H
#define ACOLLECTION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <QTreeWidget>
#include "sqlhandler.h"

typedef QMap<QString, QVariant> Record;

class ACollection : public QObject
{
    Q_OBJECT
public:
    explicit ACollection(QString Name, QObject *parent = 0);
    
    virtual void load();
    virtual void save();

    QString name() const;

    virtual QString getSqlString() = 0;
    virtual void addRecord(Record &record) = 0;
    virtual void saveData() = 0;
    virtual void defineHeaders(QStringList &list) = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool addNew() = 0;
    virtual void edit(QVariant ID) = 0;
    virtual void deleteElement(QVariant ID) = 0;

signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);
    
public slots:

private:
    QString m_Name;
    SQLHandler sqlEngine;
};

#endif // ACOLLECTION_H
