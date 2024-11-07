// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_HD_LINEAGE_H_
#define KTH_CAPI_WALLET_HD_LINEAGE_H_

typedef struct kth_hd_lineage {
    uint64_t prefixes;
    uint8_t depth;
    uint32_t parent_fingerprint;
    uint32_t child_number;
} kth_hd_lineage_t;

#endif //KTH_CAPI_WALLET_HD_LINEAGE_H_
