#include "widget.h"
#include "ui_widget.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QToolButton>
#include <QThread>
#include <QDebug>
#include <QPropertyAnimation>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initForm();
    this->initWidget();
    this->initDataTime();
}

Widget::~Widget()
{
    delete ui;
}

//界面样式初始化
void Widget::initForm()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle(tr("SmartHome System"));

    //设置顶部和首页的样式：
    ui->tbnSetting->setText(tr("设置"));
    ui->tbnSetting->setIcon(QPixmap(":/images/setting_pressed.png"));
     ui->tbnSetting->setIconSize(QPixmap(":/images/setting_pressed.png").size());
    ui->tbnSetting->setAutoRaise(true);//鼠标经过是自动凸起
    ui->tbnSetting->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//文本在图标的下面


    ui->tbnHome->setText(tr("首页"));
    ui->tbnHome->setIcon(QPixmap(":/images/home_normal.png"));
    ui->tbnHome->setIconSize(QPixmap(":/images/home_normal.png").size());
    ui->tbnHome->setAutoRaise(true);
    ui->tbnHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //中间部分样式
    ui->tbnBedRoom->setText(tr("卧室"));
    ui->tbnBedRoom->setAutoRaise(true);//auto 自动  raise 升起，凸起
    ui->tbnBedRoom->setIcon(QPixmap(":/images/midwidget/Bedroom.png"));
    ui->tbnBedRoom->setIconSize(QPixmap(":/images/midwidget/Bedroom.png").size());
    ui->tbnBedRoom->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//文本在图标下面。

        ui->tbnParlor->setText(tr("客厅"));
        ui->tbnParlor->setAutoRaise(true);
        ui->tbnParlor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        ui->tbnParlor->setIcon(QPixmap(":/images/midwidget/Parlor.png"));
        ui->tbnParlor->setIconSize(QPixmap(":/images/midwidget/Parlor.png").size());

        ui->tbnKitchen->setText(tr("厨房"));
        ui->tbnKitchen->setAutoRaise(true);
        ui->tbnKitchen->setIcon(QPixmap(":/images/midwidget/kitchen.png"));
        ui->tbnKitchen->setIconSize(QPixmap(":/images/midwidget/kitchen.png").size());
        ui->tbnKitchen->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->tbnSafety->setText(tr("安防"));
        ui->tbnSafety->setAutoRaise(true);
        ui->tbnSafety->setIcon(QPixmap(":/images/midwidget/Safety.png"));
        ui->tbnSafety->setIconSize(QPixmap(":/images/midwidget/Safety.png").size());
        ui->tbnSafety->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

//底部菜单的样式
        ui->tbnControl->setText(tr("家居控制"));
        ui->tbnControl->setAutoRaise(true);
        ui->tbnControl->setIcon(QPixmap(":/images/bottom/control.png"));
        ui->tbnControl->setIconSize(QPixmap(":/images/bottom/control.png").size());
        ui->tbnControl->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->tbnCurtain->setText(tr("窗帘"));
        ui->tbnCurtain->setAutoRaise(true);
        ui->tbnCurtain->setIcon(QPixmap(":/images/bottom/video.png"));
        ui->tbnCurtain->setIconSize(QPixmap(":/images/bottom/video.png").size());
        ui->tbnCurtain->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->tbnMusic->setText(tr("音乐"));
        ui->tbnMusic->setAutoRaise(true);
        ui->tbnMusic->setIcon(QPixmap(":/images/bottom/music.png"));
        ui->tbnMusic->setIconSize(QPixmap(":/images/bottom/music.png").size());
        ui->tbnMusic->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

//        ui->tbnNight->setText(tr("夜间"));
//        ui->tbnNight->setAutoRaise(true);
//        ui->tbnNight->setIcon(QPixmap(":/images/bottom/night.png"));
//        ui->tbnNight->setIconSize(QPixmap(":/images/bottom/night.png").size());
//        ui->tbnNight->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->tbnModel->setText(tr("模式选择"));
        ui->tbnModel->setAutoRaise(true);
        ui->tbnModel->setIcon(QPixmap(":/images/bottom/reset.png"));
        ui->tbnModel->setIconSize(QPixmap(":/images/bottom/reset.png").size());
        ui->tbnModel->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->tbnStasistion->setText(tr("统计"));
        ui->tbnStasistion->setAutoRaise(true);
        ui->tbnStasistion->setIcon(QPixmap(":/images/bottom/statistics.png"));
        ui->tbnStasistion->setIconSize(QPixmap(":/images/bottom/statistics.png").size());
        ui->tbnStasistion->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        ui->stackedWidget->setCurrentIndex(E_HOME_WIDGET);
        qDebug()<<"E_HOME_WIDGET is = "<<E_HOME_WIDGET;
        //要按下家居控制按钮后才进入中间部分样式。



}

