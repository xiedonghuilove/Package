#include "frmntpapi.h"
#include "ui_frmntpapi.h"
#include "api/ntpapi.h"

frmNTPAPI::frmNTPAPI(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNTPAPI)
{
	ui->setupUi(this);
	connect(NTPAPI::Instance(), SIGNAL(receiveTime(QDateTime)), this, SLOT(receiveTime(QDateTime)));
}

frmNTPAPI::~frmNTPAPI()
{
	delete ui;
}

void frmNTPAPI::receiveTime(QDateTime dateTime)
{
	ui->dateTimeEdit->setDateTime(dateTime);
	ui->lineEdit->setText(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

void frmNTPAPI::on_pushButton_clicked()
{
	NTPAPI::Instance()->getTime("time.nist.gov");
}
