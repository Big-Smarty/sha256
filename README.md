# SHA-256 Exercise Project

This repository is an educational SHA-256 implementation written in C++23. The goal is to understand the internals of SHA-256 well enough to later port the algorithm to a Slang compute shader.

The implementation is complete enough to pass the included comparison harness against OpenSSL. It is not intended to be production cryptography.

## Background

The broader motivation came from a cryptography course assignment to build a toy blockchain. The assignment rewarded blocks with more leading zero nibbles, and the original suggested workflow used CrypTool 2. Because CrypTool 2 did not work well on Linux, this project explores implementing the hashing logic directly in C++ first, with the longer-term idea of moving the work to GPU compute.

## What Is Implemented

The SHA-256 implementation includes:

- message padding
- big-endian 32-bit word parsing
- message schedule expansion
- SHA-256 compression rounds
- final hexadecimal digest formatting

OpenSSL is used only as a correctness oracle in the local harness.

## Build

This project uses xmake.

```sh
xmake
```

## Verify

Run the comparison harness with:

```sh
xmake run sha256
```

The binary does not provide a general-purpose CLI. Instead, it runs a randomized comparison loop, hashes generated inputs with both this implementation and OpenSSL, and exits on the first mismatch.

Current harness limitations:

- there is no formal test suite
- random generation calls `srand(time(NULL))` repeatedly, so fast loop iterations can reuse the same seed and compare repeated inputs

## License

This project is licensed under the MIT License. See `LICENSE`.
