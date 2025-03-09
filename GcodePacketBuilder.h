//
// Created by skd on 06.03.2025.
//

#ifndef GCODEPACKETBULDER_H
#define GCODEPACKETBULDER_H

#include <cstdint>
#include <vector>

#include "Gcode_reduced_commands.h"

#define GCODE_MARK 0x5F

// all motors within one big packet do actions simultaneously

/*    |    HEAD   |                  BODY                 |
name  | MRK | CNT | CNT_P | Mn | CMD | DST* | SPD* | ACC* |
bytes |   1 |  1  |     1 |  1 |  1  |   2  |   2  |   2  |

MRK - mark
CNT - counts of total packets in one frame
CNT_P - len of current packet in bytes
Mn - motor number (1 - 9) (255)
CMD - command
DST - distance
SPD - speed
ACC - accel
* - optional field
*/

class GcodePacketBuilder {
public:
  std::vector<uint8_t> getPacket();
  void clear();
  void build(uint8_t motor_num, uint8_t command, int16_t distance, uint16_t speed, uint16_t accel);
  void build(uint8_t motor_num, uint8_t command, int16_t distance, uint16_t speed);
  void build(uint8_t motor_num, uint8_t command);
private:
  std::vector<uint8_t> packet_;
  uint8_t packet_counter_ = 0;
};

#endif //GCODEPACKETBULDER_H
