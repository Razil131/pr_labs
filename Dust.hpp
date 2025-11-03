#pragma once
#define _USE_MATH_DEFINES
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include <cmath>

class Dust {
  public:
    Point center_;
    Velocity velocity_;
    double lifetime_ = 1.5;
    double radius_ = 5;
    Color color_ = Color(0, 0, 0);
    Dust(const Point& center, const Velocity& velocity);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
};