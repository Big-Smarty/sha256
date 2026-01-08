#pragma once

#include <array>

// define word sizes of 4 and 8 bytes
enum W {
  S32 = 4,
  S64 = 8
};

// generic word class
template<int w> class Word {
  Word(std::array<std::byte, w / 8> bytes);
  Word(Word const &) = delete;
  Word(Word const &&) = delete;
  Word operator=(Word const& other) = delete;
  Word operator=(Word const&& other) = delete;

  Word<w> operator&(Word<w> &other);
  Word<w> operator|(Word<w> &other);
  Word<w> operator^(Word<w> &other);
  Word<w> operator!();
  Word<w> operator+(Word<w> &other);
  Word<w> operator-(Word<w> &other);
  Word<w> operator>>(int n);
  Word<w> operator<<(int n);
  Word<w> rotr(int n);
  Word<w> rotl(int n);

  std::array<std::byte, w> data() {
    return &m_data;
  }
  
  std::array<std::byte, w> m_data;
};
