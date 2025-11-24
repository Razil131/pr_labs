#pragma once
#include <string>
#include <iostream>

class Shape
{
protected:
    std::string color;

public:
    Shape(const std::string &color = "black")
        : color(color) {}

    virtual ~Shape() = default;
    virtual std::string toString() const = 0;

    std::string getColor() const { return color; }
    void setColor(const std::string &newColor) { color = newColor; }
};