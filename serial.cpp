#include "serial.h"

QSerialPort serial;


void serialInit() {
    serial.setPortName("/dev/ttyACM0"); // Укажите имя порта (например, COM1 для Windows, /dev/ttyUSB0 для Linux)
    serial.setBaudRate(QSerialPort::Baud9600); // Скорость передачи данных
    serial.setDataBits(QSerialPort::Data8); // Биты данных
    serial.setParity(QSerialPort::NoParity); // Контроль четности
    serial.setStopBits(QSerialPort::OneStop); // Стоп-биты
    serial.setFlowControl(QSerialPort::NoFlowControl); // Управление потоком
    if (serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Порт успешно открыт!";

        QByteArray data = "Hello, Serial Port!\r\n";
        qint64 bytesWritten = serial.write(data);

        if (bytesWritten == -1) {
            qDebug() << "Ошибка записи в порт:" << serial.errorString();
        } else {
            qDebug() << "Данные успешно отправлены, количество байт:" << bytesWritten;
        }

        if (!serial.waitForBytesWritten(1000)) {
            qDebug() << "Таймаут записи!";
        }

        if (serial.waitForReadyRead(1000)) {
            QByteArray responseData = serial.readAll();
            qDebug() << "Полученные данные:" << responseData;
        } else {
            qDebug() << "Таймаут чтения!";
        }

        serial.close();
    } else {
        qDebug() << "Ошибка открытия порта:" << serial.errorString();
    }
}

void serialSend() {

}
