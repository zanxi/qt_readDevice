#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>
#include <time.h>
#include <QElapsedTimer>
#include "WorkerDevice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(4);

     ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"BA"<<"RMV"<<"RDV"<<"Y");
     ui->tableWidget->setVerticalHeaderLabels(QStringList()<<" "<<" "<<" "<<" ");

     QTableWidgetItem *itm_BA = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_BA->text()));
     QTableWidgetItem *itm_RMV = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_RMV->text()));
     QTableWidgetItem *itm_RDV = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_RDV->text()));
     QTableWidgetItem *itm_Y = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_Y->text()));

     ui->tableWidget->setItem(0,0,itm_BA);
     ui->tableWidget->setItem(0,1,itm_RMV);
     ui->tableWidget->setItem(0,2,itm_RDV);
     ui->tableWidget->setItem(0,3,itm_Y);

     timer = new QTimer(this); // запуск таймера по секундам
     //QTimer *time = new QTimer(this);
     connect(timer, SIGNAL(timeout()),this,SLOT(ActionTimer()));

     workerDev = new WorkerDevice(); // запуск чтения с устройства
     workerDev->start();

}

MainWindow::~MainWindow()
{
    workerDev->ready = false;
    QThread::msleep(500);
    //workerDev->
    delete ui;
}

void MainWindow::ActionTimer()
{

    int BA = QVariant(ui->lineEdit_BA->text()).toInt();
    workerDev->SetValue(BA); // текущая уставка, костыльная установка случайной генерации Y

    int Y = workerDev->GetValue(); // рандомный костыль для значений Y
    QTableWidgetItem *itm_Y = new QTableWidgetItem(tr("%1").arg(tr("%1").arg(Y)));
    QTableWidgetItem *itm_RMV = new QTableWidgetItem(tr("%1").arg(tr("%1").arg(Y-BA)));
    ui->tableWidget->setItem(0,1,itm_RMV);
    ui->tableWidget->setItem(0,3,itm_Y);

    ui->lineEdit_Y->setText(tr("%1").arg(tr("%1").arg(Y)));
    ui->lineEdit_RMV->setText(tr("%1").arg(tr("%1").arg(Y-BA)));


    QTableWidgetItem *itm_BA = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_BA->text()));
    QTableWidgetItem *itm_RDV = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_RDV->text()));

    ui->tableWidget->setItem(0,0,itm_BA);
    ui->tableWidget->setItem(0,2,itm_RDV);



    double sec = (QVariant(ui->lineEdit_RDV->text()).toInt()*1.0)/1000.0;
    double getValueRDV_sec = workerDev->GetValue_RDV();

    //ui->lineEdit_GetValueRDV->setText(QString::numeric(getValueRDV_sec));
    ui->lineEdit_GetValueRDV->setText(tr("%1").arg(tr("%1").arg(getValueRDV_sec*1000)));

    //int Y = QVariant(ui->lineEdit_BA->text()).toInt();
    //if(Y>= BA && true)
    if(Y>= BA && getValueRDV_sec>sec)
    {
        ui->lineEdit_MessageSystem->setText("Значение выше ВА");
        //ui->lineEdit_MessageSystem->setBackgroundRole(Qt::red);
        //ui->lineEdit_MessageSystem->foregroundRole();
    }
    else{
        ui->lineEdit_MessageSystem->setText("сработка верхней аварийной уставки - не произошло (NoNoNoNoNo)");
        //ui->lineEdit_MessageSystem->setBackgroundRole(Qt::yellow);
    }


}

void MainWindow::TimeElapsed()
{

}


void MainWindow::on_pushButton_clicked()
{

    timer->start(1000);

    //QTableWidgetItem *itm = ui->tableWidget->currentItem();
    //QMessageBox::information(this, "info", itm->text());
}


void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
}

