#include "Controller.hpp"

void Controller::newDocument()
{
    document = std::make_shared<Document>();
}
void Controller::loadDocument(const std::string &filename)
{
    if (document)
        document = DocumentIO::loadFromFile(filename);
}
void Controller::saveDocument(const std::string &filename)
{
    if (document)
        DocumentIO::saveToFile(*document, filename);
}
void Controller::addShape(std::shared_ptr<Shape> shape)
{
    if (document)
        document->addShape(shape);
}
void Controller::removeShape(size_t index)
{
    if (document)
        document->removeShape(index);
}
void Controller::renderDocument() const
{
    if (document)
        view.render(*document);
}