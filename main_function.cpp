#include "main_function.h"
#include "ui_main_function.h"
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QProcess"
#include "QDebug"

#define BASH true

QSerialPort serial_port_variable;

bool Definitions_device_availability()
{
#if BASH //work
    QProcess PROCESS_BASH;
    QString BASH_COMMAND = "../STM32_PC_realis/COM_PORT_SCAN.sh";
    PROCESS_BASH.start(BASH_COMMAND);
    PROCESS_BASH.waitForFinished();
#else
     qDebug() << "BASH off" ;
#endif
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

