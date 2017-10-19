#include "mytitlebar.h"
#include <QObjectList>
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include "mymainwindow.h"
MyTitleBar::MyTitleBar(QWidget *parent) :
    QWidget(parent)
{
    CreateWidget();
    SetWindowStyle();
    CreatLayout();
    CreateEventFilter();

    m_ptPress = QPoint(0,0);

    setMaximumHeight(35); //设置高度
}

void MyTitleBar::CreateWidget()
{
    m_pLabelIcon = new QLabel(this);
    QPixmap objPixmap(":/image/jpticowubeiji.png"); //JPT图标
    m_pLabelIcon->setPixmap(objPixmap.scaled(32,20));

    m_pLabelTitile = new QLabel(this);
    m_pLabelTitile->setText(tr("Title"));

//    m_pLabelVersion = new QLabel(this);
//    m_pLabelVersion->setText(tr("(VER1.10)"));

    m_pBtnContent = new QWidget(this);
    m_pBtnContent->setMinimumSize(96,35); ////用来存放按钮的wiget
    m_pBtnContent->setMaximumSize(96,35);

    //最小化
    m_pBtnMin = new QPushButton(m_pBtnContent);
    m_pBtnMin->move(35,1);   //可设置横坐标位置
    m_pBtnMin->setCursor(Qt::PointingHandCursor);
    SetBtnIcon(m_pBtnMin,eBtnStatePress,true);

    //关闭
    m_pBtnClose = new QPushButton(m_pBtnContent);
    m_pBtnClose->move(64,1);
    m_pBtnClose->setCursor(Qt::PointingHandCursor);
    SetBtnIcon(m_pBtnClose,eBtnStatePress,true);

    const QObjectList &objList = m_pBtnContent->children();//得到子控件保存在objList中
    for(int nIndex=0;nIndex<objList.count();++nIndex)
    {
        ((QWidget*)(objList.at(nIndex)))->setMouseTracking(true);
        if( 0 == qstrcmp(objList.at(nIndex)->metaObject()->className(),"QPushButton") )
        {
            connect(((QPushButton*)(objList.at(nIndex))),SIGNAL(clicked()),this,SLOT(slot_btnclick()));
            ((QPushButton*)(objList.at(nIndex)))->setContentsMargins(0,0,0,0);
        }
    }
}

void MyTitleBar::SetWindowStyle()
{
//    setStyleSheet(tr("QLabel{color:#ff0000;font-size:13px;}"
//                     "QToolButton{border:0px;}"
//                     "QPushButton{border:0px;margin:0px;padding:0px}"));
    setStyleSheet(tr("QLabel{color:#ff0000;font-size:13px;/*font-weight:bold;*/}"
                     "QPushButton{border:0px;margin:0px;padding:0px;background:transparent}")
                  );
//    m_pLabelTitile->setStyleSheet(tr("margin-left:314px;"));
//    m_pLabelVersion->setStyleSheet(tr("QLabel{margin-right:140px;font:14px}QLabel:hover{color:#ff0000;}"));//设置版本字体大小
}

void MyTitleBar::CreatLayout()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(0,0,0,0);
    m_pLayout->setSpacing(0);
    m_pLayout->addWidget(m_pLabelIcon);
    m_pLayout->addWidget(m_pLabelTitile);
    m_pLayout->addStretch(1);
//    m_pLayout->addWidget(m_pLabelVersion);

    m_pLayout->addWidget(m_pBtnContent);

    setLayout(m_pLayout);
}

void MyTitleBar::SetBtnIcon(QPushButton *pBtn, eBtnMouseState state, bool bInit)
{
    QString strImagePath = GetBtnImagePath(pBtn,bInit);
    QPixmap objPixmap(strImagePath);
    int nPixWidth = objPixmap.width();
    int nPixHeight = objPixmap.height();
    if(state != eBtnStateNone)
    {
        pBtn->setIcon(objPixmap.copy((nPixWidth/4)*(state),0,nPixWidth/4,nPixHeight));
        pBtn->setIconSize(QSize(nPixWidth/4,nPixHeight));
    }
}

const QString MyTitleBar::GetBtnImagePath(QPushButton *pBtn, bool bInit)
{
    QString strImagePath;
//    if(m_pBtnSkin == pBtn)
//        strImagePath = ":/image/title_bar_menu.png";
//    else if(m_pBtnMenu == pBtn)
//        strImagePath = ":/image/title_bar_menu.png";
    if(m_pBtnMin == pBtn)
        strImagePath = ":/image/sys_button_min1.png"; //最小化图标
 /*   else if(m_pBtnMax == pBtn)
    {
        if(bInit == true || ((MyMainWindow*)parent())->m_bMaxWin==false)
        {
            strImagePath = ":/image/sys_button_max.png";
        }
        else
            strImagePath = ":/image/sys_button_restore.png";
    }*/
    else if(m_pBtnClose == pBtn)
        strImagePath = ":/image/sys_button_close1.png"; //关闭图标

    return strImagePath;
}

void MyTitleBar::CreateEventFilter()
{
//    m_pBtnSkin->installEventFilter(this);
//    m_pBtnMenu->installEventFilter(this);
    m_pBtnMin->installEventFilter(this);//加载事件过滤器
//    m_pBtnMax->installEventFilter(this);
    m_pBtnClose->installEventFilter(this);
}
//更换图片的样式，通过更改按钮状态的图片
bool MyTitleBar::eventFilter(QObject *obj, QEvent *event)
{
    eBtnMouseState eState = eBtnStateNone;
    if(event->type() == QEvent::Enter)
    {
        eState = eBtnStateHover;
    }
    else if(event->type() == QEvent::Leave)
    {
        eState = eBtnStatePress;
    }
    else if(event->type() == QEvent::MouseButtonPress && ((QMouseEvent*)(event))->button() == Qt::LeftButton)
    {
        eState = eBtnStateDefault;
    }
    if(m_pBtnMin == obj || m_pBtnClose == obj)/*m_pBtnSkin == obj || m_pBtnMenu == obj |||| m_pBtnMax == obj   */
    {
        if(eState != eBtnStateNone)
        {
            SetBtnIcon((QPushButton*)obj,eState);
            return false;
        }
    }
    return QWidget::eventFilter(obj,event);
}

void MyTitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(event->y()<2 || event->x()<6 || rect().width()-event->x()<6)
        {
            event->ignore();
            return;
        }
        m_ptPress = event->globalPos();
        m_bLeftButtonPress = true;
    }
    event->ignore();
}

void MyTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftButtonPress && ((MyMainWindow*)parent())->m_bMaxWin==false)
    {
        m_ptMove = event->globalPos();
        MyMainWindow *pMainWindow = (qobject_cast<MyMainWindow*>(parent()));
        pMainWindow->move(pMainWindow->pos()+m_ptMove-m_ptPress);

        m_ptPress = m_ptMove;
    }
    event->ignore();
}

void MyTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPress = false;

    }
    event->ignore();
}

void MyTitleBar::slot_btnclick()
{
    QPushButton *pBtn = (QPushButton*)(sender());
    if(pBtn == m_pBtnMin)
        emit signal_min();
/*    else if(pBtn == m_pBtnMax)
        emit signal_maxrestore();*/
    else if(pBtn == m_pBtnClose)
        emit signal_close();

}
