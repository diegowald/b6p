/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "CalendarWindow.h"
#include "ui_CalendarWindow.h"
#include "datastore.h"
#include <QFileDialog>
#include <QsLog.h>

CalendarWindow::CalendarWindow(int LoggedUser, boost::shared_ptr<PlanificacionesDias> Model, bool inPlaceEdit, bool allowSorting, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalendarWindow)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);

    m_LoggedUser = LoggedUser;
    model = Model;
    ui->calendar->setDataModel(model);

    boost::shared_ptr<QList<QAction *> > customActions = model->getActions();
    addActions(*customActions);
    foreach(QAction *action, *customActions)
    {
        action->setParent(this);
        ui->toolBar->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(customActionTriggered()));
    }
    m_allowSorting = allowSorting;
    on_dataUpdated();
    setWindowTitle(Model->name());
    m_InPlaceEdit = inPlaceEdit;
    connect(model.get(), SIGNAL(dataUpdated()), this, SLOT(on_dataUpdated()));
    enableButtonsBasedOnAccess();
}

CalendarWindow::~CalendarWindow()
{
    QLOG_TRACE_FN();
    delete ui;
}

void CalendarWindow::on_actionNew_triggered()
{
    QLOG_TRACE_FN();
    bool result = false;
    //QTreeWidgetItem *item = new QTreeWidgetItem();
    /*if (m_InPlaceEdit)
    {
        ui->treeList->insertTopLevelItem(0, item);
        result = model->addNewRecord(item);
    }
    else*/
        result = model->addNewRecord();

    if (result)
    {
        /*ui->treeList->clear();*/
        /*model->fillData(*ui->treeList);*/
    }
}

void CalendarWindow::on_actionEdit_triggered()
{
    QLOG_TRACE_FN();
    bool result = false;

    //if (ui->treeList->currentItem())
    //{
        /*if (m_InPlaceEdit)
            result = model->editRecord(ui->treeList->currentItem(), ui->treeList->currentItem()->data(0, Qt::UserRole));
        else*/
            result =  model->editRecord(ui->calendar->selectedDate());// ui->treeList->currentItem()->data(0, Qt::UserRole));
        if (result)
        {
            //ui->treeList->clear();
            //model->fillData(*ui->treeList);
        }
    //}
}

void CalendarWindow::on_actionDelete_triggered()
{
    QLOG_TRACE_FN();
    //if (ui->treeList->currentItem())
    QVariant v;
    v.setValue(ui->calendar->selectedDate());
        if (model->deleteElement(v))
        {
            //ui->treeList->clear();
            //model->fillData(*ui->treeList);
        }
}

void CalendarWindow::AllowAdd(bool status)
{
    QLOG_TRACE_FN();
    ui->actionNew->setVisible(status);
}

void CalendarWindow::AllowEdit(bool status)
{
    QLOG_TRACE_FN();
    ui->actionEdit->setVisible(status);
}

void CalendarWindow::AllowDelete(bool status)
{
    QLOG_TRACE_FN();
    ui->actionDelete->setVisible(status);
}

void CalendarWindow::on_treeList_doubleClicked(const QModelIndex &)
{
    QLOG_TRACE_FN();
    on_actionEdit_triggered();
}

void CalendarWindow::on_treeList_itemClicked(QTreeWidgetItem *item, int column)
{
/*    QLOG_TRACE_FN();
    if (m_InPlaceEdit && model->isColumnEditable(item->data(0, Qt::UserRole), column))
        ui->treeList->editItem(item, column);*/
}

void CalendarWindow::on_treeList_itemChanged(QTreeWidgetItem *item, int)
{
/*    QLOG_TRACE_FN();
    if (m_InPlaceEdit)
    {
        if (model->editRecord(item, ui->treeList->currentItem()->data(0, Qt::UserRole)))
        {
            model->fillData(*ui->treeList);
        }
    }*/
}


void CalendarWindow::customActionTriggered()
{
    QLOG_TRACE_FN();
//    model->fillData(*ui->treeList);
}

void CalendarWindow::on_dataUpdated()
{
    QLOG_TRACE_FN();
//    ui->treeList->setSortingEnabled(false);
//    ui->treeList->clear();
//    model->fillData(*ui->treeList);
/*    for (int i = 0; i < ui->treeList->columnCount(); i++)
        ui->treeList->resizeColumnToContents(i);
    if (m_allowSorting)
    {
        ui->treeList->setSortingEnabled(true);
        ui->treeList->sortByColumn(0, Qt::AscendingOrder);
    }*/
}

void CalendarWindow::on_actionExport_triggered()
{
    QLOG_TRACE_FN();
    QFileDialog dlg(this);

    QString suggestedName = model->suggestedFileName();

    QString filename =
            QFileDialog::getSaveFileName(this, tr("Export to..."),
                                         "./" + suggestedName,
                                         tr("CSV Files (*.csv)"));

    if (filename.size() > 0)
        model->exportTo(filename);
}

void CalendarWindow::enableButtonsBasedOnAccess()
{
    QLOG_TRACE_FN();
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


QString CalendarWindow::getHTMLReport()
{
    QLOG_TRACE_FN();
    QString res(getHeader());
    res += getBody();
    return res;
}

bool CalendarWindow::printSelectedRecord(QTextDocument &textDoc)
{    
    QLOG_TRACE_FN();
//    if (ui->treeList->currentItem())
//        return model->printSelectedRecord(ui->treeList->currentItem()->data(0, Qt::UserRole), textDoc);
//    else
        return false;
}

QString CalendarWindow::getHeader() {
    QLOG_TRACE_FN();
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

QString CalendarWindow::getBody() {
    QLOG_TRACE_FN();
    return model->asHTML();
}

void CalendarWindow::showEvent(QShowEvent *evt)
{
    QLOG_TRACE_FN();
    QMainWindow::showEvent(evt);
//    for (int i = 0; i < ui->treeList->columnCount(); i++)
//        ui->treeList->resizeColumnToContents(i);
}

void CalendarWindow::setABMButtonsVisible(bool visible)
{
    QLOG_TRACE_FN();
    ui->actionDelete->setVisible(visible);
    ui->actionEdit->setVisible(visible);
    ui->actionNew->setVisible(visible);
}
