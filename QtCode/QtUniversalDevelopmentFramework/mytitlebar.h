#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
enum eBtnMouseState{
    eBtnStateNone,
    eBtnStateDefault,
    eBtnStateHover,
    eBtnStatePress
};

class MyTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit MyTitleBar(QWidget *parent = 0);
    QLabel *m_pLabelIcon,*m_pLabelTitile,*m_pLabelVersion;
    QWidget *m_pBtnContent;
    QPushButton *m_pBtnMin,*m_pBtnClose;  /**m_pBtnSkin,*m_pBtnMenu,*m_pBtnMax,*/
    QHBoxLayout * m_pLayout;
    QPoint m_ptPress,m_ptMove;
    bool   m_bLeftButtonPress;


    void CreateWidget(void);
    void SetWindowStyle(void);
    void CreatLayout(void);

    void SetBtnIcon(QPushButton *pBtn,eBtnMouseState state,bool bInit=false);
    const QString GetBtnImagePath(QPushButton *pBtn,bool bInit=false);

    void CreateEventFilter(void);

    bool eventFilter(QObject *, QEvent *);
//    bool nativeEvent(const QByteArray &event,void *message,long *result);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void signal_min(void);
    void signal_maxrestore(void);
    void signal_close(void);
public slots:
    void slot_btnclick(void);
};

#endif // MYTITLEBAR_H
