/********************************************************************************
** Form generated from reading UI file 'dlgmerge.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMERGE_H
#define UI_DLGMERGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgMerge
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tblData;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgMerge)
    {
        if (DlgMerge->objectName().isEmpty())
            DlgMerge->setObjectName(QStringLiteral("DlgMerge"));
        DlgMerge->resize(513, 300);
        verticalLayout = new QVBoxLayout(DlgMerge);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tblData = new QTableWidget(DlgMerge);
        if (tblData->columnCount() < 4)
            tblData->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblData->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblData->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblData->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblData->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tblData->setObjectName(QStringLiteral("tblData"));

        verticalLayout->addWidget(tblData);

        buttonBox = new QDialogButtonBox(DlgMerge);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgMerge);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgMerge, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgMerge, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgMerge);
    } // setupUi

    void retranslateUi(QDialog *DlgMerge)
    {
        DlgMerge->setWindowTitle(QApplication::translate("DlgMerge", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tblData->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DlgMerge", "Field", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tblData->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DlgMerge", "Server", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tblData->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DlgMerge", "Local", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tblData->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DlgMerge", "Merge", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgMerge: public Ui_DlgMerge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGMERGE_H
