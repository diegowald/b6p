/********************************************************************************
** Form generated from reading UI file 'dlglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOGIN_H
#define UI_DLGLOGIN_H

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

class Ui_DlgLogin
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *cboUsers;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgLogin)
    {
        if (DlgLogin->objectName().isEmpty())
            DlgLogin->setObjectName(QStringLiteral("DlgLogin"));
        DlgLogin->resize(194, 88);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/employees"), QSize(), QIcon::Normal, QIcon::Off);
        DlgLogin->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgLogin);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(DlgLogin);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        cboUsers = new QComboBox(DlgLogin);
        cboUsers->setObjectName(QStringLiteral("cboUsers"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboUsers);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DlgLogin);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgLogin);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgLogin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgLogin, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgLogin);
    } // setupUi

    void retranslateUi(QDialog *DlgLogin)
    {
        DlgLogin->setWindowTitle(QApplication::translate("DlgLogin", "Dialog", 0));
        label->setText(QApplication::translate("DlgLogin", "Select User", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgLogin: public Ui_DlgLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOGIN_H
