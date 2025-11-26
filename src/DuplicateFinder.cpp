#include "DuplicateFinder.hpp"
#include <iostream>
#include <algorithm>

DuplicateFinder::DuplicateFinder(size_t blockSize, HashAlgorithmPtr hashAlgo)
    : blockSize_(blockSize), hashAlgo_(std::move(hashAlgo))
{
}

DuplicateFinder::DuplicateGroups DuplicateFinder::findDuplicates(
    const std::map<uintmax_t, FileGroup> &sameSize)
{
    DuplicateGroups result;

    for (const auto &[size, files] : sameSize)
    {
        if (files.size() < 2)
        {
            continue;
        }

        auto duplicateGroups = groupByContent(files);

        for (const auto &group : duplicateGroups)
        {
            if (group.size() > 1)
            {
                result.push_back(group);
            }
        }
    }

    return result;
}

void DuplicateFinder::printDuplicates(const DuplicateGroups &duplicates) const
{
    for (const auto &group : duplicates)
    {
        for (const auto &file : group)
        {
            std::cout << file.string() << std::endl;
        }
        std::cout << std::endl;
    }
}

bool DuplicateFinder::compareFiles(FileHasher &file1, FileHasher &file2)
{
    if (file1.getBlockCount() != file2.getBlockCount())
    {
        return false;
    }

    size_t blockCount = file1.getBlockCount();

    for (size_t i = 0; i < blockCount; ++i)
    {
        std::string hash1 = file1.getBlockHash(i);
        std::string hash2 = file2.getBlockHash(i);

        if (hash1 != hash2)
        {
            return false;
        }
    }

    return true;
}

DuplicateFinder::DuplicateGroups DuplicateFinder::groupByContent(const FileGroup &files)
{
    DuplicateGroups groups;
    std::vector<bool> processed(files.size(), false);

    for (size_t i = 0; i < files.size(); ++i)
    {
        if (processed[i])
        {
            continue;
        }

        FileGroup group;
        group.push_back(files[i]);
        processed[i] = true;

        FileHasher hasher1(files[i], blockSize_, hashAlgo_.get());

        for (size_t j = i + 1; j < files.size(); ++j)
        {
            if (processed[j])
            {
                continue;
            }

            FileHasher hasher2(files[j], blockSize_, hashAlgo_.get());

            if (compareFiles(hasher1, hasher2))
            {
                group.push_back(files[j]);
                processed[j] = true;
            }
        }

        if (group.size() > 1)
        {
            groups.push_back(group);
        }
    }

    return groups;
}
