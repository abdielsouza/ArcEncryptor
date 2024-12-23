#ifndef A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0
#define A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0

#pragma once

#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

namespace ArcUtils
{
    std::string generate_sha256(const std::string& input)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*) input.c_str(), input.size(), hash);

        std::ostringstream oss;

        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        return oss.str();
    }
}

#endif /* A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0 */
