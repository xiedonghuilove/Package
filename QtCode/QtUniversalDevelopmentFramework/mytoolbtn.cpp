#include "mytoolbtn.h"

MyToolBtn::MyToolBtn(QWidget *parent) :
    QToolButton(parent)
{
}

//按钮图片路径   按钮名称     --->   继承 QToolButton
MyToolBtn::MyToolBtn(const QString &strImage, const QString &strInfo, QWidget *parent):
    QToolButton(parent),m_bOver(false),m_bPress(false),m_strImage(strImage),m_strInfo(strInfo)
{
    QPalette objPalette = palette();
    objPalette.setColor(QPalette::ButtonText,QColor(220,220,220)); //设置菜单字体颜色
    setPalette(objPalette);

    setStyleSheet("QToolButton{border:0px;}");

    setIconSize(QSize(80,60));
    resize(80,85);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setIcon(QPixmap(strImage));
    setText(strInfo);

    setCursor(Qt::PointingHandCursor);

    connect(this,SIGNAL(pressed()),this,SLOT(slot_press()));

}

void MyToolBtn::SetPress(bool bEnable)
{
    if(bEnable!=m_bPress)
    {
        m_bPress = bEnable;
        update();
    }
}


void MyToolBtn::SetOver(bool bEnable)
{
    if(bEnable!=m_bOver)
    {
        m_bOver = bEnable;
        update();
    }
}

void MyToolBtn::painterInfo(QPainter *pPainter)
{


    pPainter->drawPixmap(rect(),QPixmap("/*:/image/ToolBtnBg.png*/"));

//    QPen objPen(Qt::NoBrush,1);
//    pPainter->setPen(objPen);
//    QLinearGradient objlinear(rect().topLeft(),rect().bottomRight());
//    objlinear.setColorAt(0,QColor(200,200,200,120));
//    objlinear.setColorAt(0.5,QColor(120,120,120,180));
//    objlinear.setColorAt(1,QColor(200,200,200,120));

//    QBrush objBrush(objlinear);
//    pPainter->setBrush(objBrush);

//    pPainter->drawRoundRect(rect(),7,7);
}

void MyToolBtn::enterEvent(QEvent *)
{
    SetOver(true);
}

void MyToolBtn::leaveEvent(QEvent *)
{
    SetOver(false);
}

void MyToolBtn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_bPress)
    {
        painterInfo(&painter);
    }
    else if(m_bOver)
    {
        painterInfo(&painter);
    }
    QToolButton::paintEvent(event);
}

void MyToolBtn::slot_press()
{
    SetPress(true);
    emit signal_parent(this);
}

