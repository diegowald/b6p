/********************************************************************************
** Form generated from reading UI file 'dlgsynchronization.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSYNCHRONIZATION_H
#define UI_DLGSYNCHRONIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgSynchronization
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *lblLastSynchronization;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *lblServerName;
    QLabel *label_7;
    QLabel *lblUser;
    QFormLayout *formLayout_3;
    QLabel *label_5;
    QLabel *lblDatabase;
    QTreeWidget *treeSyncrhonizationStatus;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStartSynchro;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgSynchronization)
    {
        if (DlgSynchronization->objectName().isEmpty())
            DlgSynchronization->setObjectName(QStringLiteral("DlgSynchronization"));
        DlgSynchronization->resize(485, 343);
        verticalLayout = new QVBoxLayout(DlgSynchronization);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        label = new QLabel(DlgSynchronization);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lblLastSynchronization = new QLabel(DlgSynchronization);
        lblLastSynchronization->setObjectName(QStringLiteral("lblLastSynchronization"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblLastSynchronization);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setHorizontalSpacing(2);
        formLayout_2->setVerticalSpacing(2);
        label_3 = new QLabel(DlgSynchronization);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        lblServerName = new QLabel(DlgSynchronization);
        lblServerName->setObjectName(QStringLiteral("lblServerName"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lblServerName);

        label_7 = new QLabel(DlgSynchronization);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_7);

        lblUser = new QLabel(DlgSynchronization);
        lblUser->setObjectName(QStringLiteral("lblUser"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lblUser);


        horizontalLayout->addLayout(formLayout_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setHorizontalSpacing(2);
        formLayout_3->setVerticalSpacing(2);
        label_5 = new QLabel(DlgSynchronization);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_5);

        lblDatabase = new QLabel(DlgSynchronization);
        lblDatabase->setObjectName(QStringLiteral("lblDatabase"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lblDatabase);


        horizontalLayout->addLayout(formLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        treeSyncrhonizationStatus = new QTreeWidget(DlgSynchronization);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Element"));
        treeSyncrhonizationStatus->setHeaderItem(__qtreewidgetitem);
        treeSyncrhonizationStatus->setObjectName(QStringLiteral("treeSyncrhonizationStatus"));
        treeSyncrhonizationStatus->header()->setDefaultSectionSize(200);
        treeSyncrhonizationStatus->header()->setMinimumSectionSize(100);

        verticalLayout->addWidget(treeSyncrhonizationStatus);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnStartSynchro = new QPushButton(DlgSynchronization);
        btnStartSynchro->setObjectName(QStringLiteral("btnStartSynchro"));

        horizontalLayout_2->addWidget(btnStartSynchro);

        buttonBox = new QDialogButtonBox(DlgSynchronization);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DlgSynchronization);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgSynchronization, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgSynchronization, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgSynchronization);
    } // setupUi

    void retranslateUi(QDialog *DlgSynchronization)
    {
        DlgSynchronization->setWindowTitle(QApplication::translate("DlgSynchronization", "Dialog", 0));
        label->setText(QApplication::translate("DlgSynchronization", "Last synchronization", 0));
        lblLastSynchronization->setText(QApplication::translate("DlgSynchronization", "TextLabel", 0));
        label_3->setText(QApplication::translate("DlgSynchronization", "Server", 0));
        lblServerName->setText(QApplication::translate("DlgSynchronization", "TextLabel", 0));
        label_7->setText(QApplication::translate("DlgSynchronization", "User", 0));
        lblUser->setText(QApplication::translate("DlgSynchronization", "TextLabel", 0));
        label_5->setText(QApplication::translate("DlgSynchronization", "Database", 0));
        lblDatabase->setText(QApplication::translate("DlgSynchronization", "TextLabel", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeSyncrhonizationStatus->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("DlgSynchronization", "Status", 0));
        btnStartSynchro->setText(QApplication::translate("DlgSynchronization", "Synchronize", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgSynchronization: public Ui_DlgSynchronization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSYNCHRONIZATION_H
