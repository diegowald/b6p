#ifndef IRECORD_H
#define IRECORD_H
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <QDebug>

typedef QMap<QString, QVariant> Record;
typedef boost::shared_ptr<Record> RecordPtr;
typedef boost::shared_ptr<QList<RecordPtr> > RecordSet;

enum RecordStatus
{
    UNINITIALIZED,
    UNMODIFIED,
    NEW,
    MODIFIED,
    DELETED
};

struct IRecord
{
    IRecord() { status = UNINITIALIZED; }

    virtual RecordPtr asRecordPtr() = 0;

    virtual void setInitialized()
    {
        if (status != NEW)
            status = UNMODIFIED;
    }

    virtual bool isModified()
    {
        return status == MODIFIED;
    }

    virtual bool isDeleted()
    {
        return status == DELETED;
    }

    virtual bool isNew()
    {
        return status == NEW;
    }

    void setModified()
    {
        qDebug() << status;
        if (status == UNMODIFIED)
            status = MODIFIED;
    }
    void setDeleted()
    {
        status = DELETED;
    }
    void setNew()
    {
        status = NEW;
    }
    void setUnmodified()
    {
        status = UNMODIFIED;
    }

private:
    RecordStatus status;
};

#endif // IRECORD_H
