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
#ifndef DLGQUERYBUILDER_H
#define DLGQUERYBUILDER_H

#include <QDialog>

namespace Ui {
class DlgQueryBuilder;
}

class DlgQueryBuilder : public QDialog
{
    Q_OBJECT

public:
    explicit DlgQueryBuilder(QWidget *parent = 0);
    ~DlgQueryBuilder();

    void setDateFrom(const QDate& from);
    void setDateTo(const QDate& to);
    void setIDSector(int id);
    void setIDSubSector(int id);
    void setIDEmployee(int id);

    void setSummarizeDays(bool value);
    void setSummarizeSectors(bool value);
    void setSummarizeSubsectors(bool value);
    void setSummarizeEmployee(bool value);

    bool summarizeDays() const;
    bool summarizeSectors() const;
    bool summarizeSubsectors() const;
    bool summarizeEmployee() const;

    QDate dateFrom();
    QDate dateTo();
    int idSector();
    int idSubSector();
    int idEmployee();

    void setEmployeeEnabled(bool enabled);
    void setSectorEnabled(bool enabled);
    void setSubSectorEnabled(bool enabled);
    void setDateEnabled(bool enabled);

private slots:
    void on_cboSector_currentIndexChanged(int index);

private:
    void fillSectores();
    void fillSubSectores(int IDSector);
    void fillEmployees();

private:
    Ui::DlgQueryBuilder *ui;
};

#endif // DLGQUERYBUILDER_H
