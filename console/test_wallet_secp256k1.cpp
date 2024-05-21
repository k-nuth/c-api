// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <thread>

#include <kth/capi/chain/chain.h>
#include <kth/capi/chain/history_compact.h>
#include <kth/capi/chain/history_compact_list.h>
#include <kth/capi/chain/input.h>
#include <kth/capi/chain/input_list.h>
#include <kth/capi/chain/output.h>
#include <kth/capi/chain/output_list.h>
#include <kth/capi/chain/output_point.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/chain/transaction.h>
#include <kth/capi/chain/transaction_list.h>
#include <kth/capi/node.h>
#include <kth/capi/hash_list.h>
#include <kth/capi/helpers.hpp>
#include <kth/capi/string_list.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/payment_address_list.h>

#include <kth/domain/message/transaction.hpp>

#include <kth/infrastructure/utility/binary.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>


#include <cstdlib>
#include <cstring>
#include <cassert>
#include <secp256k1.h>

#include "ct_str.hpp"


void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

inline
kth::long_hash longhash_to_cpp(uint8_t const* x) {
    kth::long_hash ret;
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}


// hd_private hd_private::from_seed(data_slice seed, uint64_t prefixes) {
//     // This is a magic constant from BIP32.
//     static data_chunk const magic(to_chunk("Bitcoin seed"));

//     auto const intermediate = split(hmac_sha512_hash(seed, magic));

//     // The key is invalid if parse256(IL) >= n or 0:
//     if ( ! verify(intermediate.left)) {
//         return {};
//     }

//     auto const master = hd_lineage {
//         prefixes,
//         0x00,
//         0x00000000,
//         0x00000000
//     };

//     return hd_private(intermediate.left, intermediate.right, master);
// }



// void HMACSHA512(uint8_t const* input, size_t length, uint8_t const* key,
//     size_t key_length, uint8_t digest[HMACSHA512_DIGEST_LENGTH])
// {

// long_hash hmac_sha512_hash(data_slice data, data_slice key) {
//     long_hash hash;
//     HMACSHA512(data.data(), data.size(), key.data(), key.size(), hash.data());
//     return hash;
// }

// hd_private hd_private::from_seed(seed_t seed, uint64_t prefixes) {
//     constexpr auto bip32_magic = ct::str("Bitcoin seed");
//     static_assert(bip32_magic.size() == 12);

//     auto const intermediate = split(hmac_sha512_hash(seed, magic));

//     // // The key is invalid if parse256(IL) >= n or 0:
//     // if ( ! verify(intermediate.left)) {
//     //     return {};
//     // }

//     // auto const master = hd_lineage {
//     //     prefixes,
//     //     0x00,
//     //     0x00000000,
//     //     0x00000000
//     // };

//     // return hd_private(intermediate.left, intermediate.right, master);
// }


    // hd_private hd_private::derive_private(uint32_t index) const {
    //     constexpr uint8_t depth = 0;

    //     auto const data = (index >= hd_first_hardened_key) ?
    //         splice(to_array(depth), secret_, to_big_endian(index)) :
    //         splice(point_, to_big_endian(index));

    //     auto const intermediate = split(hmac_sha512_hash(data, chain_));

    //     // The child key ki is (parse256(IL) + kpar) mod n:
    //     auto child = secret_;
    //     if ( ! ec_add(child, intermediate.left)) {
    //         return {};
    //     }

    //     if (lineage_.depth == max_uint8) {
    //         return {};
    //     }

    //     hd_lineage const lineage {
    //         lineage_.prefixes,
    //         static_cast<uint8_t>(lineage_.depth + 1),
    //         fingerprint(),
    //         index
    //     };

    //     return hd_private(child, intermediate.right, lineage);
    // }

using seed_t = std::span<uint8_t, 64>;


// translate: "endurecer" to english: "harden"

constexpr
uint32_t harden(uint32_t index) {
    return index | 0x80000000;
}

