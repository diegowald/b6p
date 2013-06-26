/********************************************************************************
** Form generated from reading UI file 'dlgestimaciondia.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGESTIMACIONDIA_H
#define UI_DLGESTIMACIONDIA_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgEstimacionDia
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblDate;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QLineEdit *txtEstimation;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgEstimacionDia)
    {
        if (DlgEstimacionDia->objectName().isEmpty())
            DlgEstimacionDia->setObjectName(QStringLiteral("DlgEstimacionDia"));
        DlgEstimacionDia->resize(275, 103);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_331_dashboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        DlgEstimacionDia->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgEstimacionDia);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        lblDate = new QLabel(DlgEstimacionDia);
        lblDate->setObjectName(QStringLiteral("lblDate"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblDate);

        dateEdit = new QDateEdit(DlgEstimacionDia);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, dateEdit);

        label_2 = new QLabel(DlgEstimacionDia);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        txtEstimation = new QLineEdit(DlgEstimacionDia);
        txtEstimation->setObjectName(QStringLiteral("txtEstimation"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txtEstimation);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DlgEstimacionDia);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgEstimacionDia);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgEstimacionDia, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgEstimacionDia, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgEstimacionDia);
    } // setupUi

    void retranslateUi(QDialog *DlgEstimacionDia)
    {
        DlgEstimacionDia->setWindowTitle(QApplication::translate("DlgEstimacionDia", "Day Estimation", 0));
        lblDate->setText(QApplication::translate("DlgEstimacionDia", "Date", 0));
        label_2->setText(QApplication::translate("DlgEstimacionDia", "Estimation (hours)", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgEstimacionDia: public Ui_DlgEstimacionDia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGESTIMACIONDIA_H
