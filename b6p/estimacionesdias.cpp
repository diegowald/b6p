#include "estimacionesdias.h"
#include "dlgestimaciondia.h"

EstimacionesDias::EstimacionesDias(QObject *parent)
    : ACollection(tr("Day Estimations"), false, parent)
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
    return "insert into planificaciondias (Dia, HorasEstimadas) "
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
    list << tr("Date") << tr("Hours estimation") << tr("Planned");
}

void EstimacionesDias::fillData(QTreeWidget &tree)
{
    tree.clear();
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, e->Dia().value().toString(Qt::TextDate));
        item->setData(0, Qt::UserRole, e->Dia().value());
        item->setText(1, QString::number(e->EstimacionHoras().value()));
        item->setText(2, e->isPlanned() ? tr("Yes") : tr("No"));
        tree.insertTopLevelItem(0, item);
    }
}

bool EstimacionesDias::addNew()
{
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(id);
}

bool EstimacionesDias::edit(QVariant ID)
{
    EstimacionDiaPtr e;
    if (ID == QDateTime::fromMSecsSinceEpoch(0).date())
        e = EstimacionDiaPtr(new EstimacionDia(this));
    else
        e = m_Estimaciones[ID.toDate()];

    DlgEstimacionDia dlg;
    dlg.setData(e);
    if (dlg.exec() == QDialog::Accepted)
    {
        e->Dia().setValue(dlg.Dia());
        e->EstimacionHoras().setValue(dlg.EstimacionHoras());
        m_Estimaciones[e->Dia().value()] = e;
        return true;
    }
    return false;
}

bool EstimacionesDias::deleteElement(QVariant ID)
{
}

void EstimacionesDias::refreshID(int newRecordId)
{
}

EstimacionDiaLst EstimacionesDias::getAll()
{
    EstimacionDiaLst res(new QList<EstimacionDiaPtr>());

    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        res->push_back(e);
    }

    return res;
}

EstimacionDiaPtr EstimacionesDias::get(QDate dia)
{
    if (m_Estimaciones.find(dia) == m_Estimaciones.end())
        return EstimacionDiaPtr();
    else
        return m_Estimaciones[dia];
}
