#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QString port)
{
    objectDLLSerialPortEngine = new DLLSerialPortEngine(port);
    connect(objectDLLSerialPortEngine, SIGNAL(sendString(QString)),
            this, SLOT(receiveValue(QString)), Qt::QueuedConnection);
}

DLLSerialPort::~DLLSerialPort()
{
    delete objectDLLSerialPortEngine;
    objectDLLSerialPortEngine = nullptr;
}

void DLLSerialPort::receiveValue(QString returnString)
{
    emit returnValue(returnString);
}

void DLLSerialPort::interfaceFunctionOpenConnection()
{
    objectDLLSerialPortEngine->openConnection();
}
