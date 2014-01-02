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
/*
#include "timeassignmentplugin.h"
#include "timeassignment.h"
#include <QtPlugin>


TimeAssignmentPlugin::TimeAssignmentPlugin(QWidget *parent)
    : QObject(parent)
{
    initialized = false;
}

void TimeAssignmentPlugin::initialize(QDesignerFormEditorInterface *-/-*core*-/)
{
    if (initialized)
        return;

    initialized = true;
}


bool TimeAssignmentPlugin::isInitialized() const
{
    return initialized;
}

QWidget *TimeAssignmentPlugin::createWidget(QWidget *parent)
{
    return new TimeAssignment(parent);
}

QString TimeAssignmentPlugin::name() const
{
    return "TimeAssignment";
}

QString TimeAssignmentPlugin::group() const
{
    return "Display Widgets [Diego Wald]";
}

QIcon TimeAssignmentPlugin::icon() const
{
    return QIcon();
}

QString TimeAssignmentPlugin::toolTip() const
{
    return "";
}

QString TimeAssignmentPlugin::whatsThis() const
{
    return "";
}

bool TimeAssignmentPlugin::isContainer() const
{
    return false;
}


QString TimeAssignmentPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"TimeAssignment\" name=\"timeAssignment\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>50</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Time assignation for employee</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>The time assignment widget displays the employee assignment.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString TimeAssignmentPlugin::includeFile() const
{
    return "timeassignment.h";
}


Q_EXPORT_PLUGIN2(timeAssignmentPlugin, TimeAssignmentPlugin)
*/
