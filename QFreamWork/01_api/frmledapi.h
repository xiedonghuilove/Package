#ifndef FRMLEDAPI_H
#define FRMLEDAPI_H

#include <QWidget>

namespace Ui
{
class frmLEDAPI;
}

class frmLEDAPI : public QWidget
{
	Q_OBJECT

public:
	explicit frmLEDAPI(QWidget *parent = 0);
	~frmLEDAPI();

private slots:
	void on_pushButton_clicked();

private:
	Ui::frmLEDAPI *ui;
};

#endif // FRMLEDAPI_H
