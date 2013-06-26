/********************************************************************************
** Form generated from reading UI file 'timeassignmentitemedit.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEASSIGNMENTITEMEDIT_H
#define UI_TIMEASSIGNMENTITEMEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <timeassignment.h>
#include <timeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_TimeAssignmentItemEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *cboSectores;
    QComboBox *cboSubsectores;
    TimeEditor *timeInicio;
    TimeEditor *timeFin;
    QComboBox *cboEmpleado;
    TimeAssignment *widget;

    void setupUi(QWidget *TimeAssignmentItemEdit)
    {
        if (TimeAssignmentItemEdit->objectName().isEmpty())
            TimeAssignmentItemEdit->setObjectName(QStringLiteral("TimeAssignmentItemEdit"));
        TimeAssignmentItemEdit->resize(915, 49);
        horizontalLayout = new QHBoxLayout(TimeAssignmentItemEdit);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        cboSectores = new QComboBox(TimeAssignmentItemEdit);
        cboSectores->setObjectName(QStringLiteral("cboSectores"));

        horizontalLayout->addWidget(cboSectores);

        cboSubsectores = new QComboBox(TimeAssignmentItemEdit);
        cboSubsectores->setObjectName(QStringLiteral("cboSubsectores"));

        horizontalLayout->addWidget(cboSubsectores);

        timeInicio = new TimeEditor(TimeAssignmentItemEdit);
        timeInicio->setObjectName(QStringLiteral("timeInicio"));

        horizontalLayout->addWidget(timeInicio);

        timeFin = new TimeEditor(TimeAssignmentItemEdit);
        timeFin->setObjectName(QStringLiteral("timeFin"));

        horizontalLayout->addWidget(timeFin);

        cboEmpleado = new QComboBox(TimeAssignmentItemEdit);
        cboEmpleado->setObjectName(QStringLiteral("cboEmpleado"));

        horizontalLayout->addWidget(cboEmpleado);

        widget = new TimeAssignment(TimeAssignmentItemEdit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(400, 0));

        horizontalLayout->addWidget(widget);


        retranslateUi(TimeAssignmentItemEdit);

        QMetaObject::connectSlotsByName(TimeAssignmentItemEdit);
    } // setupUi

    void retranslateUi(QWidget *TimeAssignmentItemEdit)
    {
        TimeAssignmentItemEdit->setWindowTitle(QApplication::translate("TimeAssignmentItemEdit", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeAssignmentItemEdit: public Ui_TimeAssignmentItemEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEASSIGNMENTITEMEDIT_H
