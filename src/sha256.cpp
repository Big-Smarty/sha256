#include "sha256.hpp"
#include "util.hpp"
#include "word.hpp"
#include <format>
#include <stdlib.h>
#include <vector>

uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (WORD_SIZE - n)); }
uint32_t rotl(uint32_t x, int n) { return (x << n) | (x >> (WORD_SIZE - n)); }

uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return ((x & y) ^ (~x & z)); }
uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
  return ((x & y) ^ (x & z) ^ (y & z));
}
uint32_t bsig0(uint32_t x) { return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22)); }
uint32_t bsig1(uint32_t x) { return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25)); }
uint32_t ssig0(uint32_t x) { return (rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3)); }
uint32_t ssig1(uint32_t x) { return (rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10)); }

std::string sha256(std::string data) {
  std::array<uint32_t, 8> H = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
  auto padded = pad(data);

  // parse into words
  auto words = string_to_words(padded);

  // parse words into blocks
  std::vector<std::array<uint32_t, 16>> blocks;
  auto block_count = words.size() / 16;
  blocks.resize(block_count);
  for (auto i = 0; i < block_count; i++) {
    auto idx = i * 16;
    for (auto j = 0; j < 16; j++) {
      blocks[i][j] = words[idx + j];
    }
  }

  for (auto i = 0; i < block_count; i++) {
    std::array<uint32_t, 64> W;
    for (auto t = 0; t < 16; t++) {
      W[t] = blocks[i][t];
    }
    for (auto t = 16; t < 64; t++) {
      W[t] = ssig1(W[t - 2]) + W[t - 7] + ssig0(W[t - 15]) + W[t - 16];
    }

    auto a = H[0];
    auto b = H[1];
    auto c = H[2];
    auto d = H[3];
    auto e = H[4];
    auto f = H[5];
    auto g = H[6];
    auto h = H[7];

    for (auto t = 0; t < 64; t++) {
      auto T1 = h + bsig1(e) + ch(e, f, g) + K[t] + W[t];
      auto T2 = bsig0(a) + maj(a, b, c);
      h = g;
      g = f;
      f = e;
      e = d + T1;
      d = c;
      c = b;
      b = a;
      a = T1 + T2;
    }

    H = {
        a + H[0], b + H[1], c + H[2], d + H[3],
        e + H[4], f + H[5], g + H[6], h + H[7],
    };
  }

  std::string hash;
  for (auto h : H) {
    hash += std::format("{:08x}", h);
  }

  return hash;
}
