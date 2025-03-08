//
// Created by skd on 06.03.2025.
//

#include "CmdBuilder.h"

#include <cstdint>
#include <utility>

/*     |             HEADER            |     BODY    | CHECK |
name   | MARK | DST | SRC | IDX | SIZE |     DATA    |  CRC  |
bytes  |    1 |   1 |   1 |   1 |    2 |  0 - 65535  |    2  |
*/

CmdBuilder::CmdBuilder(std::optional<std::function<void(std::vector<uint8_t>)>> callback)
    : callback_(std::move(callback)) {}

void CmdBuilder::build(std::vector<uint8_t> data) {
    clear();
    size_ = data.size();
    addHeader();
    addBody(data);
    addCRC16();
    idx_++;
    if (callback_) {
        (*callback_)(cmd_);
    }
}

void CmdBuilder::addHeader() {
    cmd_.push_back(CMD_START_MARK);
    cmd_.push_back(CMD_DST_ADDR);
    cmd_.push_back(CMD_SRC_ADDR);
    cmd_.push_back(idx_);

    cmd_.push_back(static_cast<uint8_t>(size_ >> 8));
    cmd_.push_back(static_cast<uint8_t>(size_));
}

void CmdBuilder::addBody(std::vector<uint8_t> data) {
    cmd_.insert(cmd_.end(), data.begin(), data.end());
}

void CmdBuilder::addCRC16() {
    uint16_t crc = 0xFFFF;
    uint16_t const poly = 0x1021;
    for (uint8_t byte : cmd_) {
        crc ^= static_cast<uint16_t>(byte) << 8;
        for (int i = 0; i < 8; i++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
            }
        }
    }
}

std::vector<uint8_t> CmdBuilder::getCmd() {
    return std::move(cmd_);
}

void CmdBuilder::clear() {
    cmd_.clear();
    size_ = 0;
}
