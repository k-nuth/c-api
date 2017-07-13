/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#ifndef BITPRIM_NODECINT_VISIBILITY_H_
#define BITPRIM_NODECINT_VISIBILITY_H_

#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef bitprim_EXPORTS
    #ifdef __GNUC__
      #define BITPRIM_EXPORT __attribute__ ((dllexport))
    #else
      #define BITPRIM_EXPORT __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define BITPRIM_EXPORT __attribute__ ((dllimport))
    #else
      #define BITPRIM_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #if __GNUC__ >= 4
    #define BITPRIM_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define BITPRIM_EXPORT
  #endif
#endif

#endif /* BITPRIM_NODECINT_VISIBILITY_H_ */
