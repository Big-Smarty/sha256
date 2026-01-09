#include "util.hpp"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>

static const char FIRST_PAD = 0b10000000;

std::string gen_random() {
    srand(time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    uint32_t len = rand() % 100000;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int calculate_k(int size) {
  return (448 - 1 - size % 512 + 512) % 512;
}

std::string pad(const std::string &data) {
    uint64_t original_byte_size = data.size();
    uint64_t original_bit_size = original_byte_size * 8;

    // 1. Append the '1' bit (0x80 byte)
    std::string out = data;
    out.push_back(static_cast<char>(0x80));

    // 2. Calculate 'k' (number of 0x00 bytes)
    // We need: (data_len + 1 + k + 8) % 64 == 0
    // So: k = (448 - (data_len_bits + 8)_bits) mod 512
    // In bytes: k = (56 - (out.size() % 64)) % 64
    size_t k = (56 > (out.size() % 64)) ? (56 - (out.size() % 64)) : (120 - (out.size() % 64));
    
    out.append(k, 0x00);

    // 3. Append the length as a 64-bit BIG-ENDIAN integer (8 bytes)
    for (int i = 7; i >= 0; i--) {
        // Shift bits to get each byte in big-endian order
        out.push_back(static_cast<char>((original_bit_size >> (i * 8)) & 0xFF));
    }

    // Now the total size is a multiple of 64 bytes (512 bits)
    assert(out.size() % 64 == 0);
    return out;
}