#ifndef DLGQUERYBUILDER_H
#define DLGQUERYBUILDER_H

#include <QDialog>

namespace Ui {
class DlgQueryBuilder;
}

class DlgQueryBuilder : public QDialog
{
    Q_OBJECT

public:
    explicit DlgQueryBuilder(QWidget *parent = 0);
    ~DlgQueryBuilder();

    void setDateFrom(const QDate& from);
    void setDateTo(const QDate& to);
    void setIDSector(int id);
    void setIDSubSector(int id);
    void setIDEmployee(int id);

    void setSummarizeDays(bool value);
    void setSummarizeSectors(bool value);
    void setSummarizeSubsectors(bool value);
    void setSummarizeEmployee(bool value);

    bool summarizeDays() const;
    bool summarizeSectors() const;
    bool summarizeSubsectors() const;
    bool summarizeEmployee() const;

    QDate dateFrom();
    QDate dateTo();
    int idSector();
    int idSubSector();
    int idEmployee();

    void setEmployeeEnabled(bool enabled);
    void setSectorEnabled(bool enabled);
    void setSubSectorEnabled(bool enabled);
    void setDateEnabled(bool enabled);

private slots:
    void on_cboSector_currentIndexChanged(int index);

private:
    void fillSectores();
    void fillSubSectores(int IDSector);
    void fillEmployees();

private:
    Ui::DlgQueryBuilder *ui;
};

#endif // DLGQUERYBUILDER_H
