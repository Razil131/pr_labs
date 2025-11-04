#pragma once
#include <string>
#include <iostream>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual std::string toString() const = 0;
};