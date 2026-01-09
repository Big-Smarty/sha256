#include <vector>
#include <string>
#include <cstdint>
#include <cassert>

std::vector<uint32_t> string_to_words(const std::string& input) {
    // SHA-256 processes 512-bit (64-byte) blocks. 
    // The padded input MUST be a multiple of 64 bytes.
    assert(input.size() % 64 == 0);

    size_t word_count = input.size() / 4;
    std::vector<uint32_t> words;
    words.reserve(word_count); // Pre-allocate memory for performance

    for (size_t i = 0; i < input.size(); i += 4) {
        // Explicitly construct the 32-bit word in Big-Endian order
        // This shifts the first byte to the most significant position
        uint32_t word = (static_cast<uint8_t>(input[i])     << 24) |
                        (static_cast<uint8_t>(input[i + 1]) << 16) |
                        (static_cast<uint8_t>(input[i + 2]) << 8)  |
                        (static_cast<uint8_t>(input[i + 3]));
        
        words.push_back(word);
    }

    return words;
}