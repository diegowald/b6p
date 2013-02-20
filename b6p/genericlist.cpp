#include "genericlist.h"
#include "ui_genericlist.h"
#include <QDebug>

GenericList::GenericList(boost::shared_ptr<ACollection> Model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenericList)
{
    ui->setupUi(this);
    model = Model;
    QStringList headers;
    model->defineHeaders(headers);
    setHeader(headers);
    ui->treeList->clear();
    model->fillData(*ui->treeList);
    setWindowTitle(Model->name());
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
    if (model->addNewRecord())
    {
        ui->treeList->clear();
        model->fillData(*ui->treeList);
    }
}

void GenericList::on_actionEdit_triggered()
{
    if (ui->treeList->currentItem())
    {
        if (model->editRecord(ui->treeList->currentItem()->data(0, Qt::UserRole)))
        {
            ui->treeList->clear();
            model->fillData(*ui->treeList);
        }
    }
}

void GenericList::on_actionDelete_triggered()
{
    if (ui->treeList->currentItem())
        if (model->deleteElement(ui->treeList->currentItem()->data(0, Qt::UserRole)))
            model->fillData(*ui->treeList);
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

void GenericList::on_treeList_doubleClicked(const QModelIndex &index)
{
    on_actionEdit_triggered();
}
