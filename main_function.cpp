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

#define BASH true
#define DEBUG true

/*
DATA_STRING_COM_PORTS[] названия портов
NUMB_PORTS их количество1
*/

using namespace std;
QSerialPort serial_port_variable;

bool Definitions_device_availability()
{
#if BASH //work
    //variables
    QProcess PROCESS_BASH;
    QString DATA_STRING_COM_PORTS_FILE = "";
    string DATA_STRING_COM_PORTS[100];
    int NUMB_PORTS = 0;
    for(int i = 0; i < 100; i++)
        DATA_STRING_COM_PORTS[i] = "";
    //code
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
     qDebug() << "BASH OFF" ;
     qDebug() << DATA_STRING_COM_PORTS;
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

