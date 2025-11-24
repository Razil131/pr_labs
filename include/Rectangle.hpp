#pragma once
#include "Shape.hpp"
#include <sstream>

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(const std::string& color = "black", double width = 1.0, double height = 1.0)
        : Shape(color), width(width), height(height) {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setWidth(double newWidth) { width = newWidth; }
    void setHeight(double newHeight) { height = newHeight; }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Rectangle [color: " << color << ", width: " << width << ", height: " << height << "]";
        return oss.str();
    }
};