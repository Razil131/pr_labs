#include "DocumentIO.hpp"

bool DocumentIO::saveToFile(const Document &doc, const std::string &filename)
{
    std::cout << "document saved in " << filename << "\n";
    return true;
}
std::shared_ptr<Document> DocumentIO::loadFromFile(const std::string &filename)
{
    std::cout << "document loaded from " << filename << "\n";
    return std::make_shared<Document>();
}