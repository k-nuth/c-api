// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_COIN_SELECTION_H_
#define KTH_CAPI_CHAIN_COIN_SELECTION_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_coin_selection_algorithm_smallest_first,     // Prioriza UTXOs más pequeños
    kth_coin_selection_algorithm_largest_first,      // Prioriza UTXOs más grandes
    // kth_coin_selection_algorithm_knapsack,           // Algoritmo de la mochila para optimizar
    // kth_coin_selection_algorithm_fifo,               // Primero en entrar, primero en salir
    // kth_coin_selection_algorithm_branch_and_bound,   // Branch and Bound para optimización global
    kth_coin_selection_algorithm_manual,             // Mantiene el orden original de los UTXOs
    // kth_coin_selection_algorithm_privacy,            // Prioriza privacidad (mismo tamaño de UTXOs)
    kth_coin_selection_algorithm_send_all            // Usa todos los UTXOs disponibles
} kth_coin_selection_algorithm_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_COIN_SELECTION_H_