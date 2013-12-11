/********************************************************************************
** Form generated from reading UI file 'dlglicencia.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLICENCIA_H
#define UI_DLGLICENCIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DlgLicencia
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *lblEmployee;
    QLabel *label_3;
    QDateEdit *dateFrom;
    QLabel *label_4;
    QDateEdit *dateTo;
    QLabel *label_5;
    QComboBox *cboType;
    QLabel *label_6;
    QLineEdit *txtNotes;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgLicencia)
    {
        if (DlgLicencia->objectName().isEmpty())
            DlgLicencia->setObjectName(QStringLiteral("DlgLicencia"));
        DlgLicencia->resize(400, 150);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/calendar"), QSize(), QIcon::Normal, QIcon::Off);
        DlgLicencia->setWindowIcon(icon);
        formLayout = new QFormLayout(DlgLicencia);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        formLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(DlgLicencia);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lblEmployee = new QLabel(DlgLicencia);
        lblEmployee->setObjectName(QStringLiteral("lblEmployee"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblEmployee);

        label_3 = new QLabel(DlgLicencia);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        dateFrom = new QDateEdit(DlgLicencia);
        dateFrom->setObjectName(QStringLiteral("dateFrom"));

        formLayout->setWidget(1, QFormLayout::FieldRole, dateFrom);

        label_4 = new QLabel(DlgLicencia);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        dateTo = new QDateEdit(DlgLicencia);
        dateTo->setObjectName(QStringLiteral("dateTo"));

        formLayout->setWidget(2, QFormLayout::FieldRole, dateTo);

        label_5 = new QLabel(DlgLicencia);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        cboType = new QComboBox(DlgLicencia);
        cboType->setObjectName(QStringLiteral("cboType"));
        cboType->setEditable(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, cboType);

        label_6 = new QLabel(DlgLicencia);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        txtNotes = new QLineEdit(DlgLicencia);
        txtNotes->setObjectName(QStringLiteral("txtNotes"));

        formLayout->setWidget(4, QFormLayout::FieldRole, txtNotes);

        buttonBox = new QDialogButtonBox(DlgLicencia);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(5, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(DlgLicencia);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgLicencia, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgLicencia, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgLicencia);
    } // setupUi

    void retranslateUi(QDialog *DlgLicencia)
    {
        DlgLicencia->setWindowTitle(QApplication::translate("DlgLicencia", "Dialog", 0));
        label->setText(QApplication::translate("DlgLicencia", "Employee", 0));
        lblEmployee->setText(QApplication::translate("DlgLicencia", "TextLabel", 0));
        label_3->setText(QApplication::translate("DlgLicencia", "From", 0));
        label_4->setText(QApplication::translate("DlgLicencia", "To", 0));
        label_5->setText(QApplication::translate("DlgLicencia", "Type", 0));
        label_6->setText(QApplication::translate("DlgLicencia", "Notes", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgLicencia: public Ui_DlgLicencia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLICENCIA_H
