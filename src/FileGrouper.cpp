#include "FileGrouper.hpp"
#include <iostream>

FileGrouper::GroupedFiles FileGrouper::groupBySize(const std::vector<fs::path> &files)
{
    GroupedFiles filesBySize;

    for (const auto &file : files)
    {
        uintmax_t size = getFileSize(file);
        filesBySize[size].push_back(file);
    }

    return filesBySize;
}

uintmax_t FileGrouper::getFileSize(const fs::path &file) const
{
    return fs::file_size(file);
}
