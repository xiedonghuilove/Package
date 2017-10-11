#ifndef MYBASEDIALOG_H
#define MYBASEDIALOG_H

#include <QDialog>
#include <QPainter>
#include <windows.h>
#include <windowsx.h>
#include <QBitmap>
#include <QPixmap>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainterPath>

enum enum_Direction{
    eNone = 0x000,
    eTop = 0x001,
    eBottom = 0x002,
    eRight = 0x004,
    eLeft = 0x008,
    eTopRight = 0x010,
    eRightBottom = 0x020
};

class MyBaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyBaseDialog(QWidget *parent = 0);

    bool m_bMaxWin;
    QRect m_rectRestoreWindow;
    QPoint m_ptPressGlobal;
    bool m_bLeftBtnPress;
    enum_Direction m_eDirection;


protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void paintEvent(QPaintEvent *);

    void SetCursorStyle(enum_Direction direction);
    void SetDrayMove(int nXGlobal,int nYGlobal,enum_Direction direction);
    enum_Direction PointValid(int x,int y);
signals:

public slots:

};

#endif // MYBASEDIALOG_H
