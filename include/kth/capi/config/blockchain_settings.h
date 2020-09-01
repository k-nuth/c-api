// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_
#define KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>

typedef struct {
    kth_hash_t hash;
    size_t height;
} kth_checkpoint;

// BCB_API
// settings() = default;
// settings(infrastructure::config::settings context);

typedef struct {
    uint32_t cores;
    kth_bool_t priority;
    float byte_fee_satoshis;
    float sigop_fee_satoshis;
    uint64_t minimum_output_satoshis;
    uint32_t notify_limit_hours;
    uint32_t reorganization_limit;
    
    size_t checkpoint_count;
    kth_checkpoint* checkpoints;

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
    kth_bool_t bch_monolith;
    kth_bool_t bch_magnetic_anomaly;
    kth_bool_t bch_great_wall;
    kth_bool_t bch_graviton;
    kth_bool_t bch_phonon;      // 2020-May
    kth_bool_t bch_axion;       // 2020-Nov
        
    //2020-Nov-15 hard fork, defaults to 1605441600: Nov 15, 2020 12:00:00 UTC protocol upgrade
    uint64_t axion_activation_time;

    // The half life for the ASERTi3-2d DAA. For every (asert_half_life) seconds behind schedule the blockchain gets, difficulty is cut in half. 
    // Doubled if blocks are ahead of schedule.
    uint64_t asert_half_life;   //two days
#else
    kth_bool_t bip141;
    kth_bool_t bip143;
    kth_bool_t bip147;
#endif //KTH_CURRENCY_BCH

#if defined(KTH_WITH_MEMPOOL)
    size_t mempool_max_template_size;
    size_t mempool_size_multiplier;
#endif

} kth_blockchain_settings;

#endif // KTH_CAPI_CONFIG_BLOCKCHAIN_SETTINGS_H_
