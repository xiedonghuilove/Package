#include "frmledapi.h"
#include "ui_frmledapi.h"
#include "api/ledapi.h"

frmLEDAPI::frmLEDAPI(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLEDAPI)
{
	ui->setupUi(this);

	for (int i = 7; i < 20; i++) {
		ui->cboxFontSize->addItem(QString::number(i));
	}

	ui->cboxFontSize->setCurrentIndex(3);
}

frmLEDAPI::~frmLEDAPI()
{
	delete ui;
}

void frmLEDAPI::on_pushButton_clicked()
{
	QString text = ui->lineEdit->text();
	int width = ui->txtWidth->text().toInt();
	int height = ui->txtHeight->text().toInt();
	QString fontName = ui->fontComboBox->currentFont().family();
	int fontSize = ui->cboxFontSize->currentText().toInt();
	QPixmap pix = LEDAPI::Instance()->getLEDPix(text, width, height, fontName, fontSize, 5);
	ui->labImage->setPixmap(pix);
	QByteArray data = LEDAPI::Instance()->getLEDPixData(text, width, height, fontName, fontSize, 5);
	ui->textEdit->clear();
	ui->textEdit->append(data.toHex().toUpper());
}
