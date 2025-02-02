// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/vm/program.h>

#include <kth/capi/helpers.hpp>
// #include <kth/capi/type_conversions.h>

#include <kth/domain/machine/program.hpp>

#include <kth/capi/conversions.hpp>

// KTH_CONV_DEFINE(vm, kth_program_t, kth::domain::machine::program, program)
KTH_CONV_DEFINE_JUST_CONST(vm, kth_program_const_t, kth::domain::machine::program, program)
KTH_CONV_DEFINE_JUST_MUTABLE(vm, kth_program_t, kth::domain::machine::program, program)
// ---------------------------------------------------------------------------
extern "C" {

void kth_vm_program_destruct(kth_program_t program) {
    delete &kth_vm_program_cpp(program);
}

// kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address) {
//     return new kth::domain::wallet::payment_address(std::string(address));
// }

kth_program_t kth_vm_program_construct_default() {
    return new kth::domain::machine::program();
}

kth_program_t kth_vm_program_construct_from_script(kth_script_t script) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    return new kth::domain::machine::program(script_cpp);
}

// program(chain::script const& script, chain::transaction const& transaction, uint32_t input_index, uint32_t forks);
kth_program_t kth_vm_program_construct_from_script_transaction(kth_script_t script, kth_transaction_t transaction, uint32_t input_index, uint32_t forks) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    auto const& transaction_cpp = kth_chain_transaction_const_cpp(transaction);
    return new kth::domain::machine::program(script_cpp, transaction_cpp, input_index, forks);
}

// program(chain::script const& script, chain::transaction const& transaction, uint32_t input_index, uint32_t forks, data_stack&& stack, uint64_t value, script_version version = script_version::zero);
// kth_program_t kth_vm_program_construct_from_script_transaction_stack(kth_script_t script, kth_transaction_t transaction, uint32_t input_index, uint32_t forks, kth_data_stack_t stack, uint64_t value, kth_script_version_t version);

// program(chain::script const& script, const program& x);
kth_program_t kth_vm_program_construct_from_script_program(kth_script_t script, kth_program_t program) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    auto const& program_cpp = kth_vm_program_const_cpp(program);
    return new kth::domain::machine::program(script_cpp, kth_vm_program_const_cpp(program));
}

// // program(chain::script const& script, program&& x, bool move);
// kth_program_t kth_vm_program_construct_from_script_program_move(kth_script_t script, kth_program_t program, kth_bool_t move) {
//     auto const& script_cpp = kth_chain_script_const_cpp(script);
//     auto const& program_cpp = kth_vm_program_const_cpp(program);
//     return new kth::domain::machine::program(script_cpp, std::move(), kth::int_to_bool(move));
// }

kth_metrics_t kth_vm_program_get_metrics(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::ref_to_c(kth_vm_program_cpp(program).get_metrics());
}

// KTH_EXPORT
// kth_metrics_t kth_vm_program_get_metrics_const(kth_program_t program);

kth_bool_t kth_vm_program_is_valid(kth_program_t program) {
    // auto const& program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).is_valid());
}

uint32_t kth_vm_program_forks(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).forks();
}

kth_size_t kth_vm_program_max_script_element_size(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).max_script_element_size();
}

kth_size_t kth_vm_program_max_integer_size_legacy(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).max_integer_size_legacy();
}

kth_bool_t kth_vm_program_is_chip_vm_limits_enabled(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).is_chip_vm_limits_enabled());
}

uint32_t kth_vm_program_input_index(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).input_index();
}

uint64_t kth_vm_program_value(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).value();
}

// TODO:
// kth_script_version_t kth_vm_program_version(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
//     return kth_vm_program_const_cpp(program).version();
// }


kth_transaction_const_t kth_vm_program_transaction(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    // return kth::ref_to_c(kth_vm_program_const_cpp(program).transaction());
    return &kth_vm_program_const_cpp(program).transaction();
}


//     /// Program registers.
//     [[nodiscard]]
//     op_iterator begin() const;

//     [[nodiscard]]
//     op_iterator jump() const;

//     [[nodiscard]]
//     op_iterator end() const;


// KTH_EXPORT
// kth_operation_t kth_vm_program_begin(kth_program_t program);

