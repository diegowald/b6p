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
#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QMainWindow>
#include "planificacionesdias.h"

// For printing
#include <QTextDocument>

namespace Ui {
class CalendarWindow;
}

class CalendarWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CalendarWindow(int LoggedUser, boost::shared_ptr<PlanificacionesDias> Model, bool inPlaceEdit, bool allowSorting, QWidget *parent);

    void AllowAdd(bool status);
    void AllowEdit(bool status);
    void AllowDelete(bool status);


    ~CalendarWindow();
    void enableButtonsBasedOnAccess();
    QString getHTMLReport();
    bool printSelectedRecord(QTextDocument &textDoc);
    virtual void showEvent(QShowEvent *evt);

    void setABMButtonsVisible(bool visible);

protected:
    virtual QString getHeader();
    virtual QString getBody();

public slots:

private slots:

    void on_actionNew_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void customActionTriggered();
    void on_dataUpdated();
    void on_actionExport_triggered();
    void on_calendarDateSelected(QDate);

private:
    Ui::CalendarWindow *ui;
    boost::shared_ptr<PlanificacionesDias> model;
    bool m_InPlaceEdit;
    int m_LoggedUser;
    bool m_allowSorting;
};

#endif // CALENDARWINDOW_H
