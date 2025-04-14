// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/hash.h>

#include <algorithm>

#include <kth/infrastructure/hash_define.hpp>
#include <kth/infrastructure/math/hash.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/hash.h>


namespace {

inline
int char2int(char input) {
    // precondition:
    if (input >= '0' && input <= '9') {
        return input - '0';
    }
    if (input >= 'A' && input <= 'F') {
        return input - 'A' + 10;
    }
    if (input >= 'a' && input <= 'f') {
        return input - 'a' + 10;
    }
    return 0;
    //throw std::invalid_argument("Invalid input string");
}

inline
void hex2bin(char const* src, uint8_t* target) {
    while ((*src != 0) && (src[1] != 0)) {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

} // anonymous namespace

// ---------------------------------------------------------------------------
extern "C" {

kth_hash_t kth_sha256_hash(uint8_t const* data, kth_size_t size) {
    kth::data_slice slice(data, data + size);
    auto hash = kth::sha256_hash(slice);
    return kth::to_hash_t(hash);
}

kth_hash_t kth_sha256_hash_reversed(uint8_t const* data, kth_size_t size) {
    kth::data_slice slice(data, data + size);
    auto hash = kth::sha256_hash(slice);
    std::reverse(hash.begin(), hash.end());
    return kth::to_hash_t(hash);
}

char* kth_sha256_hash_reversed_str(uint8_t const* data, kth_size_t size) {
    auto hash = kth_sha256_hash(data, size);
    return kth_hash_to_str(hash); // this function reverses the hash when encoding to string
}

kth_hash_t kth_str_to_hash(char const* str) {
	kth::hash_digest hash_bytes;
	hex2bin(str, hash_bytes.data());
	std::reverse(hash_bytes.begin(), hash_bytes.end());
    auto res = kth::to_hash_t(hash_bytes);
    return res;
}

char* kth_hash_to_str(kth_hash_t hash) {
    size_t n = std::size(hash.hash);
    auto* ret = kth::mnew<char>(n * 2 + 1);
    ret[n * 2] = '\0';

    --n;
    auto* f = ret;
    while (true) {
        auto b = hash.hash[n];
        snprintf(f, 3, "%02x", b);
        f += 2;
        if (n == 0) break;
        --n;
    }

    return ret;
}

void kth_shorthash_set(kth_shorthash_t* shorthash, uint8_t const* data) {
    memcpy(shorthash->hash, data, KTH_BITCOIN_SHORT_HASH_SIZE);
}

void kth_shorthash_destruct(kth_shorthash_t* shorthash) {
    delete shorthash;
}

void kth_hash_set(kth_hash_t* hash, uint8_t const* data) {
    memcpy(hash->hash, data, KTH_BITCOIN_HASH_SIZE);
}

void kth_hash_destruct(kth_hash_t* hash) {
    delete hash;
}

void kth_longhash_set(kth_longhash_t* longhash, uint8_t const* data) {
    memcpy(longhash->hash, data, KTH_BITCOIN_LONG_HASH_SIZE);
}

void kth_longhash_destruct(kth_longhash_t* longhash) {
    delete longhash;
}

void kth_encrypted_seed_set(kth_encrypted_seed_t* seed, uint8_t const* data) {
    memcpy(seed->hash, data, KTH_BITCOIN_ENCRYPTED_SEED_SIZE);
}

void kth_encrypted_seed_destruct(kth_encrypted_seed_t* seed) {
    delete seed;
}

void kth_ec_secret_set(kth_ec_secret_t* secret, uint8_t const* data) {
    memcpy(secret->hash, data, KTH_BITCOIN_EC_SECRET_SIZE);
}

void kth_ec_secret_destruct(kth_ec_secret_t* secret) {
    delete secret;
}


// void print_hex(uint8_t const* data, size_t n) {
//     while (n != 0) {
//         printf("%2x", *data);
//         ++data;
//         --n;
//     }
//     printf("\n");
// }



} // extern "C"
