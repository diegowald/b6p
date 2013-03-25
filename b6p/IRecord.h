#ifndef IRECORD_H
#define IRECORD_H
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <QDebug>

#define RECORD_ID "RECORD_ID"

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
    IRecord() { status = UNINITIALIZED; Sent = false; }

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

    bool isUnSent()
    {
        return !Sent;
    }

    void setSentStatus(bool sent)
    {
        Sent = sent;
    }

private:
    RecordStatus status;
    bool Sent;
};

#endif // IRECORD_H
