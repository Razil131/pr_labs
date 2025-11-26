#pragma once

#include "IHashAlgorithm.hpp"
#include <boost/uuid/detail/md5.hpp>
#include <sstream>
#include <iomanip>

class MD5Hash : public IHashAlgorithm
{
public:
    MD5Hash() = default;

    std::string hash(const void *data, size_t size) override;
    void reset() override;

private:
    boost::uuids::detail::md5 md5_;
};
