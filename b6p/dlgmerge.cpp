#include "dlgmerge.h"
#include "ui_dlgmerge.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>

DlgMerge::DlgMerge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgMerge)
{
    QLOG_TRACE() << "DlgMerge::DlgMerge(QWidget *parent)";
    ui->setupUi(this);
}

DlgMerge::~DlgMerge()
{
    QLOG_TRACE() << "DlgMerge::~DlgMerge()";
    delete ui;
}

void DlgMerge::setData(RecordPtr ServerRecord, RecordPtr localRecord, QStringList fieldsToShow)
{
    QLOG_TRACE() << "void DlgMerge::setData(RecordPtr ServerRecord, RecordPtr localRecord, QStringList fieldsToShow)";
    local = localRecord;
    server = ServerRecord;
    foreach (QString key, ServerRecord->keys()) {
        if (fieldsToShow.contains(key)) {
            int rowNum = ui->tblData->rowCount();
            ui->tblData->insertRow(rowNum);

            // Field name
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setText(key);
            ui->tblData->setItem(rowNum, 0, item);

            // Server data
            item = new QTableWidgetItem();
            item->setText((*ServerRecord)[key].toString());
            ui->tblData->setItem(rowNum, 1, item);

            // Local data
            item = new QTableWidgetItem();
            item->setText((*localRecord)[key].toString());
            ui->tblData->setItem(rowNum, 2, item);

            // Merged data (default = local data)
            item = new QTableWidgetItem();
            item->setText((*localRecord)[key].toString());
            ui->tblData->setItem(rowNum, 3, item);
        }
    }
}

RecordPtr DlgMerge::mergedRecord()
{
    QLOG_TRACE() << "RecordPtr DlgMerge::mergedRecord()";
    RecordPtr result = boost::make_shared<Record>();

    foreach (QString key, server->keys()) {
        (*result)[key] = (*server)[key];
    }

    for (int row = 1; row < ui->tblData->rowCount(); ++row) {
        QString key = ui->tblData->item(row, 0)->text();

        if (ui->tblData->item(row, 1)->text() == ui->tblData->item(row, 3)->text())
            (*result)[key] = (*server)[key];
        else
            (*result)[key] = (*local)[key];

        qDebug() << key;
        qDebug() << (*server)[key];
        qDebug() << (*local)[key];

        qDebug() << (*result)[key];
    }

    return result;
}

void DlgMerge::on_tblData_cellClicked(int row, int column)
{
    QLOG_TRACE() << "void DlgMerge::on_tblData_cellClicked(int row, int column)";
    if ((column == 1) || (column == 2))
    {
        ui->tblData->item(row, 3)->setText(ui->tblData->item(row, column)->text());
    }
}
