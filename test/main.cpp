#include "arc_encryptor.hpp"
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string publicKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdef";
    std::string privateKey = "fedcba0987654321ZYXWVUTSRQPONMLKJIHGFEDCBA";

    // Texto a ser criptografado
    std::string text = "Hello, World!";

    ArcDataHolder holder;

    auto encoded = arc_encrypt_file(holder, "/home/abdiel/Documentos/MyLibraries/ArcEncryptor/test/example.jpeg", publicKey);

    std::cout << std::get<1>(encoded) << "\n";

    std::cout << "Encrypted coordinates:\n";

    for (const auto& coord : holder.encryptedContent)
        std::cout << "(" << coord.first << ", " << coord.second << ")\n";
    
    auto decoded = arc_decrypt_file(holder, "/home/abdiel/Documentos/MyLibraries/ArcEncryptor/test/example.jpeg", publicKey);

    std::cout << std::get<1>(decoded) << "\n";

    std::cout << "\nDecrypted text: " << holder.decryptedContent << "\n";
    

    return 0;
}
