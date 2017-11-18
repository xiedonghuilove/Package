#ifndef FRMAPPLOG_H
#define FRMAPPLOG_H

#include <QWidget>

namespace Ui
{
class frmAppLog;
}

class frmAppLog : public QWidget
{
	Q_OBJECT

public:
	explicit frmAppLog(QWidget *parent = 0);
	~frmAppLog();

private slots:
	void on_ckLog_stateChanged(int arg1);
	void on_btnDebug_clicked();


private:
	Ui::frmAppLog *ui;
};

#endif // FRMAPPLOG_H
