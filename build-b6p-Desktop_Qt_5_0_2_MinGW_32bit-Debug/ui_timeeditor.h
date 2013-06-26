/********************************************************************************
** Form generated from reading UI file 'timeeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEEDITOR_H
#define UI_TIMEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineHours;
    QLineEdit *lineMinutes;
    QLineEdit *lineSeconds;
    QCheckBox *chkBeyondThisDay;

    void setupUi(QWidget *TimeEditor)
    {
        if (TimeEditor->objectName().isEmpty())
            TimeEditor->setObjectName(QStringLiteral("TimeEditor"));
        TimeEditor->resize(150, 31);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimeEditor->sizePolicy().hasHeightForWidth());
        TimeEditor->setSizePolicy(sizePolicy);
        TimeEditor->setMinimumSize(QSize(150, 0));
        TimeEditor->setMaximumSize(QSize(150, 16777215));
        horizontalLayout = new QHBoxLayout(TimeEditor);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineHours = new QLineEdit(TimeEditor);
        lineHours->setObjectName(QStringLiteral("lineHours"));
        lineHours->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineHours);

        lineMinutes = new QLineEdit(TimeEditor);
        lineMinutes->setObjectName(QStringLiteral("lineMinutes"));
        lineMinutes->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineMinutes);

        lineSeconds = new QLineEdit(TimeEditor);
        lineSeconds->setObjectName(QStringLiteral("lineSeconds"));
        lineSeconds->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineSeconds);

        chkBeyondThisDay = new QCheckBox(TimeEditor);
        chkBeyondThisDay->setObjectName(QStringLiteral("chkBeyondThisDay"));

        horizontalLayout->addWidget(chkBeyondThisDay);


        retranslateUi(TimeEditor);

        QMetaObject::connectSlotsByName(TimeEditor);
    } // setupUi

    void retranslateUi(QWidget *TimeEditor)
    {
        TimeEditor->setWindowTitle(QApplication::translate("TimeEditor", "Form", 0));
        chkBeyondThisDay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TimeEditor: public Ui_TimeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEEDITOR_H
