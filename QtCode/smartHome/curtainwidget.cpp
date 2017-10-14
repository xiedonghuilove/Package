#include "curtainwidget.h"
#include "ui_curtainwidget.h"

CurtainWidget::CurtainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurtainWidget)
{
    ui->setupUi(this);
}

CurtainWidget::~CurtainWidget()
{
    delete ui;
}
//打开槽函数
void CurtainWidget::on_pbnOpenCurtain_clicked()
{
    ui->lable_state->setText("窗帘打开中");
}
//停止槽
void CurtainWidget::on_pbnStopCurtain_clicked()
{
    ui->lable_state->setText("窗帘停止中");
}


void CurtainWidget::on_pbnCloseCurtain_clicked()
{
    ui->lable_state->setText("窗帘关闭中");
}
