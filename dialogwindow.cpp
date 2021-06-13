#include "dialogwindow.hpp"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
}

DialogWindow::~DialogWindow()
{
    delete ui;
}

void DialogWindow::setManufacturer(const std::string sManufacturer)
{
    ui->edit_manuf->setText(QString::fromStdString(sManufacturer));
}
std::string DialogWindow::getManufacturer() const
{
    return ui->edit_manuf->text().toStdString();
}

void DialogWindow::setModel(const std::string sModel)
{
    ui->edit_model->setText(QString::fromStdString(sModel));
}
std::string DialogWindow::getModel() const
{
    return ui->edit_model->text().toStdString();
}

void DialogWindow::setCost(const int sCost)
{
    ui->spin_cost->setValue(sCost);
}
int DialogWindow::getCost() const
{
    return ui->spin_cost->value();
}

void DialogWindow::setSocket(const std::string sSocket)
{
    ui->edit_socket->setText(QString::fromStdString(sSocket));
}
std::string DialogWindow::getSocket() const
{
    return ui->edit_socket->text().toStdString();
}

void DialogWindow::setCore_num(const int sCore_num)
{
    ui->spin_numcor->setValue(sCore_num);
}
int DialogWindow::getCore_num() const
{
    return ui->spin_numcor->value();
}

void DialogWindow::setProc_speed(const int sProc_speed)
{
    ui->spin_prc_spd->setValue(sProc_speed);
}
int DialogWindow::getProc_speed() const
{
    return ui->spin_prc_spd->value();
}

void DialogWindow::setMem_type(const std::string sMem_type)
{
    ui->edit_mem_type->setText(QString::fromStdString(sMem_type));
}
std::string DialogWindow::getMem_type() const
{
    return ui->edit_mem_type->text().toStdString();
}

void DialogWindow::setMem_freq(const int sMem_freq)
{
    ui->spin_mem_freq->setValue(sMem_freq);
}
int DialogWindow::getMem_freq() const
{
    return ui->spin_mem_freq->value();
}
