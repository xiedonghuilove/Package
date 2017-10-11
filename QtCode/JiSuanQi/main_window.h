#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QDialog>
#include <QStackedLayout>
#include "titlebar.h"
#include "scientific_mode.h"
#include "simple_mode.h"
#include <QAction>
#include "mybasedialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSettings>

class MainWindow : public MyBaseDialog
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QMenu *menu;
    QWidget *mainwidget;
    QStackedLayout *layout;
    TitleBar *titleBar;
    SimpleMode *simpleMode;
    ScientificMode *scMode;

    QSettings *config;

    QAction *simpleAction;
    QAction *scientificAction;
    QAction *clearRecord;
    QAction *hideAction;
    QAction *showAction;
    QAction *lightAction;
    QAction *darkAction;

    QVBoxLayout *m_pMainLayout;
    void initUI();

    void closeEvent(QCloseEvent *);
    void loadHistory();
    void InitTheme();
    void InitMode();

signals:

public slots:

    void switchToLightTheme();
    void switchToDarkTheme();
    void switchToScientificMode();
    void switchToSimpleMode();
    void switchToClear();


};

#endif // MAINWINDOW_H
