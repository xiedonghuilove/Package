#include "frmapi.h"
#include "ui_frmapi.h"
#include "frmntpapi.h"
#include "frmapplog.h"
#include "api/saveruntime.h"
#include "api/screenapi.h"
#include "frmledapi.h"
#include "frmframeless.h"

frmAPI::frmAPI(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAPI)
{
	ui->setupUi(this);
	this->initForm();
}

frmAPI::~frmAPI()
{
	delete ui;
}

void frmAPI::initForm()
{
	setWindowTitle("API综合示例");

    QList<QPushButton *> btns = this->findChildren<QPushButton *>();//搜索所有的子pushbutton保存在btns中。

	foreach (QPushButton *btn, btns) {
		connect(btn, SIGNAL(pressed()), this, SLOT(btnClick()));
	}
}

void frmAPI::btnClick()
{
	QPushButton *btn = (QPushButton *)sender();
	QWidget *w = 0;

	if (btn == ui->btnNTPAPI) {
		w = new frmNTPAPI;
	} else if (btn == ui->btnAppLog) {
        w = new frmAppLog;//日志输出
	} else if (btn == ui->btnLEDAPI) {
        w = new frmLEDAPI;//LED取模
	} else if (btn == ui->btnFrameless) {
        w = new frmFrameless;//无边窗体移动
	}

	if (w != 0) {
		w->setWindowTitle(btn->text());
		w->setAttribute(Qt::WA_ShowModal, true);
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}
}
//保存运行时间
void frmAPI::on_btnSaveRunTime_clicked()
{
	if (ui->btnSaveRunTime->text() == "启动存储运行时间") {
		SaveRunTime::Instance()->start();
		ui->btnSaveRunTime->setText("停止存储运行时间");
	} else {
		SaveRunTime::Instance()->stop();
		ui->btnSaveRunTime->setText("启动存储运行时间");
	}
}
//截图
void frmAPI::on_btnScreenAPI_clicked()
{
    frmScreen::Instance()->showFullScreen();//显示全屏widget
}
