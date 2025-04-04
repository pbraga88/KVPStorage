#include <sodium.h>
#include <fstream>

void generate_keys() {
    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char hmac_key[crypto_auth_hmacsha256_KEYBYTES];

    randombytes_buf(key, sizeof key);
    randombytes_buf(hmac_key, sizeof hmac_key);

    std::ofstream out1("kvpstorage.key", std::ios::binary);
    out1.write(reinterpret_cast<char*>(key), sizeof key);

    std::ofstream out2("kvpstorage.hmac", std::ios::binary);
    out2.write(reinterpret_cast<char*>(hmac_key), sizeof hmac_key);
}

int main() {
    if (sodium_init() < 0) {
        return 1; // panic! the library couldn't be initialized
    }

    generate_keys();

    return 0;
}
// This program generates a random key and HMAC key for use with the KVPStorage system.