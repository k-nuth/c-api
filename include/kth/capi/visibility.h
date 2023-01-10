// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_VISIBILITY_H_
#define KTH_CAPI_VISIBILITY_H_


#if defined(KTH_LIB_STATIC)
    #define KTH_EXPORT
#else
    #if defined(_WIN32) || defined(__CYGWIN__)
      #ifdef KTH_EXPORTS
        #ifdef __GNUC__
          #define KTH_EXPORT __attribute__ ((dllexport))
        #else
          #define KTH_EXPORT __declspec(dllexport)
        #endif
      #else
        #ifdef __GNUC__
          #define KTH_EXPORT __attribute__ ((dllimport))
        #else
          #define KTH_EXPORT __declspec(dllimport)
        #endif
      #endif
    #else
      #if __GNUC__ >= 4
        #define KTH_EXPORT __attribute__ ((visibility ("default")))
      #else
        #define KTH_EXPORT
      #endif
    #endif
#endif




#endif /* KTH_CAPI_VISIBILITY_H_ */
