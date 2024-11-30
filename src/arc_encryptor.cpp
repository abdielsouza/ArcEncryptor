#include "arc_encryptor.hpp"
#include "arc_utils.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <functional>

void arc_encrypt_content(ArcEncryptor& encryptor, std::string& message, double radius)
{
    auto key = arc_generate_random_key();
    encryptor.decrypt_key = key;

    encryptor.arc_radius = radius;

    for (auto chr : message)
    {
        auto theta = static_cast<double>((int) chr / 256 * 2 * M_PI);
        auto theta_prime = std::modulus<double>()((theta + key), (2 * M_PI));

        auto x = radius * std::cos(theta_prime);
        auto y = radius * std::sin(theta_prime);

        std::get<ArcEncryptedText>(encryptor.encrypted_content).push_back(std::make_tuple(x, y));
    }
}

void arc_decrypt_content(ArcEncryptor& encryptor)
{
    for (auto [x, y] : std::get<ArcEncryptedText>(encryptor.encrypted_content))
    {
        auto theta_prime = std::atan2(y, x);
        auto theta = std::modulus<double>()((theta_prime - encryptor.decrypt_key), (2 * M_PI));

        auto chr = static_cast<char>(
            static_cast<int>(theta / (2 * M_PI) * 256)
        );

        encryptor.decrypted_content.push_back(chr);
    }
}

void arc_encrypt_file(
    ArcEncryptor& encryptor, 
    const std::string& inputFilePath, 
    const std::string& outputFilePath, 
    double radius = 1.0
)
{
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath + ".arc", std::ios::binary);

    auto key = arc_generate_random_key();
    encryptor.decrypt_key = key;

    unsigned char byte;

    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
    {
        auto [x, y] = arc_encrypt_byte(byte, encryptor.decrypt_key, radius);
        outputFile.write(reinterpret_cast<char*>(&x), sizeof(x));
        outputFile.write(reinterpret_cast<char*>(&y), sizeof(y));
    }

    inputFile.close();
    outputFile.close();
}

void arc_decrypt_file(ArcEncryptor& encryptor, const std::string& inputFilePath, const std::string& outputFilePath)
{
    std::ifstream inputFile(inputFilePath + ".arc", std::ios::binary);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    double x, y;

    while (
        inputFile.read(reinterpret_cast<char*>(&x), sizeof(x)) &&
        inputFile.read(reinterpret_cast<char*>(&y), sizeof(y))
    )
    {
        unsigned char byte = arc_decrypt_byte(x, y, encryptor.decrypt_key, encryptor.arc_radius);
        outputFile.write(reinterpret_cast<char*>(&byte), sizeof(byte));
    }

    inputFile.close();
    outputFile.close();
}