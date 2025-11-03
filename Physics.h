#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

class Physics {
  public:
    std::vector<Dust> dusts;
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, size_t ticks);

  private:
    void collideBalls(std::vector<Ball>& balls);
    void collideWithBox(std::vector<Ball>& balls);
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    void create_dust(Point& p);

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
