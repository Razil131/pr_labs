#pragma once

#include "Shape.hpp"
#include <vector>
#include <memory>

class Document
{
    std::vector<std::shared_ptr<Shape>> shapes;

public:
    std::vector<std::shared_ptr<Shape>> getShapes();
    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(size_t index);
};