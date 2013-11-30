/********************************************************************************
** Form generated from reading UI file 'dlgselectorbytdate.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSELECTORBYTDATE_H
#define UI_DLGSELECTORBYTDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgSelectorBytDate
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *Label;
    QComboBox *cboValues;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgSelectorBytDate)
    {
        if (DlgSelectorBytDate->objectName().isEmpty())
            DlgSelectorBytDate->setObjectName(QStringLiteral("DlgSelectorBytDate"));
        DlgSelectorBytDate->setWindowModality(Qt::ApplicationModal);
        DlgSelectorBytDate->resize(180, 70);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_119_table.png"), QSize(), QIcon::Normal, QIcon::Off);
        DlgSelectorBytDate->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgSelectorBytDate);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        Label = new QLabel(DlgSelectorBytDate);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        cboValues = new QComboBox(DlgSelectorBytDate);
        cboValues->setObjectName(QStringLiteral("cboValues"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboValues);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DlgSelectorBytDate);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgSelectorBytDate);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgSelectorBytDate, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgSelectorBytDate, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgSelectorBytDate);
    } // setupUi

    void retranslateUi(QDialog *DlgSelectorBytDate)
    {
        DlgSelectorBytDate->setWindowTitle(QApplication::translate("DlgSelectorBytDate", "Select by date.", 0));
        Label->setText(QApplication::translate("DlgSelectorBytDate", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgSelectorBytDate: public Ui_DlgSelectorBytDate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSELECTORBYTDATE_H
