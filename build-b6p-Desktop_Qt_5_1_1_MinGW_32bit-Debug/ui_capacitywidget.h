/********************************************************************************
** Form generated from reading UI file 'capacitywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPACITYWIDGET_H
#define UI_CAPACITYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CapacityWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *cboSectores;
    QComboBox *cboSubSectores;
    QLabel *lblValue;
    QSpacerItem *horizontalSpacer;
    QSlider *slideCapacity;

    void setupUi(QWidget *CapacityWidget)
    {
        if (CapacityWidget->objectName().isEmpty())
            CapacityWidget->setObjectName(QStringLiteral("CapacityWidget"));
        CapacityWidget->resize(619, 35);
        horizontalLayout = new QHBoxLayout(CapacityWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        cboSectores = new QComboBox(CapacityWidget);
        cboSectores->setObjectName(QStringLiteral("cboSectores"));
        cboSectores->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(cboSectores);

        cboSubSectores = new QComboBox(CapacityWidget);
        cboSubSectores->setObjectName(QStringLiteral("cboSubSectores"));
        cboSubSectores->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(cboSubSectores);

        lblValue = new QLabel(CapacityWidget);
        lblValue->setObjectName(QStringLiteral("lblValue"));

        horizontalLayout->addWidget(lblValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        slideCapacity = new QSlider(CapacityWidget);
        slideCapacity->setObjectName(QStringLiteral("slideCapacity"));
        slideCapacity->setMinimumSize(QSize(200, 0));
        slideCapacity->setMaximumSize(QSize(200, 16777215));
        slideCapacity->setMaximum(10);
        slideCapacity->setPageStep(3);
        slideCapacity->setOrientation(Qt::Horizontal);
        slideCapacity->setTickPosition(QSlider::TicksBelow);
        slideCapacity->setTickInterval(2);

        horizontalLayout->addWidget(slideCapacity);


        retranslateUi(CapacityWidget);

        QMetaObject::connectSlotsByName(CapacityWidget);
    } // setupUi

    void retranslateUi(QWidget *CapacityWidget)
    {
        CapacityWidget->setWindowTitle(QApplication::translate("CapacityWidget", "Form", 0));
        lblValue->setText(QApplication::translate("CapacityWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class CapacityWidget: public Ui_CapacityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPACITYWIDGET_H
