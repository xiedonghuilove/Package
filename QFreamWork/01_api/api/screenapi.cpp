#include "screenapi.h"
#include "qapplication.h"
#include "qpainter.h"
#include "qdesktopwidget.h"
#include "qfiledialog.h"
#include "qevent.h"
#include "qdatetime.h"
#include "qstringlist.h"
#include <QDebug>

#define AppPath qApp->applicationDirPath()
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

ScreenAPI::ScreenAPI(QSize size)
{
    maxWidth = size.width();//获得整个屏幕的大小
	maxHeight = size.height();

    startPos = QPoint(-1, -1);//开始坐标
    endPos = startPos;//结束坐标
    leftUpPos = startPos;//左上角坐标
    rightDownPos = startPos;//右下角坐标
	status = SELECT;
}

int ScreenAPI::width()
{
	return maxWidth;
}

int ScreenAPI::height()
{
	return maxHeight;
}

ScreenAPI::STATUS ScreenAPI::getStatus()
{
	return status;
}

void ScreenAPI::setStatus(STATUS status)
{
	this->status = status;
}

void ScreenAPI::setEnd(QPoint pos)
{
	endPos = pos;
	leftUpPos = startPos;
	rightDownPos = endPos;
	cmpPoint(leftUpPos, rightDownPos);
}

void ScreenAPI::setStart(QPoint pos)
{
	startPos = pos;
}

QPoint ScreenAPI::getEnd()
{
	return endPos;
}

QPoint ScreenAPI::getStart()
{
	return startPos;
}

QPoint ScreenAPI::getLeftUp()
{
	return leftUpPos;
}

QPoint ScreenAPI::getRightDown()
{
	return rightDownPos;
}

bool ScreenAPI::isInArea(QPoint pos)
{
	if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() && pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
		return true;
	}

	return false;
}

void ScreenAPI::move(QPoint p)
{
	int lx = leftUpPos.x() + p.x();
	int ly = leftUpPos.y() + p.y();
	int rx = rightDownPos.x() + p.x();
	int ry = rightDownPos.y() + p.y();

	if (lx < 0) {
		lx = 0;
		rx -= p.x();
	}

	if (ly < 0) {
		ly = 0;
		ry -= p.y();
	}

	if (rx > maxWidth)  {
		rx = maxWidth;
		lx -= p.x();
	}

	if (ry > maxHeight) {
		ry = maxHeight;
		ly -= p.y();
	}

	leftUpPos = QPoint(lx, ly);
	rightDownPos = QPoint(rx, ry);
	startPos = leftUpPos;
	endPos = rightDownPos;
}

void ScreenAPI::cmpPoint(QPoint &leftTop, QPoint &rightDown)
{
	QPoint l = leftTop;
	QPoint r = rightDown;

	if (l.x() <= r.x()) {
		if (l.y() <= r.y()) {
			;
		} else {
			leftTop.setY(r.y());
			rightDown.setY(l.y());
		}
	} else {
		if (l.y() < r.y()) {
			leftTop.setX(r.x());
			rightDown.setX(l.x());
		} else {
			QPoint tmp;
			tmp = leftTop;
			leftTop = rightDown;
			rightDown = tmp;
		}
	}
}

/**************************************************************************************************/

frmScreen *frmScreen::self = 0;
frmScreen::frmScreen(QWidget *parent) : QDialog(parent)
{
	this->initForm();
}

void frmScreen::initForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//隐藏标题栏，窗体出现在最顶层

	menu = new QMenu(this);
	menu->addAction("保存截图", this, SLOT(saveScreen()));
	menu->addAction("截图另存为", this, SLOT(saveScreenOther()));
	menu->addAction("全屏截图", this, SLOT(saveFullScreen()));
	menu->addAction("退出截图", this, SLOT(hide()));

	//取得屏幕大小
    qDebug()<<QApplication::desktop()->size();
	screen = new ScreenAPI(QApplication::desktop()->size());
	//保存全屏图像
	fullScreen = new QPixmap();
}