// KTH_EXPORT
// kth_operation_t kth_vm_program_jump(kth_program_t program);

// KTH_EXPORT
// kth_operation_t kth_vm_program_end(kth_program_t program);

kth_size_t kth_vm_program_operation_count(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).operation_count();
}

kth_error_code_t kth_vm_program_evaluate(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::to_c_err(kth_vm_program_cpp(program).evaluate());
}

kth_error_code_t kth_vm_program_evaluate_operation(kth_program_t program, kth_operation_t op) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    auto op_cpp = kth_chain_operation_const_cpp(op);
    return kth::to_c_err(kth_vm_program_cpp(program).evaluate(op_cpp));
}

kth_bool_t kth_vm_program_increment_operation_count(kth_program_t program, kth_operation_t op) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    auto op_cpp = kth_chain_operation_const_cpp(op);
    return kth::bool_to_int(kth_vm_program_cpp(program).increment_operation_count(op_cpp));
}

kth_bool_t kth_vm_program_increment_operation_count_public_keys(kth_program_t program, int32_t public_keys) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_cpp(program).increment_operation_count(public_keys));
}

kth_bool_t kth_vm_program_set_jump_register(kth_program_t program, kth_operation_t op, int32_t offset) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    auto op_cpp = kth_chain_operation_const_cpp(op);
    return kth::bool_to_int(kth_vm_program_cpp(program).set_jump_register(op_cpp, offset));
}

void kth_vm_program_push(kth_program_t program, kth_bool_t value) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).push(kth::int_to_bool(value));
}

// void kth_vm_program_push_move(kth_program_t program, kth_value_type_t item) {
//     auto program_cpp = kth_vm_program_const_cpp(program);
//     kth_vm_program_const_cpp(program).push_move(item);
// }

// void kth_vm_program_push_copy(kth_program_t program, kth_value_type_t item) {
//     auto program_cpp = kth_vm_program_const_cpp(program);
//     kth_vm_program_const_cpp(program).push_copy(item);
// }


uint8_t const* kth_vm_program_pop(kth_program_t program, kth_size_t* out_size) {
    auto data = kth_vm_program_cpp(program).pop();
    return kth::create_c_array(data, *out_size);
}

//     bool pop(int32_t& out_value);
kth_bool_t kth_vm_program_pop_int32_t(kth_program_t program, int32_t* out_value) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_cpp(program).pop(*out_value));
}

//     bool pop(int64_t& out_value);
kth_bool_t kth_vm_program_pop_int64_t(kth_program_t program, int64_t* out_value) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_cpp(program).pop(*out_value));
}

//     bool pop(number& out_number, size_t maximum_size);
// KTH_EXPORT
// kth_bool_t kth_vm_program_pop_number(kth_program_t program, kth_number_t out_number, kth_size_t maximum_size);

//     bool pop_binary(number& first, number& second);
// KTH_EXPORT
// kth_bool_t kth_vm_program_pop_binary(kth_program_t program, kth_number_t out_first, kth_number_t out_second);

//     bool pop_ternary(number& first, number& second, number& third);
// KTH_EXPORT
// kth_bool_t kth_vm_program_pop_ternary(kth_program_t program, kth_number_t out_first, kth_number_t out_second, kth_number_t out_third);

//     bool pop_position(stack_iterator& out_position);
// KTH_EXPORT
// kth_bool_t kth_vm_program_pop_position(kth_program_t program, kth_stack_iterator_t out_position);

//     bool pop(data_stack& section, size_t count);
// KTH_EXPORT
// kth_bool_t kth_vm_program_pop_data_stack(kth_program_t program, kth_data_stack_t out_section, kth_size_t count);

//     void duplicate(size_t index);
void kth_vm_program_duplicate(kth_program_t program, kth_size_t index) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).duplicate(index);
}

//     void swap(size_t index_left, size_t index_right);
void kth_vm_program_swap(kth_program_t program, kth_size_t index_left, kth_size_t index_right) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).swap(index_left, index_right);
}

//     void erase(stack_iterator const& position);
// KTH_EXPORT
// void kth_vm_program_erase(kth_program_t program, kth_stack_iterator_t position);

