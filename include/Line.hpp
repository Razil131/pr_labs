#pragma once
#include "Shape.hpp"
#include <sstream>

class Line : public Shape
{
private:
    double length;

public:
    Line(const std::string& color = "black", double length = 1.0)
        : Shape(color), length(length) {}

    double getLength() const { return length; }
    void setLength(double newLength) { length = newLength; }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Line [color: " << color << ", length: " << length << "]";
        return oss.str();
    }
};