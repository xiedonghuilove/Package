#include "systemsettingdialog.h"
#include "ui_systemsettingdialog.h"

SystemSettingDialog::SystemSettingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingDialog)
{
    ui->setupUi(this);

    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint);

    //根据不同平台初始化串口名称
#ifdef Q_OS_LINUX
    m_portName << "ttySAC0" <<"ttySAC1" << "ttySAC2" << "ttySAC3"<< "ttySAC4";
#elif defined (Q_OS_WIN)
    m_portName <<"COM0" <<"COM1"<<"COM2" <<"COM3" <<"COM4" <<"COM5"<<"COM6"
              <<"COM7" <<"COM8"<<"COM9" <<"COM10"<<"COM11"<<"COM12"<<"COM13";
#endif
    m_portBaud <<"9600"<<"115200";

    QString port;
    foreach (port, m_portName) {
        ui->cbx_PortName->addItem(port);
    }
    QString baud;
    foreach (baud, m_portBaud) {
        ui->cbx_PortBaud->addItem(baud);
    }
    this->setMaximumSize(245,292);
    ui->label_title->setText(tr("SystemSetting"));
    ui->cbx_PortName->setEnabled(false);
    ui->cbx_PortBaud->setEnabled(false);
    m_isopenPort = true;                    //默认串口已经打开

}

SystemSettingDialog::~SystemSettingDialog()
{
    delete ui;
}

void SystemSettingDialog::on_pbnClosePort_clicked()
{
    if (m_isopenPort)
    {
        //关闭串口
        //m_serialThread->stopThread();
        m_isopenPort = false;
        ui->cbx_PortName->setEnabled(true);
        ui->cbx_PortBaud->setEnabled(true);
        ui->pbnClosePort->setText(tr("open_port"));
    }else
    {
        //打开串口
        m_isopenPort = true;
        ui->cbx_PortName->setEnabled(false);
        ui->cbx_PortBaud->setEnabled(false);
        ui->pbnClosePort->setText(tr("close_port"));
        //m_serialThread->startThread();
    }
}

void SystemSettingDialog::on_pbnOk_clicked()
{
    this->close();
}
