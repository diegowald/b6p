#ifndef ACOLLECTION_H
#define ACOLLECTION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <QTreeWidget>

class ACollection : public QObject
{
    Q_OBJECT
public:
    explicit ACollection(QString Name, QObject *parent = 0);
    
    virtual void load();
    virtual void save();

    QString name() const;

    virtual void loadData() = 0;
    virtual void saveData() = 0;
    virtual void defineHeaders(QStringList &list) = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool addNew();
    virtual void edit(QVariant ID) = 0;
    virtual void deleteElement(QVariant ID) = 0;

signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);
    
public slots:

private:
    QString m_Name;

};

#endif // ACOLLECTION_H
