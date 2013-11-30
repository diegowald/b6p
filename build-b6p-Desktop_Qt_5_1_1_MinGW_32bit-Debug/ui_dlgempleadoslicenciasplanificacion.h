/********************************************************************************
** Form generated from reading UI file 'dlgempleadoslicenciasplanificacion.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEMPLEADOSLICENCIASPLANIFICACION_H
#define UI_DLGEMPLEADOSLICENCIASPLANIFICACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgEmpleadosLicenciasPlanificacion
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnAdd_2;
    QToolButton *btnEdit_2;
    QToolButton *btnDelete_2;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgEmpleadosLicenciasPlanificacion)
    {
        if (DlgEmpleadosLicenciasPlanificacion->objectName().isEmpty())
            DlgEmpleadosLicenciasPlanificacion->setObjectName(QStringLiteral("DlgEmpleadosLicenciasPlanificacion"));
        DlgEmpleadosLicenciasPlanificacion->resize(672, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/employees"), QSize(), QIcon::Normal, QIcon::Off);
        DlgEmpleadosLicenciasPlanificacion->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgEmpleadosLicenciasPlanificacion);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        btnAdd_2 = new QToolButton(DlgEmpleadosLicenciasPlanificacion);
        btnAdd_2->setObjectName(QStringLiteral("btnAdd_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/add"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd_2->setIcon(icon1);

        gridLayout_2->addWidget(btnAdd_2, 0, 0, 1, 1);

        btnEdit_2 = new QToolButton(DlgEmpleadosLicenciasPlanificacion);
        btnEdit_2->setObjectName(QStringLiteral("btnEdit_2"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/images/glyphicons_150_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnEdit_2->setIcon(icon2);

        gridLayout_2->addWidget(btnEdit_2, 0, 1, 1, 1);

        btnDelete_2 = new QToolButton(DlgEmpleadosLicenciasPlanificacion);
        btnDelete_2->setObjectName(QStringLiteral("btnDelete_2"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/remove"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete_2->setIcon(icon3);

        gridLayout_2->addWidget(btnDelete_2, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        treeWidget = new QTreeWidget(DlgEmpleadosLicenciasPlanificacion);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        buttonBox = new QDialogButtonBox(DlgEmpleadosLicenciasPlanificacion);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgEmpleadosLicenciasPlanificacion);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgEmpleadosLicenciasPlanificacion, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgEmpleadosLicenciasPlanificacion, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgEmpleadosLicenciasPlanificacion);
    } // setupUi

    void retranslateUi(QDialog *DlgEmpleadosLicenciasPlanificacion)
    {
        DlgEmpleadosLicenciasPlanificacion->setWindowTitle(QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Available Employees", 0));
        btnAdd_2->setText(QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Add", 0));
        btnEdit_2->setText(QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Edit", 0));
        btnDelete_2->setText(QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "...", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Notes", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Type", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "To", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "From", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("DlgEmpleadosLicenciasPlanificacion", "Employee", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgEmpleadosLicenciasPlanificacion: public Ui_DlgEmpleadosLicenciasPlanificacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEMPLEADOSLICENCIASPLANIFICACION_H