//     void erase(stack_iterator const& first, stack_iterator const& last);
// KTH_EXPORT
// void kth_vm_program_erase_range(kth_program_t program, kth_stack_iterator_t first, kth_stack_iterator_t last);

/// Primary push/pop optimizations (passive).

//     bool empty() const;
kth_bool_t kth_vm_program_empty(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).empty());
}

//     bool stack_true(bool clean) const;
kth_bool_t kth_vm_program_stack_true(kth_program_t program, kth_bool_t clean) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).stack_true(kth::int_to_bool(clean)));
}

//     bool stack_result(bool clean) const;
kth_bool_t kth_vm_program_stack_result(kth_program_t program, kth_bool_t clean) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).stack_result(kth::int_to_bool(clean)));
}

//     bool is_stack_overflow() const;
kth_bool_t kth_vm_program_is_stack_overflow(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).is_stack_overflow());
}

//     bool if_(operation const& op) const;
kth_bool_t kth_vm_program_if(kth_program_t program, kth_operation_t op) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    auto op_cpp = kth_chain_operation_const_cpp(op);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).if_(op_cpp));
}

//     value_type const& item(size_t index) const;
// kth_value_type_t kth_vm_program_item(kth_program_t program, kth_size_t index) {
//     auto program_cpp = kth_vm_program_const_cpp(program);
//     return kth_vm_program_const_cpp(program).item(index);
// }
uint8_t const* kth_vm_program_item(kth_program_t program, kth_size_t index, kth_size_t* out_size) {
    auto data = kth_vm_program_const_cpp(program).item(index);
    return kth::create_c_array(data, *out_size);
}

//     value_type& item(size_t index);
// KTH_EXPORT
// kth_value_type_t kth_vm_program_item_mutable(kth_program_t program, kth_size_t index);

//     data_chunk& top();
uint8_t const* kth_vm_program_top(kth_program_t program, kth_size_t* out_size) {
    auto data = kth_vm_program_const_cpp(program).top();
    return kth::create_c_array(data, *out_size);
}

//     bool top(number& out_number, size_t maximum_size) const;
// KTH_EXPORT
// kth_bool_t kth_vm_program_top_number(kth_program_t program, kth_number_t out_number, kth_size_t maximum_size);

//     stack_iterator position(size_t index) const;
// KTH_EXPORT
// kth_stack_iterator_t kth_vm_program_position(kth_program_t program, kth_size_t index);

//     stack_mutable_iterator position(size_t index);
// KTH_EXPORT
// kth_stack_mutable_iterator_t kth_vm_program_position_mutable(kth_program_t program, kth_size_t index);

//     size_t index(stack_iterator const& position) const;
// KTH_EXPORT
// kth_size_t kth_vm_program_index(kth_program_t program, kth_stack_iterator_t position);

//     operation::list subscript() const;
kth_operation_list_t kth_vm_program_subscript(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    auto ops = kth_vm_program_const_cpp(program).subscript();
    return kth::move_or_copy_and_leak(std::move(ops));
}

//     size_t size() const;
kth_size_t kth_vm_program_size(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).size();
}

//     bool empty_alternate() const;
kth_bool_t kth_vm_program_empty_alternate(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).empty_alternate());
}

//     void push_alternate(value_type&& value);
// KTH_EXPORT
// void kth_vm_program_push_alternate(kth_program_t program, kth_value_type_t value);

//     value_type pop_alternate();
// KTH_EXPORT
// kth_value_type_t kth_vm_program_pop_alternate(kth_program_t program);

// Conditional stack.
//-------------------------------------------------------------------------

//     void open(bool value);
void kth_vm_program_open(kth_program_t program, kth_bool_t value) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).open(kth::int_to_bool(value));
}

//     void negate();
void kth_vm_program_negate(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).negate();
}

//     void close();
void kth_vm_program_close(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    kth_vm_program_cpp(program).close();
}

//     bool closed() const;
kth_bool_t kth_vm_program_closed(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).closed());
}

//     bool succeeded() const;
kth_bool_t kth_vm_program_succeeded(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth::bool_to_int(kth_vm_program_const_cpp(program).succeeded());
}

