#include "Animation.h"

void Animation::setOffset(uint8_t offset) {
    offset = offset;
}

bool Animation::isFinished() const {
    return offset > col_count - 8;
}

Frame Animation::render(bool loop) {
    uint8_t data[8] {};

    // if !loop, values should never be greater than col_count → `% col_count + 1` has no effect
    uint8_t mod = loop ? col_count : col_count + 1;
    uint8_t i;
    for (i = 0; i < 8 && (i + offset) % mod < col_count; ++i) {
        data[i] = columns[(i + offset) % mod];
    }

    offset = (offset + 1) % mod;

    Frame frame {data};
    frame.transpose();



    return frame;
}
