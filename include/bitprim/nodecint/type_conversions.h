/**
 * Copyright (c) 2016-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_TYPE_CONVERSIONS_H_
#define BITPRIM_NODECINT_TYPE_CONVERSIONS_H_

#include <stdint.h>

#include <bitprim/nodecint/error.h>
#include <bitprim/nodecint/visibility.h>

#define BITPRIM_CONV_DECLARE(api, type_c, type_cpp, obj_name)   \
type_cpp const& api##_##obj_name##_const_cpp(type_c);           \
type_cpp& api##_##obj_name##_cpp(type_c);

#define BITPRIM_CONV_DEFINE(api, type_c, type_cpp, obj_name)    \
type_cpp const& api##_##obj_name##_const_cpp(type_c o) {        \
    return *static_cast<type_cpp const*>(o);                    \
}                                                               \
type_cpp& api##_##obj_name##_cpp(type_c o) {                    \
    return *static_cast<type_cpp*>(o);                          \
}

#endif /* BITPRIM_NODECINT_TYPE_CONVERSIONS_H_ */
