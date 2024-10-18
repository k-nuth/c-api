// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/transaction.h>

#include <kth/capi/chain/input_list.h>
#include <kth/capi/chain/output_list.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/wallet/payment_address.h>


KTH_CONV_DEFINE(chain, kth_transaction_t, kth::domain::chain::transaction, transaction)

// ---------------------------------------------------------------------------
extern "C" {

kth_transaction_t kth_chain_transaction_factory_from_data(uint8_t* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    kth::byte_reader reader(data_cpp);
    auto obj = kth::domain::chain::transaction::from_data(reader, true);
    if ( ! obj) {
        return nullptr;
    }
    return kth::move_or_copy_and_leak(std::move(obj.value()));
}

kth_transaction_t kth_chain_transaction_construct_default() {
    return new kth::domain::chain::transaction();
}

kth_transaction_t kth_chain_transaction_construct(uint32_t version, uint32_t locktime, kth_input_list_t inputs, kth_output_list_t outputs) {
    return new kth::domain::chain::transaction(version, locktime,
                                                kth_chain_input_list_const_cpp(inputs),
                                                kth_chain_output_list_const_cpp(outputs));
}

void kth_chain_transaction_destruct(kth_transaction_t transaction) {
    delete &kth_chain_transaction_cpp(transaction);
}

kth_bool_t kth_chain_transaction_is_valid(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_valid());
}

uint32_t kth_chain_transaction_version(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).version();
}

void kth_chain_transaction_set_version(kth_transaction_t transaction, uint32_t version) {
    return static_cast<kth::domain::chain::transaction*>(transaction)->set_version(version);
}

kth_hash_t kth_chain_transaction_hash(kth_transaction_t transaction) {
    auto const& hash_cpp = kth_chain_transaction_const_cpp(transaction).hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_transaction_hash_out(kth_transaction_t transaction, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_transaction_const_cpp(transaction).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

// kth_hash_t kth_chain_transaction_hash_sighash_type(kth_transaction_t transaction, uint32_t sighash_type) {
//     auto const& hash_cpp = kth_chain_transaction_const_cpp(transaction).hash(sighash_type != 0u);
//     return kth::to_hash_t(hash_cpp);
// }

// void kth_chain_transaction_hash_sighash_type_out(kth_transaction_t transaction, uint32_t sighash_type, kth_hash_t* out_hash) {
//     auto const& hash_cpp = kth_chain_transaction_const_cpp(transaction).hash(sighash_type != 0u);
//     kth::copy_c_hash(hash_cpp, out_hash);
// }

uint32_t kth_chain_transaction_locktime(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).locktime();
}

kth_size_t kth_chain_transaction_serialized_size(kth_transaction_t transaction, kth_bool_t wire /*= true*/) {
    return kth_chain_transaction_const_cpp(transaction).serialized_size(wire);
}

uint64_t kth_chain_transaction_fees(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).fees();
}

kth_size_t kth_chain_transaction_signature_operations(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).signature_operations();
}

kth_size_t kth_chain_transaction_signature_operations_bip16_active(kth_transaction_t transaction, kth_bool_t bip16_active) {
#if defined(KTH_CURRENCY_BCH)
    kth_bool_t bip141_active = 0;
#else
    kth_bool_t bip141_active = 1;
#endif
    return kth_chain_transaction_const_cpp(transaction).signature_operations(kth::int_to_bool(bip16_active), kth::int_to_bool(bip141_active));
}

uint64_t kth_chain_transaction_total_input_value(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).total_input_value();
}

uint64_t kth_chain_transaction_total_output_value(kth_transaction_t transaction) {
    return kth_chain_transaction_const_cpp(transaction).total_output_value();
}

kth_bool_t kth_chain_transaction_is_coinbase(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_coinbase());
}

kth_bool_t kth_chain_transaction_is_null_non_coinbase(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_null_non_coinbase());
}

kth_bool_t kth_chain_transaction_is_oversized_coinbase(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_oversized_coinbase());
}

kth_bool_t kth_chain_transaction_is_mature(kth_transaction_t transaction, kth_size_t target_height) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_mature(target_height));
}

kth_bool_t kth_chain_transaction_is_overspent(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_overspent());
}

kth_bool_t kth_chain_transaction_is_double_spend(kth_transaction_t transaction, kth_bool_t include_unconfirmed) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_double_spend(kth::int_to_bool(include_unconfirmed)));
}

kth_bool_t kth_chain_transaction_is_missing_previous_outputs(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_missing_previous_outputs());
}

kth_bool_t kth_chain_transaction_is_final(kth_transaction_t transaction, kth_size_t block_height, uint32_t kth_block_time) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_final(block_height, kth_block_time));
}

kth_bool_t kth_chain_transaction_is_locktime_conflict(kth_transaction_t transaction) {
    return static_cast<int>(kth_chain_transaction_const_cpp(transaction).is_locktime_conflict());
}

kth_output_list_t kth_chain_transaction_outputs(kth_transaction_t transaction) {
    auto& tx = kth_chain_transaction_cpp(transaction);
    return kth_chain_output_list_construct_from_cpp(tx.outputs()); // TODO(fernando): transaction::outputs() is deprecated... check how to do it better...
}

kth_input_list_t kth_chain_transaction_inputs(kth_transaction_t transaction) {
    auto& tx = kth_chain_transaction_cpp(transaction);
    return kth_chain_input_list_construct_from_cpp(tx.inputs()); // TODO(fernando): transaction::inputs() is deprecated... check how to do it better...
}

