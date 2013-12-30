#include "dlgempleadoslicenciasplanificacion.h"
#include "ui_dlgempleadoslicenciasplanificacion.h"
#include "QsLog.h"
#include "datastore.h"

DlgEmpleadosLicenciasPlanificacion::DlgEmpleadosLicenciasPlanificacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEmpleadosLicenciasPlanificacion)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgEmpleadosLicenciasPlanificacion::~DlgEmpleadosLicenciasPlanificacion()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgEmpleadosLicenciasPlanificacion::setData(QDate currentDay, QList<int> employeesToExclude)
{
    QLOG_TRACE_FN();
    m_CurrentDay = currentDay;
    m_EmployeesToExclude = employeesToExclude;
    fillTree();
}

void DlgEmpleadosLicenciasPlanificacion::fillTree()
{
    QLOG_TRACE_FN();
    EmpleadosLst empleados = DataStore::instance()->getEmpleados()->getAllAvailableByDay(m_CurrentDay, m_EmployeesToExclude, true);
    foreach (EmpleadoPtr empleado, *empleados)
    {
        addEmpleadoToTree(empleado);
    }
}

void DlgEmpleadosLicenciasPlanificacion::addEmpleadoToTree(EmpleadoPtr empleado)
{
    QLOG_TRACE_FN();
    QTreeWidgetItem *item = new QTreeWidgetItem();
    //item->setCheckState(0, Qt::Unchecked);
    QString aux("%1, %2");
    aux = aux.arg(empleado->Apellido().value(), empleado->Nombre().value());
    item->setText(0, aux);
    item->setData(0, Qt::UserRole, empleado->IDEmpleado().value());


    LicenciaEmpleadoPtr licencia = empleado->LicenciaProgramada(m_CurrentDay);
    LicenciaEmpleadoPtr ultimoFranco = DataStore::instance()->getLicencias()->getUltimoFranco(empleado->IDEmpleado().value(), m_CurrentDay);

    if (licencia != LicenciaEmpleadoPtr())
    {
        item->setData(1, Qt::UserRole, licencia->ID().value());
        if (ultimoFranco != LicenciaEmpleadoPtr())
        {
            item->setText(1, ultimoFranco->FechaHasta().value().toString(Qt::TextDate));
        }
        else
        {
            item->setText(1, "");
        }
        item->setText(2, licencia->FechaDesde().value().toString(Qt::TextDate));
        item->setText(3, licencia->FechaHasta().value().toString(Qt::TextDate));
        item->setText(4, licencia->TipoLicencia().value());
        item->setText(5, licencia->Descripcion().value());
    }
    else
    {
        item->setData(1, Qt::UserRole, 0);
    }
    ui->treeWidget->insertTopLevelItem(0, item);
}

void DlgEmpleadosLicenciasPlanificacion::on_btnAdd_2_clicked()
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> selectedItems = ui->treeWidget->selectedItems();
    if (selectedItems.count() > 0)
    {
        QTreeWidgetItem *selectedItem = selectedItems.at(0);
        if (selectedItem->data(1, Qt::UserRole) == 0)
        {
            QList<QVariant> auxData;
            auxData.push_back(m_CurrentDay);
            auxData.push_back(selectedItem->data(0, Qt::UserRole));
            if (DataStore::instance()->getLicencias()->addNewRecordWithAuxiliarydata(QVariant(auxData)))
            {
                ui->treeWidget->clear();
                fillTree();
            }
        }
    }
}

void DlgEmpleadosLicenciasPlanificacion::on_btnEdit_2_clicked()
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> selectedItems = ui->treeWidget->selectedItems();
    if (selectedItems.count() > 0)
    {
        QTreeWidgetItem *selectedItem = selectedItems.at(0);
        if (selectedItem->data(1, Qt::UserRole) != 0)
            DataStore::instance()->getLicencias()->editRecord(selectedItem->data(1, Qt::UserRole));
    }
}

void DlgEmpleadosLicenciasPlanificacion::on_btnDelete_2_clicked()
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> selectedItems = ui->treeWidget->selectedItems();
    if (selectedItems.count() > 0)
    {
        QTreeWidgetItem * selectedItem = selectedItems.at(0);
        QVariant IDLicencia = selectedItem->data(1, Qt::UserRole);
        ((ACollection*)DataStore::instance()->getLicencias().get())->deleteRecord(IDLicencia);
    }
}
