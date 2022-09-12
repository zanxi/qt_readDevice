#ifndef WorkerDevice_H
#define WorkerDevice_H

#include <QObject>
#include <QThread>
#include <QDebug>


#include <QTimer>
#include <QDateTime>
#include <QXmlStreamReader>
#include <QMutex>

#include <ctime>
#include <iostream>
#include <windows.h>



class WorkerDevice : public QThread
{
    Q_OBJECT
public:
    explicit WorkerDevice();

    ~WorkerDevice();


private:
void run();
  int Y;
  int BA = 1000;


  clock_t t1, t2, t3;

  QMutex mutex;
  QMap<int,QString> values;
  QMap<QString,int> vars;
  QDateTime lastOperation=QDateTime::currentDateTime();



public:

    bool ready = true;
    int GetValue();
    double GetValue_RDV();
    void SetValue(int BA);
    void makeStep();

};

#endif // WorkerDevice_H
