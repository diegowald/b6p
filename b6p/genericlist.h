#ifndef GENERICLIST_H
#define GENERICLIST_H

#include <QMainWindow>
#include "acollection.h"

namespace Ui {
class GenericList;
}

class GenericList : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GenericList(boost::shared_ptr<ACollection> Model, bool inPlaceEdit, QWidget *parent /*= 0*/);

    void AllowAdd(bool status);
    void AllowEdit(bool status);
    void AllowDelete(bool status);

    ~GenericList();
    void setHeader(QStringList &headers);

public slots:

private slots:

    void on_actionNew_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void on_treeList_doubleClicked(const QModelIndex &index);
    void on_treeList_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeList_itemChanged(QTreeWidgetItem *item, int column);
    void customActionTriggered();
private:
    Ui::GenericList *ui;
    boost::shared_ptr<ACollection> model;
    bool m_InPlaceEdit;
};

#endif // GENERICLIST_H
