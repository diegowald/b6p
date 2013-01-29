#ifndef NULLABLEFIELD_H
#define NULLABLEFIELD_H

template <typename T>
class NullableField
{
public:
    NullableField()
    {
        m_Value = NULL;
    }

    NullableField(T value)
    {
        m_Value = NULL;
        setValue(value);
    }

    T *value()
    {
        return m_Value;
    }

    void setValue(T newValue)
    {
        if (isNull())
            m_Value = new T;
        (*m_Value) = newValue;
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
        }
        m_Value = NULL;
    }

private:
    T* m_Value;
};

#endif // NULLABLEFIELD_H
