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
    model->fillData(*ui->treeList);
}

GenericList::~GenericList()
{
    delete ui;
}

void GenericList::setHeader(QStringList &headers)
{
    ui->treeList->clear();
    ui->treeList->setHeaderLabels(headers);
}


void GenericList::on_actionNew_triggered()
{
    if (model->addNewRecord())
        model->fillData(*ui->treeList);
}

void GenericList::on_actionEdit_triggered()
{
    if (ui->treeList->currentItem())
    {
        if (model->editRecord(ui->treeList->currentItem()->data(0, Qt::UserRole)))
            model->fillData(*ui->treeList);
    }
}

void GenericList::on_actionDelete_triggered()
{
    if (ui->treeList->currentItem())
        if (model->deleteElement(ui->treeList->currentItem()->data(0, Qt::UserRole)))
            model->fillData(*ui->treeList);
}
