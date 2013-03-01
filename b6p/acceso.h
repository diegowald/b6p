#ifndef ACCESO_H
#define ACCESO_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"


class Acceso;
typedef boost::shared_ptr<Acceso> AccesoPtr;
typedef boost::shared_ptr<QList<AccesoPtr> > AccesoLst;


class Acceso : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit Acceso(QObject *parent = 0);
    virtual ~Acceso();

    virtual RecordPtr asRecordPtr();

    NullableField<int> &IDSector();
    NullableField<QString> &Feature();

    NullableField<bool> &canRead();
    NullableField<bool> &canCreate();
    NullableField<bool> &canUpdate();
    NullableField<bool> &canDelete();

    bool CanRead();
    bool CanCreate();
    bool CanUpdate();
    bool CanDelete();

private:
    NullableField<int> m_IDSector;
    NullableField<QString> m_Feature;
    NullableField<bool> m_canRead;
    NullableField<bool> m_canCreate;
    NullableField<bool> m_canUpdate;
    NullableField<bool> m_canDelete;

};

#endif // ACCESO_H
