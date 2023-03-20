// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>
#include <kth/capi.h>

int ds_proof_handler(kth_node_t node, kth_chain_t chain, void* ctx, kth_error_code_t error, kth_double_spend_proof_t dsp) {
    printf("Caution: a Double-Spend Proof notification has been received.");
	return 1;
}

int main() {
    kth_settings* settings;
    char* error_message;
    kth_bool_t ok = kth_config_settings_get_from_file("mainnet.cfg", &settings, &error_message);

    if ( ! ok) {
        printf("error: %s", error_message);
        return -1;
    }

    kth_node_t node = kth_node_construct(settings, 1);
    kth_node_init_and_run_wait(node);
    kth_chain_t chain = kth_node_get_chain(node);

    kth_chain_subscribe_ds_proof(node, chain, NULL, ds_proof_handler);



    return 0;
}

