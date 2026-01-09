#pragma once

#include <bit>
#include <cstdint>
#include <string>
#include <unistd.h>

std::string gen_random();

template <typename T> inline T to_big_endian(T input) {
  if constexpr (std::endian::native == std::endian::big) {
    return input;
  } else if constexpr (std::endian::native == std::endian::little) {
    if constexpr (sizeof(T) == 2) {
      return __builtin_bswap16(std::bit_cast<uint16_t>(input));
    } else if constexpr (sizeof(T) == 4) {
      return __builtin_bswap32(std::bit_cast<uint32_t>(input));
    } else if constexpr (sizeof(T) == 8) {
      return __builtin_bswap64(std::bit_cast<uint64_t>(input));
    }
  }
}

std::string pad(const std::string &data);