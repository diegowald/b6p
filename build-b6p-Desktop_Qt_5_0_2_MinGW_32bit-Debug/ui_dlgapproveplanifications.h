/********************************************************************************
** Form generated from reading UI file 'dlgapproveplanifications.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGAPPROVEPLANIFICATIONS_H
#define UI_DLGAPPROVEPLANIFICATIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgApprovePlanifications
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treePlanifications;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgApprovePlanifications)
    {
        if (DlgApprovePlanifications->objectName().isEmpty())
            DlgApprovePlanifications->setObjectName(QStringLiteral("DlgApprovePlanifications"));
        DlgApprovePlanifications->resize(400, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
        DlgApprovePlanifications->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgApprovePlanifications);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        treePlanifications = new QTreeWidget(DlgApprovePlanifications);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treePlanifications->setHeaderItem(__qtreewidgetitem);
        treePlanifications->setObjectName(QStringLiteral("treePlanifications"));
        treePlanifications->setAlternatingRowColors(true);
        treePlanifications->setIndentation(0);
        treePlanifications->setRootIsDecorated(false);
        treePlanifications->setItemsExpandable(false);
        treePlanifications->setSortingEnabled(true);
        treePlanifications->setExpandsOnDoubleClick(false);
        treePlanifications->header()->setVisible(false);

        verticalLayout->addWidget(treePlanifications);

        buttonBox = new QDialogButtonBox(DlgApprovePlanifications);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgApprovePlanifications);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgApprovePlanifications, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgApprovePlanifications, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgApprovePlanifications);
    } // setupUi

    void retranslateUi(QDialog *DlgApprovePlanifications)
    {
        DlgApprovePlanifications->setWindowTitle(QApplication::translate("DlgApprovePlanifications", "Approve Planifications", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgApprovePlanifications: public Ui_DlgApprovePlanifications {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGAPPROVEPLANIFICATIONS_H
