//
// Created by skd on 06.03.2025.
//

#include "GcodePacketBuilder.h"

std::vector<uint8_t> GcodePacketBuilder::getPacket() {
    if (packet_counter_ == 0) return {};

    packet_.insert(packet_.begin(), packet_counter_);
    packet_.insert(packet_.begin(), GCODE_MARK);
    packet_counter_ = 0;
    return std::move(packet_);
}

void GcodePacketBuilder::clear() {
    packet_.clear();
}

void GcodePacketBuilder::build(uint8_t motor_num, uint8_t command) {
    packet_.push_back(sizeof(motor_num) + sizeof(command));
    packet_.push_back(motor_num);
    packet_.push_back(command);
    packet_counter_++;
}

void GcodePacketBuilder::build(uint8_t motor_num, uint8_t command, int16_t distance, uint16_t speed) {
    packet_.push_back(sizeof(motor_num) + sizeof(command) + sizeof(distance) + sizeof(speed));
    packet_.push_back(motor_num);
    packet_.push_back(command);

    packet_.push_back(static_cast<uint8_t>(distance >> 8));
    packet_.push_back(static_cast<uint8_t>(distance));

    packet_.push_back(static_cast<uint8_t>(speed >> 8));
    packet_.push_back(static_cast<uint8_t>(speed));

    packet_counter_++;
}

void GcodePacketBuilder::build(uint8_t motor_num, uint8_t command, int16_t distance, uint16_t speed, uint16_t accel) {
    packet_.push_back(sizeof(motor_num) + sizeof(command) + sizeof(distance) + sizeof(speed) + sizeof(accel));
    packet_.push_back(motor_num);
    packet_.push_back(command);

    packet_.push_back(static_cast<uint8_t>(distance >> 8));
    packet_.push_back(static_cast<uint8_t>(distance));

    packet_.push_back(static_cast<uint8_t>(speed >> 8));
    packet_.push_back(static_cast<uint8_t>(speed));

    packet_.push_back(static_cast<uint8_t>(accel >> 8));
    packet_.push_back(static_cast<uint8_t>(accel));

    packet_counter_++;
}
