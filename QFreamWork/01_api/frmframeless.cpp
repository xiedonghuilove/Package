#include "frmframeless.h"
#include "ui_frmframeless.h"
#include "api/framelesshelper.h"

frmFrameless::frmFrameless(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmFrameless)
{
	ui->setupUi(this);
	this->setWindowTitle("无边框拖动示例");
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

	FramelessHelper *pHelper = new FramelessHelper(this);
	pHelper->activateOn(this);              //激活当前窗体
	pHelper->setTitleHeight(30);            //设置窗体的标题栏高度
	pHelper->setWidgetMovable(true);        //设置窗体可移动
	pHelper->setWidgetResizable(true);      //设置窗体可缩放
	pHelper->setRubberBandOnMove(true);     //设置橡皮筋效果-可移动
	pHelper->setRubberBandOnResize(true);   //设置橡皮筋效果-可缩放

	connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

frmFrameless::~frmFrameless()
{
	delete ui;
}
