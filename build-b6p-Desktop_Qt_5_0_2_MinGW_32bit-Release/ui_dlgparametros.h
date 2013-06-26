/********************************************************************************
** Form generated from reading UI file 'dlgparametros.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPARAMETROS_H
#define UI_DLGPARAMETROS_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <timeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_DlgParametros
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    TimeEditor *timeOpen;
    QLabel *label_3;
    TimeEditor *timeClose;
    QLabel *label_5;
    QLineEdit *MinWorkingHours;
    QLabel *lblMessage;
    QWidget *tab_2;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QLineEdit *employeeMinWorkingHours;
    QLabel *label_7;
    QLineEdit *employeeMaxWorkingHours;
    QLabel *label_8;
    QLineEdit *employeeDaysBetweenFreeDay;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout_3;
    QLabel *label;
    QLineEdit *txtServer;
    QLabel *label_4;
    QLineEdit *txtDatabase;
    QLabel *label_9;
    QLineEdit *txtUser;
    QLabel *label_10;
    QLineEdit *txtPassword;
    QPushButton *pushButton;
    QLabel *lblConnectionResult;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgParametros)
    {
        if (DlgParametros->objectName().isEmpty())
            DlgParametros->setObjectName(QStringLiteral("DlgParametros"));
        DlgParametros->setWindowModality(Qt::ApplicationModal);
        DlgParametros->resize(360, 244);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_139_adjust_alt.png"), QSize(), QIcon::Normal, QIcon::Off);
        DlgParametros->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DlgParametros);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(DlgParametros);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 0, 274, 137));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        timeOpen = new TimeEditor(layoutWidget);
        timeOpen->setObjectName(QStringLiteral("timeOpen"));

        formLayout->setWidget(0, QFormLayout::FieldRole, timeOpen);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        timeClose = new TimeEditor(layoutWidget);
        timeClose->setObjectName(QStringLiteral("timeClose"));

        formLayout->setWidget(1, QFormLayout::FieldRole, timeClose);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        MinWorkingHours = new QLineEdit(layoutWidget);
        MinWorkingHours->setObjectName(QStringLiteral("MinWorkingHours"));

        formLayout->setWidget(2, QFormLayout::FieldRole, MinWorkingHours);

        lblMessage = new QLabel(layoutWidget);
        lblMessage->setObjectName(QStringLiteral("lblMessage"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, lblMessage);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        formLayout_2 = new QFormLayout(tab_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setHorizontalSpacing(2);
        formLayout_2->setVerticalSpacing(2);
        formLayout_2->setContentsMargins(2, 2, 2, 2);
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        employeeMinWorkingHours = new QLineEdit(tab_2);
        employeeMinWorkingHours->setObjectName(QStringLiteral("employeeMinWorkingHours"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, employeeMinWorkingHours);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_7);

        employeeMaxWorkingHours = new QLineEdit(tab_2);
        employeeMaxWorkingHours->setObjectName(QStringLiteral("employeeMaxWorkingHours"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, employeeMaxWorkingHours);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_8);

        employeeDaysBetweenFreeDay = new QLineEdit(tab_2);
        employeeDaysBetweenFreeDay->setObjectName(QStringLiteral("employeeDaysBetweenFreeDay"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, employeeDaysBetweenFreeDay);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_2 = new QHBoxLayout(tab_3);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setHorizontalSpacing(2);
        formLayout_3->setVerticalSpacing(2);
        label = new QLabel(tab_3);
        label->setObjectName(QStringLiteral("label"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label);

        txtServer = new QLineEdit(tab_3);
        txtServer->setObjectName(QStringLiteral("txtServer"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, txtServer);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_4);

        txtDatabase = new QLineEdit(tab_3);
        txtDatabase->setObjectName(QStringLiteral("txtDatabase"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, txtDatabase);

        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        txtUser = new QLineEdit(tab_3);
        txtUser->setObjectName(QStringLiteral("txtUser"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, txtUser);

        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_10);

        txtPassword = new QLineEdit(tab_3);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, txtPassword);

        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, pushButton);

        lblConnectionResult = new QLabel(tab_3);
        lblConnectionResult->setObjectName(QStringLiteral("lblConnectionResult"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, lblConnectionResult);


        horizontalLayout_2->addLayout(formLayout_3);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(DlgParametros);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(timeOpen);
        label_3->setBuddy(timeClose);
        label_5->setBuddy(MinWorkingHours);
        label_6->setBuddy(employeeMinWorkingHours);
        label_7->setBuddy(employeeMaxWorkingHours);
        label_8->setBuddy(employeeDaysBetweenFreeDay);
        label->setBuddy(txtServer);
        label_4->setBuddy(txtDatabase);
        label_9->setBuddy(txtUser);
        label_10->setBuddy(txtPassword);
#endif // QT_NO_SHORTCUT

        retranslateUi(DlgParametros);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgParametros, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgParametros, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DlgParametros);
    } // setupUi

    void retranslateUi(QDialog *DlgParametros)
    {
        DlgParametros->setWindowTitle(QApplication::translate("DlgParametros", "Parameters", 0));
        label_2->setText(QApplication::translate("DlgParametros", "Open", 0));
        label_3->setText(QApplication::translate("DlgParametros", "Close", 0));
        label_5->setText(QApplication::translate("DlgParametros", "<html><head/><body><p>Minimun Working </p><p>hours for a task</p></body></html>", 0));
        lblMessage->setText(QApplication::translate("DlgParametros", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DlgParametros", "Estimations & Planifications", 0));
        label_6->setText(QApplication::translate("DlgParametros", "Minimum Working hours.", 0));
        label_7->setText(QApplication::translate("DlgParametros", "Maximum Working hours", 0));
        label_8->setText(QApplication::translate("DlgParametros", "Days between free day.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DlgParametros", "Employee", 0));
        label->setText(QApplication::translate("DlgParametros", "Server", 0));
        label_4->setText(QApplication::translate("DlgParametros", "Database", 0));
        label_9->setText(QApplication::translate("DlgParametros", "User", 0));
        label_10->setText(QApplication::translate("DlgParametros", "Password", 0));
        pushButton->setText(QApplication::translate("DlgParametros", "Test Connection", 0));
        lblConnectionResult->setText(QApplication::translate("DlgParametros", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("DlgParametros", "Synchronization", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgParametros: public Ui_DlgParametros {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPARAMETROS_H
