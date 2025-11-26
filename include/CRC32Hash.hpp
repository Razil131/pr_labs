#pragma once

#include "IHashAlgorithm.hpp"
#include <boost/crc.hpp>
#include <sstream>
#include <iomanip>

class CRC32Hash : public IHashAlgorithm
{
public:
    CRC32Hash() = default;

    std::string hash(const void *data, size_t size) override;
    void reset() override;

private:
    boost::crc_32_type crc_;
};
