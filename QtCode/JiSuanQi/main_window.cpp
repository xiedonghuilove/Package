#include "main_window.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : MyBaseDialog(parent)
{
    menu = new QMenu;
    titleBar = new TitleBar(this);//标题栏
    mainwidget = new QWidget;
    simpleMode = new SimpleMode;
    scMode = new ScientificMode;

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->addWidget(titleBar);
    m_pMainLayout->addWidget(simpleMode);
    m_pMainLayout->addWidget(scMode);
    m_pMainLayout->setContentsMargins(0,0,0,0);//设置内容间距
    scMode->close();

    simpleAction = new QAction("简单模式", this);
    scientificAction = new QAction("科学计算", this);
    clearRecord = new QAction("清除记录", this);
    hideAction = new QAction("程序员型", this);
    showAction = new QAction("显示按键", this);
    lightAction = new QAction("浅色主题", this);
    darkAction = new QAction("深色主题", this);

    menu->addAction(simpleAction);
    menu->addAction(scientificAction);
    menu->addAction(hideAction);
    menu->addAction(clearRecord);
    menu->addAction(showAction);
    menu->addAction(lightAction);
    menu->addAction(darkAction);

    titleBar->m_pBtnMenu->setMenu(menu);
    titleBar->m_pBtnMenu->setStyleSheet("QPushButton::menu-indicator{image:none}");
    connect(titleBar,SIGNAL(signal_min()),this,SLOT(showMinimized()));
    connect(titleBar,SIGNAL(signal_close()),this,SLOT(close()));

    //点击菜单样式触发草函数
    connect(lightAction,SIGNAL(triggered(bool)),this,SLOT(switchToLightTheme()));
    connect(darkAction,SIGNAL(triggered(bool)),this,SLOT(switchToDarkTheme()));
    connect(scientificAction,SIGNAL(triggered(bool)),this,SLOT(switchToScientificMode()));
    connect(simpleAction,SIGNAL(triggered(bool)),this,SLOT(switchToSimpleMode()));
    connect(clearRecord,SIGNAL(triggered(bool)),this,SLOT(switchToClear()));

    //生成一个配置文件
    config = new QSettings("myapp.ini",QSettings::IniFormat);

    loadHistory();
    InitMode();
    InitTheme();
    initUI();
    scMode->editor->setFocus();
}

void MainWindow::initUI()
{

    setWindowFlags(Qt::FramelessWindowHint);

}

//切换浅色背景
void MainWindow::switchToLightTheme()
{
    QFile file(":/qss/light.qss");
    file.open(QFile::ReadOnly);//只读
    QTextStream qss(&file);
    QString lightstysheet = qss.readAll();
    qApp->setStyleSheet(lightstysheet);
    scMode->editor->setStyleSheet("font-size: 18px;color: #000000;border: 1px solid #D8D8D8;background: #D8D8D8;");
    config->setValue("theme","light");
}
//切换深色背景
void MainWindow::switchToDarkTheme()
{
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    QTextStream qss(&file);
    QString darkstysheet = qss.readAll();
    qApp->setStyleSheet(darkstysheet);
    scMode->editor->setStyleSheet("font-size: 18px;color: #FFFFFF;border: 1px solid #2B2B2B;background: #2B2B2B;");
    config->setValue("theme","dark");

}
//切换科学
void MainWindow::switchToScientificMode()
{
    setFixedSize(650,450);
    simpleAction->setVisible(true);
    scientificAction->setVisible(false);
    scMode->show();
    simpleMode->close();
    config->setValue("mode","scientific");
    scMode->editor->setFocus();
}
//切换为普通
void MainWindow::switchToSimpleMode()
{
    setFixedSize(260,370);
    simpleAction->setVisible(false);
    scientificAction->setVisible(true);
    scMode->close();
    simpleMode->show();
    config->setValue("mode","simple");
    simpleMode->editText->setFocus();
}

//清除记录
void MainWindow::switchToClear()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to clear history?");
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Ok://确定清除
        {
            QFile file("myapp.ini");

            if(file.open(QFile::WriteOnly))//只写
            {
                QTextStream out(&file);
                out << "";
            }
            scMode->display->clear();
        }
        break;
        case QMessageBox::Cancel:
        {
            qDebug()<<"取消";
        }
        break;
    }
}

//关闭窗口时触发事件
void MainWindow::closeEvent(QCloseEvent *)
{
    qDebug()<<"关闭窗口保存信息";
    QFile file("myapp.ini");
    if(file.open(QFile::WriteOnly))
    {
        QTextStream out(&file);
        out << scMode->display->toPlainText();
    }
    file.close();
}

//加载历史
void MainWindow::loadHistory()
{
    qDebug()<<"加载历史记录";
    QFile file("myapp.ini");
    QTextStream out(&file);
    if(file.open(QFile::ReadOnly))//只读
    {
        scMode->display->setPlainText(file.readAll());
        qDebug()<<scMode->display->toPlainText();
    }
    else
    {
        file.open(QFile::WriteOnly);
        out<<"";
    }
    file.close();
}
//默认初始化状态
void MainWindow::InitMode()
{
    if(config->value("mode").toString() == "simple")
    {
        simpleAction->setVisible(false);
        scientificAction->setVisible(true);
        switchToSimpleMode();
    }
    else//科学计算
    {
        simpleAction->setVisible(true);
        scientificAction->setVisible(false);
        switchToScientificMode();

    }
}

//加载样式
void MainWindow::InitTheme()
{
    if(config->value("theme").toString() == "light")
    {
        lightAction->setVisible(false);
        darkAction->setVisible(true);
        switchToLightTheme();
    }
    else//黑色背景
    {
        lightAction->setVisible(true);
        darkAction->setVisible(false);
        switchToDarkTheme();
    }
}
