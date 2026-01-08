#include "word.hpp"

template <int w> Word<w>::Word(std::array<std::byte, w / 8> bytes) {
  m_data = bytes;
}

template <int w> Word<w> Word<w>::operator&(Word<w> &other) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] & other.data()[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator|(Word<w> &other) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] | other.data()[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator^(Word<w> &other) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] ^ other.data()[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator!() {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = ~m_data[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator+(Word<w> &other) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] + other.data()[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator-(Word<w> &other) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] - other.data()[i];
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator>>(int n) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] >> n;
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::operator<<(int n) {
  std::array<std::byte, w / 8> out;
  for (auto i = 0; i < w / 8; i++) {
    out[i] = m_data[i] << n;
  }
  return Word(out);
}
template <int w> Word<w> Word<w>::rotr(int n) {
  return (*this >> n) | (*this << (w - n));
}
template <int w> Word<w> Word<w>::rotl(int n) {
  return (*this << n) | (*this >> (w - n));
}
