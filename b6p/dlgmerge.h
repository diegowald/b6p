#ifndef DLGMERGE_H
#define DLGMERGE_H

#include <QDialog>
#include "IRecord.h"

namespace Ui {
class DlgMerge;
}

class DlgMerge : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgMerge(QWidget *parent = 0);
    ~DlgMerge();

    void setData(RecordPtr ServerRecord, RecordPtr localRecord, QStringList fieldsToShow);
    RecordPtr mergedRecord();
    
private slots:
    void on_tblData_cellClicked(int row, int column);

private:
    Ui::DlgMerge *ui;
    RecordPtr local;
    RecordPtr server;
};

#endif // DLGMERGE_H
