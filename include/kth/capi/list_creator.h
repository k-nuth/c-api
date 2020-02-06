// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_LIST_CREATOR_H_
#define KTH_NODECINT_LIST_CREATOR_H_

#include <stdint.h>

#include <kth/capi/error.h>
#include <kth/capi/visibility.h>

#define KTH_LIST_DECLARE_CONVERTERS(api, list_t, cpp_elem_t, list_name)  \
std::vector<cpp_elem_t> const& api##_##list_name##_const_cpp(list_t l);      \
std::vector<cpp_elem_t>& api##_##list_name##_cpp(list_t l);                  \

#define KTH_LIST_DEFINE_CONVERTERS(api, list_t, cpp_elem_t, list_name)  \
std::vector<cpp_elem_t> const& api##_##list_name##_const_cpp(list_t l) {    \
    return *static_cast<std::vector<cpp_elem_t> const*>(l);                 \
}                                                                           \
std::vector<cpp_elem_t>& api##_##list_name##_cpp(list_t l) {                \
    return *static_cast<std::vector<cpp_elem_t>*>(l);                       \
}

#define KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(api, list_t, cpp_elem_t, list_name)  \
list_t api##_##list_name##_construct_from_cpp(std::vector<cpp_elem_t>& l);

#define KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(api, list_t, cpp_elem_t, list_name)  \
list_t api##_##list_name##_construct_from_cpp(std::vector<cpp_elem_t>& l) {         \
    return &l;                                                                      \
}

#define KTH_LIST_DECLARE(api, list_t, elem_t, list_name)                \
    KTH_EXPORT                                                          \
    list_t api##_##list_name##_construct_default(void);                     \
    KTH_EXPORT                                                          \
    void api##_##list_name##_push_back(list_t, elem_t);                     \
    KTH_EXPORT                                                          \
    void api##_##list_name##_destruct(list_t);                              \
    KTH_EXPORT                                                          \
    uint64_t /*size_t*/ api##_##list_name##_count(list_t);                  \
    KTH_EXPORT                                                          \
    elem_t api##_##list_name##_nth(list_t, uint64_t /*size_t*/);

#define KTH_LIST_DEFINE(api, list_t, elem_t, list_name, cpp_elem_t, value_converter)    \
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

#define KTH_LIST_DEFINE_VALUE(api, list_t, elem_t, list_name, cpp_elem_t, value_converter)  \
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


#endif /* KTH_NODECINT_LIST_CREATOR_H_ */
