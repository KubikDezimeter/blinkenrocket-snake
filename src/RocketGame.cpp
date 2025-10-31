#include "RocketGame.h"

void RocketGame::execute(HardwareDisplay display) {
    uint8_t animation[] {
        0b00000000,
        0b00011000,
        0b00100100,
        0b00000100,
        0b00001000,
        0b00000100,
        0b00100100,
        0b00011000
    };

    Frame frame {animation};
    display.show(frame);

    while (true);
}
