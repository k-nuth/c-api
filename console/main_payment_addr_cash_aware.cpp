// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <thread>

#include <kth/domain/wallet/payment_address.hpp>


#include <kth/infrastructure/wallet/cashaddr.hpp>

using namespace kth::infrastructure::wallet;
using kth::data_chunk;

template <unsigned int frombits, unsigned int tobits, bool pad, typename O, typename I>
bool convert_bits(O& out, I it, I end) {
    size_t acc = 0;
    size_t bits = 0;
    constexpr size_t maxv = (1U << tobits) - 1;
    constexpr size_t max_acc = (1U << (frombits + tobits - 1)) - 1;
    while (it != end) {
        acc = ((acc << frombits) | *it) & max_acc;
        bits += frombits;
        while (bits >= tobits) {
            bits -= tobits;
            out.push_back((acc >> bits) & maxv);
        }
        ++it;
    }

    // We have remaining bits to encode but do not pad.
    if ( ! pad && bits) {
        return false;
    }

    // We have remaining bits to encode so we do pad.
    if (pad && bits) {
        out.push_back((acc << (tobits - bits)) & maxv);
    }

    return true;
}

// Convert the data part to a 5 bit representation.
template <typename T>
data_chunk pack_addr_data_(T const& id, uint8_t type) {
    uint8_t version_byte(type << 3U);
    size_t size = id.size();
    uint8_t encoded_size = 0;

    switch (size * 8) {
        case 160:
            encoded_size = 0;
            break;
        case 192:
            encoded_size = 1;
            break;
        case 224:
            encoded_size = 2;
            break;
        case 256:
            encoded_size = 3;
            break;
        case 320:
            encoded_size = 4;
            break;
        case 384:
            encoded_size = 5;
            break;
        case 448:
            encoded_size = 6;
            break;
        case 512:
            encoded_size = 7;
            break;
        default:
            throw std::runtime_error("Error packing cashaddr: invalid address length");
    }

    version_byte |= encoded_size;
    data_chunk data = {version_byte};
    data.insert(data.end(), std::begin(id), std::end(id));

    data_chunk converted;
    // Reserve the number of bytes required for a 5-bit packed version of a
    // hash, with version byte.  Add half a byte(4) so integer math provides
    // the next multiple-of-5 that would fit all the data.
    converted.reserve(((size + 1) * 8 + 4) / 5);
    convert_bits<8, 5, true>(converted, std::begin(data), std::end(data));

    return converted;
}

enum cash_addr_type : uint8_t {
    PUBKEY_TYPE = 0,
    SCRIPT_TYPE = 1,
    TOKEN_PUBKEY_TYPE = 2, // Token-Aware P2PKH
    TOKEN_SCRIPT_TYPE = 3, // Token-Aware P2SH
};

std::string encode_cashaddr_(kth::domain::wallet::payment_address const& wallet, bool token_aware) {
    // Mainnet
    if (wallet.version() == kth::domain::wallet::payment_address::mainnet_p2kh || wallet.version() == kth::domain::wallet::payment_address::mainnet_p2sh) {
        if (token_aware) {
            return cashaddr::encode(kth::domain::wallet::payment_address::cashaddr_prefix_mainnet,
                pack_addr_data_(wallet.hash20(), wallet.version() == kth::domain::wallet::payment_address::mainnet_p2kh ? TOKEN_PUBKEY_TYPE : TOKEN_SCRIPT_TYPE));
        }
        return cashaddr::encode(kth::domain::wallet::payment_address::cashaddr_prefix_mainnet,
            pack_addr_data_(wallet.hash20(), wallet.version() == kth::domain::wallet::payment_address::mainnet_p2kh ? PUBKEY_TYPE : SCRIPT_TYPE));
    }

    // Testnet
    if (wallet.version() == kth::domain::wallet::payment_address::testnet_p2kh || wallet.version() == kth::domain::wallet::payment_address::testnet_p2sh) {
        if (token_aware) {
            return cashaddr::encode(kth::domain::wallet::payment_address::cashaddr_prefix_testnet,
                pack_addr_data_(wallet.hash20(), wallet.version() == kth::domain::wallet::payment_address::testnet_p2kh ? TOKEN_PUBKEY_TYPE : TOKEN_SCRIPT_TYPE));
        }
        return cashaddr::encode(kth::domain::wallet::payment_address::cashaddr_prefix_testnet,
            pack_addr_data_(wallet.hash20(), wallet.version() == kth::domain::wallet::payment_address::testnet_p2kh ? PUBKEY_TYPE : SCRIPT_TYPE));
    }
    return "";
}

int main(int /*argc*/, char* /*argv*/[]) {
    using kth::domain::wallet::payment_address;

    std::string addr = "bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p";
    payment_address const pa("bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p");
    if ( ! pa) {
        std::cout << "Invalid address" << std::endl;
        return -1;
    }
    std::cout << "Valid address" << std::endl;
    std::cout << "Original Address: " << addr << std::endl;
    std::cout << "Encoded cashaddr: " << pa.encoded_cashaddr(false) << std::endl;
    std::cout << "Encoded cashaddr: " << pa.encoded_cashaddr(true) << std::endl;
    std::cout << "Encoded cashaddr: " << encode_cashaddr_(pa, false) << std::endl;
    std::cout << "Encoded cashaddr: " << encode_cashaddr_(pa, true) << std::endl;

    std::cout << "Encoded legacy:   " << pa.encoded_legacy() << std::endl;


    // const result = paymentAddress.fromData('bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p');
    // expect(result.ok).toBe(true);
    // const addr = result.obj;
    // expect(addr.encoded()).toBe('bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p');
    // // expect(addr.encodedCashAddr()).toBe('bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p');
    // // expect(addr.encodedLegacy()).toBe('1P3GQYtcWgZHrrJhUa4ctoQ3QoCU2F65nz');

    return 0;
}
