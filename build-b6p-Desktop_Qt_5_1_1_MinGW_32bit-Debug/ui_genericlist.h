/********************************************************************************
** Form generated from reading UI file 'genericlist.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERICLIST_H
#define UI_GENERICLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenericList
{
public:
    QAction *actionNew;
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionExport;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeList;
    QToolBar *toolBar;

    void setupUi(QMainWindow *GenericList)
    {
        if (GenericList->objectName().isEmpty())
            GenericList->setObjectName(QStringLiteral("GenericList"));
        GenericList->resize(800, 600);
        GenericList->setMinimumSize(QSize(400, 300));
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/glyphicons_352_nameplate.png"), QSize(), QIcon::Normal, QIcon::Off);
        GenericList->setWindowIcon(icon);
        actionNew = new QAction(GenericList);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/add"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionEdit = new QAction(GenericList);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/images/glyphicons_150_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon2);
        actionDelete = new QAction(GenericList);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/remove"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon3);
        actionExport = new QAction(GenericList);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/img/images/glyphicons_151_new_window.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon4);
        centralwidget = new QWidget(GenericList);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        treeList = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeList->setHeaderItem(__qtreewidgetitem);
        treeList->setObjectName(QStringLiteral("treeList"));
        treeList->setAlternatingRowColors(true);

        horizontalLayout->addWidget(treeList);

        GenericList->setCentralWidget(centralwidget);
        toolBar = new QToolBar(GenericList);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        GenericList->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionNew);
        toolBar->addAction(actionEdit);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionExport);

        retranslateUi(GenericList);

        QMetaObject::connectSlotsByName(GenericList);
    } // setupUi

    void retranslateUi(QMainWindow *GenericList)
    {
        GenericList->setWindowTitle(QApplication::translate("GenericList", "MainWindow", 0));
        actionNew->setText(QApplication::translate("GenericList", "New", 0));
        actionEdit->setText(QApplication::translate("GenericList", "Edit", 0));
        actionDelete->setText(QApplication::translate("GenericList", "Delete", 0));
        actionExport->setText(QApplication::translate("GenericList", "Export", 0));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("GenericList", "Export to CSV File", 0));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("GenericList", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class GenericList: public Ui_GenericList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERICLIST_H
