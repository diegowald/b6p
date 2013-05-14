#include "genericlist.h"
#include "ui_genericlist.h"
#include "datastore.h"
#include <QFileDialog>

GenericList::GenericList(int LoggedUser, boost::shared_ptr<ACollection> Model, bool inPlaceEdit, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenericList)
{
    ui->setupUi(this);
    m_LoggedUser = LoggedUser;
    model = Model;
    QStringList headers;

    boost::shared_ptr<QList<QAction *> > customActions = model->getActions();
    addActions(*customActions);
    foreach(QAction *action, *customActions)
    {
        action->setParent(this);
        ui->toolBar->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(customActionTriggered()));
    }

    model->defineHeaders(headers);
    setHeader(headers);
    on_dataUpdated();
    setWindowTitle(Model->name());
    m_InPlaceEdit = inPlaceEdit;
    connect(model.get(), SIGNAL(dataUpdated()), this, SLOT(on_dataUpdated()));
    enableButtonsBasedOnAccess();
}

GenericList::~GenericList()
{
    delete ui;
}

void GenericList::setHeader(QStringList &headers)
{
    Q_ASSERT(headers.size() > 0);
    ui->treeList->clear();
    ui->treeList->setHeaderLabels(headers);
}


void GenericList::on_actionNew_triggered()
{
    bool result = false;
    QTreeWidgetItem *item = new QTreeWidgetItem();
    if (m_InPlaceEdit)
    {
        ui->treeList->insertTopLevelItem(0, item);
        result = model->addNewRecord(item);
    }
    else
        result = model->addNewRecord();

    if (result)
    {
        ui->treeList->clear();
        model->fillData(*ui->treeList);
    }
}

void GenericList::on_actionEdit_triggered()
{
    bool result = false;

    if (ui->treeList->currentItem())
    {
        if (m_InPlaceEdit)
            result = model->editRecord(ui->treeList->currentItem(), ui->treeList->currentItem()->data(0, Qt::UserRole));
        else
            result =  model->editRecord(ui->treeList->currentItem()->data(0, Qt::UserRole));
        if (result)
        {
            ui->treeList->clear();
            model->fillData(*ui->treeList);
        }
    }
}

void GenericList::on_actionDelete_triggered()
{
    if (ui->treeList->currentItem())
        if (model->deleteRecord(ui->treeList->currentItem()->data(0, Qt::UserRole)))
        {
            ui->treeList->clear();
            model->fillData(*ui->treeList);
        }
}

void GenericList::AllowAdd(bool status)
{
    ui->actionNew->setVisible(status);
}

void GenericList::AllowEdit(bool status)
{
    ui->actionEdit->setVisible(status);
}

void GenericList::AllowDelete(bool status)
{
    ui->actionDelete->setVisible(status);
}

void GenericList::on_treeList_doubleClicked(const QModelIndex &)
{
    on_actionEdit_triggered();
}

void GenericList::on_treeList_itemClicked(QTreeWidgetItem *item, int column)
{
    if (m_InPlaceEdit && model->isColumnEditable(item->data(0, Qt::UserRole), column))
        ui->treeList->editItem(item, column);
}

void GenericList::on_treeList_itemChanged(QTreeWidgetItem *item, int)
{
    if (m_InPlaceEdit)
    {
        if (model->editRecord(item, ui->treeList->currentItem()->data(0, Qt::UserRole)))
        {
            model->fillData(*ui->treeList);
        }
    }
}


void GenericList::customActionTriggered()
{
    model->fillData(*ui->treeList);
}

void GenericList::on_dataUpdated()
{
    ui->treeList->clear();
    model->fillData(*ui->treeList);
    for (int i = 0; i < ui->treeList->columnCount(); i++)
        ui->treeList->resizeColumnToContents(i);
}

void GenericList::on_actionExport_triggered()
{
    QFileDialog dlg(this);

    QString suggestedName = model->suggestedFileName();

    QString filename =
            QFileDialog::getSaveFileName(this, tr("Export to..."),
                                         "./" + suggestedName,
                                         tr("CSV Files (*.csv)"));

    if (filename.size() > 0)
        model->exportTo(filename);
}

void GenericList::enableButtonsBasedOnAccess()
{
    if (m_LoggedUser > 0)
    {
        QString feature = model->invariableName();
        ui->actionDelete->setEnabled(DataStore::instance()->getAccesos()->canDelete(m_LoggedUser, feature));
        ui->actionEdit->setEnabled(DataStore::instance()->getAccesos()->canUpdate(m_LoggedUser, feature));
        ui->actionExport->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));
        ui->actionNew->setEnabled(DataStore::instance()->getAccesos()->canCreate(m_LoggedUser, feature));
    }
    else
    {
        ui->actionDelete->setEnabled(true);
        ui->actionEdit->setEnabled(true);
        ui->actionExport->setEnabled(true);
        ui->actionNew->setEnabled(true);
    }
}


QString GenericList::getHTMLReport()
{
    QString res(getHeader());
    res += getBody();
    return res;
}

bool GenericList::printSelectedRecord(QTextDocument &textDoc)
{    
    if (ui->treeList->currentItem())
        return model->printSelectedRecord(ui->treeList->currentItem()->data(0, Qt::UserRole), textDoc);
    else
        return false;
}

QString GenericList::getHeader() {
    // Aca se arma una tabla que contiene al header
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n"
                 "<tr>"
                 "<td bgcolor=\"lightgray\"><font size=\"+1\">"    "<b><i>" + tr("Report") + model->name() + "</i></b></font>\n</td>"
                 "<td bgcolor=\"lightgray\"><font size=\"+1\">"
                 "<b><i>" + tr("Date") + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</i></b></font>\n</td>"
                 "</tr>"
                 + "\n</table>\n<br>\n");
    return html;
}

QString GenericList::getBody() {
    return model->asHTML(false);
}
