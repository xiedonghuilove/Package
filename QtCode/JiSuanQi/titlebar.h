#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

enum eBtnMouseState{
    eBtnStateNone,//未选择状态 1
    eBtnStateDefault,//默认状态 2
    eBtnStateHover,//鼠标移动到状态 3
    eBtnStatePress//按下状态 4
};

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    QLabel *m_pLabelIcon,*m_pLabelTitile,*m_pLabelVersion;
    QWidget *m_pBtnContent;
    QPushButton *m_pBtnMin,*m_pBtnClose,*m_pBtnMenu;  /**m_pBtnSkin,*m_pBtnMenu,*m_pBtnMax,*/
    QHBoxLayout * m_pLayout;
    QPoint m_ptPress,m_ptMove;
    bool   m_bLeftButtonPress;

    void SetBtnIcon(QPushButton *pBtn,eBtnMouseState state,bool bInit=false);
    const QString GetBtnImagePath(QPushButton *pBtn,bool bInit=false);

    void SetWindowStyle(void);
    void CreatLayout(void);

     void CreateEventFilter(void);

     bool eventFilter(QObject *, QEvent *);

     void mousePressEvent(QMouseEvent *);
     void mouseMoveEvent(QMouseEvent *);
     void mouseReleaseEvent(QMouseEvent *);
 signals:
     void signal_min(void);
     void signal_menu(void);
     void signal_maxrestore(void);
     void signal_close(void);
 public slots:
     void slot_btnclick(void);

};

#endif // TITLEBAR_H
