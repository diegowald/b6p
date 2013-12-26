#ifndef GENERICLIST_H
#define GENERICLIST_H

#include <QMainWindow>
#include "acollection.h"

// For printing
#include <QTextDocument>

namespace Ui {
class GenericList;
}

class GenericList : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GenericList(int LoggedUser, boost::shared_ptr<ACollection> Model, bool inPlaceEdit, bool allowSorting, QWidget *parent);

    void AllowAdd(bool status);
    void AllowEdit(bool status);
    void AllowDelete(bool status);


    ~GenericList();
    void setHeader(QStringList &headers);
    void enableButtonsBasedOnAccess();
    QString getHTMLReport();
    bool printSelectedRecord(QTextDocument &textDoc);
    virtual void showEvent(QShowEvent *evt);

    void setABMButtonsVisible(bool visible);

protected:
    virtual QString getHeader();
    virtual QString getBody();

public slots:

private slots:

    void on_actionNew_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void on_treeList_doubleClicked(const QModelIndex &index);
    void on_treeList_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeList_itemChanged(QTreeWidgetItem *item, int column);
    void customActionTriggered();
    void on_dataUpdated();
    void on_actionExport_triggered();

private:
    Ui::GenericList *ui;
    boost::shared_ptr<ACollection> model;
    bool m_InPlaceEdit;
    int m_LoggedUser;
    bool m_allowSorting;
};

#endif // GENERICLIST_H
