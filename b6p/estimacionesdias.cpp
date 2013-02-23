#include "estimacionesdias.h"
#include "dlgestimaciondia.h"
#include "dlgaddmanyestimationdays.h"

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
    e->Dia().setValue(QDateTime::fromMSecsSinceEpoch(record["Dia"].toLongLong()).date());
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

boost::shared_ptr<QList<QAction*> > EstimacionesDias::getActions()
{
    boost::shared_ptr<QList<QAction*> >actions = boost::make_shared<QList<QAction*> >();

    QAction* action = new QAction(tr("Add Range"), NULL);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/calendar"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon);
    connect(action, SIGNAL(triggered()), this, SLOT(addManyDays()));

    actions->push_back(action);

    return actions;
}

void EstimacionesDias::defineHeaders(QStringList &list)
{
    list << tr("Date") << tr("Hours estimation") << tr("Planned");
}

bool EstimacionesDias::isColumnEditable(int column)
{
    return column == 1;
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
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
        tree.insertTopLevelItem(0, item);
    }
}

bool EstimacionesDias::addNew(QTreeWidgetItem *item)
{
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(item, id);
}

bool EstimacionesDias::addNew()
{
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(id);
}

bool EstimacionesDias::edit(QTreeWidgetItem *item, QVariant ID)
{
    EstimacionDiaPtr e = m_Estimaciones[ID.toDate()];
    e->EstimacionHoras().setValue(item->text(1).toInt());
    return true;
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
/*    bool result = false;
    if (m_Empleados.find(ID.toInt()) != m_Empleados.end())
    {
        m_Empleados[ID.toInt()]->setDeleted();
        result = true;
    }
    return result;*/
}

void EstimacionesDias::refreshID(int oldID, int newRecordId)
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

EstimacionDiaLst EstimacionesDias::getUnplanned()
{
    EstimacionDiaLst res(new QList<EstimacionDiaPtr>());

    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (!e->isPlanned())
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

void EstimacionesDias::setStatusToUnmodified()
{
    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        e->setUnmodified();
    }
}

void EstimacionesDias::addManyDays()
{
    DlgAddManyEstimationDays dlg;
    dlg.setFrom(QDate::currentDate());
    dlg.setTo(QDate::currentDate().addMonths(1));
    if (dlg.exec() == QDialog::Accepted)
    {
        QDate from = dlg.From();
        QDate To = dlg.To();
        int delta = from.daysTo(To);
        for (int i = 0; i < delta; ++i)
        {
            QDate date = from.addDays(i);
            if (m_Estimaciones.find(date) == m_Estimaciones.end())
            {
                EstimacionDiaPtr e = boost::make_shared<EstimacionDia>(true, this);
                e->Dia().setValue(date);
                m_Estimaciones[e->Dia().value()] = e;
            }
        }
    }
}
