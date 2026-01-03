#include "Frame.h"

Frame::Frame(const volatile uint8_t* data) {
    for (uint8_t row = 0; row < 8; ++row) {
        for (uint8_t col = 0; col < 8; ++col) {
            frame[row][col] = ((data[row] & (0b10000000 >> col)) != 0);
        }
    }
}

void Frame::setPixel(Coordinates coordinates) {
    if (coordinates.x < 8 && coordinates.y < 8)
        frame[coordinates.y][coordinates.x] = true;
}

void Frame::setPixel(uint8_t x, uint8_t y) {
    if (x < 8 && y < 8)
        frame[y][x] = true;
}

void Frame::clearPixel(Coordinates coordinates) {
    if (coordinates.x < 8 && coordinates.y < 8)
        frame[coordinates.y][coordinates.x] = false;
}

void Frame::clearPixel(uint8_t x, uint8_t y) {
    if (x < 8 && y < 8)
        frame[y][x] = false;
}

uint8_t Frame::rowByte(uint8_t row) const {
    uint8_t byte {0};

    if (row > 7)
        return 0;

    for (uint8_t i = 0; i < 8; i++) {
        bool pixel = frame[row][i];
        byte = byte << 1;
        if (pixel) byte += 1;
    }

    return byte;
}

//std::array<bool, 8>* Frame::begin() {
//    return frame.begin();
//}
//
//std::array<bool, 8>* Frame::end() {
//    return frame.end();
//}
//
//const std::array<bool, 8>* Frame::begin() const {
//    return frame.cbegin();
//}
//
//const std::array<bool, 8>* Frame::end() const {
//    return frame.cend();
//}

//std::ostream& operator<<(std::ostream& out, const Frame& frame) {
//    for (auto& row : frame.frame) {
//        for (auto& pixel : row) {
//            out << (pixel ? 1 : 0);
//        }
//        out << '\n';
//    }
//
//    return out;
//}
