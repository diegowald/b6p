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
#ifndef NULLABLEFIELD_H
#define NULLABLEFIELD_H
#include "IRecord.h"
#include <QVariant>

enum FieldStatus
{
    Unmodified = -1,
    New,
    Updated
};

template <typename T>
class NullableField
{
public:
    NullableField()
    {
        m_Value = NULL;
        parent = NULL;
        status = Unmodified;
    }

    NullableField(T value)
    {
        m_Value = NULL;
        parent = NULL;
        setValue(value);
    }

    virtual ~NullableField()
    {
        if (!isNull())
            delete m_Value;
    }

    void setParent(IRecord *newParent)
    {
        parent = newParent;
    }

    T value()
    {
        return *m_Value;
    }

    QVariant toVariant()
    {
        return isNull() ? QVariant() : value();
    }

    void setValue(NullableField<T> value)
    {
        if (value.isNull())
            setNull();
        else
            setValue(value.value());
    }

    void setValue(T newValue)
    {
        if (isNull())
        {
            m_Value = new T;
            (*m_Value) = newValue;
            SetModified();
        }
        else
        {
            if (*m_Value != newValue)
            {
                (*m_Value) = newValue;
                SetModified();
            }
        }
    }

    bool isNull()
    {
        return m_Value == NULL;
    }

    void setNull()
    {
        if (!isNull())
        {
            delete m_Value;
            SetModified();
        }
        m_Value = NULL;
    }

    FieldStatus Status() const
    {
        return status;
    }

private:
    void SetModified()
    {
        if (status == Unmodified)
        {
            status = Updated;
        }
        if (parent != NULL)
            parent->setModified();
    }

private:
    T* m_Value;
    FieldStatus status;
    IRecord *parent;
};

#endif // NULLABLEFIELD_H
