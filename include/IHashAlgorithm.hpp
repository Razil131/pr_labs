#pragma once

#include <vector>
#include <cstdint>
#include <memory>

class IHashAlgorithm
{
public:
    virtual ~IHashAlgorithm() = default;

    virtual std::string hash(const void *data, size_t size) = 0;

    virtual void reset() = 0;
};

using HashAlgorithmPtr = std::unique_ptr<IHashAlgorithm>;
