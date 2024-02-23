#include "temp.h"
#include "ui_temp.h"

Temp::Temp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Temp)
{
    ui->setupUi(this);
}

Temp::~Temp()
{
    delete ui;
}
