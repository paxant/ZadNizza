#include "main_function.h"
#include "ui_main_function.h"
#include "QSerialPort"
#include "QSerialPortInfo"

QSerialPort serial_port_variable;

bool Definitions_device_availability()
{

    return false;

}

Main_function::Main_function(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_function)
{
QString PORT_NAME;
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       PORT_NAME = info.portName();
    }
    switch (Definitions_device_availability()) {
    case true:
        ui->Definitions_device_availability->deleteLater();
        break;
    default:
        ui->Definitions_device_availability->setStyleSheet("QTextEdit { background-color: rgb(255, 0, 0) }");
        break;
    }



}

Main_function::~Main_function()
{

    delete ui;

}

