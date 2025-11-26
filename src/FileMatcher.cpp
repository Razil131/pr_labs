#include "FileMatcher.hpp"

FileMatcher::FileMatcher(const std::string &mask)
    : mask_(mask), pattern_(mask, std::regex::icase)
{
}

bool FileMatcher::matches(const std::string &filename) const
{
    if (mask_.empty())
    {
        return true;
    }
    return std::regex_match(filename, pattern_);
}
