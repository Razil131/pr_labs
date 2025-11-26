#pragma once

#include "IHashAlgorithm.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace fs = std::filesystem;

class FileHasher
{
public:
    FileHasher(const fs::path &filePath, size_t blockSize, IHashAlgorithm *hashAlgo);

    std::string getBlockHash(size_t blockIndex);

    size_t getBlockCount() const;

    const fs::path &getFilePath() const { return filePath_; }

private:
    std::string readAndHashBlock(size_t blockIndex);

    fs::path filePath_;
    size_t blockSize_;
    IHashAlgorithm *hashAlgo_;
    size_t blockCount_;
    std::vector<std::string> cachedHashes_;
    std::vector<bool> hashedBlocks_;
};
