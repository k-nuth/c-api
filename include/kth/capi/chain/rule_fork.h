// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_RULE_FORK_H_
#define KTH_CAPI_CHAIN_RULE_FORK_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_rule_fork_no_rules = 0,

    /// Allow minimum difficulty blocks (hard fork, testnet).
    kth_rule_fork_easy_blocks = 1U << 0,

    /// Pay-to-script-hash enabled (soft fork, feature).
    kth_rule_fork_bip16_rule = 1U << 1,

    /// No duplicated unspent transaction ids (hard fork, security).
    kth_rule_fork_bip30_rule = 1U << 2,

    /// Coinbase must include height (soft fork, security).
    kth_rule_fork_bip34_rule = 1U << 3,

    /// Strict DER signatures required (soft fork, security).
    kth_rule_fork_bip66_rule = 1U << 4,

    /// Operation nop2 becomes check locktime verify (soft fork, feature).
    kth_rule_fork_bip65_rule = 1U << 5,

    /// Hard code bip34-based activation heights (hard fork, optimization).
    kth_rule_fork_bip90_rule = 1U << 6,

    /// Assume hash collisions cannot happen (hard fork, optimization).
    kth_rule_fork_allow_collisions = 1U << 7,

    /// Enforce relative locktime (soft fork, feature).
    kth_rule_fork_bip68_rule = 1U << 8,

    /// Operation nop3 becomes check sequence verify (soft fork, feature).
    kth_rule_fork_bip112_rule = 1U << 9,

    /// Use median time past for locktime (soft fork, feature).
    kth_rule_fork_bip113_rule = 1U << 10,

#if defined(KTH_CURRENCY_BCH)
    kth_rule_fork_bch_uahf = 1U << 11,                //2017-Aug Upgrade - Bitcoin Cash UAHF (1501590000)
    kth_rule_fork_bch_daa_cw144  = 1U << 12,          //2017-Nov Upgrade - DAA/cw-144 - (1510600000)
    kth_rule_fork_bch_pythagoras = 1U << 13,          //2018-May Upgrade - pythagoras - (1526400000)
    kth_rule_fork_bch_euclid = 1U << 14,              //2018-Nov Upgrade - euclid - (1542300000)
    kth_rule_fork_bch_pisano = 1U << 15,              //2019-May Upgrade - pisano - (1557921600)
    kth_rule_fork_bch_mersenne = 1U << 16,            //2019-Nov Upgrade - mersenne - (1573819200)
    kth_rule_fork_bch_fermat = 1U << 17,              //2020-May Upgrade - fermat - (1589544000)
    kth_rule_fork_bch_euler = 1U << 18,               //2020-Nov Upgrade - euler - (1605441600)
                                                      //2021-May NO-Upgrade - (1621080000)
    kth_rule_fork_bch_gauss = 1U << 19,               //2022-May Upgrade - gauss - (1652616000)
    kth_rule_fork_bch_descartes = 1U << 20,           //2023-May Upgrade - descartes - (1684152000)
    kth_rule_fork_bch_lobachevski = 1U << 21,         //2024-May Upgrade - lobachevski - (1715774400)
    kth_rule_fork_bch_galois = 1U << 22,              //2025-May Upgrade - galois - (1747310400)
    kth_rule_fork_bch_leibniz = 1U << 23,             //2026-May Upgrade - leibniz - (1778846400)
    kth_rule_fork_bch_cantor = 1U << 24,              //2027-May Upgrade - cantor - (xxxxxxxxxxxx)
    
    // kth_rule_fork_bch_unnamed = 1U << xx,          //20xx-May Upgrade - unnamed - (9999999999)
#else
    // Just for segwit coins
    /// Segregated witness consensus layer (soft fork, feature).
    kth_rule_fork_bip141_rule = 1U << 11,

    /// Segregated witness v0 verification (soft fork, feature).
    kth_rule_fork_bip143_rule = 1U << 12,

    /// Prevent dummy value malleability (soft fork, feature).
    kth_rule_fork_bip147_rule = 1U << 13,
#endif //KTH_CURRENCY_BCH


    /// Perform difficulty retargeting (hard fork, regtest).
    kth_rule_fork_retarget = 1U << 30,

    /// Sentinel bit to indicate tx has not been validated.
    kth_rule_fork_unverified = 1U << 31,

    /// Rules that use bip34-based activation.
    kth_rule_fork_bip34_activations =
        kth_rule_fork_bip34_rule |
        kth_rule_fork_bip65_rule |
        kth_rule_fork_bip66_rule,


#if ! defined(KTH_CURRENCY_BCH)
    /// Rules that use BIP9 bit zero first time activation.
    kth_rule_fork_bip9_bit0_group =
        kth_rule_fork_bip68_rule |
        kth_rule_fork_bip112_rule |
        kth_rule_fork_bip113_rule,

    /// Rules that use BIP9 bit one first time activation.
    kth_rule_fork_bip9_bit1_group =
        kth_rule_fork_bip141_rule |
        kth_rule_fork_bip143_rule |
        kth_rule_fork_bip147_rule,
#endif

    /// Simple mask to set all bits.
    kth_rule_fork_all_rules = 0xffffffff
} kth_rule_fork_t;


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_RULE_FORK_H_ */
