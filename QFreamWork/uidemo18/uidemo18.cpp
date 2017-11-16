#pragma execution_character_set("utf-8")

#include "uidemo18.h"
#include "ui_uidemo18.h"
#include "iconhelper.h"

#define iconSize    50
#define iconWidth   100
#define iconHeight  70
#define navBtnWidth 45
#define navIcoWidth 18

UIDemo18::UIDemo18(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIDemo18)
{
    ui->setupUi(this);
    this->initForm();//初始化样式
    this->initNav();
}

UIDemo18::~UIDemo18()
{
    delete ui;
}

void UIDemo18::initForm()
{
    ui->labTitle->setText("可视化围栏报警平台");//顶部标题栏
    this->setWindowTitle(ui->labTitle->text());
    this->setProperty("canMove", true);//将对象的名称属性的设置为canMove。 可以移动
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);//去除标题栏
    //自定义顶部标题栏窗体
    ui->widgetTop->setProperty("flag", "nav");//设置属性
    ui->widgetTop->setFixedHeight(40);//设置高度

    // 设置按钮图标
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf073, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->btnMsg, 0xf27a, navIcoWidth);

    QStringList qss;

    //全局无焦点虚边框,全局文字颜色,全局字号
    qss.append(QString("*{outline:0px;color:#FEFEFE;}"));

    //主窗体背景
    qss.append(QString("QWidget#widgetMain{border-image:url(%1);}").arg(":/image/main.jpg"));

    //标题字体大小
    qss.append(QString("QLabel#labTitle{font:%1px;}").arg(navIcoWidth));

//    //顶部导航
    qss.append(QString("QWidget[flag=\"nav\"]{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                       "stop:0 %1,stop:1 %2);}").arg("#00688B").arg("#093746"));
    qss.append(QString("QWidget[flag=\"nav\"] QAbstractButton{background:none;border:none;"
                       "min-width:%1px;max-width:%1px;}").arg(navBtnWidth));

    this->setStyleSheet(qss.join(""));
}

void UIDemo18::initNav()
{
    QList<QString> listColorBg;//背景颜色
    listColorBg << "#1570A5" << "#16A085" << "#C0392B" << "#047058" << "#9B59BB" << "#34495E";
    QList<QString> listColorText;//字体颜色
    listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

    QList<QChar> listChar;//对应的图标 Unicode
    listChar << 0xf030 << 0xf108 << 0xf002 << 0xf03e << 0xf0e8 << 0xf085;
    QList<QString> listText;
    listText << "地图监控" << "设备监控" << "记录查询" << "地图管理" << "设备管理" << "系统设置";

    btns << ui->btnViewMap << ui->btnViewPanel << ui->btnData << ui->btnMap << ui->btnDevice << ui->btnConfig;
    for (int i = 0; i < btns.count(); i++) {
        QToolButton *btn = btns.at(i);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(QSize(iconWidth, iconHeight));

        QPixmap pix = IconHelper::Instance()->getPixmap(listColorText.at(i), listChar.at(i), iconSize, iconWidth, iconHeight);
        btn->setIcon(QIcon(pix));
        btn->setText(listText.at(i));
        btn->setCursor(Qt::PointingHandCursor);

        QStringList list;
        list.append(QString("QToolButton{font:%1px;background:%2;}").arg(iconSize / 2.5).arg(listColorBg.at(i)));
        list.append(QString("QToolButton{border:none;border-radius:8px;padding:30px;}"));
        list.append(QString("QToolButton:pressed{background:%1;}").arg("#737A97"));
        btn->setStyleSheet(list.join(""));//设置样式

        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }
}

void UIDemo18::buttonClicked()
{
    QToolButton *btn = (QToolButton *)sender();
    ui->stackedWidget->setCurrentIndex(1);
    ui->labTitle->setText(btn->text());
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
}

void UIDemo18::on_btnReturn_pressed()
{
    int index = ui->stackedWidget->currentIndex();
    if (index != 0) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->labTitle->setText("可视化围栏报警平台");
        IconHelper::Instance()->setIcon(ui->btnReturn, 0xf073, navIcoWidth);
    }
}

void UIDemo18::on_btnMsg_pressed()
{
    exit(0);
}
