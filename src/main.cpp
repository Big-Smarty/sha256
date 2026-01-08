#include <cstdio>
#include <openssl/sha.h>
#include "util.hpp"
#include "sha256.hpp"

int main(int argc, char **argv) {
    for (auto i = 0; i < 1000; i++) {
        auto len = 100;
        std::string data = gen_random(len);
        std::string openssl_hash;
        openssl_hash.resize(64);
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), reinterpret_cast<unsigned char*>(openssl_hash.data()));
        std::string own_hash = sha256(data);
        if (openssl_hash != own_hash) {
            printf("Test failed! input: %s\nopenssl hash: %s\nown hash: %s", data.c_str(), openssl_hash.c_str(), own_hash.c_str());
            return -1;
        }
    }
    return 0;
}
