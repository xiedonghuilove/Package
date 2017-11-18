#ifndef FRMNTPAPI_H
#define FRMNTPAPI_H

#include <QWidget>
#include <QDateTime>

namespace Ui
{
class frmNTPAPI;
}

class frmNTPAPI : public QWidget
{
	Q_OBJECT

public:
	explicit frmNTPAPI(QWidget *parent = 0);
	~frmNTPAPI();

private:
	Ui::frmNTPAPI *ui;

private slots:
	void on_pushButton_clicked();

private slots:
	void receiveTime(QDateTime dateTime);
};

#endif // FRMNTPAPI_H
