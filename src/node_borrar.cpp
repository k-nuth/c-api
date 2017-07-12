///**
// * Copyright (c) 2017 Bitprim developers (see AUTHORS)
// *
// * This file is part of Bitprim.
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU Affero General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU Affero General Public License for more details.
// *
// * You should have received a copy of the GNU Affero General Public License
// * along with this program.  If not, see <http://www.gnu.org/licenses/>.
// */
//
//#include <bitprim/nodecint/node.h>
//
//#include <memory>
//
//#include <bitcoin/node/full_node.hpp>
//
//extern "C" {
//
//struct node {
//    // template <typename... Args>
//    // node(Args&&... args)
//    //     : actual(std::forward<Args>(args)...)
//    // {}
//
////    node(char const* path)
////        : actual(path)
////    {}
//
//    libbitcoin::node::full_node actual;
//};
//
//// node_t node_construct(char const* person, error_t* out_error) {
//node_t node_construct(char const* path) {
//    // node_t result = nullptr;
//
//    // translateExceptions(out_error, [&]{
//    //     result = std::make_unique<node>(person).release();
//    // });
//
//
//    // return result;
//
//    //std::make_unique<node>(path).release();
//
//
//    return node_t();
//
//}
//
//void node_destruct(node_t obj) {
//    delete obj;
//}
//
//} /* extern "C" */
