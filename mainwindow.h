#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WorkerDevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void ActionTimer();
    void on_pushButton_2_clicked();
    void on_lineEdit_Y_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    //QElapsedTimer ti;
    void TimeElapsed();
    void MsgDev(double  sec);
    void UpdateInfo();
    //WorkerDevice *workerDev;

    int Y0=1000,Y=1000,
    BA=1000,
    RMV=100,
    RDV=100;

    clock_t t1, t2, t3;
    double getValueRDV_sec = 0;

};
#endif // MAINWINDOW_H
