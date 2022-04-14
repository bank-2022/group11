#include "dllserialport.h"

DLLSerialPort::DLLSerialPort()
{
    objectDLLSerialPortEngine = new DLLSerialPortEngine;
    connect(objectDLLSerialPortEngine, SIGNAL(sendString(QString)),
            this, SLOT(receiveValue(QString)));
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