//     size_t conditional_stack_size() const;
kth_size_t kth_vm_program_conditional_stack_size(kth_program_t program) {
    // auto program_cpp = kth_vm_program_const_cpp(program);
    return kth_vm_program_const_cpp(program).conditional_stack_size();
}




// kth_payment_address_t kth_wallet_payment_address_construct_from_short_hash(kth_shorthash_t const* hash, uint8_t version) {
//     auto const hash_cpp = kth::short_hash_to_cpp(hash->hash);
//     return new kth::domain::wallet::payment_address(hash_cpp, version);
// }

// kth_payment_address_t kth_wallet_payment_address_construct_from_point(kth_ec_public_t point, uint8_t version) {
//     auto const point_cpp = kth_wallet_ec_public_const_cpp(point);
//     return new kth::domain::wallet::payment_address(point_cpp, version);
// }

// kth_payment_address_t kth_wallet_payment_address_construct_from_script(kth_script_t script, uint8_t version) {
//     auto const& script_cpp = kth_chain_script_const_cpp(script);
//     return new kth::domain::wallet::payment_address(script_cpp, version);
// }

// void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address) {
//     delete &kth_wallet_payment_address_cpp(payment_address);
// }

// #if defined(KTH_CURRENCY_BCH)
// void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix) {
//     std::string prefix_cpp(prefix);
//     kth::set_cashaddr_prefix(prefix_cpp);
// }
// #endif //KTH_CURRENCY_BCH

// //User is responsible for releasing return value memory
// char* kth_wallet_payment_address_encoded_legacy(kth_payment_address_t payment_address) {
//     std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded_legacy();
//     return kth::create_c_str(str);
// }

// #if defined(KTH_CURRENCY_BCH)
// //User is responsible for releasing return value memory
// char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address, kth_bool_t token_aware) {
//     std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded_cashaddr(token_aware);
//     return kth::create_c_str(str);
// }
// #endif //KTH_CURRENCY_BCH

// kth_shorthash_t kth_wallet_payment_address_hash20(kth_payment_address_t payment_address) {
//     auto hash_cpp = kth_wallet_payment_address_const_cpp(payment_address).hash20();
//     return kth::to_shorthash_t(hash_cpp);
// }

// kth_hash_t kth_wallet_payment_address_hash32(kth_payment_address_t payment_address) {
//     auto hash_cpp = kth_wallet_payment_address_const_cpp(payment_address).hash32();
//     return kth::to_hash_t(hash_cpp);
// }

// uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address) {
//     return kth_wallet_payment_address_const_cpp(payment_address).version();
// }

// kth_bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address) {
//     return kth::bool_to_int(static_cast<bool>(kth_wallet_payment_address_const_cpp(payment_address)));
// }

// // payment_address_list_t kth_wallet_payment_address_extract(chain::script_t const* script, uint8_t p2kh_version, uint8_t p2sh_version) {
// //     kth::chain::script kth_script = kth_chain_script_const_cpp(script);
// //     auto list = kth::domain::wallet::payment_address::extract(kth_script, p2kh_version, p2sh_version);
// //     return kth_wallet_payment_address_list_to_capi(new std::vector<kth::domain::wallet::payment_address>(list));
// // }

// // payment_address_list_t kth_wallet_payment_address_extract_input(chain::script_t const* script, uint8_t p2kh_version, uint8_t p2sh_version) {
// //     kth::chain::script kth_script = kth_chain_script_const_cpp(script);
// //     auto list = kth::domain::wallet::payment_address::extract_input(kth_script, p2kh_version, p2sh_version);
// //     return kth_wallet_payment_address_list_to_capi(new std::vector<kth::domain::wallet::payment_address>(list));
// // }

// // payment_address_list_t kth_wallet_payment_address_extract_output(chain::script_t const* script, uint8_t p2kh_version, uint8_t p2sh_version) {
// //     kth::chain::script kth_script = kth_chain_script_const_cpp(script);
// //     auto list = kth::domain::wallet::payment_address::extract_output(kth_script, p2kh_version, p2sh_version);
// //     return kth_wallet_payment_address_list_to_capi(new std::vector<kth::domain::wallet::payment_address>(list));
// // }

} // extern "C"
