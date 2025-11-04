#pragma once
#include "Document.hpp"
#include "DocumentIO.hpp"
#include "Shape.hpp"
#include "View.hpp"
#include <memory>
#include <string>

class Controller
{
    View view = View();
    std::shared_ptr<Document> document;

public:
    Controller() = default;

    void newDocument();
    void loadDocument(const std::string &filename);
    void saveDocument(const std::string &filename);
    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(size_t index);
    void renderDocument() const;
};
