#pragma once
#include "Shape.hpp"

class Line : public Shape
{
public:
    std::string toString() const override { return "Line"; }
};