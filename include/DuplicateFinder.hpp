#pragma once

#include "FileHasher.hpp"
#include <vector>
#include <map>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class DuplicateFinder
{
public:
    using FileGroup = std::vector<fs::path>;
    using DuplicateGroups = std::vector<FileGroup>;

    DuplicateFinder(size_t blockSize, HashAlgorithmPtr hashAlgo);

    DuplicateGroups findDuplicates(const std::map<uintmax_t, FileGroup> &sameSize);

    void printDuplicates(const DuplicateGroups &duplicates) const;

private:
    bool compareFiles(FileHasher &file1, FileHasher &file2);

    DuplicateGroups groupByContent(const FileGroup &files);

    size_t blockSize_;
    HashAlgorithmPtr hashAlgo_;
};
