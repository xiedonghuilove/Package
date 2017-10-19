#include "mybasedialog.h"
MyBaseDialog::MyBaseDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumWidth(390);
    setMinimumHeight(250);
    setMouseTracking(true);

    m_bMaxWin = false;
    m_bLeftBtnPress = false;

}

bool MyBaseDialog::nativeEvent(const QByteArray &event, void *message1, long *result)
{
    Q_UNUSED(event);
    MSG *message = reinterpret_cast<MSG*>(message1);

    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam)-this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(message->lParam)-this->frameGeometry().y();
  //      if(this->childAt(xPos,yPos) != 0)
   //     {
  //          if(yPos<52)
  //              *result = HTCAPTION;
  //          else
  //              *result = HTCLIENT;
  //      }
  //      else
            *result = HTCLIENT;
        if(xPos > 0 && xPos < 4)
            *result = HTLEFT;
        else if(xPos > (this->width()-4) && xPos < (this->width()-0))
            *result = HTRIGHT;
        if(yPos > 0 && yPos < 4)
        {
            *result = HTTOP;
        }
        else if(yPos > (this->height()-4) && yPos < (this->height()-0))
        {
            if(*result == HTRIGHT)
                *result = HTBOTTOMRIGHT;
            else
                *result = HTBOTTOM;
        }
        return true;

    }
    return false;
}

void MyBaseDialog::paintEvent(QPaintEvent */*event*/)
{
    QBitmap objBitmap(size());
    QPainter painter(&objBitmap);
    painter.setBrush(QColor(0,0,0));
    painter.fillRect(rect(),Qt::white);
    painter.drawRoundedRect(this->rect(),5,5);
    setMask(objBitmap);

    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/image/360bg.png"));//UI底色
    p.setPen(QPen(QColor(0,0,0,50)));

    p.drawRoundRect(0,0,width()-1,height()-1,1,1);

    p.setPen(QPen(QColor(220,220,220,90)));
    p.drawRoundRect(1,1,width()-3,height()-3,1,1);
}

void MyBaseDialog::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton && event->y()<= 0)
    {
        if(!m_bMaxWin)
        {
            m_bMaxWin = !m_bMaxWin;
            m_rectRestoreWindow = geometry();
            setGeometry(qApp->desktop()->availableGeometry());
        }
        else
        {
            m_bMaxWin = !m_bMaxWin;
            setGeometry(m_rectRestoreWindow);
        }

        repaint();
        update();
    }
}

void MyBaseDialog::SetCursorStyle(enum_Direction direction)
{
    switch(direction)
    {
    case eTop:
    case eBottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case eRight:
    case eLeft:
        setCursor(Qt::SizeHorCursor);
        break;
    case eTopRight:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case eRightBottom:
        setCursor(Qt::SizeFDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void MyBaseDialog::SetDrayMove(int nXGlobal, int nYGlobal, enum_Direction direction)
{
    int ndx = nXGlobal - m_ptPressGlobal.x();
    int ndy = nYGlobal - m_ptPressGlobal.y();
    QRect rectWinow = geometry();
    if(direction & eTop)
    {
        rectWinow.setTop(rectWinow.top()+ndy);
    }
    else if(direction & eRight)
    {
        rectWinow.setRight(rectWinow.right()+ndx);
    }
    else if(direction & eBottom)
    {
        rectWinow.setBottom(rectWinow.bottom()+ndy);
    }
    else if(direction & eLeft)
    {
        rectWinow.setLeft(rectWinow.left()+ndx);
    }
    if(rectWinow.width()<minimumWidth() || rectWinow.height()<minimumHeight())
        return;
    setGeometry(rectWinow);
}

enum_Direction MyBaseDialog::PointValid(int x, int y)
{
    enum_Direction direction = eNone;
    if(x<5)
        direction = eLeft;
    else if(x>rect().width()-5)
        direction = eRight;
    else if(y<5)
        direction = eTop;
    else if(y>rect().height()-5)
        direction = eBottom;

    return direction;
}
