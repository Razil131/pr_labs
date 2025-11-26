#include "MD5Hash.hpp"

std::string MD5Hash::hash(const void *data, size_t size)
{
    boost::uuids::detail::md5 md5;
    md5.process_bytes(data, size);

    boost::uuids::detail::md5::digest_type digest;
    md5.get_digest(digest);

    std::ostringstream oss;
    for (int i = 0; i < 4; ++i)
    {
        oss << std::hex << std::setw(8) << std::setfill('0') << digest[i];
    }

    return oss.str();
}

void MD5Hash::reset()
{
    md5_ = boost::uuids::detail::md5();
}
