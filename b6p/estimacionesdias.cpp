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
    e->Dia(NullableField<QDate>(record["Dia"].toDate()));
    e->EstimacionHoras(NullableField<int>(record["HorasEstimadas"].toInt()));
    m_Estimaciones[*e->Dia().value()] = e;
}

void EstimacionesDias::saveData()
{
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

void EstimacionesDias::edit(QVariant ID)
{
}

void EstimacionesDias::deleteElement(QVariant ID)
{
}
