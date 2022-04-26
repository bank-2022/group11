#include "dllserialportengine.h"

DLLSerialPortEngine::DLLSerialPortEngine(QString port)
{
    objectQSerialPort = new QSerialPort(this);
    objectQSerialPort->setPortName(port);
    objectQSerialPort->setBaudRate(QSerialPort::Baud9600);
    objectQSerialPort->setDataBits(QSerialPort::Data8);
    objectQSerialPort->setParity(QSerialPort::NoParity);
    objectQSerialPort->setStopBits(QSerialPort::OneStop);
    objectQSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    //objectQSerialPort->open(QIODevice::ReadOnly);
    connect(objectQSerialPort, SIGNAL(readyRead()), this, SLOT(serialReceived()),
            Qt::QueuedConnection);
}

DLLSerialPortEngine::~DLLSerialPortEngine()
{
    objectQSerialPort->close();
    delete objectQSerialPort;
    objectQSerialPort = nullptr;
}

void DLLSerialPortEngine::serialReceived()
{
    // store serial data into a byte array
    objectQByteArray = objectQSerialPort->readAll();

    // convert into string
    objectQString = QTextCodec::codecForMib(106)->toUnicode(objectQByteArray);

    // trim excess
    objectQString.remove(0, 3);
    objectQString.chop(3);
    emit sendString(objectQString);
}

void DLLSerialPortEngine::openConnection()
{
    objectQSerialPort->open(QIODevice::ReadOnly);
    objectQSerialPort->clear(QSerialPort::AllDirections);   // clear buffer before reading new data
}