//重绘事件  update调用
void frmScreen::paintEvent(QPaintEvent *)
{
	int x = screen->getLeftUp().x();
	int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;//宽度
    int h = screen->getRightDown().y() - y;//高度

	QPainter painter(this);

	QPen pen;
	pen.setColor(Qt::green);
	pen.setWidth(2);
    pen.setStyle(Qt::DotLine);//虚线样式
	painter.setPen(pen);

	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(10);
	painter.setFont(font);

    //截屏思想：点击截屏工具的时候，截取全屏的像素，并且将全屏保存到一个全局的变量pixmap中。
    //然后，在点击鼠标移动，截取一个相应的矩形。将其绘制出来。
    painter.drawPixmap(0, 0, *bgScreen);//

	if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, fullScreen->copy(x, y, w, h));//绘制选择截屏的区域
	}

    painter.drawRect(x, y, w, h);

	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	painter.drawText(x + 2, y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )")
	                 .arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));
}

//显示窗口Widget发出事件被调用
void frmScreen::showEvent(QShowEvent *)
{
	QPoint point(-1, -1);
    screen->setStart(point);//设置开启坐标点
    screen->setEnd(point);//设置结束坐标点

    //全屏图像
	*fullScreen = QPixmap::grabWindow(QApplication::desktop()->winId(), 0, 0, screen->width(), screen->height());

	//设置透明度实现模糊背景
	QPixmap pix(screen->width(), screen->height());
	pix.fill((QColor(160, 160, 160, 200)));
	bgScreen = new QPixmap(*fullScreen);
	QPainter p(bgScreen);
	p.drawPixmap(0, 0, pix);
}

void frmScreen::saveScreenOther()
{
	QString fileName = QFileDialog::getSaveFileName(this, "保存图片", STRDATETIME, "JPEG Files (*.jpg)");

	if (fileName.length() > 0) {
		int x = screen->getLeftUp().x();
		int y = screen->getLeftUp().y();
		int w = screen->getRightDown().x() - x;
		int h = screen->getRightDown().y() - y;

		fullScreen->copy(x, y, w, h).save(fileName, "jpg");

		close();
	}
}

void frmScreen::saveScreen()
{
	int x = screen->getLeftUp().x();
	int y = screen->getLeftUp().y();
	int w = screen->getRightDown().x() - x;
	int h = screen->getRightDown().y() - y;

	QString fileName = QString("%1/screen_%2.jpg").arg(AppPath).arg(STRDATETIME);
	fullScreen->copy(x, y, w, h).save(fileName, "jpg");

	close();
}

void frmScreen::saveFullScreen()
{
	QString fileName = QString("%1/full_%2.jpg").arg(AppPath).arg(STRDATETIME);
	fullScreen->save(fileName, "jpg");

	close();
}

//鼠标移动事件
void frmScreen::mouseMoveEvent(QMouseEvent *e)
{
    if (screen->getStatus() == ScreenAPI::SELECT) {//选择区域
        screen->setEnd(e->pos());//得到结束点坐标
    } else if (screen->getStatus() == ScreenAPI::MOV) {//移动区域
		QPoint p(e->x() - movPos.x(), e->y() - movPos.y());
		screen->move(p);
		movPos = e->pos();
	}

	update();
}

//鼠标按下事件
void frmScreen::mousePressEvent(QMouseEvent *e)
{
    int status = screen->getStatus();//获取状态

	if (status == ScreenAPI::SELECT) {
		screen->setStart(e->pos());
	} else if (status == ScreenAPI::MOV) {
		if (screen->isInArea(e->pos()) == false) {
			screen->setStart(e->pos());
			screen->setStatus(ScreenAPI::SELECT);
		} else {
			movPos = e->pos();
			this->setCursor(Qt::SizeAllCursor);
		}
	}

	update();
}

//鼠标释放事件
void frmScreen::mouseReleaseEvent(QMouseEvent *)
{
	if (screen->getStatus() == ScreenAPI::SELECT) {
		screen->setStatus(ScreenAPI::MOV);
	} else if (screen->getStatus() == ScreenAPI::MOV) {
		this->setCursor(Qt::ArrowCursor);
	}
}

void frmScreen::contextMenuEvent(QContextMenuEvent *)
{
    this->setCursor(Qt::ArrowCursor);//设置鼠标样式
	menu->exec(cursor().pos());
}
