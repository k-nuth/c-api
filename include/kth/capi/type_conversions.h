// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_TYPE_CONVERSIONS_H_
#define KTH_CAPI_TYPE_CONVERSIONS_H_

#include <stdint.h>

#include <kth/capi/error.h>
#include <kth/capi/visibility.h>

#define KTH_CONV_DECLARE(api, type_c, type_cpp, obj_name)       \
type_cpp const& kth_##api##_##obj_name##_const_cpp(type_c);     \
type_cpp& kth_##api##_##obj_name##_cpp(type_c);

#define KTH_CONV_DEFINE(api, type_c, type_cpp, obj_name)        \
type_cpp const& kth_##api##_##obj_name##_const_cpp(type_c o) {  \
    return *static_cast<type_cpp const*>(o);                    \
}                                                               \
type_cpp& kth_##api##_##obj_name##_cpp(type_c o) {              \
    return *static_cast<type_cpp*>(o);                          \
}

#define KTH_CONV_DECLARE_JUST_CONST(api, type_c, type_cpp, obj_name)  \
type_cpp const& kth_##api##_##obj_name##_const_cpp(type_c);

#define KTH_CONV_DEFINE_JUST_CONST(api, type_c, type_cpp, obj_name)   \
type_cpp const& kth_##api##_##obj_name##_const_cpp(type_c o) {        \
    return *static_cast<type_cpp const*>(o);                          \
}

#endif /* KTH_CAPI_TYPE_CONVERSIONS_H_ */
