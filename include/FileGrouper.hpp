#pragma once

#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

class FileGrouper
{
public:
    using FileGroup = std::vector<fs::path>;
    using GroupedFiles = std::map<uintmax_t, FileGroup>;

    GroupedFiles groupBySize(const std::vector<fs::path> &files);

private:
    uintmax_t getFileSize(const fs::path &file) const;
};
