#include "FileHasher.hpp"
#include <cmath>
#include <stdexcept>

FileHasher::FileHasher(const fs::path &filePath, size_t blockSize, IHashAlgorithm *hashAlgo)
    : filePath_(filePath), blockSize_(blockSize), hashAlgo_(hashAlgo)
{
    if (blockSize_ == 0)
    {
        throw std::invalid_argument("Block size must be greater than 0");
    }
    uintmax_t fileSize = fs::file_size(filePath_);
    blockCount_ = (fileSize + blockSize_ - 1) / blockSize_;

    cachedHashes_.resize(blockCount_);
    hashedBlocks_.resize(blockCount_, false);
}

std::string FileHasher::getBlockHash(size_t blockIndex)
{
    if (blockIndex >= blockCount_)
    {
        return "";
    }

    if (hashedBlocks_[blockIndex])
    {
        return cachedHashes_[blockIndex];
    }

    std::string hash = readAndHashBlock(blockIndex);
    cachedHashes_[blockIndex] = hash;
    hashedBlocks_[blockIndex] = true;

    return hash;
}

size_t FileHasher::getBlockCount() const
{
    return blockCount_;
}

std::string FileHasher::readAndHashBlock(size_t blockIndex)
{
    std::ifstream file(filePath_, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open file: " + filePath_.string());
    }

    file.seekg(blockIndex * blockSize_);

    std::vector<char> buffer(blockSize_, 0);
    file.read(buffer.data(), blockSize_);

    std::streamsize bytesRead = file.gcount();

    hashAlgo_->reset();
    return hashAlgo_->hash(buffer.data(), blockSize_);
}
