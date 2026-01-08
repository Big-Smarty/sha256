#include "util.hpp"
#include <bitset>
#include <cassert>
#include <string>

static const char FIRST_PAD = 0b10000000;

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int calculate_k(int size) {
  return (448 - 1 - size % 512 + 512) % 512;
}

std::string pad(std::string &data) {
  auto size = data.size();
  auto k = calculate_k(size);
  auto zero_chars_required = k;
  std::string padding(zero_chars_required, 0);
  std::string out = data + FIRST_PAD + padding + std::bitset<64>(to_big_endian(static_cast<uint64_t>(size))).to_string();
  assert(out.size() % 512 == 0);
  return out;
}
