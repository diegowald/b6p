#ifndef TIMEASSIGNMENTITEMEDIT_H
#define TIMEASSIGNMENTITEMEDIT_H

#include <QWidget>

namespace Ui {
class TimeAssignmentItemEdit;
}

class TimeAssignmentItemEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignmentItemEdit(QWidget *parent = 0);
    ~TimeAssignmentItemEdit();
    
private:
    Ui::TimeAssignmentItemEdit *ui;
};

#endif // TIMEASSIGNMENTITEMEDIT_H
