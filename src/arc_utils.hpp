#ifndef A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0
#define A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0

#pragma once

#include <random>
#include <tuple>
#include <cmath>

const double arc_generate_random_key()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist(-3.14f, 3.14f);

    const double random_key = dist(gen);

    return random_key;
}

const std::tuple<double, double> arc_encrypt_byte(unsigned char byte, double key, double radius = 1.0)
{
    double theta = static_cast<double>(byte) / 256.0 * 2 * M_PI;
    double theta_prime = std::fmod(theta + key, 2 * M_PI);

    double x = radius * std::cos(theta_prime);
    double y = radius * std::sin(theta_prime);

    return std::make_tuple(x, y);
}

unsigned char arc_decrypt_byte(double x, double y, double key, double radius = 1.0)
{
    double theta_prime = std::atan2(y, x);
    double theta = std::fmod(theta_prime - key + 2 * M_PI, 2 * M_PI);

    unsigned char byte = static_cast<unsigned char>(theta / (2 * M_PI) * 256.0);

    return byte;
}

#endif /* A279248C_D4B1_4F6A_B1B5_CFEEF5CF85B0 */
