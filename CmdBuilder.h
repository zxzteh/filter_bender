#ifndef CMDBUILDER_H
#define CMDBUILDER_H

#define CMD_START_MARK 0x10
#define CMD_DST_ADDR 0x01
#define CMD_SRC_ADDR 0x1F

#include <cstdint>
#include <functional>
#include <optional>

/*     |             HEADER            |     BODY    | CHECK |
name   | MARK | DST | SRC | IDX | SIZE |     DATA    |  CRC  |
bytes  |    1 |   1 |   1 |   1 |    2 |  0 - 65535  |    2  |
*/

class CmdBuilder {

public:
    explicit CmdBuilder(std::optional<std::function<void(std::vector<uint8_t>)>> callback = std::nullopt);
    void build(std::vector<uint8_t> data);
    std::vector<uint8_t> getCmd();

private:
    std::vector<uint8_t> cmd_;
    uint16_t size_ = 0;
    uint8_t idx_ = 0;
    std::optional<std::function<void(std::vector<uint8_t>)>> callback_;
    void addHeader();
    void addBody(std::vector<uint8_t> data);
    void addCRC16();
    void clear();
};

#endif //CMDBUILDER_H
