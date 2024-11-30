#ifndef ARC_ENCRYPTOR_H
#define ARC_ENCRYPTOR_H

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <tuple>
#include <variant>
#include <fstream>

// cryptography formula: ß = (x^a) * 3

using ArcEncryptedText = std::vector<std::tuple<double, double>>;

struct ArcEncryptor
{
    std::string decrypted_content;
    std::variant<ArcEncryptedText, std::string> encrypted_content;
    double decrypt_key;
    uint16_t arc_radius;
};

void arc_encrypt_content(ArcEncryptor& encryptor, std::string& message, double radius = 1.0);
void arc_decrypt_content(ArcEncryptor& encryptor);

void arc_encrypt_file(ArcEncryptor& encryptor, const std::string& inputFilePath, const std::string& outputFilePath, double radius = 1.0);
void arc_decrypt_file(ArcEncryptor& encryptor, const std::string& inputFilePath, const std::string& outputFilePath);

#endif