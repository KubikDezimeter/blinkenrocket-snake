#include "Frame.h"

void Frame::setPixel(Coordinates coordinates) {
    frame.at(coordinates.y).at(coordinates.x) = true;
}

void Frame::setPixel(uint8_t x, uint8_t y) {
    frame.at(y).at(x) = true;
}

void Frame::clearPixel(Coordinates coordinates) {
    frame.at(coordinates.y).at(coordinates.x) = false;
}

void Frame::clearPixel(uint8_t x, uint8_t y) {
    frame.at(y).at(x) = false;
}

std::array<bool, 8>* Frame::begin() {
    return frame.begin();
}

std::array<bool, 8>* Frame::end() {
    return frame.end();
}

const std::array<bool, 8>* Frame::begin() const {
    return frame.cbegin();
}

const std::array<bool, 8>* Frame::end() const {
    return frame.cend();
}

std::ostream& operator<<(std::ostream& out, const Frame& frame) {
    for (auto& row : frame.frame) {
        for (auto& pixel : row) {
            out << (pixel ? 1 : 0);
        }
        out << '\n';
    }

    return out;
}
