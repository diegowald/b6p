#ifndef DLGDATERANGEFILTER_H
#define DLGDATERANGEFILTER_H

#include <QDialog>

namespace Ui {
class DlgDateRangeFilter;
}

class DlgDateRangeFilter : public QDialog
{
    Q_OBJECT

public:
    explicit DlgDateRangeFilter(QWidget *parent = 0);
    ~DlgDateRangeFilter();

    QDate dateFrom();
    QDate dateTo();

    void setDateFrom(const QDate& from);
    void setDateTo(const QDate& to);
private:
    Ui::DlgDateRangeFilter *ui;
};

#endif // DLGDATERANGEFILTER_H
