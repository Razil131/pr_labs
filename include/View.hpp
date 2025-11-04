#pragma once
#include "Document.hpp"

class View
{
public:
    static void render(Document &doc)
    {
        for (const auto &shape : doc.getShapes())
        {
            std::cout << shape->toString() << "\n";
        }
    }
};