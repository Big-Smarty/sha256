#include "util.hpp"
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

std::string pad(std::string &data) {
  auto size = data.size();
  // TODO: fix k calculation
  auto k = (size + 1)%512 - 448;
  auto zero_chars_required = k / 8;
  printf("size: %zu, zero chars required: %zu\n", size, zero_chars_required);
  std::string padding(zero_chars_required, 0);
  printf("padding: %s", padding.c_str());
  std::string out = data + FIRST_PAD + padding + std::to_string(to_big_endian(size));
  assert(out.size() % 512 == 0);
  return out;
}
