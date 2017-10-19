#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QVBoxLayout>
#include <QDateTime>
#include "mybasedialog.h"
#include "mytitlebar.h"
#include "mytoolbar.h"
#include "mycontentwidget.h"

class MyMainWindow : public MyBaseDialog
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = 0);
    
    MyTitleBar *m_pTitleBar;
    MyToolBar *m_pToolBar;
    MyContentWidget *m_pConWidget;
    QVBoxLayout *m_pMainLayout;

signals:
    
public slots:



};

#endif // MYMAINWINDOW_H
