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

#ifndef BITPRIM_NODECINT_LIST_CREATOR_H_
#define BITPRIM_NODECINT_LIST_CREATOR_H_

#include <stdint.h>

#include <bitprim/nodecint/error.h>
#include <bitprim/nodecint/visibility.h>

#define BITPRIM_LIST_DECLARE_CONVERTERS(api, list_t, cpp_elem_t, list_name)  \
std::vector<cpp_elem_t> const& api##_##list_name##_const_cpp(list_t l);      \
std::vector<cpp_elem_t>& api##_##list_name##_cpp(list_t l);                  \

#define BITPRIM_LIST_DEFINE_CONVERTERS(api, list_t, cpp_elem_t, list_name)  \
std::vector<cpp_elem_t> const& api##_##list_name##_const_cpp(list_t l) {    \
    return *static_cast<std::vector<cpp_elem_t> const*>(l);                 \
}                                                                           \
std::vector<cpp_elem_t>& api##_##list_name##_cpp(list_t l) {                \
    return *static_cast<std::vector<cpp_elem_t>*>(l);                       \
}

#define BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(api, list_t, cpp_elem_t, list_name)  \
list_t api##_##list_name##_construct_from_cpp(std::vector<cpp_elem_t>& l);

#define BITPRIM_LIST_DEFINE_CONSTRUCT_FROM_CPP(api, list_t, cpp_elem_t, list_name)  \
list_t api##_##list_name##_construct_from_cpp(std::vector<cpp_elem_t>& l) {         \
    return &l;                                                                      \
}

#define BITPRIM_LIST_DECLARE(api, list_t, elem_t, list_name)                \
    BITPRIM_EXPORT                                                          \
    list_t api##_##list_name##_construct_default(void);                     \
    BITPRIM_EXPORT                                                          \
    void api##_##list_name##_push_back(list_t, elem_t);                     \
    BITPRIM_EXPORT                                                          \
    void api##_##list_name##_destruct(list_t);                              \
    BITPRIM_EXPORT                                                          \
    uint64_t /*size_t*/ api##_##list_name##_count(list_t);                  \
    BITPRIM_EXPORT                                                          \
    elem_t api##_##list_name##_nth(list_t, uint64_t /*size_t*/);

#define BITPRIM_LIST_DEFINE(api, list_t, elem_t, list_name, cpp_elem_t, value_converter)    \
list_t api##_##list_name##_construct_default() {                                            \
    return new std::vector<cpp_elem_t>();                                                   \
}                                                                                           \
void api##_##list_name##_push_back(list_t l, elem_t e) {                                    \
    api##_##list_name##_cpp(l).push_back(value_converter(e));                               \
}                                                                                           \
void api##_##list_name##_destruct(list_t l) {                                               \
    delete &api##_##list_name##_cpp(l);                                                     \
}                                                                                           \
uint64_t /*size_t*/ api##_##list_name##_count(list_t l) {                                   \
    return api##_##list_name##_const_cpp(l).size();                                         \
}                                                                                           \
elem_t api##_##list_name##_nth(list_t l, uint64_t /*size_t*/ n) {                           \
    auto &x = api##_##list_name##_cpp(l)[n];                                                \
    return &x;                                                                              \
}

#define BITPRIM_LIST_DEFINE_VALUE(api, list_t, elem_t, list_name, cpp_elem_t, value_converter)  \
list_t api##_##list_name##_construct_default() {                                                \
    return new std::vector<cpp_elem_t>();                                                       \
}                                                                                               \
void api##_##list_name##_push_back(list_t l, elem_t e) {                                        \
    api##_##list_name##_cpp(l).push_back(value_converter(e));                                   \
}                                                                                               \
void api##_##list_name##_destruct(list_t l) {                                                   \
    delete &api##_##list_name##_cpp(l);                                                         \
}                                                                                               \
uint64_t /*size_t*/ api##_##list_name##_count(list_t l) {                                       \
    return api##_##list_name##_const_cpp(l).size();                                             \
}                                                                                               \
elem_t api##_##list_name##_nth(list_t l, uint64_t /*size_t*/ n) {                               \
    return api##_##list_name##_cpp(l)[n];                                                       \
}


#endif /* BITPRIM_NODECINT_LIST_CREATOR_H_ */
