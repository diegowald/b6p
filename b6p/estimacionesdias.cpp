#include "estimacionesdias.h"
#include "dlgestimaciondia.h"
#include "dlgaddmanyestimationdays.h"
#include "dlgapproveplanifications.h"
#include "datastore.h"
#include <QsLog.h>

EstimacionesDias::EstimacionesDias(QObject *parent)
    : ACollection(tr("Day Estimations"),
                  "Day Estimations",false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE() << "EstimacionesDias::EstimacionesDias(QObject *parent)";
}

QString EstimacionesDias::getSelectFromMainDB()
{
    QLOG_TRACE() << "QString EstimacionesDias::getSelectFromMainDB()";
    return QString("select Dia, HorasEstimadas, LastUpdate from planificaciondias "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString EstimacionesDias::getSqlString()
{
    QLOG_TRACE() << "QString EstimacionesDias::getSqlString()";
    return QString("select Dia, HorasEstimadas, sent from planificaciondias ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString EstimacionesDias::getSQLExistsInMainDB()
{
    QLOG_TRACE() << "QString EstimacionesDias::getSQLExistsInMainDB()";
    return QString("select Dia, HorasEstimadas from planificaciondias ")
            + QString(" where Dia = :Dia;");
}

void EstimacionesDias::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE() << "void EstimacionesDias::addRecord(RecordPtr record, bool setNew)";
    EstimacionDiaPtr e = boost::make_shared<EstimacionDia>(this);
    e->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    e->EstimacionHoras().setValue((*record)["HorasEstimadas"].toInt());
    e->setSentStatus((*record)["sent"].toInt() == 1);

    if (setNew)
        e->setNew();
    else
        e->setInitialized();

    m_Estimaciones[e->Dia().value()] = e;
}

void EstimacionesDias::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE() << "void EstimacionesDias::updateRecord(RecordPtr record)";
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    e->EstimacionHoras().setValue((*record)["HorasEstimadas"].toInt());
    e->setSentStatus((*record)["sent"].toInt() == 1);
    e->setSentStatus(isFromSincro);
}

void EstimacionesDias::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE() << "void EstimacionesDias::deleteRecord(RecordPtr record)";
    m_Estimaciones.remove(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
}

bool EstimacionesDias::exists(RecordPtr record)
{
    QLOG_TRACE() << "bool EstimacionesDias::exists(RecordPtr record)";
    return (m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()] != EstimacionDiaPtr());
}

bool EstimacionesDias::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE() << "virtual bool EstimacionesDias::localRecordIsEqualsTo(RecordPtr record)";
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    if (e != EstimacionDiaPtr())
    {
        return e->isEqualsTo(record);
    }
    else
        return false;
}

bool EstimacionesDias::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE() << "bool EstimacionesDias::isRecordUnsent(RecordPtr record)";
    if (!exists(record))
        return false;
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return e->isUnSent();
}

RecordPtr EstimacionesDias::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE() << "RecordPtr EstimacionesDias::getLocalRecord(RecordPtr record)";
    if (!exists(record))
        return RecordPtr();
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return e->asRecordPtr();
}

QString EstimacionesDias::getDeleteStatement(bool)
{
    QLOG_TRACE() << "QString EstimacionesDias::getDeleteStatement()";
    return QString("update planificacionDias set RecordStatus = %1, sent = 0 where Dia = :Dia;").arg(RECORD_DELETED);
}

QString EstimacionesDias::getUpdateStatement(bool)
{
    QLOG_TRACE() << "QString EstimacionesDias::getUpdateStatement()";
    return QString("update planificaciondias set HorasEstimadas = :HorasEstimadas "
                   " , RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia;").arg(RECORD_MODIFIED);
}

QString EstimacionesDias::getInsertStatement(bool, bool)
{
    QLOG_TRACE() << "QString EstimacionesDias::getInsertStatement(bool)";
    return QString("insert into planificaciondias (Dia, HorasEstimadas, RecordStatus, sent) "
                   " values "
                   " (:Dia, :HorasEstimadas, %1, 0);").arg(RECORD_NEW);
}

RecordSet EstimacionesDias::getRecords(RecordStatus status)
{
    QLOG_TRACE() << "RecordSet EstimacionesDias::getRecords(RecordStatus status)";
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
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

RecordSet EstimacionesDias::getUnsent()
{
    QLOG_TRACE() << "RecordSet EstimacionesDias::getUnsent()";
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (e->isUnSent())
            res->push_back(e->asRecordPtr());
    }
    return res;
}

void EstimacionesDias::setSentFlagIntoMemory()
{
    QLOG_TRACE() << "void EstimacionesDias::setSentFlagIntoMemory()";
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        e->setSentStatus(true);
    }
}

boost::shared_ptr<QList<QAction*> > EstimacionesDias::getActions()
{
    QLOG_TRACE() << "boost::shared_ptr<QList<QAction*> > EstimacionesDias::getActions()";
    boost::shared_ptr<QList<QAction*> >actions = boost::make_shared<QList<QAction*> >();

    QAction* action = new QAction(tr("Add Range"), NULL);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/calendar"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon);
    connect(action, SIGNAL(triggered()), this, SLOT(addManyDays()));
    actions->push_back(action);

    action = new QAction(tr("Approve"), NULL);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon2);
    connect(action, SIGNAL(triggered()), this, SLOT(approveSelected()));
    actions->push_back(action);

    return actions;
}

void EstimacionesDias::defineHeaders(QStringList &list)
{
    QLOG_TRACE() << "void EstimacionesDias::defineHeaders(QStringList &list)";
    list << tr("Date") << tr("Hours estimation") << tr("Planned");
}

