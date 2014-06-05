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
#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "accesos.h"
#include "empleados.h"
#include "parametros.h"
#include "estimacionesdias.h"
#include "planificacionesdias.h"
#include "planificacionesdiassubsectores.h"
#include "sectores.h"
#include "subsectores.h"
#include "calendariopersonas.h"
#include "capacidadespersonasector.h"
#include "licenciasempleados.h"
#include "reportehorassectorsubsector.h"
#include "reportehorasdiaadia.h"
#include "reportehorasporempleado.h"
#include "reportefrancosplanificados.h"

class DataStore : public QObject
{
    Q_OBJECT
public:
    virtual ~DataStore();
    static DataStore* instance();
    void initialize(QObject *parent);

    AccesosPtr getAccesos();
    ParametrosPtr getParametros();
    EmpleadosPtr getEmpleados();
    EstimacionesDiasPtr getEstimacionesDias();
    PlanificacionesDiasPtr getPlanificacionesDias();
    PlanificacionesSubSectoresPtr getPlanificacionesSubSectores();
    SectoresPtr getSectores();
    SubSectoresPtr getSubSectores();
    CalendarioPersonasPtr getCalendarios();
    CapacidadesPersonaSectorPtr getCapacidades();
    LicenciasEmpleadosPtr getLicencias();
    ReporteHorasSectorSubSectorPtr getReporteHorasSectorSubSector();
    ReporteHorasDiaADiaPtr getReporteHorasDiaADia();
    ReporteHorasPorEmpleadoPtr getReporteHorasPorEmpleado();
    ReporteFrancosPlanificadosPtr getReporteFrancosPlanificados();

    void refreshData();

protected:
    explicit DataStore(QObject *parent = 0);
    
signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);

public slots:
    
protected:
    void establishConnections(ACollection *newMember);

private:

    AccesosPtr accessosPtr;
    ParametrosPtr parametrosPtr;
    EmpleadosPtr empleadosPtr;
    EstimacionesDiasPtr estimacionesDiasPtr;
    PlanificacionesDiasPtr planificacionesDiasPtr;
    PlanificacionesSubSectoresPtr planificacionesSubSectoresPtr;
    SectoresPtr sectoresPtr;
    SubSectoresPtr subSectoresPtr;
    CalendarioPersonasPtr calendariosPtr;
    CapacidadesPersonaSectorPtr capacidadesPtr;
    LicenciasEmpleadosPtr licenciasEmpleadosPtr;
    ReporteHorasSectorSubSectorPtr reporteHorasSectorSubSectorPtr;
    ReporteHorasDiaADiaPtr reporteHorasDiaADiaPtr;
    ReporteHorasPorEmpleadoPtr reporteHorasPorEmpleadoPtr;
    ReporteFrancosPlanificadosPtr reporteFrancosPlanificadosPtr;

    bool accesosCreated;
    bool parametrosCreated;
    bool empleadosCreated;
    bool estimacionesDiasCreated;
    bool planificacionesDiasCreated;
    bool planificacionesSubSectoresCreated;
    bool sectoresCreated;
    bool subSectoresCreated;
    bool calendariosCreated;
    bool capacidadesCreated;
    bool licenciasEmpleadosCreated;
    bool reporteHorasSectorSubSectorCreated;
    bool reporteHorasDiaADiaCreated;
    bool reporteHorasPorEmpleadoCreated;
    bool reporteFrancosPlanificadosCreated;

    static DataStore* m_Instance;
};

#endif // DATASTORE_H
