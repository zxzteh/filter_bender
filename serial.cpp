#include "serial.h"
#include <QDebug>

SerialPortWorker::SerialPortWorker(const QString &portName, QObject *parent)
    : QObject(parent),
    portName(portName),
    isTransmitting(false),
    isReceiving(false)
{
    serialPort.setPortName(portName);
}

SerialPortWorker::~SerialPortWorker()
{
    if (serialPort.isOpen())
    {
        serialPort.close();
    }
}

void SerialPortWorker::start()
{
    if (!serialPort.open(QIODevice::ReadWrite))
    {
        emit errorOccurred("Failed to open serial port");
        return;
    }

    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    connect(&serialPort, &QSerialPort::readyRead, this, &SerialPortWorker::readData);
    connect(&timer, &QTimer::timeout, this, &SerialPortWorker::processData);

    timer.setInterval(50);
    timer.setSingleShot(true);
}

void SerialPortWorker::stop()
{
    if (serialPort.isOpen())
    {
        serialPort.close();
    }
}

void SerialPortWorker::sendData(const std::vector<uint8_t> &data)
{
    QMutexLocker locker(&mutex);
    if (isTransmitting || isReceiving)
    {
        emit errorOccurred("Cannot send data while transmitting or receiving");
        return;
    }

    isTransmitting = true;
    emit transmissionStarted();

    QByteArray byteArray(reinterpret_cast<const char*>(data.data()), data.size());
    qint64 bytesWritten = serialPort.write(byteArray);

    if (bytesWritten == -1)
    {
        emit errorOccurred("Failed to write data to serial port");
        isTransmitting = false;
        return;
    }

    if (!serialPort.waitForBytesWritten(50))
    {
        emit errorOccurred("Timeout while writing data to serial port");
        isTransmitting = false;
        return;
    }

    isTransmitting = false;
    emit transmissionFinished();
}

void SerialPortWorker::readData()
{
    QMutexLocker locker(&mutex);
    if (isTransmitting)
    {
        emit errorOccurred("Cannot receive data while transmitting");
        return;
    }

    isReceiving = true;
    emit receptionStarted();

    QByteArray data = serialPort.readAll();
    std::vector<uint8_t> temp = qByteArrayToVector(data);
    receiveBuffer.insert(receiveBuffer.end(), temp.begin(), temp.end());

    timer.start(); // Перезапуск таймера
}

void SerialPortWorker::processData()
{
    QMutexLocker locker(&mutex);
    if (!receiveBuffer.empty())
    {
        // Обработка данных
        qDebug() << "Processing data:" << receiveBuffer.size() << "bytes";
        receiveBuffer.clear(); // Очистка буфера
    }

    isReceiving = false;
    emit receptionFinished();
}

std::vector<uint8_t> SerialPortWorker::qByteArrayToVector(const QByteArray &byteArray)
{
    const uint8_t* data = reinterpret_cast<const uint8_t*>(byteArray.data());
    size_t size = byteArray.size();
    return std::vector<uint8_t>(data, data + size);
}
