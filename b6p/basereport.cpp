#include "basereport.h"
#include "QsLog.h"

BaseReport::BaseReport(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent) :
    ACollection(Name, InvariableName, useLastInsertId, MergeStrategy, parent)
{
    QLOG_TRACE_FN();
}

BaseReport::~BaseReport()
{
    QLOG_TRACE_FN();
}


QString BaseReport::getSqlString()
{
    QLOG_TRACE_FN();
    return "";
}

void BaseReport::addRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

void BaseReport::updateRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

void BaseReport::deleteRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

bool BaseReport::exists(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::localRecordIsEqualsTo(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::isRecordUnsent(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

RecordPtr BaseReport::getLocalRecord(RecordPtr)
{
    QLOG_TRACE_FN();
    return RecordPtr();
}

QStringList BaseReport::getFieldsToShowInMerge()
{
    QLOG_TRACE_FN();
    return QStringList();
}

bool BaseReport::printSelectedRecord(QVariant IDElement, QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    return false;
}


boost::shared_ptr<QList<QStringList> > BaseReport::getAll()
{
    QLOG_TRACE_FN();
}

bool BaseReport::addNew()
{
    QLOG_TRACE_FN();
}

bool BaseReport::addNew(QTreeWidgetItem *)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::addNewWithAdditionalData(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::edit(QVariant ID)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::edit(QTreeWidgetItem *, QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

void BaseReport::refreshID(int, int)
{
    QLOG_TRACE_FN();
}

void BaseReport::saveDependants()
{
    QLOG_TRACE_FN();
}

void BaseReport::setStatusToUnmodified(bool, bool, bool)
{
    QLOG_TRACE_FN();
}

bool BaseReport::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
}

QString BaseReport::getTableName()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return "";
}

RecordSet BaseReport::getRecords(RecordStatus, bool)
{
    QLOG_TRACE_FN();
    return RecordSet();
}

RecordSet BaseReport::getUnsent()
{
    QLOG_TRACE_FN();
    return RecordSet();
}

QString BaseReport::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return "";
}

boost::shared_ptr<QList<QAction*> > BaseReport::getActions()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QAction*> >actions = boost::make_shared<QList<QAction*> >();

    QAction* action = new QAction(tr("Filter..."), NULL);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/magnet"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon);
    connect(action, SIGNAL(triggered()), this, SLOT(filter()));
    actions->push_back(action);

/*    action = new QAction(tr("Approve"), NULL);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon2);
    connect(action, SIGNAL(triggered()), this, SLOT(approveSelected()));
    actions->push_back(action);*/

    return actions;
}


void BaseReport::filter()
{
    QLOG_TRACE_FN();
    Q_ASSERT(1 == 0);
}
