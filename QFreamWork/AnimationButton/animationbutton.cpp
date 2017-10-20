#include "animationbutton.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

AnimationButton::AnimationButton(QWidget *parent) : QWidget(parent)
{
	enter = true;
	leave = false;
	pixWidth = 0;
	pixHeight = 0;
	oldWidth = 0;
	oldHeight = 0;

	enterAnimation = new QPropertyAnimation(this, "");
	enterAnimation->setStartValue(0);
	enterAnimation->setEndValue(5);
	enterAnimation->setDuration(200);
	connect(enterAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(enterImageChanged(QVariant)));

	leaveAnimation = new QPropertyAnimation(this, "");
	leaveAnimation->setStartValue(0);
	leaveAnimation->setEndValue(5);
	leaveAnimation->setDuration(200);
	connect(leaveAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leaveImageChanged(QVariant)));
}

AnimationButton::~AnimationButton()
{
	delete enterAnimation;
	delete leaveAnimation;
}

//离开事件
void AnimationButton::enterEvent(QEvent *)
{

	enter = true;
	leave = false;
	pixWidth = pixWidth - 25;
	pixHeight = pixHeight - 25;
	enterAnimation->start();
}
//进入事件
void AnimationButton::leaveEvent(QEvent *)
{
    setCursor(QCursor(Qt::PointingHandCursor));//设置鼠标手型
	enter = false;
	leave = true;
	pixWidth = oldWidth;
	pixHeight = oldHeight;
	leaveAnimation->start();
}

//鼠标点击事件,发出相应的信号
void AnimationButton::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

//重绘事件
void AnimationButton::paintEvent(QPaintEvent *)
{
    //图片为空，则退出
	if (image.isEmpty()) {
		return;
	}

    QPainter painter(this);//绘画对象
    painter.setRenderHint(QPainter::Antialiasing);//给定渲染提示:边缘进行反锯齿。

	QPixmap pix(image);
    //尺寸自由缩放。 长宽比不保留。使用双线性滤波来转换所得到的图像。将像素图放大到给定大小。
    pix = pix.scaled(targetWidth, targetHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	if (enter || leave) {
		int pixX = rect().center().x() - targetWidth / 2;
		int pixY = rect().center().y() - targetHeight / 2 - 10;
		QPoint point(pixX, pixY);
		painter.drawPixmap(point, pix);
		painter.drawText(QRectF(0, height() - 20, width(), 20), Qt::AlignCenter, text);
	}
}
//进入动画
void AnimationButton::enterImageChanged(QVariant index)
{
	int i = index.toInt();
	targetWidth = pixWidth + i * 5;
	targetHeight = pixHeight + i * 5;
	update();
}
//离开动画
void AnimationButton::leaveImageChanged(QVariant index)
{
	int i = index.toInt();
	targetWidth = pixWidth - i * 5;
	targetHeight = pixWidth - i * 5;
	update();
}
//设置图片
void AnimationButton::setImage(QString image)
{
	this->image = image;
	QPixmap pix(image);
	pixWidth = pix.width();
	pixHeight = pix.height();
	oldWidth = pixWidth;
	oldHeight = pixHeight;
	targetWidth = pixWidth - 25;
	targetHeight = pixHeight - 25;
	update();
}
//设置文本
void AnimationButton::setText(QString text)
{
	this->text = text;
	update();
}

