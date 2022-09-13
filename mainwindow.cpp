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
    //ui->tableWidget->widt();

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

     timer->start(1000);


     //workerDev = new WorkerDevice(); // запуск чтения с устройства
     //workerDev->start();

}

MainWindow::~MainWindow()
{
    //workerDev->ready = false;
    QThread::msleep(500);
    //workerDev->
    delete ui;
}


void MainWindow::ActionTimer()
{
    double sec = (QVariant(ui->lineEdit_RDV->text()).toInt()*1.0)/1000.0;
    BA = QVariant(ui->lineEdit_BA->text()).toInt();
    RDV = QVariant(ui->lineEdit_RDV->text()).toInt();
    RMV = QVariant(ui->lineEdit_RMV->text()).toInt();

    if(Y0!=Y){
        t2 = std::clock();
        getValueRDV_sec =  ((double)(t2-t1) / CLOCKS_PER_SEC);
    }
    else
    {

    }

    Y=Y0;

    UpdateInfo();

    // --------------------------------------------------------

    // состояние сработки устройства
    MsgDev(sec);

}

void MainWindow::UpdateInfo()
{
    QTableWidgetItem *itm_Y = new QTableWidgetItem(tr("%1").arg(tr("%1").arg(Y)));
    QTableWidgetItem *itm_RMV = new QTableWidgetItem(tr("%1").arg(tr("%1").arg(RMV)));
    ui->tableWidget->setItem(0,1,itm_RMV);
    ui->tableWidget->setItem(0,3,itm_Y);

    ui->lineEdit_Y->setText(tr("%1").arg(tr("%1").arg(Y)));
    ui->lineEdit_RMV->setText(tr("%1").arg(tr("%1").arg(RMV)));


    QTableWidgetItem *itm_BA = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_BA->text()));
    QTableWidgetItem *itm_RDV = new QTableWidgetItem(tr("%1").arg(ui->lineEdit_RDV->text()));

    ui->tableWidget->setItem(0,0,itm_BA);
    ui->tableWidget->setItem(0,2,itm_RDV);

    ui->lineEdit_GetValueRDV->setText(tr("%1").arg(tr("%1").arg(getValueRDV_sec*1000)));

    if(ui->listWidget->count()>20)
    {
        ui->listWidget->clear();

    }

}

void  MainWindow::MsgDev(double  sec)
{
    if(Y>= BA && getValueRDV_sec>sec &&RMV<(Y-BA))
    {
        ui->lineEdit_MessageSystem->setText("Значение выше ВА");

        ui->listWidget->addItem("Значение выше ВА: Y="+
                                tr("%1").arg(tr("%1").arg(Y))+
                                "; RDV="+
                                tr("%1").arg(tr("%1").arg(getValueRDV_sec*1000))+
                                "; BA="+
                                tr("%1").arg(tr("%1").arg(BA))
                                );
        //ui->lineEdit_MessageSystem->setBackgroundRole(Qt::red);
        //ui->lineEdit_MessageSystem->foregroundRole();
    }
    else{
        ui->lineEdit_MessageSystem->setText("сработка верхней аварийной уставки - не произошло (NoNoNoNoNo)");
        ui->listWidget->addItem("сработка верхней аварийной уставки - не произошло (NoNoNoNoNo): Y="+
                                tr("%1").arg(tr("%1").arg(Y))+
                                "; RDV="+
                                tr("%1").arg(tr("%1").arg(getValueRDV_sec*1000))+
                                "; BA="+
                                tr("%1").arg(tr("%1").arg(BA))
                                );
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


void MainWindow::on_lineEdit_Y_textChanged(const QString &arg1)
{
     if(!ui->lineEdit_Y->text().isEmpty())
     {
         Y0=ui->lineEdit_Y->text().toInt();
         t1 = std::clock();
         getValueRDV_sec = 0;
     }
}

