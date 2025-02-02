// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_VM_PROGRAM_H_
#define KTH_CAPI_VM_PROGRAM_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// class KD_API program {
// public:
//     using value_type = data_stack::value_type;
//     using op_iterator = operation::iterator;
//     using stack_iterator = data_stack::const_iterator;
//     using stack_mutable_iterator = data_stack::iterator;


KTH_EXPORT
void kth_vm_program_destruct(kth_program_t program);

/// Create an instance that does not expect to verify signatures.
/// This is useful for script utilities but not with input validation.
/// This can only run individual operations via run(op, program).
KTH_EXPORT
kth_program_t kth_vm_program_construct_default(void);

/// Create an instance that does not expect to verify signatures.
/// This is useful for script utilities but not with input validation.
/// This can run ops via run(op, program) or the script via run(program).
KTH_EXPORT
kth_program_t kth_vm_program_construct_from_script(kth_script_t script);

/// Create an instance with empty stacks, value unused/max (input run).
// program(chain::script const& script, chain::transaction const& transaction, uint32_t input_index, uint32_t forks);
KTH_EXPORT
kth_program_t kth_vm_program_construct_from_script_transaction(kth_script_t script, kth_transaction_t transaction, uint32_t input_index, uint32_t forks);


/// Create an instance with initialized stack (witness run, v0 by default).
// program(chain::script const& script, chain::transaction const& transaction, uint32_t input_index, uint32_t forks, data_stack&& stack, uint64_t value, script_version version = script_version::zero);
// KTH_EXPORT
// kth_program_t kth_vm_program_construct_from_script_transaction_stack(kth_script_t script, kth_transaction_t transaction, uint32_t input_index, uint32_t forks, kth_data_stack_t stack, uint64_t value, kth_script_version_t version);


/// Create using copied tx, input, forks, value, stack (prevout run).
// program(chain::script const& script, const program& x);
KTH_EXPORT
kth_program_t kth_vm_program_construct_from_script_program(kth_script_t script, kth_program_t program);


/// Create using copied tx, input, forks, value and moved stack (p2sh run).
// program(chain::script const& script, program&& x, bool move);
KTH_EXPORT
kth_program_t kth_vm_program_construct_from_script_program_move(kth_script_t script, kth_program_t program, kth_bool_t move);

KTH_EXPORT
kth_metrics_t kth_vm_program_get_metrics(kth_program_t program);

// KTH_EXPORT
// kth_metrics_t kth_vm_program_get_metrics_const(kth_program_t program);

KTH_EXPORT
kth_bool_t kth_vm_program_is_valid(kth_program_t program);

KTH_EXPORT
uint32_t kth_vm_program_forks(kth_program_t program);


KTH_EXPORT
kth_size_t kth_vm_program_max_script_element_size(kth_program_t program);

KTH_EXPORT
kth_size_t kth_vm_program_max_integer_size_legacy(kth_program_t program);

KTH_EXPORT
kth_bool_t kth_vm_program_is_chip_vm_limits_enabled(kth_program_t program);

KTH_EXPORT
uint32_t kth_vm_program_input_index(kth_program_t program);

KTH_EXPORT
uint64_t kth_vm_program_value(kth_program_t program);

// KTH_EXPORT
// kth_script_version_t kth_vm_program_version(kth_program_t program);

KTH_EXPORT
kth_transaction_const_t kth_vm_program_transaction(kth_program_t program);


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

KTH_EXPORT
kth_size_t kth_vm_program_operation_count(kth_program_t program);

/// Instructions.
KTH_EXPORT
kth_error_code_t kth_vm_program_evaluate(kth_program_t program);

KTH_EXPORT
kth_error_code_t kth_vm_program_evaluate_operation(kth_program_t program, kth_operation_t op);

KTH_EXPORT
kth_bool_t kth_vm_program_increment_operation_count(kth_program_t program, kth_operation_t op);

KTH_EXPORT
kth_bool_t kth_vm_program_increment_operation_count_public_keys(kth_program_t program, int32_t public_keys);

KTH_EXPORT
kth_bool_t kth_vm_program_set_jump_register(kth_program_t program, kth_operation_t op, int32_t offset);


// Primary stack.
//-------------------------------------------------------------------------

/// Primary push.
KTH_EXPORT
void kth_vm_program_push(kth_program_t program, kth_bool_t value);