void derive_hardened(uint8_t* key, uint8_t* chain, uint32_t index) {
    index = harden(index);

    uint8_t data[37];
    data[0] = 0; // Profundidad (0 para la clave maestra)
    memcpy(data + 1, key, 32); // Copiar clave privada padre
    // Agregar índice al final
    data[33] = (index >> 24) & 0xFF;
    data[34] = (index >> 16) & 0xFF;
    data[35] = (index >> 8) & 0xFF;
    data[36] = index & 0xFF;
    uint8_t const* parent_key = data + 1;

    // Calcular HMAC-SHA512
    uint8_t digest[64];
    HMACSHA512(data, sizeof(data), chain, 32, digest);

    // Copiar la nueva clave privada a 'key'
    memcpy(key, digest, 32);

    // Sumar la nueva clave privada con la clave privada padre en la curva elíptica
    if ( ! secp256k1_ec_privkey_tweak_add(ctx_, key, parent_key)) {
        // Manejar error
    }

    // Copiar la nueva cadena de derivación a 'chain'
    memcpy(chain, digest + 32, 32);
}



struct wallet {
    constexpr
    int to_flags(bool compressed) {
        return compressed ? SECP256K1_EC_COMPRESSED : SECP256K1_EC_UNCOMPRESSED;
    }

    constexpr static unsigned int context_flags = SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY;
    constexpr static auto compressed_flags = to_flags(true);

    wallet(seed_t seed, uint64_t prefixes)
        : ctx_(secp256k1_context_create(context_flags))
        , secret_(long_bytes_)
        , chain_(long_bytes_ + 32)
    {
        constexpr auto bip32_magic = ct::str("Bitcoin seed");
        static_assert(bip32_magic.size() == 12);
        HMACSHA512(seed.data(), seed.size(), bip32_magic.data(), bip32_magic.size(), long_bytes_);
    }

    // // "m/44'/145'/0'/0";
    // void derive_hardened(uint32_t index) {
    //     constexpr uint8_t depth = 0;
    //     index |= 0x80000000;

    //     secret_expanded_[0] = 0; depth
    //     memcpy(secret_expanded_ + 1, secret_, 32);
    //     secret_expanded_[33] = (index >> 24) & 0xFF;
    //     secret_expanded_[34] = (index >> 16) & 0xFF;
    //     secret_expanded_[35] = (index >> 8) & 0xFF;
    //     secret_expanded_[36] = index & 0xFF;

    //     HMACSHA512(secret_expanded_, sizeof(secret_expanded_), chain_.data(), chain_.size(), long_bytes2_);
    //     std::span<uint8_t, 32> left(long_bytes2_);
    //     std::span<uint8_t, 32> right(long_bytes2_ + 32);

    //     std::span<uint8_t, 32> child(long_bytes_);
    //     secp256k1_pubkey pubkey;
    //     bool res = secp256k1_ec_pubkey_parse(ctx_, &pubkey, child.data(), child.size()) == 1;
    //     res = secp256k1_ec_pubkey_tweak_add(ctx_, &pubkey, secret.data()) == 1;

    //     size_t size;
    //     secp256k1_ec_pubkey_serialize(context, long_bytes_, &size, &pubkey, compressed_flags);
    //     res = size == 32;
    // }

    void derive_path() {
        // Derivar "m/44'"
        memcpy(current_key_, master_key_, 32);
        derive_hardened(current_key_, current_chain_, 44 | 0x80000000);

        // Derivar "m/44'/145'"
        derive_hardened(current_key_, current_chain_, 145 | 0x80000000);

        // Derivar "m/44'/145'/0'"
        derive_hardened(current_key_, current_chain_, 0 | 0x80000000);

        // Derivar "m/44'/145'/0'/0"
        derive_hardened(current_key_, current_chain_, 0);
    }

private:
    secp256k1_context* ctx_;

    uint8_t master_key_[32];
    uint8_t master_chain_[32];
    uint8_t current_key_[32];
    uint8_t current_chain_[32];

    // uint8_t long_bytes_[64];
    // uint8_t long_bytes2_[64];
    // std::span<uint8_t, 32> secret_;
    // std::span<uint8_t, 32> chain_;

