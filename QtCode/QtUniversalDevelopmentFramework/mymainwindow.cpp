#include "mymainwindow.h"
#include <QDebug>


MyMainWindow::MyMainWindow(QWidget *parent) :
    MyBaseDialog(parent)
{

    setMinimumSize(960,645);
    setMaximumSize(960,645);

    m_pTitleBar = new MyTitleBar(this);//标题栏
    m_pToolBar = new MyToolBar(this);//工具栏
    m_pConWidget = new MyContentWidget(this);//内容栏

    m_pMainLayout = new QVBoxLayout(this);//垂直布局

    m_pMainLayout->addWidget(m_pTitleBar);
    m_pMainLayout->addWidget(m_pToolBar);
    m_pMainLayout->addWidget(m_pConWidget);
    m_pMainLayout->setContentsMargins(2,0,2,2);

    connect(m_pTitleBar,SIGNAL(signal_close()),this,SLOT(close()));
    connect(m_pTitleBar,SIGNAL(signal_min()),this,SLOT(showMinimized()));
    connect(m_pToolBar,SIGNAL(signal_toolbar(int)),m_pConWidget,SLOT(slot_toolbar(int)));


}




