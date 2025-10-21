#ifndef BALL_H_
#define BALL_H_

#include <cstdint>
#include <utility>
#include "Coordinates.h"
#include "Vector.h"


class Ball {
    private:
        Coordinates position {4, 6};
        Vector velocity {+1, -1};

    public:
        Coordinates getPosition() const;
        Vector getVelocity() const;
        void setPosition(Coordinates position);
        void setPosition(int8_t x, int8_t y);
        void setVelocity(Vector velocity);
        void setVelocity(int8_t dx, int8_t dy);
};

#endif
