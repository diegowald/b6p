#include "estimacionesdias.h"

EstimacionesDias::EstimacionesDias(QObject *parent)
    : ACollection(tr("Day Estimations"), parent)
{
}

QString EstimacionesDias::getSqlString()
{
    return "select Dia, HorasEstimadas from planificaciondias;";
}

void EstimacionesDias::addRecord(Record &record)
{
    EstimacionDiaPtr e(new EstimacionDia(this));
    e->Dia().setValue(record["Dia"].toDate());
    e->EstimacionHoras().setValue(record["HorasEstimadas"].toInt());
    e->setInitialized();
    m_Estimaciones[e->Dia().value()] = e;
}

QString EstimacionesDias::getDeleteStatement()
{
    return "delete from planificaciondias where Dia = :Dia;";
}

QString EstimacionesDias::getUpdateStatement()
{
    return "update planificaciondias set HorasEstimadas = :HorasEstimadas where Dia = :Dia;";
}

QString EstimacionesDias::getInsertStatement()
{
    return "insert into (Dia, HorasEstimadas) "
            " values "
            " (:Dia, :HorasEstimadas);";
}

RecordSet EstimacionesDias::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        switch (status)
        {
        case NEW:
            if (e->isNew())
                res->push_back(e->asRecordPtr());
            break;
        case MODIFIED:
            if (e->isModified())
                res->push_back(e->asRecordPtr());
            break;
        case DELETED:
            if (e->isDeleted())
                res->push_back(e->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;

}

void EstimacionesDias::defineHeaders(QStringList &list)
{
}

void EstimacionesDias::fillData(QTreeWidget &tree)
{
}

bool EstimacionesDias::addNew()
{
}

bool EstimacionesDias::edit(QVariant ID)
{
}

bool EstimacionesDias::deleteElement(QVariant ID)
{
}
