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
    explicit GenericList(boost::shared_ptr<ACollection> Model, QWidget *parent = 0);
    ~GenericList();
    void setHeader(QStringList &headers);

public slots:

private slots:

    void on_actionNew_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

private:
    Ui::GenericList *ui;
    boost::shared_ptr<ACollection> model;
};

#endif // GENERICLIST_H
