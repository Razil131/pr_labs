#pragma once
#include "Shape.hpp"
#include <sstream>

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(const std::string& color = "black", double radius = 1.0)
        : Shape(color), radius(radius) {}

    double getRadius() const { return radius; }
    void setRadius(double newRadius) { radius = newRadius; }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Circle [color: " << color << ", radius: " << radius << "]";
        return oss.str();
    }
};