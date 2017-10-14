#include "modelchoosewidget.h"
#include "ui_modelchoosewidget.h"
#include <QDebug>

ModelChooseWidget::ModelChooseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelChooseWidget)
{
    ui->setupUi(this);
}

ModelChooseWidget::~ModelChooseWidget()
{
    delete ui;
}

void ModelChooseWidget::on_pbn_leve_home_clicked()
{
//    a++;
//    qDebug()<<"a="<<a;
    FlagSTateHome=!FlagSTateHome;
    qDebug()<<"FlagStateHome2 = "<<FlagSTateHome;
    if(FlagSTateHome)
    {
        ui->model_state_label->setText("离家模式开启");
    }
    else
    {
        ui->model_state_label->setText("离家模式关闭");
    }
}

void ModelChooseWidget::on_pbn_go_home_clicked()
{
    FlagSTateHome1=!FlagSTateHome1;
    qDebug()<<"FlagStateHome2 = "<<FlagSTateHome1;
    if(FlagSTateHome1)
    {
        ui->model_state_label->setText("回家模式开启");
    }
    else
    {
        ui->model_state_label->setText("回家模式关闭");
    }

}


void ModelChooseWidget::on_pbn_key_led_clicked()
{
    FlagSTateHome2=!FlagSTateHome2;
    qDebug()<<"FlagStateHome2 = "<<FlagSTateHome2;
    if(FlagSTateHome2)
    {
        ui->model_state_label->setText("一键关灯模式开启");
    }
    else
    {
        ui->model_state_label->setText("一键关灯模式关闭");
    }
}
