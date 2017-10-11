#include "titlebar.h"
#include <QLabel>
#include <QPushButton>
#include <QObjectList>
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include "main_window.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    m_pLabelIcon = new QLabel(this);
    QPixmap objPixmap(":/image/icon.svg"); //图标
    m_pLabelIcon->setPixmap(objPixmap.scaled(30,22));

    m_pLabelTitile = new QLabel(this);
    m_pLabelTitile->setText(tr("Calculator"));


    m_pBtnContent = new QWidget(this);
    m_pBtnContent->setMinimumSize(96,35); //用来存放按钮的wiget
    m_pBtnContent->setMaximumSize(96,35);

    //菜单
    m_pBtnMenu = new QPushButton(m_pBtnContent);
    m_pBtnMenu->move(0,9);   //可设置横坐标位置
    m_pBtnMenu->setCursor(Qt::PointingHandCursor);
    SetBtnIcon(m_pBtnMenu,eBtnStatePress,true);

    //最小化
    m_pBtnMin = new QPushButton(m_pBtnContent);
    m_pBtnMin->move(35,9);   //可设置横坐标位置
    m_pBtnMin->setCursor(Qt::PointingHandCursor);
    SetBtnIcon(m_pBtnMin,eBtnStatePress,true);

    //关闭
    m_pBtnClose = new QPushButton(m_pBtnContent);
    m_pBtnClose->move(64,9);
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
    SetWindowStyle();
    CreatLayout();//设计分层，从左到右的顺序
    CreateEventFilter();

    m_ptPress = QPoint(0,0);

    setMaximumHeight(35); //设置高度
}

void TitleBar::SetWindowStyle()
{
    setStyleSheet(tr("QLabel{color:#ff0000;font-size:13px;/*font-weight:bold;*/}"
                     "QPushButton{border:0px;margin:0px;padding:0px;background:transparent}")
                  );

}

void TitleBar::CreatLayout()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(0,0,0,0);
    m_pLayout->setSpacing(0);
    m_pLayout->addWidget(m_pLabelIcon);
    m_pLayout->addWidget(m_pLabelTitile);
    m_pLayout->addStretch(0);
    m_pLayout->addWidget(m_pBtnContent);
    setLayout(m_pLayout);
}


void TitleBar::SetBtnIcon(QPushButton *pBtn, eBtnMouseState state, bool bInit)
{
    QString strImagePath = GetBtnImagePath(pBtn,bInit);
    QPixmap objPixmap(strImagePath);
    int nPixWidth = objPixmap.width();//得到四张图片总的宽度
    int nPixHeight = objPixmap.height();//四张图片总的高度
    if(state != eBtnStateNone)
    {
        pBtn->setIcon(objPixmap.copy((nPixWidth/4)*(state),0,nPixWidth/4,nPixHeight));//
        pBtn->setIconSize(QSize(nPixWidth/4,nPixHeight));
    }
}

const QString TitleBar::GetBtnImagePath(QPushButton *pBtn, bool bInit)
{
    QString strImagePath;

    if(m_pBtnMin == pBtn)
        strImagePath = ":/image/sys_button_min.png"; //最小化图标
    else if(m_pBtnMenu == pBtn)
        strImagePath = ":/image/sys_button_max.png"; //关闭图标
    else if(m_pBtnClose == pBtn)
        strImagePath = ":/image/sys_button_close.png"; //关闭图标

    return strImagePath;
}

void TitleBar::CreateEventFilter()
{
    m_pBtnMin->installEventFilter(this);
    m_pBtnMenu->installEventFilter(this);//加载事件过滤器
    m_pBtnClose->installEventFilter(this);
}

//更换图片的样式，通过更改按钮状态的图片
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    eBtnMouseState eState = eBtnStateNone;
    if(event->type() == QEvent::Enter)
    {
        eState = eBtnStateHover;//eBtnStateHover
    }
    else if(event->type() == QEvent::Leave)
    {
        eState = eBtnStatePress;//eBtnStateDefault
    }
    else if(event->type() == QEvent::MouseButtonPress && ((QMouseEvent*)(event))->button() == Qt::LeftButton)
    {
        eState = eBtnStateDefault;//eBtnStatePress
    }
    if(m_pBtnMin == obj || m_pBtnClose == obj || m_pBtnMenu == obj)/*m_pBtnSkin == obj  |||| m_pBtnMax == obj   */
    {
        if(eState != eBtnStateNone)
        {
            SetBtnIcon((QPushButton*)obj,eState);
            return false;
        }
    }
    return QWidget::eventFilter(obj,event);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
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

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftButtonPress && ((MainWindow*)parent())->m_bMaxWin==false)
    {
        m_ptMove = event->globalPos();
        MainWindow *pMainWindow = (qobject_cast<MainWindow*>(parent()));
        pMainWindow->move(pMainWindow->pos()+m_ptMove-m_ptPress);

        m_ptPress = m_ptMove;
    }
    event->ignore();
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPress = false;

    }
    event->ignore();
}

void TitleBar::slot_btnclick()
{
    QPushButton *pBtn = (QPushButton*)(sender());
    if(pBtn == m_pBtnMin)
        emit signal_min();
    else if(pBtn == m_pBtnClose)
        emit signal_close();
    else if(pBtn == m_pBtnMenu)
        emit signal_menu();

}
