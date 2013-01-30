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
    }

    NullableField(T value)
    {
        m_Value = NULL;
        parent = NULL;
        setValue(value);
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
            m_Value = new T;
        (*m_Value) = newValue;
        SetModified();
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
            status = Updated;
        if (parent != NULL)
            parent->setModified();
    }

private:
    T* m_Value;
    FieldStatus status;
    IRecord *parent;
};

#endif // NULLABLEFIELD_H
