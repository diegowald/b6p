/********************************************************************************
** Form generated from reading UI file 'dlgaddmanyestimationdays.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGADDMANYESTIMATIONDAYS_H
#define UI_DLGADDMANYESTIMATIONDAYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgAddManyEstimationDays
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QDateEdit *dateFrom;
    QLabel *label_2;
    QDateEdit *dateTo;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgAddManyEstimationDays)
    {
        if (DlgAddManyEstimationDays->objectName().isEmpty())
            DlgAddManyEstimationDays->setObjectName(QStringLiteral("DlgAddManyEstimationDays"));
        DlgAddManyEstimationDays->resize(194, 125);
        verticalLayout = new QVBoxLayout(DlgAddManyEstimationDays);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(DlgAddManyEstimationDays);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        dateFrom = new QDateEdit(DlgAddManyEstimationDays);
        dateFrom->setObjectName(QStringLiteral("dateFrom"));

        formLayout->setWidget(0, QFormLayout::FieldRole, dateFrom);

        label_2 = new QLabel(DlgAddManyEstimationDays);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        dateTo = new QDateEdit(DlgAddManyEstimationDays);
        dateTo->setObjectName(QStringLiteral("dateTo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, dateTo);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DlgAddManyEstimationDays);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgAddManyEstimationDays);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgAddManyEstimationDays, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgAddManyEstimationDays, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgAddManyEstimationDays);
    } // setupUi

    void retranslateUi(QDialog *DlgAddManyEstimationDays)
    {
        DlgAddManyEstimationDays->setWindowTitle(QApplication::translate("DlgAddManyEstimationDays", "Dialog", 0));
        label->setText(QApplication::translate("DlgAddManyEstimationDays", "From", 0));
        label_2->setText(QApplication::translate("DlgAddManyEstimationDays", "To", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgAddManyEstimationDays: public Ui_DlgAddManyEstimationDays {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGADDMANYESTIMATIONDAYS_H
