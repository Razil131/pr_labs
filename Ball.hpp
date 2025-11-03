#pragma once
#define _USE_MATH_DEFINES
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include <cmath>

class Ball {
  private:
    Point center_;
    Velocity velocity_;
    double radius_;
    Color color_;
    bool isCollidable_;

  public:
    Ball(Point& center, double radius, Velocity& velocity, Color& color,
         bool isCollidable);
    bool isCollidable();
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
