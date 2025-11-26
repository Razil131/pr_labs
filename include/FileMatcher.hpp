#pragma once

#include <string>
#include <regex>

class FileMatcher
{
public:
    FileMatcher(const std::string &mask);
    bool matches(const std::string &filename) const;

private:
    std::string mask_;
    std::regex pattern_;
};
