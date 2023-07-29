#include "main_function.h"
#include "ui_main_function.h"
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QProcess"
#include "QDebug"
#include <QFile>
#include <QByteArray>
#include <QString>
#include "string"
#include "vector"

#define BASH false
#define DEBUG true

/*
DATA_STRING_COM_PORTS[] названия портов
NUMB_PORTS их количество
*/

using namespace std;
QSerialPort serial_port_variable;

bool Definitions_device_availability()
{
    string DATA_STRING_COM_PORTS[100];
    int NUMB_PORTS = 0;
#if BASH //work
    //variables
    QProcess PROCESS_BASH;
    QString DATA_STRING_COM_PORTS_FILE = "";

    //code
    for(int i = 0; i < 100; i++)
        DATA_STRING_COM_PORTS[i] = "";

#if DEBUG
    qDebug() << "BASH ENEBLE" ;
#endif
    QString BASH_COMMAND = "../STM32_PC_realis/COM_PORT_SCAN.sh"; //Получение данных о портах в файл
    PROCESS_BASH.start(BASH_COMMAND);
    PROCESS_BASH.waitForFinished();

    QFile READ_A_BASH_FILE("../STM32_PC_realis/COM_PORTS.ZadNizza");
    if (!READ_A_BASH_FILE.open(QIODevice::ReadOnly))
        qDebug() << "FILE FAIL";
    else
        {
            int NUMB = 0;
            DATA_STRING_COM_PORTS_FILE = QString(READ_A_BASH_FILE.readAll());
            string FILE_DATA = DATA_STRING_COM_PORTS_FILE.toStdString();
            for(int i = 0; i < DATA_STRING_COM_PORTS_FILE.length(); i++)
            {
                if(FILE_DATA[i] == '\n' )
                {
                    i++;
                    NUMB++;
                }
                DATA_STRING_COM_PORTS[NUMB] += FILE_DATA[i];
            }
            while(true)
            {
                if(DATA_STRING_COM_PORTS[NUMB_PORTS] != "" && NUMB_PORTS != 99)
                NUMB_PORTS++;
                else
                    break;
            }
#if DEBUG
      qDebug() << DATA_STRING_COM_PORTS;
#endif
    }
#else
#if DEBUG
     qDebug() << "BASH OFF";
#endif
     //code
     for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
     {
         // print the port name
         DATA_STRING_COM_PORTS[NUMB_PORTS] = port.portName().toStdString();
         NUMB_PORTS++;
     }
#endif
    return false;

}

Main_function::Main_function(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_function)
{

QString PORT_NAME;
    ui->setupUi(this);
    ui->OUTPIUT_CONSOLE->deleteLater();
    ui->ENTERING->deleteLater();
    ui->ENTERING_COMMANDS->deleteLater();
    ui->COM_PORT_CHOICE->deleteLater();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       PORT_NAME = info.portName();
    }
    switch (Definitions_device_availability()) {
    case true:
        ui->DONT_WORK->deleteLater();
        break;
    default:
        ui->DONT_WORK->setAlignment(Qt::AlignCenter);
        QPalette pal;
        pal.setColor(QPalette::Base, Qt::red);
        ui->DONT_WORK->setPalette(pal);
        break;
    }

}

Main_function::~Main_function()
{

    delete ui;

}


void Main_function::on_action_17_triggered()
{

}

