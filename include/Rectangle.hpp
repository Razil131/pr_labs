#pragma once
#include "Shape.hpp"

class Rectangle : public Shape
{
public:
    std::string toString() const override { return "Rectangle"; }
};