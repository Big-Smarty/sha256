#include "sha256.hpp"
#include "util.hpp"

std::string sha256(std::string data) {
  auto padded = pad(data);
  return padded;
}
