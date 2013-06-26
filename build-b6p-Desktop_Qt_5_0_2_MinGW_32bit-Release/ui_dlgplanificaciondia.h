/********************************************************************************
** Form generated from reading UI file 'dlgplanificaciondia.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPLANIFICACIONDIA_H
#define UI_DLGPLANIFICACIONDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgPlanificacionDia
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lblDia;
    QLabel *lblHorasEstimadas;
    QLabel *lblStatus;
    QGridLayout *gridLayout;
    QToolButton *btnAdd;
    QToolButton *btnEdit;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnDelete;
    QToolButton *btnExport;
    QTreeWidget *treeWidget;
    QLabel *lblHorasPlanificadas;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Notes;
    QLineEdit *txtNotes;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgPlanificacionDia)
    {
        if (DlgPlanificacionDia->objectName().isEmpty())
            DlgPlanificacionDia->setObjectName(QStringLiteral("DlgPlanificacionDia"));
        DlgPlanificacionDia->resize(801, 480);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DlgPlanificacionDia->sizePolicy().hasHeightForWidth());
        DlgPlanificacionDia->setSizePolicy(sizePolicy);
        DlgPlanificacionDia->setMinimumSize(QSize(800, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_057_history.png"), QSize(), QIcon::Normal, QIcon::Off);
        DlgPlanificacionDia->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgPlanificacionDia);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblDia = new QLabel(DlgPlanificacionDia);
        lblDia->setObjectName(QStringLiteral("lblDia"));

        horizontalLayout->addWidget(lblDia);

        lblHorasEstimadas = new QLabel(DlgPlanificacionDia);
        lblHorasEstimadas->setObjectName(QStringLiteral("lblHorasEstimadas"));

        horizontalLayout->addWidget(lblHorasEstimadas);

        lblStatus = new QLabel(DlgPlanificacionDia);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));

        horizontalLayout->addWidget(lblStatus);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QToolButton(DlgPlanificacionDia);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/add"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon1);

        gridLayout->addWidget(btnAdd, 0, 0, 1, 1);

        btnEdit = new QToolButton(DlgPlanificacionDia);
        btnEdit->setObjectName(QStringLiteral("btnEdit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/images/glyphicons_150_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnEdit->setIcon(icon2);

        gridLayout->addWidget(btnEdit, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        btnDelete = new QToolButton(DlgPlanificacionDia);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/remove"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon3);

        gridLayout->addWidget(btnDelete, 0, 2, 1, 1);

        btnExport = new QToolButton(DlgPlanificacionDia);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/img/images/glyphicons_151_new_window.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExport->setIcon(icon4);

        gridLayout->addWidget(btnExport, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        treeWidget = new QTreeWidget(DlgPlanificacionDia);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setAutoFillBackground(true);
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setFrameShadow(QFrame::Raised);
        treeWidget->setLineWidth(0);
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setProperty("showDropIndicator", QVariant(false));
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setItemsExpandable(false);
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        lblHorasPlanificadas = new QLabel(DlgPlanificacionDia);
        lblHorasPlanificadas->setObjectName(QStringLiteral("lblHorasPlanificadas"));

        verticalLayout->addWidget(lblHorasPlanificadas);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Notes = new QLabel(DlgPlanificacionDia);
        Notes->setObjectName(QStringLiteral("Notes"));

        horizontalLayout_2->addWidget(Notes);

        txtNotes = new QLineEdit(DlgPlanificacionDia);
        txtNotes->setObjectName(QStringLiteral("txtNotes"));

        horizontalLayout_2->addWidget(txtNotes);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(DlgPlanificacionDia);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgPlanificacionDia);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgPlanificacionDia, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgPlanificacionDia, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgPlanificacionDia);
    } // setupUi

    void retranslateUi(QDialog *DlgPlanificacionDia)
    {
        DlgPlanificacionDia->setWindowTitle(QApplication::translate("DlgPlanificacionDia", "Planning", 0));
        lblDia->setText(QApplication::translate("DlgPlanificacionDia", "TextLabel", 0));
        lblHorasEstimadas->setText(QApplication::translate("DlgPlanificacionDia", "TextLabel", 0));
        lblStatus->setText(QApplication::translate("DlgPlanificacionDia", "TextLabel", 0));
        btnAdd->setText(QApplication::translate("DlgPlanificacionDia", "Add", 0));
        btnEdit->setText(QApplication::translate("DlgPlanificacionDia", "Edit", 0));
        btnDelete->setText(QApplication::translate("DlgPlanificacionDia", "...", 0));
        btnExport->setText(QApplication::translate("DlgPlanificacionDia", "Export", 0));
        lblHorasPlanificadas->setText(QApplication::translate("DlgPlanificacionDia", "TextLabel", 0));
        Notes->setText(QApplication::translate("DlgPlanificacionDia", "Notes:", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgPlanificacionDia: public Ui_DlgPlanificacionDia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPLANIFICACIONDIA_H
