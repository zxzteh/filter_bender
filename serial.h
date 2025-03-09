#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QVector>
#include <QPushButton>
#include <vector>
#include <cstdint>

class SerialPortWorker : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortWorker(const QString &portName, QObject *parent = nullptr);
    ~SerialPortWorker();

    void start();
    void stop();
    void sendData(const std::vector<uint8_t> &data);

signals:
    void errorOccurred(const QString &error);
    void transmissionStarted();
    void transmissionFinished();
    void receptionStarted();
    void receptionFinished();

private slots:
    void readData();
    void processData();

private:
    QSerialPort serialPort;
    QString portName;
    QTimer timer;
    QMutex mutex;
    std::vector<uint8_t> receiveBuffer;
    bool isTransmitting;
    bool isReceiving;

    std::vector<uint8_t> qByteArrayToVector(const QByteArray &byteArray);
};

#endif // SERIAL_H
