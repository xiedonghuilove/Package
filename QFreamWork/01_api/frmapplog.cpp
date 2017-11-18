#include "frmapplog.h"
#include "ui_frmapplog.h"
#include "api/applog.h"
#include "qdebug.h"
#include "qdatetime.h"

frmAppLog::frmAppLog(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAppLog)
{
	ui->setupUi(this);
}

frmAppLog::~frmAppLog()
{
	delete ui;
}

//状态改变槽函数
void frmAppLog::on_ckLog_stateChanged(int arg1)
{
	if (arg1 == 0) {
		AppLog::Instance()->stop();
	} else {
		AppLog::Instance()->start();
	}
}

void frmAppLog::on_btnDebug_clicked()
{
    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "测试输出日志";
}



