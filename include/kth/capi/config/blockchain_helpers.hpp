// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_BLOCKCHAIN_HELPERS_HPP_
#define KTH_CAPI_CONFIG_BLOCKCHAIN_HELPERS_HPP_

#include <vector>

#include <kth/blockchain/settings.hpp>
#include <kth/capi/config/checkpoint_helpers.hpp>
#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>

namespace kth::capi::helpers {


namespace {

template <typename Target, typename Source>
Target blockchain_settings_to_common(Source const& x) {
    Target res;
    
    res.cores = x.cores;
    res.priority = x.priority;
    res.byte_fee_satoshis = x.byte_fee_satoshis;
    res.sigop_fee_satoshis = x.sigop_fee_satoshis;
    res.minimum_output_satoshis = x.minimum_output_satoshis;
    res.notify_limit_hours = x.notify_limit_hours;
    res.reorganization_limit = x.reorganization_limit;
    res.allow_collisions = x.allow_collisions;
    res.easy_blocks = x.easy_blocks;
    res.retarget = x.retarget;
    res.bip16 = x.bip16;
    res.bip30 = x.bip30;
    res.bip34 = x.bip34;
    res.bip66 = x.bip66;
    res.bip65 = x.bip65;
    res.bip90 = x.bip90;
    res.bip68 = x.bip68;
    res.bip112 = x.bip112;
    res.bip113 = x.bip113;

#if defined(KTH_CURRENCY_BCH)
    res.bch_uahf = x.bch_uahf;
    res.bch_daa_cw144 = x.bch_daa_cw144;
    res.bch_monolith = x.bch_monolith;
    res.bch_magnetic_anomaly = x.bch_magnetic_anomaly;
    res.bch_great_wall = x.bch_great_wall;
    res.bch_graviton = x.bch_graviton;
    res.bch_phonon = x.bch_phonon;
    res.bch_axion = x.bch_axion;
    res.axion_activation_time = x.axion_activation_time;
    res.asert_half_life = x.asert_half_life;
#else
    res.bip141 = x.bip141;
    res.bip143 = x.bip143;
    res.bip147 = x.bip147;
#endif //KTH_CURRENCY_BCH

#if defined(KTH_WITH_MEMPOOL)
    res.mempool_max_template_size = x.mempool_max_template_size;
    res.mempool_size_multiplier = x.mempool_size_multiplier;
#endif

    return res;
}

}

inline
kth::blockchain::settings blockchain_settings_to_cpp(kth_blockchain_settings const& x) {
    auto res = blockchain_settings_to_common<kth::blockchain::settings>(x);
    res.checkpoints = kth::capi::helpers::checkpoint_list_to_cpp(x.checkpoints, x.checkpoint_count);
    return res;
}

inline
kth_blockchain_settings blockchain_settings_to_c(kth::blockchain::settings const& x) {
    auto res = blockchain_settings_to_common<kth_blockchain_settings>(x);
    res.checkpoints = kth::capi::helpers::checkpoint_list_to_c(x.checkpoints, res.checkpoint_count);
    return res;
}

} // namespace kth::capi::helpers

#endif // KTH_CAPI_CONFIG_BLOCKCHAIN_HELPERS_HPP_
