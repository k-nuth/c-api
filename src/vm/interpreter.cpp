// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/vm/interpreter.h>

#include <kth/capi/helpers.hpp>
// #include <kth/capi/type_conversions.h>

#include <kth/domain/machine/program.hpp>

#include <kth/capi/conversions.hpp>


// KTH_CONV_DEFINE(vm, kth_program_t, kth::domain::machine::program, program)

// ---------------------------------------------------------------------------
extern "C" {



/// Run program script.

    // static
    // code run(program& program);

    // /// Run individual operations (idependent of the script).
    // /// For best performance use script runner for a sequence of operations.
    // static
    // code run(operation const& op, program& program);


kth_error_code_t kth_vm_interpreter_run(kth_program_t program) {
    auto const result = kth::domain::machine::interpreter::run(kth_vm_program_cpp(program));
    return kth::to_c_err(result);
}

kth_error_code_t kth_vm_interpreter_run_operation(kth_operation_t operation, kth_program_t program) {
    auto const result = kth::domain::machine::interpreter::run(
        kth_chain_operation_cpp(operation),
        kth_vm_program_cpp(program)
    );
    return kth::to_c_err(result);
}



    // static
    // std::pair<code, size_t> debug_start(program const& program);

    // static
    // bool debug_steps_available(program const& program, size_t step);

    // static
    // std::tuple<code, size_t, program> debug_step(program program, size_t step);

    // static
    // code debug_end(program const& program);


kth_error_code_t kth_vm_interpreter_debug_start(kth_program_const_t program, kth_size_t* out_step) {
    auto const result = kth::domain::machine::interpreter::debug_start(kth_vm_program_const_cpp(program));
    *out_step = result.second;
    return kth::to_c_err(result.first);
}

kth_bool_t kth_vm_interpreter_debug_steps_available(kth_program_const_t program, kth_size_t step) {
    return kth::domain::machine::interpreter::debug_steps_available(kth_vm_program_const_cpp(program), step);
}

kth_error_code_t kth_vm_interpreter_debug_step(kth_program_const_t program, kth_size_t step, kth_size_t* out_step, kth_program_t* out_program) {
    auto const [err, new_step, new_program_cpp] = kth::domain::machine::interpreter::debug_step(kth_vm_program_const_cpp(program), step);
    *out_step = new_step;
    *out_program = kth::move_or_copy_and_leak(std::move(new_program_cpp));
    // printf("kth_vm_interpreter_debug_step() - out_step:     %p\n", out_step);
    // printf("kth_vm_interpreter_debug_step() - out_program:  %p\n", out_program);
    // printf("kth_vm_interpreter_debug_step() - *out_program: %p\n", *out_program);
    return kth::to_c_err(err);
}

kth_error_code_t kth_vm_interpreter_debug_end(kth_program_const_t program) {
    return kth::to_c_err(kth::domain::machine::interpreter::debug_end(kth_vm_program_const_cpp(program)));
}

} // extern "C"