void Widget::initWidget()
{
    m_settingDialog = new SystemSettingDialog;
    m_statisticWidget = new StatisticWidget();
    m_bedRoomWidget = new BedRoomWidget();
    m_curtainWidget = new CurtainWidget();
    m_musicPlayWidget = new MusicWidget();
    m_modelWidget = new ModelChooseWidget();
    m_parlourWidget = new Parlourwidget();
    m_kitchenWidget = new KitchenWidget();
    ui->stackedWidget->addWidget(m_bedRoomWidget);
    ui->stackedWidget->addWidget(m_curtainWidget);
    ui->stackedWidget->addWidget(m_musicPlayWidget);
    ui->stackedWidget->addWidget(m_modelWidget);
    ui->stackedWidget->addWidget(m_parlourWidget);
    ui->stackedWidget->addWidget(m_kitchenWidget);
    ui->stackedWidget->addWidget(m_statisticWidget);
}

void Widget::initDataTime()
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotShowCurrentDataTime()));
    m_timer->start(1000);//定时1s钟。
}

void Widget::startAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "geometry");
    animation->setDuration(800);
    animation->setStartValue(QRect(0, 0,100, 30));
    animation->setEndValue(QRect(0, 0, 800, 360));
    animation->start();
}



//显示当期的日期和时间
void Widget::slotShowCurrentDataTime()
{
    ui->label_hour->setText(QTime::currentTime().toString("hh"));
    ui->label_min->setText(QTime::currentTime().toString("mm"));
    ui->label_sec->setText(QTime::currentTime().toString("ss"));
    ui->label_data->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    ui->label_week->setText(QDate::currentDate().toString("dddd"));

}


void Widget::setCurrentWidget(enum_widget enum_widget_name)
{
    startAnimation();
    ui->stackedWidget->setCurrentIndex(enum_widget_name);
}

void Widget::on_tbnControl_clicked()
{
    this->setCurrentWidget(E_Control_WIDGET);//按下控制按钮后才
    qDebug()<<"当前索引页 控制：="<<ui->stackedWidget->currentIndex();
    //用这种方式就实现了，StackedWidget 页面的切换。
}

void Widget::on_tbnHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(E_HOME_WIDGET);
     qDebug()<<"当前索引页 主页：="<<ui->stackedWidget->currentIndex();
}



void Widget::on_tbnBedRoom_clicked()
{

  ui->stackedWidget->setCurrentIndex(E_BEDROOM_WIDGET);
  qDebug()<<"当前索引页 卧室：="<<ui->stackedWidget->currentIndex();
}

void Widget::on_tbnCurtain_clicked()
{
    ui->stackedWidget->setCurrentIndex(E_CURTAIN_WIDGET);
}

void Widget::on_tbnMusic_clicked()
{
    ui->stackedWidget->setCurrentIndex(E_MUSIC_WIDGET);
}

void Widget::on_tbnModel_clicked()
{
    ui->stackedWidget->setCurrentIndex(E_MODEL_WIDGET);
}

void Widget::on_tbnParlor_clicked()
{
    this->setCurrentWidget(E_PARLOUR_WIDGET);
}

void Widget::on_tbnKitchen_clicked()
{
    this->setCurrentWidget(E_KITCHEN_WIDGET);
}

void Widget::on_tbnSetting_clicked()
{
     m_settingDialog->show();
}

void Widget::on_tbnStasistion_clicked()
{
  ui->stackedWidget->setCurrentIndex(E_TEMPTURE);
}

void Widget::on_tbnSafety_clicked()
{
    QMessageBox::information(this,"报警","正在报警，请稍后！",QMessageBox::Yes,QMessageBox::No);
}
