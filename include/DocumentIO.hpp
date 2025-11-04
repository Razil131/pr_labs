#pragma once
#include "Document.hpp"
#include <string>

class DocumentIO
{
public:
    static bool saveToFile(const Document &doc, const std::string &filename);
    static std::shared_ptr<Document> loadFromFile(const std::string &filename);
};
