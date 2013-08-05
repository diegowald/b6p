#ifndef IRECORD_H
#define IRECORD_H
#include <boost/shared_ptr.hpp>
#include <QMap>

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
    IRecord() {
        inMemoryStatus = UNINITIALIZED;
        localStatus = UNINITIALIZED;
        //status = UNINITIALIZED;
        Sent = false; }

    virtual RecordPtr asRecordPtr() = 0;

    virtual void setInitialized()
    {
        if (inMemoryStatus != NEW)
        {
            inMemoryStatus = UNMODIFIED;
            setSentStatus(true);
        }
    }

    virtual bool isModifiedInMemory()
    {
        return inMemoryStatus == MODIFIED;
    }

    virtual bool isLocallyModified()
    {
        return localStatus == MODIFIED;
    }

    virtual bool isDeleted()
    {
        return localStatus == DELETED;
        //return status == DELETED;
    }

    virtual bool isNew()
    {
        return inMemoryStatus == NEW;
    }

    void setModified()
    {
        if (inMemoryStatus == UNMODIFIED)
        {
            inMemoryStatus = MODIFIED;
            localStatus = MODIFIED;
            setSentStatus(false);
        }
    }

    void setDeleted()
    {
        inMemoryStatus = DELETED;
        localStatus = DELETED;
        setSentStatus(false);
    }

    void setNew()
    {
        inMemoryStatus = NEW;
        localStatus = NEW;
    }

    void setUnmodified()
    {
        inMemoryStatus = UNMODIFIED;
    }

    bool isUnSent()
    {
        return !Sent;
    }

    void setSentStatus(bool sent)
    {
        Sent = sent;
    }

    RecordStatus getInMemoryRecordStatus() const
    {
        return inMemoryStatus;
    }

    RecordStatus getLocalRecordStatus() const
    {
        return localStatus;
    }

private:
    ///DIEGO///
    //aca hay que setear local status para cuando se maneja en memoria y
    //el status para cuando se refiere a los elementos en la base central

    //RecordStatus status; ahora se desdobla en InMemoryStatus y LocalStatus

    RecordStatus inMemoryStatus;
    RecordStatus localStatus;

    bool Sent;
};

#endif // IRECORD_H
