#include <cstdio>
#include <iomanip>
#include <ios>
#include <openssl/sha.h>
#include "util.hpp"
#include "sha256.hpp"

std::string to_hex(unsigned char* data, size_t len) {
    std::stringstream ss;
    for(size_t i = 0; i < len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}

int main(int argc, char **argv) {
    for (auto i = 0; i < 1000; i++) {
        auto len = 100;
        std::string data = gen_random();
        unsigned char hash[SHA256_DIGEST_LENGTH]; // SHA256_DIGEST_LENGTH is 32
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
        std::string own_hash = sha256(data);
        std::string openssl_hex = to_hex(hash, SHA256_DIGEST_LENGTH);
        if (openssl_hex != own_hash) {
            printf("Test failed! input: %s\nopenssl hash: %s\nown hash: %s\n", data.c_str(), openssl_hex.c_str(), own_hash.c_str());
            return -1;
        }
    }
    printf("All tests passed.\n");
    return 0;
}
