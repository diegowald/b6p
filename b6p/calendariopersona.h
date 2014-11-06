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
#ifndef CALENDARIOPERSONA_H
#define CALENDARIOPERSONA_H

#include <QObject>
#include <QSharedPointer>
#include "nullablefield.h"

class CalendarioPersona;
typedef QSharedPointer<CalendarioPersona> CalendarioPersonaPtr;
typedef QSharedPointer<QList<CalendarioPersonaPtr> > CalendarioPersonaLst;


class CalendarioPersona : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit CalendarioPersona(QObject *parent = 0);
    
    NullableField<int>& Dia();
    NullableField<int>& IDEmpleado();
    NullableField<int>& HoraIngreso1();
    NullableField<int>& HoraEgreso1();
    NullableField<int>& HoraIngreso2();
    NullableField<int>& HoraEgreso2();

    virtual RecordPtr asRecordPtr();
    virtual bool isEqualsTo(RecordPtr record);
    bool EqualsTo(CalendarioPersonaPtr other);
    void updateWith(CalendarioPersonaPtr other);

    void updateIDEmpleado(int newId);
    bool canWork(int Dia, int HoraInicio, int HoraFin);
    bool canWork(int Dia);

    int cantWorkingHours();

signals:
    
public slots:
    
private:
    NullableField<int> m_Dia;
    NullableField<int> m_IDEmpleado;
    NullableField<int> m_HoraIngreso1;
    NullableField<int> m_HoraEgreso1;
    NullableField<int> m_HoraIngreso2;
    NullableField<int> m_HoraEgreso2;
};

#endif // CALENDARIOPERSONA_H
