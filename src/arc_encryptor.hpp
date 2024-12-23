#ifndef ARC_ENCRYPTOR_H
#define ARC_ENCRYPTOR_H

#pragma once

#define ARC_RADIUS_FACTOR 10

#include <vector>
#include <utility>
#include <string>
#include <filesystem>
#include <tuple>

namespace fs = std::filesystem;

using ArcEncryptedData = typename std::vector<std::pair<double, double>>;
using ArcResult = typename std::tuple<bool, std::string>;

struct ArcDataHolder
{
    ArcEncryptedData encryptedContent;
    std::string decryptedContent;
};

/*
 * Cryptography functions applied for raw strings
 */

ArcResult arc_encrypt_content(ArcDataHolder& holder, const std::string& text, const std::string& key);
ArcResult arc_decrypt_content(ArcDataHolder& holder, const std::string& key);

/*
 * Cryptography functions applied for files
 */

ArcResult arc_encrypt_file(ArcDataHolder& holder, const fs::path& filename, const std::string& key);
ArcResult arc_decrypt_file(ArcDataHolder& holder, const fs::path& filename, const std::string& key);

#endif