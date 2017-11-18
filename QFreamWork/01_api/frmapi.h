#ifndef FRMAPI_H
#define FRMAPI_H

#include <QWidget>

namespace Ui {
class frmAPI;
}

class frmAPI : public QWidget
{
    Q_OBJECT

public:
    explicit frmAPI(QWidget *parent = 0);
    ~frmAPI();

private:
    Ui::frmAPI *ui;

private slots:
    void initForm();
    void btnClick();
    void on_btnSaveRunTime_clicked();
    void on_btnScreenAPI_clicked();
};

#endif // FRMAPI_H
