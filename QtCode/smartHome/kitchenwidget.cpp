#include "kitchenwidget.h"
#include "ui_kitchenwidget.h"

KitchenWidget::KitchenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KitchenWidget)
{
    ui->setupUi(this);

    m_styleOn = "QLabel{border-image:url(:/images/module/light_on.png);border:0px;}";
    m_styleoff = "QLabel{border-image:url(:/images/module/light_off.png);border:0px;}";
    ui->pbn_light_main->setFocusPolicy(Qt::NoFocus);

    setToolButtonStyle(ui->tbn_smoke_add,tr("浓度加"),
                       ":/images/module/temp_add.png");
    setToolButtonStyle(ui->tbn_smoke_sub,tr("浓度减"),
                       ":/images/module/temp_sub.png");

     ui->label_light_main->setStyleSheet(m_styleoff);
     ui->pbn_light_main->setText("打开");

     //设置预设的烟雾浓度
     smorkcur = 8;
     ui->label_set_smoke->setText(QString::number(smorkcur)+"%");
}

KitchenWidget::~KitchenWidget()
{
    delete ui;
}

void KitchenWidget::setToolButtonStyle(QToolButton *tbn,
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


void KitchenWidget::on_pbn_light_main_clicked()
{
    a++;
    Flag = !Flag;
     if(Flag)
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
//减少：
void KitchenWidget::on_tbn_smoke_sub_clicked()
{
    smorkcur--;
    if(smorkcur <= 1)
    {
        smorkcur = 1;
    }
    ui->label_set_smoke->setText(QString::number(smorkcur)+"%");
}


//增加
void KitchenWidget::on_tbn_smoke_add_clicked()
{

    smorkcur++;
    if(smorkcur >= 50)
    {
        smorkcur = 50;
    }
    ui->label_set_smoke->setText(QString::number(smorkcur)+"%");

}
