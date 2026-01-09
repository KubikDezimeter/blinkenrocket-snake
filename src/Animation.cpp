#include "Animation.h"

Animation::Animation(uint8_t* const columns, const uint8_t col_count, const uint8_t capacity) :
    columns {columns},
    col_count {col_count},
    capacity {capacity != 0 ? capacity : col_count},
    offset {0}
{};

uint8_t Animation::getOffset() const {
    return offset;
}

void Animation::setOffset(uint8_t offset) {
    offset = offset;
}

void Animation::append(const uint8_t* columns, const uint8_t col_count) {
    for (uint8_t i = 0; i < col_count; ++i) {
        this->columns[this->col_count + i] = columns[i];
    }
    this->col_count += col_count;
}


void Animation::append(const uint8_t n) {
    uint8_t index = n;
    uint8_t width = digit_font[index][0];

    for (uint8_t i = 1; i <= width; ++i) {
        this->columns[this->col_count + i] = digit_font[index][i];
    }
    this->col_count += width + 1;
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
