/********************************************************************************
** Form generated from reading UI file 'availabilitywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVAILABILITYWIDGET_H
#define UI_AVAILABILITYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <timeassignment.h>
#include <timeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_AvailabilityWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *lblDay;
    TimeEditor *timeFrom;
    TimeEditor *timeTo;
    TimeAssignment *widget;

    void setupUi(QWidget *AvailabilityWidget)
    {
        if (AvailabilityWidget->objectName().isEmpty())
            AvailabilityWidget->setObjectName(QStringLiteral("AvailabilityWidget"));
        AvailabilityWidget->resize(471, 35);
        horizontalLayout = new QHBoxLayout(AvailabilityWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        lblDay = new QLabel(AvailabilityWidget);
        lblDay->setObjectName(QStringLiteral("lblDay"));

        horizontalLayout->addWidget(lblDay);

        timeFrom = new TimeEditor(AvailabilityWidget);
        timeFrom->setObjectName(QStringLiteral("timeFrom"));

        horizontalLayout->addWidget(timeFrom);

        timeTo = new TimeEditor(AvailabilityWidget);
        timeTo->setObjectName(QStringLiteral("timeTo"));

        horizontalLayout->addWidget(timeTo);

        widget = new TimeAssignment(AvailabilityWidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(AvailabilityWidget);

        QMetaObject::connectSlotsByName(AvailabilityWidget);
    } // setupUi

    void retranslateUi(QWidget *AvailabilityWidget)
    {
        AvailabilityWidget->setWindowTitle(QApplication::translate("AvailabilityWidget", "Form", 0));
        lblDay->setText(QApplication::translate("AvailabilityWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class AvailabilityWidget: public Ui_AvailabilityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVAILABILITYWIDGET_H
