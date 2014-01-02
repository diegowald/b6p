/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include <QWidget>
#include <QSpinBox>

namespace Ui {
class TimeEditor;
}

class TimeEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeEditor(QWidget *parent = 0);
    ~TimeEditor();

    void setTime(int hh, int mm, int ss);
    void setTime(int seconds);
    int timeSeconds();

    void setMinTime(int hh, int mm, int ss);
    void setMinTime(int seconds);
    int minTimeSeconds();

    void setMaxTime(int hh, int mm, int ss);
    void setMaxTime(int seconds);
    int maxTimeSeconds();

    void setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2);
    void setValidRange(int secondsFrom, int secondsTo);

    void setbeyondThisDayVisibility(bool value);
    bool beyondThisDayVisibility();

    bool isBeyondThisDay() const;

private:
    bool checkTime(const QString& time);
    bool checkTime(int hh, int mm, int ss);
    bool checkTime(int seconds);
    int HHMMSS2Seconds(const QString &time, bool canBeBeyondThisDay);
    int HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay);
    int getHours(int seconds);
    int getMinutes(int seconds);
    int getSeconds(int seconds);
    void onValueChanged(QLineEdit *control, int arg1);
    void setDefaultValues();
signals:
    void timeChanged(int newTime);
    void IncorrectTime(const QString& cause);

private slots:
    void on_chkBeyondThisDay_clicked(bool checked);

    void on_lineTime_textChanged(const QString &arg1);

private:
    Ui::TimeEditor *ui;

    bool maxTimeBeyondThisDay;
    int currentTime; // Stored in seconds
    int minValue;
    int maxValue;
    int previouslySelectedHour;
};

#endif // TIMEEDITOR_H
