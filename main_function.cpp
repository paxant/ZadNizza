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
#include "QMessageBox"
#include "QTimer"

#define BASH false
#define DEBUG true

/*
DATA_STRING_COM_PORTS[] названия портов
NUMB_PORTS их количество
*/

using namespace std;
QSerialPort serial_port_variable;
bool TERMINAL_ENABLE = false;


bool Definitions_device_availability_bool()
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
    return true;

}

bool Main_function::Setting_the_permission_to_work_with_the_COM_port_bool(bool CONSOLE_OUTPUT = false)
{
    if(!serial_port_variable.open(QIODevice::ReadWrite))  // Проверка подключения на чтение и запись
    {
        if(CONSOLE_OUTPUT)
        ui->OUTPIUT_CONSOLE->setText("Ошибка подключения");
        return false;
    }
    else
    {
        if(CONSOLE_OUTPUT)
        ui->OUTPIUT_CONSOLE->setText("Соединение установлено");
        return true;
    }
}

void Definitions_device_availability_void(string(&DATA_STRING_COM_PORTS)[], int& NUMB_PORTS)
{

     //code
     for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
     {
         // print the port name
         DATA_STRING_COM_PORTS[NUMB_PORTS] = port.portName().toStdString();
         NUMB_PORTS++;
     }

}

Main_function::Main_function(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_function)
{

QString PORT_NAME;
    ui->setupUi(this);
    ui->OUTPIUT_CONSOLE->hide();
    ui->ENTERING->hide();
    ui->ENTERING_COMMANDS->hide();
    ui->COM_PORT_CHOICE->hide();
    ui->CONNECT->hide();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       PORT_NAME = info.portName();
    }
    switch (Definitions_device_availability_bool()) {
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
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Read_COM_port_to_CONSOLE_OUTPUT()));
    timer->start(300);

}

void Main_function::Read_COM_port_to_CONSOLE_OUTPUT()
{
    if(TERMINAL_ENABLE)
    {
        QByteArray data;  // специальный тип QT для хранения последовательности байтов
        data = serial_port_variable.readAll();
        QString stroka = QString::fromStdString(data.toStdString());
        if(stroka != "")
        ui->OUTPIUT_CONSOLE->append(stroka);
    }
}

Main_function::~Main_function()
{

    delete ui;

}

void Main_function::COM_PORT_CHOICE_UPDATE() //Переписать на проверку отсутствия в списке combobox или наличию лишнего
{
    string DATA_STRING_COM_PORTS[100];
    QStringList itemsInComboBox;
    int NUMB_PORTS = 0;

    Definitions_device_availability_void(DATA_STRING_COM_PORTS, NUMB_PORTS);

    for (int index = 0; index < ui->COM_PORT_CHOICE->count(); index++)
        itemsInComboBox << ui->COM_PORT_CHOICE->itemText(index);
    qDebug() << itemsInComboBox[0];
        for(int i = 0; i < NUMB_PORTS; i++)
            ui->COM_PORT_CHOICE->addItem(QString::fromStdString(DATA_STRING_COM_PORTS[i]));
}

 void Main_function::COM_PORT_CHOICE_UPDATE(QString CURRENT_CHOICE)
{
    string DATA_STRING_COM_PORTS[100];
    int NUMB_PORTS = 0;
    ui->COM_PORT_CHOICE->clear();
    ui->COM_PORT_CHOICE->addItem("Порт не выбран");
    Definitions_device_availability_void(DATA_STRING_COM_PORTS, NUMB_PORTS);
    for(int i = 0; i < NUMB_PORTS; i++)
        ui->COM_PORT_CHOICE->addItem(QString::fromStdString(DATA_STRING_COM_PORTS[i]));
    ui->COM_PORT_CHOICE->setCurrentText(CURRENT_CHOICE);
}

void Main_function::on_action_17_triggered()
{
    TERMINAL_ENABLE = true;
    ui->OUTPIUT_CONSOLE->show();
    ui->ENTERING->show();
    ui->ENTERING_COMMANDS->show();
    ui->COM_PORT_CHOICE->show();
    ui->CONNECT->show();
    ui->COM_PORT_CHOICE->clear();
    ui->COM_PORT_CHOICE->addItem("Порт не выбран");
    COM_PORT_CHOICE_UPDATE();
}


void Main_function::on_action_10_triggered()
{
    exit(0);
}

void Main_function::on_COM_PORT_CHOICE_activated(int index)
{
  QString CURRENT_CHOICE = ui->COM_PORT_CHOICE->currentText();
  COM_PORT_CHOICE_UPDATE(CURRENT_CHOICE);
}

bool click = false;
void Main_function::on_CONNECT_clicked()
{
    if(click)
    {
        serial_port_variable.close();
        ui->CONNECT->setText("Подключиться");
        click = false;
    }
    else
    {
        serial_port_variable.setPortName(ui->COM_PORT_CHOICE->currentText());
        serial_port_variable.setBaudRate(QSerialPort::Baud115200);   // Значение по умолчанию, не важно при передачи данных по USB для STM32
        ui->CONNECT->setText("Отключиться");
        click = true;
#if DEBUG
      qDebug() << Setting_the_permission_to_work_with_the_COM_port_bool(true);
#endif
    }

}


void Main_function::on_ENTERING_clicked()
{
    serial_port_variable.write(QByteArray::fromStdString(ui->ENTERING_COMMANDS->toPlainText().toStdString()));
    serial_port_variable.waitForBytesWritten();
    ui->ENTERING_COMMANDS->clear();
}


