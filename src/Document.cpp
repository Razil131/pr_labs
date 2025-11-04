#include "Document.hpp"

std::vector<std::shared_ptr<Shape>> Document::getShapes() { return shapes; }
void Document::addShape(std::shared_ptr<Shape> shape) { shapes.push_back(shape); }
void Document::removeShape(size_t index) { shapes.erase(shapes.begin() + index); }