// KTH_EXPORT
// void kth_vm_program_push_move(kth_program_t program, kth_value_type_t item);

// KTH_EXPORT
// void kth_vm_program_push_copy(kth_program_t program, kth_value_type_t item);

/// Primary pop.

//     data_chunk pop();
KTH_EXPORT
uint8_t const* kth_vm_program_pop(kth_program_t program, kth_size_t* out_size);

//     bool pop(int32_t& out_value);
KTH_EXPORT
kth_bool_t kth_vm_program_pop_int32_t(kth_program_t program, int32_t* out_value);

//     bool pop(int64_t& out_value);
KTH_EXPORT
kth_bool_t kth_vm_program_pop_int64_t(kth_program_t program, int64_t* out_value);

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

/// Primary push/pop optimizations (active).
//     void duplicate(size_t index);
KTH_EXPORT
void kth_vm_program_duplicate(kth_program_t program, kth_size_t index);

//     void swap(size_t index_left, size_t index_right);
KTH_EXPORT
void kth_vm_program_swap(kth_program_t program, kth_size_t index_left, kth_size_t index_right);

//     void erase(stack_iterator const& position);
// KTH_EXPORT
// void kth_vm_program_erase(kth_program_t program, kth_stack_iterator_t position);

//     void erase(stack_iterator const& first, stack_iterator const& last);
// KTH_EXPORT
// void kth_vm_program_erase_range(kth_program_t program, kth_stack_iterator_t first, kth_stack_iterator_t last);

/// Primary push/pop optimizations (passive).

//     bool empty() const;
KTH_EXPORT
kth_bool_t kth_vm_program_empty(kth_program_t program);

//     bool stack_true(bool clean) const;
KTH_EXPORT
kth_bool_t kth_vm_program_stack_true(kth_program_t program, kth_bool_t clean);

//     bool stack_result(bool clean) const;
KTH_EXPORT
kth_bool_t kth_vm_program_stack_result(kth_program_t program, kth_bool_t clean);

//     bool is_stack_overflow() const;
KTH_EXPORT
kth_bool_t kth_vm_program_is_stack_overflow(kth_program_t program);

//     bool if_(operation const& op) const;
KTH_EXPORT
kth_bool_t kth_vm_program_if(kth_program_t program, kth_operation_t op);

//     value_type const& item(size_t index) const;
KTH_EXPORT
uint8_t const* kth_vm_program_item(kth_program_t program, kth_size_t index, kth_size_t* out_size);

//     value_type& item(size_t index);
// KTH_EXPORT
// kth_value_type_t kth_vm_program_item_mutable(kth_program_t program, kth_size_t index);

//     data_chunk& top();
KTH_EXPORT
uint8_t const* kth_vm_program_top(kth_program_t program, kth_size_t* out_size);

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
KTH_EXPORT
kth_operation_list_t kth_vm_program_subscript(kth_program_t program);

//     size_t size() const;
KTH_EXPORT
kth_size_t kth_vm_program_size(kth_program_t program);


// Alternate stack.

//     bool empty_alternate() const;
KTH_EXPORT
kth_bool_t kth_vm_program_empty_alternate(kth_program_t program);

//     void push_alternate(value_type&& value);
// KTH_EXPORT
// void kth_vm_program_push_alternate(kth_program_t program, kth_value_type_t value);

//     value_type pop_alternate();
// KTH_EXPORT
// kth_value_type_t kth_vm_program_pop_alternate(kth_program_t program);

// Conditional stack.
//-------------------------------------------------------------------------

//     void open(bool value);
KTH_EXPORT
void kth_vm_program_open(kth_program_t program, kth_bool_t value);

//     void negate();
KTH_EXPORT
void kth_vm_program_negate(kth_program_t program);

//     void close();
KTH_EXPORT
void kth_vm_program_close(kth_program_t program);

//     bool closed() const;
KTH_EXPORT
kth_bool_t kth_vm_program_closed(kth_program_t program);

//     bool succeeded() const;
KTH_EXPORT
kth_bool_t kth_vm_program_succeeded(kth_program_t program);

//     size_t conditional_stack_size() const;
KTH_EXPORT
kth_size_t kth_vm_program_conditional_stack_size(kth_program_t program);



#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_VM_PROGRAM_H_ */
