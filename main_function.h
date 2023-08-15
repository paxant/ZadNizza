#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H

#include <QMainWindow>
#include "QKeyEvent"

QT_BEGIN_NAMESPACE
namespace Ui { class Main_function; }
QT_END_NAMESPACE

class Main_function : public QMainWindow
{
    Q_OBJECT

public:
    Main_function(QWidget *parent = nullptr);
    ~Main_function();

private slots:
    void COM_PORT_CHOICE_UPDATE();

    void COM_PORT_CHOICE_UPDATE(QString CURRENT_CHOICE);

    void on_action_17_triggered();

    void on_action_10_triggered();

    void on_COM_PORT_CHOICE_activated(int index);

    void on_CONNECT_clicked();

    bool Setting_the_permission_to_work_with_the_COM_port_bool(bool CONSOLE_OUTPUT);

    void Read_COM_port_to_CONSOLE_OUTPUT();
    void on_ENTERING_clicked();


private:
    Ui::Main_function *ui;
};
#endif // MAIN_FUNCTION_H
