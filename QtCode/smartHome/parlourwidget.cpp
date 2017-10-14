#include "parlourwidget.h"
#include "ui_parlourwidget.h"
#include <QDebug>

Parlourwidget::Parlourwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Parlourwidget)
{
    ui->setupUi(this);
  //开始设置按钮的样式。
    this->setToolButtonStyle(ui->tbn_temp_add,tr("温度+"),
                             ":/images/module/temp_add.png");
    this->setToolButtonStyle(ui->tbn_temp_sub,tr("温度-"),
                             ":/images/module/temp_sub.png");
    this->setToolButtonStyle(ui->tbn_hum_add,tr("湿度+"),
                             ":/images/module/temp_add.png");
    this->setToolButtonStyle(ui->tbn_hum_sub,tr("湿度-"),
                             ":/images/module/temp_sub.png");

    m_styleOn = "QLabel{border-image:url(:/images/module/light_on.png);border:0px;}";
    m_styleoff = "QLabel{border-image:url(:/images/module/light_off.png);border:0px;}";


     ui->label_light_main->setStyleSheet(m_styleoff);
     ui->label_light_top->setStyleSheet(m_styleoff);
     ui->label_light_help->setStyleSheet(m_styleoff);

     ui->pbn_light_main->setText("打开");
     ui->pbn_light_top->setText("打开");
     ui->pbn_light_help->setText("打开");
     //初始设定温度为28，湿度为50%
     tempcur = 28;
     shiducur = 50;
     ui->label_set_temp->setText(QString::number(tempcur));
     ui->label_set_hum->setText(QString::number(shiducur));

}

Parlourwidget::~Parlourwidget()
{
    delete ui;
}


void Parlourwidget::setToolButtonStyle(QToolButton *tbn,
                                       const QString &text,
                                       const QString iconName)
{
    //设置显示的文本
    tbn->setText(text);
    //tbn->setFont(QFont("文泉驿雅黑",10,QFont::Normal));

    tbn->setAutoRaise(true);
    //设置按钮图标
    tbn->setIcon(QPixmap(QString("%1").arg(iconName)));
    tbn->setIconSize(QSize(40,40));
    //设置文本在图标下边
    tbn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}


//主灯
void Parlourwidget::on_pbn_light_main_clicked()
{
    a++;
    flagLightmain = !flagLightmain;
    if(flagLightmain)
    {
        ui->label_light_main->setStyleSheet(m_styleOn);
        ui->pbn_light_main->setText("关闭");
    }
    else
    {
        ui->label_light_main->setStyleSheet(m_styleoff);
        ui->pbn_light_main->setText("打开");
    }
}
//顶灯
void Parlourwidget::on_pbn_light_top_clicked()
{
    flagLighttop = !flagLighttop;
    if(flagLighttop)
    {
        ui->label_light_top->setStyleSheet(m_styleOn);
        ui->pbn_light_top->setText("关闭");
    }
    else
    {
        ui->label_light_top->setStyleSheet(m_styleoff);
        ui->pbn_light_top->setText("打开");
    }
}
//副灯
void Parlourwidget::on_pbn_light_help_clicked()
{
    flagLighthelp = !flagLighthelp;
    if(flagLighthelp)
    {
        ui->label_light_help->setStyleSheet(m_styleOn);
        ui->pbn_light_help->setText("关闭");
    }
    else
    {
        ui->label_light_help->setStyleSheet(m_styleoff);
        ui->pbn_light_help->setText("打开");
    }
}




//  温度加
void Parlourwidget::on_tbn_temp_add_clicked()
{
    tempcur++;
    QString tempstr = QString::number(tempcur);
    qDebug()<<"温度 = "<<tempcur;

    if(tempcur >= 38)
    {
        tempcur = 38;
    }
    ui->label_set_temp->setText(tempstr);
}


void Parlourwidget::on_tbn_temp_sub_clicked()
{
    tempcur--;

    if(tempcur <= 15)
    {
        tempcur = 15;
    }
    ui->label_set_temp->setText(QString::number(tempcur));
}

//湿度加
void Parlourwidget::on_tbn_hum_add_clicked()
{
    shiducur++;
    if(shiducur >= 90)
    {
        shiducur = 90;
    }
    ui->label_set_hum->setText(QString::number(shiducur));
}
//湿度减
void Parlourwidget::on_tbn_hum_sub_clicked()
{
    shiducur--;
    if(shiducur <= 20)
    {
        shiducur = 20;
    }
    ui->label_set_hum->setText(QString::number(shiducur));
}