uint8_t const* kth_chain_transaction_to_data(kth_transaction_t transaction, kth_bool_t wire, kth_size_t* out_size) {
    auto tx_data = kth_chain_transaction_const_cpp(transaction).to_data(kth::int_to_bool(wire));
    return kth::create_c_array(tx_data, *out_size);
}

// code verify(transaction const& tx, uint32_t input_index, uint32_t forks, script const& input_script, script const& prevout_script, uint64_t /*value*/);
kth_error_code_t kth_chain_transaction_verify(kth_transaction_t transaction, uint32_t input_index, uint32_t forks, kth_script_t input_script, kth_script_t prevout_script, uint64_t value) {
    auto const& tx_cpp = kth_chain_transaction_const_cpp(transaction);
    auto const& input_script_cpp = kth_chain_script_const_cpp(input_script);
    auto const& prevout_script_cpp = kth_chain_script_const_cpp(prevout_script);
    return kth::to_c_err(kth::domain::chain::script::verify(tx_cpp, input_index, forks, input_script_cpp, prevout_script_cpp, value));
}

// code verify(transaction const& tx, uint32_t input, uint32_t forks);
kth_error_code_t kth_chain_transaction_verify_transaction(kth_transaction_t transaction, uint32_t input, uint32_t forks) {
    auto const& tx_cpp = kth_chain_transaction_const_cpp(transaction);
    return kth::to_c_err(kth::domain::chain::script::verify(tx_cpp, input, forks));
}

// kth_error_code_t kth_vm_interpreter_debug_step(kth_program_const_t program, kth_size_t step, kth_size_t* out_step, kth_program_t* out_program) {
//     auto const [err, new_step, new_program_cpp] = kth::domain::machine::interpreter::debug_step(kth_vm_program_const_cpp(program), step);
//     *out_step = new_step;
//     *out_program = kth::move_or_copy_and_leak(std::move(new_program_cpp));
//     // printf("kth_vm_interpreter_debug_step() - out_step:     %p\n", out_step);
//     // printf("kth_vm_interpreter_debug_step() - out_program:  %p\n", out_program);
//     // printf("kth_vm_interpreter_debug_step() - *out_program: %p\n", *out_program);
//     return kth::to_c_err(err);
// }


kth_error_code_t kth_chain_transaction_create_template_with_change_ratios(
    kth_utxo_list_t available_utxos,
    uint64_t amount_to_send,
    kth_payment_address_t destination_address,
    kth_payment_address_list_t change_addresses,
    kth_double_list_t change_ratios,
    kth_coin_selection_algorithm_t selection_algo,
    kth_transaction_t* out_transaction,
    kth_u32_list_t* out_selected_utxo_indices,
    kth_payment_address_list_t* out_addresses,
    kth_u64_list_t* out_amounts
) {
    auto const& available_utxos_cpp = kth_chain_utxo_list_const_cpp(available_utxos);
    auto const& destination_address_cpp = kth_wallet_payment_address_const_cpp(destination_address);
    auto const& change_addresses_cpp = kth_wallet_payment_address_list_const_cpp(change_addresses);
    auto const& change_ratios_cpp = kth_core_double_list_const_cpp(change_ratios);

    auto res = kth::domain::chain::transaction::create_template(
        available_utxos_cpp,
        amount_to_send,
        destination_address_cpp,
        change_addresses_cpp,
        change_ratios_cpp,
        kth::coin_selection_algorithm_to_cpp(selection_algo));

    if ( ! res) {
        return kth::to_c_err(res.error());
    }

    *out_transaction = kth::move_or_copy_and_leak(std::move(std::get<0>(res.value())));
    *out_selected_utxo_indices = kth::move_or_copy_and_leak(std::move(std::get<1>(res.value())));
    *out_addresses = kth::move_or_copy_and_leak(std::move(std::get<2>(res.value())));
    *out_amounts = kth::move_or_copy_and_leak(std::move(std::get<3>(res.value())));

    return kth_ec_success;
}

kth_error_code_t kth_chain_transaction_create_template(
    kth_utxo_list_t available_utxos,
    uint64_t amount_to_send,
    kth_payment_address_t destination_address,
    kth_payment_address_list_t change_addresses,
    kth_coin_selection_algorithm_t selection_algo,
    kth_transaction_t* out_transaction,
    kth_u32_list_t* out_selected_utxo_indices,
    kth_payment_address_list_t* out_addresses,
    kth_u64_list_t* out_amounts
) {
    auto const& available_utxos_cpp = kth_chain_utxo_list_const_cpp(available_utxos);
    auto const& destination_address_cpp = kth_wallet_payment_address_const_cpp(destination_address);
    auto const& change_addresses_cpp = kth_wallet_payment_address_list_const_cpp(change_addresses);

    auto res = kth::domain::chain::transaction::create_template(
        available_utxos_cpp,
        amount_to_send,
        destination_address_cpp,
        change_addresses_cpp,
        kth::coin_selection_algorithm_to_cpp(selection_algo)
    );

    if ( ! res) {
        return kth::to_c_err(res.error());
    }

    *out_transaction = kth::move_or_copy_and_leak(std::move(std::get<0>(res.value())));
    *out_selected_utxo_indices = kth::move_or_copy_and_leak(std::move(std::get<1>(res.value())));
    *out_addresses = kth::move_or_copy_and_leak(std::move(std::get<2>(res.value())));
    *out_amounts = kth::move_or_copy_and_leak(std::move(std::get<3>(res.value())));

    return kth_ec_success;
}

} // extern "C"
