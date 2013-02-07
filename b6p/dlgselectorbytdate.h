#ifndef DLGSELECTORBYTDATE_H
#define DLGSELECTORBYTDATE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DlgSelectorBytDate;
}

class DlgSelectorBytDate : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgSelectorBytDate(QWidget *parent = 0);
    ~DlgSelectorBytDate();

    void setData(QList<QDate> &values);
    QDate selectedDay();

    void setLabel(QString txt);
    void setTitle(QString txt);
    
private:
    Ui::DlgSelectorBytDate *ui;
};

#endif // DLGSELECTORBYTDATE_H