boost::shared_ptr<QList<QStringList> > EstimacionesDias::getAll()
{
    QLOG_TRACE() << "boost::shared_ptr<QList<QStringList> > EstimacionesDias::getAll()";
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    EstimacionDiaLst lst = getAll(false);

    foreach(EstimacionDiaPtr e, *lst)
    {
        QStringList r;
        r << e->Dia().value().toString()
          << QString::number(e->EstimacionHoras().value())
          << (e->isPlanned() ? tr("Planned") : tr("Not Planned"));
        res->push_back(r);
    }

    return res;
}

bool EstimacionesDias::isColumnEditable(QVariant ID, int column)
{
    QLOG_TRACE() << "bool EstimacionesDias::isColumnEditable(QVariant ID, int column)";
    EstimacionDiaPtr ptr = m_Estimaciones[ID.toDate()];
    return ((column == 1) && (!ptr->isPlanned()));
}

void EstimacionesDias::fillData(QTreeWidget &tree)
{
    QLOG_TRACE() << "void EstimacionesDias::fillData(QTreeWidget &tree)";
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
    QLOG_TRACE() << "bool EstimacionesDias::addNew(QTreeWidgetItem *item)";
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(item, id);
}

bool EstimacionesDias::addNew()
{
    QLOG_TRACE() << "bool EstimacionesDias::addNew()";
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(id);
}

bool EstimacionesDias::edit(QTreeWidgetItem *item, QVariant ID)
{
    QLOG_TRACE() << "bool EstimacionesDias::edit(QTreeWidgetItem *item, QVariant ID)";
    EstimacionDiaPtr e = m_Estimaciones[ID.toDate()];
    e->EstimacionHoras().setValue(item->text(1).toInt());
    return true;
}

bool EstimacionesDias::edit(QVariant ID)
{
    QLOG_TRACE() << "bool EstimacionesDias::edit(QVariant ID)";
    EstimacionDiaPtr e;
    if (ID == QDateTime::fromMSecsSinceEpoch(0).date())
        e = boost::make_shared<EstimacionDia>(this);
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
    QLOG_TRACE() << "bool EstimacionesDias::deleteElement(QVariant ID)";
    bool result = false;
    if (m_Estimaciones.find(ID.toDate()) != m_Estimaciones.end())
    {
        m_Estimaciones[ID.toDate()]->setDeleted();
        result = true;
    }
    return result;
}

bool EstimacionesDias::canBeDeleted(QVariant ID)
{
    QLOG_TRACE() << "bool EstimacionesDias::canBeDeleted(QVariant ID)";
    bool result = false;
    if (m_Estimaciones.find(ID.toDate()) != m_Estimaciones.end())
        result = m_Estimaciones[ID.toDate()]->canBeDeleted();
    return result;
}

void EstimacionesDias::refreshID(int, int)
{
    QLOG_TRACE() << "void EstimacionesDias::refreshID(int, int)";
}

EstimacionDiaLst EstimacionesDias::getAll(bool includeDeleted)
{
    QLOG_TRACE() << "EstimacionDiaLst EstimacionesDias::getAll(bool includeDeleted)";
    EstimacionDiaLst res = boost::make_shared<QList<EstimacionDiaPtr> >();

    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (!e->isDeleted())
            res->push_back(e);
        else
            if (includeDeleted)
                res->push_back(e);
    }

    return res;
}

EstimacionDiaLst EstimacionesDias::getUnplanned(bool includeDeleted)
{
    QLOG_TRACE() << "EstimacionDiaLst EstimacionesDias::getUnplanned(bool includeDeleted)";
    EstimacionDiaLst res = boost::make_shared<QList<EstimacionDiaPtr> >();

    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (!e->isPlanned())
        {
            if (!e->isDeleted())
                res->push_back(e);
            else
                if (includeDeleted)
                    res->push_back(e);
        }
    }

    return res;
}

EstimacionDiaPtr EstimacionesDias::get(QDate dia, bool includeDeleted)
{
    QLOG_TRACE() << "EstimacionDiaPtr EstimacionesDias::get(QDate dia, bool includeDeleted)";
    if (m_Estimaciones.find(dia) == m_Estimaciones.end())
        return EstimacionDiaPtr();
    else
    {
        EstimacionDiaPtr e = m_Estimaciones[dia];
        if (!e->isDeleted())
            return e;
        else
        {
            if (includeDeleted)
                return e;
            else
                return EstimacionDiaPtr();
        }
    }
}

void EstimacionesDias::setStatusToUnmodified(bool removeDeleted)
{
    QLOG_TRACE() << "void EstimacionesDias::setStatusToUnmodified(bool removeDeleted)";
    QList<QDate> toDelete;
    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (removeDeleted && e->isDeleted())
            toDelete.push_back(e->Dia().value());
        else
            e->setUnmodified();
    }
    foreach(QDate dt, toDelete)
    {
        m_Estimaciones.remove(dt);
    }
}

void EstimacionesDias::addManyDays()
{
    QLOG_TRACE() << "void EstimacionesDias::addManyDays()";
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
        save();
    }
}

void EstimacionesDias::approveSelected()
{
    QLOG_TRACE() << "void EstimacionesDias::approveSelected()";
    DlgApprovePlanifications dlg;
    dlg.setData(DataStore::instance()->getPlanificacionesDias()->getAllReadyForApproval());
    if (dlg.exec() == QDialog::Accepted)
    {
        PlanificacionDiaLst lst = dlg.getPlanificacionToApprove();

        foreach(PlanificacionDiaPtr p, *lst)
        {
            p->approve();
        }

        DataStore::instance()->getPlanificacionesDias()->save();
    }
}
