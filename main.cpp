#include <iostream>
#include <memory>
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include "Controller.hpp"

int main()
{
    Controller controller;
    controller.newDocument();

    controller.addShape(std::make_shared<Circle>());
    controller.addShape(std::make_shared<Rectangle>());
    controller.addShape(std::make_shared<Line>());

    controller.renderDocument();

    std::string filename = "example.png";
    controller.saveDocument(filename);

    controller.loadDocument(filename);

    controller.renderDocument();

    return 0;
}
