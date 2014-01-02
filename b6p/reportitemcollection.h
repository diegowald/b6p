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
#ifndef REPORTITEMCOLLECTION_H
#define REPORTITEMCOLLECTION_H

#include <QObject>
#include "reportitem.h"
#include "planificacionsubsector.h"


class ReportItemCollection : public QObject
{
    Q_OBJECT
public:
    explicit ReportItemCollection(const QDate& dateFrom, const QDate& dateTo,
                                  int IDSectorFilter, int IDSubSectorFilter, int IDEmpleadoFilter,
                                  bool summarizeDays, bool summarizeSectors, bool summarizeSubSectors, bool summarizeEmployee,
                                  QObject *parent = 0);

    virtual ~ReportItemCollection();
    void addPlanificacionSubSector(PlanificacionSubSectorPtr planificacion);
    void addPlanificacionSubSector(PlanificacionSubSectorLst ListPlanificacion);

    void clear();
    void setDateFrom(const QDate& dateFrom);
    void setDateTo(const QDate& dateTo);
    void setIDEmpleado(int idEmpleado);
    void setIDSector(int idSector);
    void setIDSubSector(int idSubSector);

    void SetSummarizeDays(bool value);
    void setSummarizeSectors(bool value);
    void setSummarizeSubSectors(bool value);
    void setSummarizeEmployee(bool value);

    QDate dateFrom() const;
    QDate dateTo() const;
    int idEmpleado() const;
    int idSector() const;
    int idSubSector() const;

    bool summarizeDays() const;
    bool summarizeSectors() const;
    bool summarizeSubSectors() const;
    bool summarizeEmployee() const;


    void refresh();

    QList<ReportItemPtr> items();

private:
    QString createIndex(PlanificacionSubSectorPtr planificacion);
    bool isValid(PlanificacionSubSectorPtr planificacion);
    bool doSummarizeDays;
    bool doSummarizeSectors;
    bool doSummarizeSubsectors;
    bool doSummarizeEmployee;

signals:

public slots:

private:
    QMap<QString, ReportItemPtr> reportItems;
    int idSectorFilter;
    int idSubSectorFilter;
    int idEmpleadoFilter;
    QDate dateFromFilter;
    QDate dateToFilter;
};

typedef boost::shared_ptr<ReportItemCollection> ReportItemCollectionPtr;

#endif // REPORTITEMCOLLECTION_H
