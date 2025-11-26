#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "FileMatcher.hpp"

namespace fs = std::filesystem;

class FileScanner
{
public:
    FileScanner(int maxDepth, int minSize, const std::vector<std::string> &excludeDirs);

    void scan(const std::vector<std::string> &directories,
              const FileMatcher &matcher,
              std::vector<fs::path> &files);

private:
    void scanDirectory(const fs::path &dirPath,
                       std::vector<fs::path> &files,
                       int currentDepth,
                       const FileMatcher &matcher);

    bool isExcluded(const fs::path &path) const;

    int maxDepth_;
    int minSize_;
    std::vector<std::string> excludeDirs_;
};
