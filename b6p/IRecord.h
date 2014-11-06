/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef IRECORD_H
#define IRECORD_H
#include <QMap>
#include <QSharedPointer>

#define RECORD_ID "RECORD_ID"

typedef QMap<QString, QVariant> Record;
typedef QSharedPointer<Record> RecordPtr;
typedef QSharedPointer<QList<RecordPtr> > RecordSet;

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
    IRecord()
    {
        inMemoryStatus = UNINITIALIZED;
        localStatus = UNINITIALIZED;
    }

    virtual RecordPtr asRecordPtr() = 0;

    virtual void setInitialized()
    {
        if (inMemoryStatus != NEW)
        {
            inMemoryStatus = UNMODIFIED;
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
        }
    }

    void setDeleted()
    {
        inMemoryStatus = DELETED;
        localStatus = DELETED;
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
        return ((localStatus != UNMODIFIED) && (localStatus != UNINITIALIZED));
    }

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

    void setInMemoryRecordStatus(RecordStatus newStatus)
    {
        inMemoryStatus = newStatus;
    }

private:
    RecordStatus inMemoryStatus;
    RecordStatus localStatus;
};

#endif // IRECORD_H
