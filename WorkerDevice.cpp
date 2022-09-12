#include "WorkerDevice.h"
#include <time.h>

WorkerDevice::WorkerDevice()
{
    t1 = std::clock();
    t2 = std::clock();
    qInfo() << this << "Constructed" << QThread::currentThread();
}

WorkerDevice::~WorkerDevice()
{
    qInfo() << this << "Deconstructed" << QThread::currentThread();
}

int WorkerDevice::GetValue()
{
    return Y;
}

double WorkerDevice::GetValue_RDV()
{
    t3 = t1 - t2;                           // Разница между метками

       double sec = ((double)t3 / CLOCKS_PER_SEC);

    return sec;
}

void WorkerDevice::SetValue(int BA)
{
    this->BA = BA;
}



void WorkerDevice::makeStep()
{

    Y = rand()%(2*BA);
    //values.insert(var.id,"not read");
}

void WorkerDevice::run()
{
   srand(time(NULL));
    //return;    


    while(ready)
    {
        if(Y>BA)
        {
            t1 = std::clock();
        }
        else
        {
            t2 = std::clock();
        }

        mutex.lock();
        makeStep();

        mutex.unlock();
        QThread::msleep(100);
    }


    return;

    for(int i = 0; i < 10; i++)
    {
        qInfo() << "Working" << QString::number(i) << QThread::currentThread();
        QThread::currentThread()->msleep(500);
    }

    this->deleteLater();
}
