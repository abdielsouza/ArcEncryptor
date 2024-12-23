#include "arc_encryptor.hpp"
#include "arc_utils.hpp"

#include <cstdint>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <iostream>


/*
 * Cryptography functions applied for raw strings
 */

ArcResult arc_encrypt_content(ArcDataHolder& holder, const std::string& text, const std::string& key)
{
    const std::string seed = ArcUtils::generate_sha256(key);
    const double k = std::stod("0." + seed.substr(0, 16));
    const double offset = std::stod("0." + seed.substr(16, 16));

    for (size_t i = 0; i < text.size(); i++)
    {
        double x = static_cast<double>(i) / 10;
        double y = std::sin(k * x + offset) + text[i];

        holder.encryptedContent.emplace_back(x, y);
    }

    return {true, "success"};
}

ArcResult arc_decrypt_content(ArcDataHolder& holder, const std::string& key)
{
    const std::string seed = ArcUtils::generate_sha256(key);
    const double k = std::stod("0." + seed.substr(0, 16));
    const double offset = std::stod("0." + seed.substr(16, 16));

    for (const auto& coord : holder.encryptedContent)
    {
        double x = coord.first;
        double y = coord.second;
        char originalChar = static_cast<char>((int) (y - std::sin(k * x + offset)));

        if ((int) originalChar == 31) originalChar = ' ';

        holder.decryptedContent += originalChar;
    }

    return {true, "success"};
}

/*
 * Cryptography functions applied for files
 */

ArcResult arc_encrypt_file(ArcDataHolder& holder, const fs::path& filename, const std::string& key)
{
    if (std::fstream file(fs::absolute(filename).string(), std::ios::in | std::ios::out | std::ios::binary | std::ios::ate); !file)
    {
        return {false, "failed to open file!"};
    }
    else
    {
        if (file.tellg() == 0)
        {
            return {false, "file is empty"};
        }

        file.seekg(0, std::ios::beg);

        std::ostringstream oss;
        oss << file.rdbuf();

        std::string data = oss.str();

        arc_encrypt_content(holder, data, key);

        file.close();

        file.open(fs::absolute(filename).string(), std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

        file.seekp(0, std::ios::beg);

        for (const auto& coord : holder.encryptedContent)
        {
            file.write(reinterpret_cast<const char*>(&coord.first), sizeof(coord.first));
            file.write(reinterpret_cast<const char*>(&coord.second), sizeof(coord.second));
        }

        file.close();
    }

    return {true, "success"};
}

ArcResult arc_decrypt_file(ArcDataHolder& holder, const fs::path& filename, const std::string& key)
{
    if (std::fstream file(fs::absolute(filename).string(), std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc); !file)
    {
        return {false, "failed to open file"};
    }
    else
    {
        arc_decrypt_content(holder, key);

        file.seekp(0, std::ios::beg);
        file.write(holder.decryptedContent.c_str(), holder.decryptedContent.size());
        file.close();
    }

    return {true, "success"};
}