// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_VM_INTERPRETER_H_
#define KTH_CAPI_VM_INTERPRETER_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Run program script.

    // static
    // code run(program& program);

    // /// Run individual operations (idependent of the script).
    // /// For best performance use script runner for a sequence of operations.
    // static
    // code run(operation const& op, program& program);


KTH_EXPORT
kth_error_code_t kth_vm_interpreter_run(kth_program_t program);

KTH_EXPORT
kth_error_code_t kth_vm_interpreter_run_operation(kth_operation_t operation, kth_program_t program);


// Debug step by step
// ----------------------------------------------------------------------------
    // static
    // std::pair<code, size_t> debug_start(program const& program);

    // static
    // bool debug_steps_available(program const& program, size_t step);

    // static
    // std::tuple<code, size_t, program> debug_step(program program, size_t step);

    // static
    // code debug_end(program const& program);

KTH_EXPORT
kth_error_code_t kth_vm_interpreter_debug_start(kth_program_const_t program, kth_size_t* out_step);

KTH_EXPORT
kth_bool_t kth_vm_interpreter_debug_steps_available(kth_program_const_t program, kth_size_t step);

KTH_EXPORT
kth_error_code_t kth_vm_interpreter_debug_step(kth_program_const_t program, kth_size_t step, kth_size_t* out_step, kth_program_t* out_program);

KTH_EXPORT
kth_error_code_t kth_vm_interpreter_debug_end(kth_program_const_t program);


#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_VM_PROGRAM_H_ */
