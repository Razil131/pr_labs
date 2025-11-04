#pragma once
#include "Shape.hpp"

class Circle : public Shape
{
public:
    std::string toString() const override { return "Circle"; }
};