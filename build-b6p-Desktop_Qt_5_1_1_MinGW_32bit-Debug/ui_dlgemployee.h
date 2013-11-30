/********************************************************************************
** Form generated from reading UI file 'dlgemployee.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEMPLOYEE_H
#define UI_DLGEMPLOYEE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <availabilitywidget.h>

QT_BEGIN_NAMESPACE

class Ui_DlgEmployee
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *txtLastName;
    QLabel *label_2;
    QLineEdit *txtNames;
    QLabel *label_3;
    QLineEdit *txtID;
    QLabel *label_4;
    QDateEdit *dateStart;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnAdd;
    QToolButton *btnEdit;
    QToolButton *btnDelete;
    QTreeWidget *treeCapacities;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    AvailabilityWidget *TimeSunday;
    AvailabilityWidget *TimeMonday;
    AvailabilityWidget *TimeTuesday;
    AvailabilityWidget *TimeWednesday;
    AvailabilityWidget *TimeThrursday;
    AvailabilityWidget *TimeFriday;
    AvailabilityWidget *TimeSaturday;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnAdd_2;
    QToolButton *btnEdit_2;
    QToolButton *btnDelete_2;
    QTreeWidget *treeLicencias;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgEmployee)
    {
        if (DlgEmployee->objectName().isEmpty())
            DlgEmployee->setObjectName(QStringLiteral("DlgEmployee"));
        DlgEmployee->resize(745, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_024_parents.png"), QSize(), QIcon::Normal, QIcon::Off);
        DlgEmployee->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgEmployee);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(DlgEmployee);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        formLayout = new QFormLayout(tab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        formLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        txtLastName = new QLineEdit(tab);
        txtLastName->setObjectName(QStringLiteral("txtLastName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, txtLastName);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        txtNames = new QLineEdit(tab);
        txtNames->setObjectName(QStringLiteral("txtNames"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txtNames);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        txtID = new QLineEdit(tab);
        txtID->setObjectName(QStringLiteral("txtID"));

        formLayout->setWidget(2, QFormLayout::FieldRole, txtID);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        dateStart = new QDateEdit(tab);
        dateStart->setObjectName(QStringLiteral("dateStart"));

        formLayout->setWidget(3, QFormLayout::FieldRole, dateStart);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        btnAdd = new QToolButton(tab_2);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/add"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon1);

        gridLayout->addWidget(btnAdd, 0, 0, 1, 1);

        btnEdit = new QToolButton(tab_2);
        btnEdit->setObjectName(QStringLiteral("btnEdit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/images/glyphicons_150_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnEdit->setIcon(icon2);

        gridLayout->addWidget(btnEdit, 0, 1, 1, 1);

        btnDelete = new QToolButton(tab_2);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/remove"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon3);

        gridLayout->addWidget(btnDelete, 0, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        treeCapacities = new QTreeWidget(tab_2);
        treeCapacities->headerItem()->setText(0, QString());
        treeCapacities->setObjectName(QStringLiteral("treeCapacities"));
        treeCapacities->header()->setVisible(false);

        verticalLayout_3->addWidget(treeCapacities);


        horizontalLayout_2->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        TimeSunday = new AvailabilityWidget(tab_3);
        TimeSunday->setObjectName(QStringLiteral("TimeSunday"));

        verticalLayout_2->addWidget(TimeSunday);

        TimeMonday = new AvailabilityWidget(tab_3);
        TimeMonday->setObjectName(QStringLiteral("TimeMonday"));

        verticalLayout_2->addWidget(TimeMonday);

        TimeTuesday = new AvailabilityWidget(tab_3);
        TimeTuesday->setObjectName(QStringLiteral("TimeTuesday"));

        verticalLayout_2->addWidget(TimeTuesday);

        TimeWednesday = new AvailabilityWidget(tab_3);
        TimeWednesday->setObjectName(QStringLiteral("TimeWednesday"));

        verticalLayout_2->addWidget(TimeWednesday);

        TimeThrursday = new AvailabilityWidget(tab_3);
        TimeThrursday->setObjectName(QStringLiteral("TimeThrursday"));

        verticalLayout_2->addWidget(TimeThrursday);

        TimeFriday = new AvailabilityWidget(tab_3);
        TimeFriday->setObjectName(QStringLiteral("TimeFriday"));

        verticalLayout_2->addWidget(TimeFriday);

        TimeSaturday = new AvailabilityWidget(tab_3);
        TimeSaturday->setObjectName(QStringLiteral("TimeSaturday"));

        verticalLayout_2->addWidget(TimeSaturday);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        horizontalLayout = new QHBoxLayout(tab_4);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        btnAdd_2 = new QToolButton(tab_4);
        btnAdd_2->setObjectName(QStringLiteral("btnAdd_2"));
        btnAdd_2->setIcon(icon1);

        gridLayout_2->addWidget(btnAdd_2, 0, 0, 1, 1);

        btnEdit_2 = new QToolButton(tab_4);
        btnEdit_2->setObjectName(QStringLiteral("btnEdit_2"));
        btnEdit_2->setIcon(icon2);

        gridLayout_2->addWidget(btnEdit_2, 0, 1, 1, 1);

        btnDelete_2 = new QToolButton(tab_4);
        btnDelete_2->setObjectName(QStringLiteral("btnDelete_2"));
        btnDelete_2->setIcon(icon3);

        gridLayout_2->addWidget(btnDelete_2, 0, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);

        treeLicencias = new QTreeWidget(tab_4);
        treeLicencias->setObjectName(QStringLiteral("treeLicencias"));

        verticalLayout_4->addWidget(treeLicencias);


        horizontalLayout->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(DlgEmployee);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DlgEmployee);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgEmployee, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgEmployee, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DlgEmployee);
    } // setupUi

    void retranslateUi(QDialog *DlgEmployee)
    {
        DlgEmployee->setWindowTitle(QApplication::translate("DlgEmployee", "Employee", 0));
        label->setText(QApplication::translate("DlgEmployee", "Lastname", 0));
        label_2->setText(QApplication::translate("DlgEmployee", "Names", 0));
        label_3->setText(QApplication::translate("DlgEmployee", "ID", 0));
        label_4->setText(QApplication::translate("DlgEmployee", "Start date", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DlgEmployee", "Information", 0));
        btnAdd->setText(QApplication::translate("DlgEmployee", "Add", 0));
        btnEdit->setText(QApplication::translate("DlgEmployee", "Edit", 0));
        btnDelete->setText(QApplication::translate("DlgEmployee", "...", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DlgEmployee", "Sector", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("DlgEmployee", "Availability", 0));
        btnAdd_2->setText(QApplication::translate("DlgEmployee", "Add", 0));
        btnEdit_2->setText(QApplication::translate("DlgEmployee", "Edit", 0));
        btnDelete_2->setText(QApplication::translate("DlgEmployee", "...", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeLicencias->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("DlgEmployee", "Notes", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("DlgEmployee", "Type", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("DlgEmployee", "To", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("DlgEmployee", "From", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("DlgEmployee", "Rest", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgEmployee: public Ui_DlgEmployee {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEMPLOYEE_H
