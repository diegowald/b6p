#ifndef PLANIFICACIONITEMWIDGET_H
#define PLANIFICACIONITEMWIDGET_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "timeassignmentitemedit.h"
#include <QWidget>

class PlanificacionItemWidget : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    explicit PlanificacionItemWidget(TimeAssignmentItemEdit *timeItem, QTreeWidget *parent = 0);

signals:

public slots:
    void onEmployeeChanged(const QString &empleado);
    void onSectorChanged(const QString &sector);
    void onSubsectorChanged(const QString &subSector);
};

#endif // PLANIFICACIONITEMWIDGET_H
