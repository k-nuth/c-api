// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_
#define KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/config/checkpoint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t cores;
    kth_bool_t priority;
    float byte_fee_satoshis;
    float sigop_fee_satoshis;
    uint64_t minimum_output_satoshis;
    uint32_t notify_limit_hours;
    uint32_t reorganization_limit;
    kth_size_t checkpoint_count;
    kth_checkpoint* checkpoints;
    kth_bool_t fix_checkpoints;
    kth_bool_t allow_collisions;
    kth_bool_t easy_blocks;
    kth_bool_t retarget;
    kth_bool_t bip16;
    kth_bool_t bip30;
    kth_bool_t bip34;
    kth_bool_t bip66;
    kth_bool_t bip65;
    kth_bool_t bip90;
    kth_bool_t bip68;
    kth_bool_t bip112;
    kth_bool_t bip113;

#if defined(KTH_CURRENCY_BCH)
    kth_bool_t bch_uahf;
    kth_bool_t bch_daa_cw144;
    kth_bool_t bch_pythagoras;
    kth_bool_t bch_euclid;
    kth_bool_t bch_pisano;
    kth_bool_t bch_mersenne;
    kth_bool_t bch_fermat;         // 2020-May
    kth_bool_t bch_euler;          // 2020-Nov
                                   // 2021-May no Hard Fork
    kth_bool_t bch_gauss;          // 2022-May
    kth_bool_t bch_descartes;      // 2023-May
    kth_bool_t bch_lobachevski;    // 2024-May
    // kth_bool_t bch_galois;      // 2025-May
    // kth_bool_t bch_leibniz;     // 2026-May

    // //2020-Nov-15 hard fork, defaults to 1605441600: Nov 15, 2020 12:00:00 UTC protocol upgrade
    // uint64_t euler_activation_time;

    // //2022-May-15 hard fork, defaults to 1652616000: May 15, 2022 12:00:00 UTC protocol upgrade
    // uint64_t gauss_activation_time;

    // //2023-May-15 hard fork, defaults to 1684152000: May 15, 2023 12:00:00 UTC protocol upgrade
    // uint64_t descartes_activation_time;

    // //2024-May-15 hard fork, defaults to 1715774400: May 15, 2024 12:00:00 UTC protocol upgrade
    // uint64_t lobachevski_activation_time;

    //2025-May-15 hard fork, defaults to 1747310400: May 15, 2025 12:00:00 UTC protocol upgrade
    uint64_t galois_activation_time;

    // 2026-May-15 hard fork, defaults to 1778846400: May 15, 2026 12:00:00 UTC protocol upgrade
    uint64_t leibniz_activation_time;

    // The half life for the ASERTi3-2d DAA. For every (asert_half_life) seconds behind schedule the blockchain gets, difficulty is cut in half.
    // Doubled if blocks are ahead of schedule.
    uint64_t asert_half_life;   //two days
#else
    kth_bool_t bip141;
    kth_bool_t bip143;
    kth_bool_t bip147;
#endif //KTH_CURRENCY_BCH

#if defined(KTH_WITH_MEMPOOL)
    kth_size_t mempool_max_template_size;
    kth_size_t mempool_size_multiplier;
#endif
} kth_blockchain_settings;

KTH_EXPORT
kth_blockchain_settings kth_config_blockchain_settings_default(kth_network_t net);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_
