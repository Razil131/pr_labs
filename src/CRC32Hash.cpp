#include "CRC32Hash.hpp"

std::string CRC32Hash::hash(const void *data, size_t size)
{
    crc_.reset();
    crc_.process_bytes(data, size);

    std::ostringstream oss;
    oss << std::hex << std::setw(8) << std::setfill('0') << crc_.checksum();
    return oss.str();
}

void CRC32Hash::reset()
{
    crc_.reset();
}
