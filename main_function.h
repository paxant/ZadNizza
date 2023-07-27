#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Main_function; }
QT_END_NAMESPACE

class Main_function : public QMainWindow
{
    Q_OBJECT

public:
    Main_function(QWidget *parent = nullptr);
    ~Main_function();

private:
    Ui::Main_function *ui;
};
#endif // MAIN_FUNCTION_H
