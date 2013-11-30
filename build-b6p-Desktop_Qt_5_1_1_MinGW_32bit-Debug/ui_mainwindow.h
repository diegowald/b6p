/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionView;
    QAction *actionParameters;
    QAction *actionAbout;
    QAction *actionSetup_days;
    QAction *actionSynchronize;
    QAction *actionPrint_Preview;
    QAction *actionPrint_Selected;
    QAction *actionPrint_Preview_Selected_Record;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuPlanification;
    QMenu *menuEmployees;
    QMenu *menuCustomization;
    QMenu *menuAbout;
    QMenu *menuSynchronization;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        QFont font;
        font.setPointSize(16);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/app"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(true);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/images/glyphicons_144_folder_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionOpen->setMenuRole(QAction::ApplicationSpecificRole);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/images/glyphicons_015_print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon2);
        actionPrint->setVisible(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setMenuRole(QAction::QuitRole);
        actionView = new QAction(MainWindow);
        actionView->setObjectName(QStringLiteral("actionView"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/images/glyphicons_024_parents.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView->setIcon(icon3);
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QStringLiteral("actionParameters"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/img/images/glyphicons_139_adjust_alt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionParameters->setIcon(icon4);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/img/images/glyphicons_195_circle_info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionAbout->setMenuRole(QAction::AboutRole);
        actionSetup_days = new QAction(MainWindow);
        actionSetup_days->setObjectName(QStringLiteral("actionSetup_days"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/img/images/glyphicons_327_sampler.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetup_days->setIcon(icon6);
        actionSynchronize = new QAction(MainWindow);
        actionSynchronize->setObjectName(QStringLiteral("actionSynchronize"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/img/images/glyphicons_082_roundabout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSynchronize->setIcon(icon7);
        actionPrint_Preview = new QAction(MainWindow);
        actionPrint_Preview->setObjectName(QStringLiteral("actionPrint_Preview"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/img/images/glyphicons_039_notes.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint_Preview->setIcon(icon8);
        actionPrint_Preview->setVisible(true);
        actionPrint_Selected = new QAction(MainWindow);
        actionPrint_Selected->setObjectName(QStringLiteral("actionPrint_Selected"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/img/images/glyphicons_083_random.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint_Selected->setIcon(icon9);
        actionPrint_Preview_Selected_Record = new QAction(MainWindow);
        actionPrint_Preview_Selected_Record->setObjectName(QStringLiteral("actionPrint_Preview_Selected_Record"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/img/images/glyphicons_051_eye_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint_Preview_Selected_Record->setIcon(icon10);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        verticalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 37));
        menuPlanification = new QMenu(menuBar);
        menuPlanification->setObjectName(QStringLiteral("menuPlanification"));
        menuEmployees = new QMenu(menuBar);
        menuEmployees->setObjectName(QStringLiteral("menuEmployees"));
        menuCustomization = new QMenu(menuBar);
        menuCustomization->setObjectName(QStringLiteral("menuCustomization"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuSynchronization = new QMenu(menuBar);
        menuSynchronization->setObjectName(QStringLiteral("menuSynchronization"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPlanification->menuAction());
        menuBar->addAction(menuEmployees->menuAction());
        menuBar->addAction(menuCustomization->menuAction());
        menuBar->addAction(menuSynchronization->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuPlanification->addSeparator();
        menuPlanification->addAction(actionSetup_days);
        menuPlanification->addAction(actionOpen);
        menuPlanification->addSeparator();
        menuPlanification->addAction(actionPrint);
        menuPlanification->addAction(actionPrint_Preview);
        menuPlanification->addSeparator();
        menuPlanification->addAction(actionPrint_Preview_Selected_Record);
        menuPlanification->addAction(actionPrint_Selected);
        menuPlanification->addSeparator();
        menuPlanification->addAction(actionExit);
        menuEmployees->addAction(actionView);
        menuCustomization->addAction(actionParameters);
        menuAbout->addAction(actionAbout);
        menuSynchronization->addAction(actionSynchronize);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Big Six Planner", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open Planification", 0));
#endif // QT_NO_TOOLTIP
        actionPrint->setText(QApplication::translate("MainWindow", "Print", 0));
#ifndef QT_NO_TOOLTIP
        actionPrint->setToolTip(QApplication::translate("MainWindow", "Prints Planification", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Exits application", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionView->setText(QApplication::translate("MainWindow", "View", 0));
#ifndef QT_NO_TOOLTIP
        actionView->setToolTip(QApplication::translate("MainWindow", "View Employees", 0));
#endif // QT_NO_TOOLTIP
        actionParameters->setText(QApplication::translate("MainWindow", "Parameters", 0));
#ifndef QT_NO_TOOLTIP
        actionParameters->setToolTip(QApplication::translate("MainWindow", "Edit configuration parameters", 0));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("MainWindow", "About...", 0));
        actionSetup_days->setText(QApplication::translate("MainWindow", "Setup days...", 0));
        actionSynchronize->setText(QApplication::translate("MainWindow", "Synchronize...", 0));
        actionPrint_Preview->setText(QApplication::translate("MainWindow", "Print Preview", 0));
        actionPrint_Selected->setText(QApplication::translate("MainWindow", "Print Selected", 0));
#ifndef QT_NO_TOOLTIP
        actionPrint_Selected->setToolTip(QApplication::translate("MainWindow", "Prints selected record.", 0));
#endif // QT_NO_TOOLTIP
        actionPrint_Preview_Selected_Record->setText(QApplication::translate("MainWindow", "Print Preview Selected Record", 0));
        menuPlanification->setTitle(QApplication::translate("MainWindow", "Planification", 0));
        menuEmployees->setTitle(QApplication::translate("MainWindow", "Employees", 0));
        menuCustomization->setTitle(QApplication::translate("MainWindow", "Customization", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
        menuSynchronization->setTitle(QApplication::translate("MainWindow", "Synchronization", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
