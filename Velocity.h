#pragma once
#include "Point.h"
#include <cmath>

class Velocity {
  public:
    inline Velocity() = default;

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

    inline friend std::istream& operator>>(std::istream& stream,
                                           Velocity& vel) {
        return stream >> vel.vec;
    }

  private:
    Point vec;
};
