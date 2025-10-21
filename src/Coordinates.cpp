#include "Coordinates.h"

Coordinates operator+(const Coordinates& coords, const Vector& vector) {
    return Coordinates(coords.x + vector.dx, coords.y + vector.dy);
}

bool operator==(const Coordinates& left, const Coordinates& right) {
    return left.x == right.x && left.y == right.y;
}

bool operator!=(const Coordinates& left, const Coordinates& right) {
    return !(operator==(left, right));
}