    // uint8_t secret_expanded_[37];
};


int main(int argc, char* argv[]) {
    using kth::infrastructure::wallet::hd_private;
    using kth::infrastructure::wallet::hd_first_hardened_key;

   // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
   // https://iancoleman.io/bip39/
   // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

    auto wl = kth_core_string_list_construct();
    kth_core_string_list_push_back(wl, "car");
    kth_core_string_list_push_back(wl, "slab");
    kth_core_string_list_push_back(wl, "tail");
    kth_core_string_list_push_back(wl, "dirt");
    kth_core_string_list_push_back(wl, "wife");
    kth_core_string_list_push_back(wl, "custom");
    kth_core_string_list_push_back(wl, "front");
    kth_core_string_list_push_back(wl, "shield");
    kth_core_string_list_push_back(wl, "diet");
    kth_core_string_list_push_back(wl, "pear");
    kth_core_string_list_push_back(wl, "skull");
    kth_core_string_list_push_back(wl, "vapor");
    kth_core_string_list_push_back(wl, "gorilla");
    kth_core_string_list_push_back(wl, "token");
    kth_core_string_list_push_back(wl, "yard");

    kth_longhash_t seed_c;
    kth_wallet_mnemonics_to_seed_out(wl, &seed_c);
    print_hex(seed_c.hash, 64);
    // auto seed_hash = longhash_to_cpp(seed_c.hash);
    // kth::data_chunk seed(std::begin(seed_hash), std::end(seed_hash));

    // std::cout << "seed: ";
    // print_hex(seed.data(), seed.size());





    // Inicializar secp256k1 context
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    // Suponiendo que seed es un array de 64 bytes
    unsigned char seed[64]; // Debes llenar esto con tu seed real
    unsigned char private_key[32];
    // Aquí deberías derivar private_key de seed, por ejemplo, usando SHA256

    // Verificar que la clave privada es válida
    int valid = secp256k1_ec_seckey_verify(ctx, private_key);
    assert(valid);

    // Generar la clave pública
    secp256k1_pubkey public_key;
    valid = secp256k1_ec_pubkey_create(ctx, &public_key, private_key);
    assert(valid);

    // Aquí deberías continuar con la conversión de public_key a una dirección Bitcoin

    // Limpiar
    secp256k1_context_destroy(ctx);
    return 0;




    std::cout << std::endl;
}





// void derive_hardened(uint8_t const* parent_key, uint8_t const* parent_chain, uint32_t index, uint8_t* child_key, uint8_t* child_chain) {
//     index = harden(index);

//     uint8_t data[37];

//     data[0] = 0; // Profundidad (0 para la clave maestra)
//     memcpy(data + 1, parent_key, 32); // Copiar clave privada padre
//     // Agregar índice al final
//     data[33] = (index >> 24) & 0xFF;
//     data[34] = (index >> 16) & 0xFF;
//     data[35] = (index >> 8) & 0xFF;
//     data[36] = index & 0xFF;

//     // Calcular HMAC-SHA512 utilizando 'parent_chain' como clave
//     uint8_t digest[64];
//     HMACSHA512(data, sizeof(data), parent_chain, 32, digest);

//     // memcpy(child_key, parent_key, 32);
//     memcpy(child_chain, digest + 32, 32);

//     // // Sumar la nueva clave privada con la clave privada padre en la curva elíptica
//     // if ( ! secp256k1_ec_privkey_tweak_add(ctx_, child_key, digest)) {
//     //     // Manejar error
//     // }


//     secp256k1_pubkey pubkey;
//     bool res = secp256k1_ec_pubkey_parse(ctx_, &pubkey, parent_key, 32) == 1;
//     res = secp256k1_ec_pubkey_tweak_add(ctx_, &pubkey, secret.data()) == 1;

//     size_t size;
//     secp256k1_ec_pubkey_serialize(context, long_bytes_, &size, &pubkey, compressed_flags);
//     res = size == 32;

// }