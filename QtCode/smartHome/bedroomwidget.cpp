#include "bedroomwidget.h"
#include "ui_bedroomwidget.h"

BedRoomWidget::BedRoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BedRoomWidget)
{
    ui->setupUi(this);

    m_styleOn = "QLabel{border-image:url(:/images/module/light_on.png);border:0px;}";
    m_styleOff = "QLabel{border-image:url(:/images/module/light_off.png);border:0px;}";

    ui->label_light_top->setStyleSheet(m_styleOff);
    ui->pbn_light_left->setText("打开");
    ui->label_light_help->setStyleSheet(m_styleOff);
    ui->pbn_light_right->setText("打开");
}

BedRoomWidget::~BedRoomWidget()
{
    delete ui;
}

void BedRoomWidget::on_pbn_light_left_clicked()
{
    a++;
    Flag = !Flag;
    if(Flag)
    {   ui->label_light_top->setStyleSheet(m_styleOn);
        ui->pbn_light_left->setText("关闭");
    }
    else
    {
        ui->label_light_top->setStyleSheet(m_styleOff);
        ui->pbn_light_left->setText("打开");
    }
}

void BedRoomWidget::on_pbn_light_right_clicked()
{
    a++;
    Flag1 = !Flag1;
    if(Flag1)
    {   ui->label_light_help->setStyleSheet(m_styleOn);
        ui->pbn_light_right->setText("关闭");
    }
    else
    {
        ui->label_light_help->setStyleSheet(m_styleOff);
        ui->pbn_light_right->setText("打开");
    }
}
