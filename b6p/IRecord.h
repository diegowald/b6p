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
        /*Sent = false;*/ }

    virtual RecordPtr asRecordPtr() = 0;

    virtual void setInitialized()
    {
        if (inMemoryStatus != NEW)
        {
            inMemoryStatus = UNMODIFIED;
            //setSentStatus(true);
        }
    }

    virtual bool isModified(bool inMemory)
    {
        return (inMemory ?
                    (inMemoryStatus == MODIFIED) :
                    (localStatus == MODIFIED));
    }

    virtual bool isDeleted(bool inMemory)
    {
        return (inMemory ?
                    (inMemoryStatus == DELETED) :
                    (localStatus == DELETED));
    }

    virtual bool isNew(bool inMemory)
    {
        return (inMemory ?
                    (inMemoryStatus == NEW) :
                    (localStatus == NEW));
    }

    void setModified()
    {
        if (inMemoryStatus == UNMODIFIED)
        {
            inMemoryStatus = MODIFIED;
            localStatus = MODIFIED;
            //setSentStatus(false);
        }
    }

    void setDeleted()
    {
        inMemoryStatus = DELETED;
        localStatus = DELETED;
        //setSentStatus(false);
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
        //return !Sent;
        return localStatus != UNMODIFIED;
    }

    /*void setSentStatus(bool sent)
    {
        Sent = sent;
    }*/

    RecordStatus getInMemoryRecordStatus() const
    {
        return inMemoryStatus;
    }

    RecordStatus getLocalRecordStatus() const
    {
        return localStatus;
    }

    void setLocalRecordStatus(RecordStatus newStatus)
    {
        localStatus = newStatus;
    }

private:
    RecordStatus inMemoryStatus;
    RecordStatus localStatus;

    ///DIEGO///
    //bool Sent;
};

#endif // IRECORD_H
