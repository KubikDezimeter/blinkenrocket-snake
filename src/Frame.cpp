#include "Frame.h"

Frame::Frame(const volatile uint8_t* data) {
    for (uint8_t row = 0; row < 8; ++row) {
        frame[row] = data[row];
    }
}

void Frame::setPixel(Coordinates coordinates) {
    if (coordinates.x < 8 && coordinates.y < 8)
        frame[coordinates.y] |= 0x80 >> coordinates.x;
}

void Frame::setPixel(uint8_t x, uint8_t y) {
    if (x < 8 && y < 8)
        frame[y] |= 0x80 >> x;
}

void Frame::clearPixel(Coordinates coordinates) {
    if (coordinates.x < 8 && coordinates.y < 8)
        frame[coordinates.y] &= 0x80 >> coordinates.x ^ 0xFF;
}

void Frame::clearPixel(uint8_t x, uint8_t y) {
    if (x < 8 && y < 8)
        frame[y] &= 0x80 >> x ^ 0xFF;
}

uint8_t Frame::rowByte(uint8_t row) const {
    if (row > 7)
        return 0;

    return frame[row];
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
