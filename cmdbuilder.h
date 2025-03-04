#ifndef CMDBUILDER_H
#define CMDBUILDER_H

#include <QByteArray>

#define CMD_START_MARK 0x10
#define CMD_DST_ADDR 0x01
#define CMD_SRC_ADDR 0x1F

/*     |             HEADER            |     BODY    | CHECK |
name   | MARK | DST | SRC | IDX | SIZE |     DATA    |  CRC  |
bytes  |    1 |   1 |   1 |   1 |    2 |  0 - 65535  |    2  |
*/



class CmdBuilder
{

public:
    CmdBuilder(std::optional<std::function<void(int)>> callback = std::nullopt);
    void build(QByteArray data);
    QByteArray* read();
    void send();

private:
    QByteArray cmd;
    quint16 size_;
    void addHeader();
    void addBody(QByteArray data);
    void addCRC();
    void clear();
};

#endif // CMDBUILDER_H
