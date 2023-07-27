#include "main_function.h"
#include "ui_main_function.h"

Main_function::Main_function(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_function)
{
    ui->setupUi(this);
}

Main_function::~Main_function()
{
    delete ui;
}

