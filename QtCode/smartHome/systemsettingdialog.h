#ifndef SYSTEMSETTINGDIALOG_H
#define SYSTEMSETTINGDIALOG_H

#include <QWidget>

namespace Ui {
class SystemSettingDialog;
}

class SystemSettingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingDialog(QWidget *parent = 0);
    ~SystemSettingDialog();

private slots:
    void on_pbnClosePort_clicked();

    void on_pbnOk_clicked();

private:
    Ui::SystemSettingDialog *ui;

    bool m_isopenPort;
    QStringList m_portName;
    QStringList m_portBaud;
};

#endif // SYSTEMSETTINGDIALOG_H
