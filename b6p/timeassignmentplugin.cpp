#include "timeassignmentplugin.h"
#include "timeassignment.h"
#include <QtPlugin>

TimeAssignmentPlugin::TimeAssignmentPlugin(QWidget *parent)
    : QObject(parent)
{
    initialized = false;
}

void TimeAssignmentPlugin::initialize(QDesignerFormEditorInterface *core)
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
