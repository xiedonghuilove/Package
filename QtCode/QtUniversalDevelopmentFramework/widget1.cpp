#include "widget1.h"
#include "ui_widget1.h"

Widget1::Widget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget1)
{
    ui->setupUi(this);
}

Widget1::~Widget1()
{
    delete ui;
}
