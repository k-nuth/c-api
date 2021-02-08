# Copyright (c) 2016-2020 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 3.8)

# kth-c-api
#==============================================================================
project(kth-c-api
        VERSION 0
        LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++17 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================

# Implement --use-conan
#------------------------------------------------------------------------------
option(USE_CONAN "Use Conan Build Tool." OFF)
option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

if (NO_CONAN_AT_ALL)
  set(USE_CONAN OFF)
endif()

# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" ON)
option(ENABLE_SHARED_CAPI "" ON)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)

# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)

# Implement --with-console and declare WITH_CONSOLE.
#------------------------------------------------------------------------------
option(WITH_CONSOLE "Compile console application." ON)
option(WITH_CONSOLE_CAPI "Compile console application." ON)


# # Implement --binlog.
# #------------------------------------------------------------------------------
# option(BINLOG "Uses BinLog logging library." OFF)
# if (BINLOG)
#   add_definitions(-DKTH_USE_BINLOG)
# endif()

set(LOG_LIBRARY "boost" CACHE STRING "Setting for the logging library (boost|spdlog|binlog).")

if (${LOG_LIBRARY} STREQUAL "boost")
  add_definitions(-DKTH_LOG_LIBRARY_BOOST)
elseif (${LOG_LIBRARY} STREQUAL "spdlog")
  add_definitions(-DKTH_LOG_LIBRARY_SPDLOG)
elseif (${LOG_LIBRARY} STREQUAL "binlog")
  add_definitions(-DKTH_LOG_LIBRARY_BINLOG)
else()
  message(FATAL_ERROR "Invalid Logging Library: ${LOG_LIBRARY}")
endif()

message(STATUS "Knuth: Logging Library: ${LOG_LIBRARY}")


# Implement --use_libmdbx.
#------------------------------------------------------------------------------
option(USE_LIBMDBX "Uses libmdbx DB library." OFF)
if (USE_LIBMDBX)
  add_definitions(-DKTH_USE_LIBMDBX)
endif()



set(KTH_PROJECT_VERSION "-" CACHE STRING "Specify the Knuth Project Version.")
# message(${KTH_PROJECT_VERSION})

set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Microarchitecture (x86_64|...).")
message( STATUS "Knuth: Compiling for ${MICROARCHITECTURE}")
add_definitions(-DKTH_MICROARCHITECTURE=${MICROARCHITECTURE})
# add_definitions(-DKTH_MICROARCHITECTURE_STR="${MICROARCHITECTURE}")

set(MARCH_ID "" CACHE STRING "Specify the Microarchitecture ID (x86_64|...).")
message( STATUS "Knuth: Compiling for Microarchitecture ID ${MARCH_ID}")
add_definitions(-DKTH_MARCH_ID=${MARCH_ID})

message( STATUS "Knuth: CONAN_CXX_FLAGS ${CONAN_CXX_FLAGS}")
message( STATUS "Knuth: CONAN_C_FLAGS ${CONAN_C_FLAGS}")


set(CURRENCY "BCH" CACHE STRING "Specify the Cryptocurrency (BCH|BTC|LTC).")

if (${CURRENCY} STREQUAL "BCH")
  add_definitions(-DKTH_CURRENCY_BCH)
elseif (${CURRENCY} STREQUAL "BTC")
  add_definitions(-DKTH_CURRENCY_BTC)
elseif (${CURRENCY} STREQUAL "LTC")
  add_definitions(-DKTH_CURRENCY_LTC)
else()
  message(FATAL_ERROR "Invalid Cryptocurrency: ${CURRENCY}")
endif()

message(STATUS "Knuth: Cryptocurrency: ${CURRENCY}")

# Implement --with-keoken and declare WITH_KEOKEN.
#------------------------------------------------------------------------------
option(WITH_KEOKEN "Keoken enabled." OFF)
if (WITH_KEOKEN)
  message(STATUS "Knuth: Keoken enabled")
  add_definitions(-DKTH_WITH_KEOKEN)
endif()

# Implement --with-mempool and declare WITH_MEMPOOL.
#------------------------------------------------------------------------------
option(WITH_MEMPOOL "Mempool enabled." OFF)
if (WITH_MEMPOOL)
  message(STATUS "Knuth: Mempool enabled")
  add_definitions(-DKTH_WITH_MEMPOOL)
endif()

# Implement and declare DB_TRANSACTION_UNCONFIRMED.
#------------------------------------------------------------------------------
option(DB_TRANSACTION_UNCONFIRMED "DB Transactions Unconfirmed enabled." OFF)
if (DB_TRANSACTION_UNCONFIRMED)
  message(STATUS "Knuth: DB Transactions Unconfirmed enabled")
  add_definitions(-DKTH_DB_TRANSACTION_UNCONFIRMED)
endif()

# Implement and declare DB_SPENDS.
#------------------------------------------------------------------------------
option(DB_SPENDS "DB Spends enabled." OFF)
if (DB_SPENDS)
  message(STATUS "Knuth: DB Spends enabled")
  add_definitions(-DKTH_DB_SPENDS)
endif()

# Implement and declare DB_HISTORY.
#------------------------------------------------------------------------------
option(DB_HISTORY "DB History enabled." OFF)
if (DB_HISTORY)
  message(STATUS "Knuth: DB History enabled")
  add_definitions(-DKTH_DB_HISTORY)
endif()

# Implement and declare DB_STEALTH.
#------------------------------------------------------------------------------
option(DB_STEALTH "DB Stealth enabled." OFF)
if (DB_STEALTH)
  message(STATUS "Knuth: DB Stealth enabled")
  add_definitions(-DKTH_DB_STEALTH)
endif()

# Implement and declare DB_UNSPENT_LEGACY.
#------------------------------------------------------------------------------
option(DB_UNSPENT_LEGACY "DB Unspent Legacy enabled." OFF)
if (DB_UNSPENT_LEGACY)
  message(STATUS "Knuth: DB Unspent Legacy enabled")
  add_definitions(-DKTH_DB_UNSPENT_LEGACY)
endif()

# Implement and declare DB_LEGACY.
#------------------------------------------------------------------------------
option(DB_LEGACY "DB Legacy enabled." OFF)
if (DB_LEGACY)
  message(STATUS "Knuth: DB Legacy enabled")
  add_definitions(-DKTH_DB_LEGACY)
endif()

# Implement and declare DB_NEW.
#------------------------------------------------------------------------------
option(DB_NEW "DB New enabled." OFF)
if (DB_NEW)
  message(STATUS "Knuth: DB New enabled")
  add_definitions(-DKTH_DB_NEW)
endif()

# Implement and declare DB_NEW_BLOCKS.
#------------------------------------------------------------------------------
option(DB_NEW_BLOCKS "DB Blocks New enabled." OFF)
if (DB_NEW_BLOCKS)
  message(STATUS "Knuth: DB Blocks New enabled")
  add_definitions(-DKTH_DB_NEW_BLOCKS)
endif()

# Implement and declare DB_NEW_FULL.
#------------------------------------------------------------------------------
option(DB_NEW_FULL "DB New Full enabled." OFF)
if (DB_NEW_FULL)
  message(STATUS "Knuth: DB New Full enabled")
  add_definitions(-DKTH_DB_NEW_FULL)
endif()

# Implement --db_readonly_mode and declare KTH_DB_READONLY.
#------------------------------------------------------------------------------
option(DB_READONLY_MODE "Readonly DB mode enabled." OFF)
if (DB_READONLY_MODE)
  message(STATUS "Knuth: Readonly DB mode enabled")
  add_definitions(-DKTH_DB_READONLY)
endif()

if (ENABLE_SHARED_CAPI)
  set(ENABLE_SHARED ON)
endif()

# set(WITH_CONSOLE_CAPI ON)

# Conan infrastructure
#==============================================================================
if(EXISTS ${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
else()
    message( STATUS "knuthbuildinfo doent exists")
endif()

#TODO(fernando): enable sanitizers
# -fsanitize=memory
# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
# set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")

# Check dependencies.
#==============================================================================
#------------------------------------------------------------------------------
if (NO_CONAN_AT_ALL)
  # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
  #------------------------------------------------------------------------------
  if (NOT ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  if (MSVC)
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS atomic chrono date_time filesystem iostreams locale log log_setup program_options regex system thread unit_test_framework
    )
  else()
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS chrono date_time filesystem iostreams locale log program_options regex system thread unit_test_framework
    )
  endif()
endif()

if (NOT USE_CONAN)
  ## Require kth-consensus of at least version 2.0.0 and output ${kth_consensus_CPPFLAGS/LIBS/PKG}.
  ##------------------------------------------------------------------------------
  #if (WITH_CONSENSUS)
  #  if (NOT TARGET kth-consensus)
  #    find_package(kth-consensus 2.0.0 REQUIRED)
  #  endif()
  #endif()

  # Require kth-node of at least version 0 and output ${kth_node_CPPFLAGS/LIBS/PKG}.
  #------------------------------------------------------------------------------
  if (NOT TARGET kth-node)
    find_package(kth-node 0 REQUIRED)
  endif()
endif()


# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)

include(KnuthTools)


# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
# set(CMAKE_C_FLAGS_RELEASE " -s ${CMAKE_C_FLAGS_RELEASE}")
# set(CMAKE_CXX_FLAGS_RELEASE " -s ${CMAKE_CXX_FLAGS_RELEASE}")

# message( STATUS "CMAKE_C_FLAGS_RELEASE:   ${CMAKE_C_FLAGS_RELEASE}")
# message( STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Target Windows Vista. Enabled in msvc only.
#------------------------------------------------------------------------------
if (MSVC) # OR MINGW)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

# src/kth-c-api.la => ${libdir}
#------------------------------------------------------------------------------
#set(MODE STATIC)
if (ENABLE_SHARED)
    set(MODE SHARED)
else()
    set(MODE STATIC)
endif()

set(_kth_sources
        src/hash.cpp
        src/hash_list.cpp
        # src/parser.cpp
        src/binary.cpp
        src/node.cpp
        src/platform.cpp
        src/string_list.cpp

        src/chain/block.cpp
        src/chain/block_indexes.cpp
        src/chain/block_list.cpp
        
        src/chain/chain_async.cpp
        src/chain/chain_other.cpp
        src/chain/chain_sync.cpp

        src/chain/compact_block.cpp
        src/chain/get_blocks.cpp
        src/chain/get_headers.cpp
        src/chain/header.cpp
        src/chain/history_compact.cpp
        src/chain/history_compact_list.cpp
        src/chain/stealth_compact.cpp
        src/chain/stealth_compact_list.cpp
        src/chain/input.cpp
        src/chain/input_list.cpp
        src/chain/mempool_transaction_list.cpp
        src/chain/merkle_block.cpp
        src/chain/output.cpp
        src/chain/output_list.cpp
        src/chain/output_point.cpp
        src/chain/point.cpp
        src/chain/point_list.cpp
        src/chain/script.cpp
        src/chain/transaction.cpp
        src/chain/mempool_transaction.cpp
        src/chain/transaction_list.cpp

        src/config/authority.cpp
        src/config/blockchain_settings.cpp
        src/config/checkpoint.cpp
        src/config/database_settings.cpp
        src/config/endpoint.cpp
        src/config/network_settings.cpp
        src/config/node_settings.cpp
        src/config/settings.cpp

        src/libconfig/libconfig.cpp

        src/node/settings.cpp

        src/p2p/p2p.cpp

        src/wallet/payment_address.cpp
        src/wallet/payment_address_list.cpp
        # src/wallet/ec_public.cpp
        src/wallet/raw_output.cpp
        src/wallet/raw_output_list.cpp
        src/wallet/transaction_functions.cpp
        src/wallet/wallet.cpp
)

# if (ENABLE_SHARED)
#   set(_kth_sources
#     ${_kth_sources}
#     src/user_agent.cpp
#   )
# endif()

if (WITH_KEOKEN)
  set(_kth_sources
    ${_kth_sources}
    src/keoken/get_all_asset_addresses_data.cpp
    src/keoken/get_all_asset_addresses_list.cpp
    src/keoken/get_assets_by_address_data.cpp
    src/keoken/get_assets_by_address_list.cpp
    src/keoken/get_assets_data.cpp
    src/keoken/get_assets_list.cpp
    src/keoken/manager.cpp
    src/keoken/memory_state.cpp
    src/keoken/wallet/create_transactions.cpp
  )
endif()


add_library(kth-c-api ${MODE}
        ${_kth_sources}
)

# if (NOT ENABLE_SHARED)
#   add_library(kth-c-api-version ${MODE}
#     src/user_agent.cpp
#   )

#   if (ENABLE_POSITION_INDEPENDENT_CODE) 
#     set_property(TARGET kth-c-api-version PROPERTY POSITION_INDEPENDENT_CODE ON)
#   endif(ENABLE_POSITION_INDEPENDENT_CODE)

#   target_compile_definitions(kth-c-api-version PUBLIC -DKTH_PROJECT_VERSION="${KTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????

#   target_include_directories(kth-c-api-version PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>)
# endif()


if (ENABLE_POSITION_INDEPENDENT_CODE) 
  set_property(TARGET kth-c-api PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)

#set_target_properties(kth-c-api PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_definitions(kth-c-api PUBLIC -DKTH_PROJECT_VERSION="${KTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????
target_compile_definitions(kth-c-api PUBLIC -DKTH_EXPORTS)

target_include_directories(kth-c-api PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# target_compile_definitions(kth-c-api PUBLIC -DBCN_STATIC)
if (NOT ENABLE_SHARED)
  target_compile_definitions(kth-c-api PUBLIC -DKTH_LIB_STATIC)
  # target_compile_definitions(kth-c-api PUBLIC -DBCN_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)
# else()
  # target_compile_definitions(kth-c-api PUBLIC -DBC_DLL)
endif()

#Note: Knuth modules are Static, C-API Shared
target_compile_definitions(kth-c-api PUBLIC -DBCN_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)



if (NOT MSVC)
  target_compile_definitions(kth-c-api PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()

if (NOT USE_CONAN)
  set(DEP_LIBS ${DEP_LIBS} "kth-node")
#   if (NOT ENABLE_SHARED)
#     set(DEP_LIBS ${DEP_LIBS} "kth-c-api-version")
#   endif()

  target_link_libraries(kth-c-api PUBLIC ${DEP_LIBS})
endif()

# lib/libkth-c-api-version


if (NOT NO_CONAN_AT_ALL)
#   if (NOT ENABLE_SHARED)
#     set(CONAN_LIBS ${CONAN_LIBS} "kth-c-api-version")
#   endif()
  target_link_libraries(kth-c-api PUBLIC ${CONAN_LIBS})
endif()

if (USE_CONAN)
  if (MINGW)
    target_link_libraries(kth-c-api PUBLIC ws2_32 wsock32) #TODO(fernando): manage with Conan
  endif()
endif()



# if (MSVC)
#   target_link_libraries(kth-c-api PUBLIC ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})
# endif()
#if (MINGW)
#  target_link_libraries(kth-c-api PUBLIC kth-node wsock32)
#else()
#    target_link_libraries(kth-c-api PUBLIC kth-node)
#endif()


_group_sources(kth-c-api "${CMAKE_CURRENT_LIST_DIR}")



# Console
#==============================================================================

if (WITH_CONSOLE_CAPI)
  #add_executable(test-console-twos
  #        console/main.c)

    if (WITH_KEOKEN)
      set(_test_console_sources
          console/state_test.cpp
      )
    else()
      set(_test_console_sources
        # console/test_wallet.cpp
        # console/test_header_hash.cpp
        # console/main.cpp
        # console/main.c
        # console/print_headers.cpp
        # console/error_test.cpp
        # console/test_deadlock.cpp
        # console/config_test.cpp
        # console/platform_test.cpp
        console/test_libconfig.cpp
      )
    endif()

  add_executable(test_console ${_test_console_sources})

  target_link_libraries(test_console kth-c-api)

  set_target_properties(
          test_console PROPERTIES
          FOLDER "node"
          OUTPUT_NAME test_console)
endif()





#==============================================================================

# Tests
#==============================================================================

# if (WITH_TESTS)
#   enable_testing()
# endif()

  # local: test/kth_node_cint_test
  #------------------------------------------------------------------------------
 if (WITH_TESTS)
   add_executable(queries
           test/queries.cpp)
   target_link_libraries(queries PUBLIC kth-c-api)
   #_group_sources(queries "${CMAKE_CURRENT_LIST_DIR}/test")

   #_add_tests(kth_node_cint_test
   #        configuration_tests
   #        node_tests
   #       header_queue_tests
   #        performance_tests
   #        reservation_tests
   #        reservations_tests
   #        settings_tests)
 endif()





# Install
#==============================================================================
#install(TARGETS kth-c-api
#        EXPORT kth-c-api
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#)

# if (NOT ENABLE_SHARED)
#   install(TARGETS kth-c-api-version
#           EXPORT kth-c-api-version
#           LIBRARY DESTINATION "lib"
#           ARCHIVE DESTINATION "lib"
#           RUNTIME DESTINATION "lib"
#           COMPONENT library
#           )
# endif()

install(TARGETS kth-c-api
        EXPORT kth-c-api
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "lib"
        COMPONENT library
        )


set(_kth_headers
        kth/capi/binary.h
        kth/capi/conversions.hpp
        kth/capi/helpers.hpp
        kth/capi/hash_list.h
        kth/capi/node.h
        kth/capi/platform.h
        kth/capi/primitives.h
        kth/capi/version.h
        kth/capi/visibility.h
        kth/capi/string_list.h

        kth/capi/chain/block.h
        kth/capi/chain/block_indexes.h
        kth/capi/chain/block_list.h
        kth/capi/chain/chain.h
        kth/capi/chain/compact_block.h
        kth/capi/chain/get_blocks.h
        kth/capi/chain/get_headers.h
        kth/capi/chain/header.h
        kth/capi/chain/history_compact.h
        kth/capi/chain/history_compact_list.h
        kth/capi/chain/stealth_compact.h
        kth/capi/chain/stealth_compact_list.h
        kth/capi/chain/input.h
        kth/capi/chain/input_list.h
        kth/capi/chain/mempool_transaction_list.h
        kth/capi/chain/merkle_block.h
        kth/capi/chain/output.h
        kth/capi/chain/output_list.h
        kth/capi/chain/output_point.h
        kth/capi/chain/point.h
        kth/capi/chain/point_list.h
        kth/capi/chain/script.h
        kth/capi/chain/mempool_transaction.h
        kth/capi/chain/transaction.h
        kth/capi/chain/transaction_list.h

        kth/capi/node/settings.h

        kth/capi/p2p/p2p.h

        kth/capi/wallet/payment_address.h
        kth/capi/wallet/payment_address_list.h
        kth/capi/wallet/wallet.h
)

if (WITH_KEOKEN)
  set(_kth_headers
    ${_kth_headers}
    kth/capi/keoken/manager.h
  )
endif()

foreach (_header ${_kth_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

# if (NOT ENABLE_SHARED)
#   export(EXPORT kth-c-api-version
#           FILE "${CMAKE_CURRENT_BINARY_DIR}/kth-c-api-versionTargets.cmake")
#   export(PACKAGE kth-c-api-version)
# endif()

export(EXPORT kth-c-api
        FILE "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiTargets.cmake")
export(PACKAGE kth-c-api)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()


# if (NOT ENABLE_SHARED)
#   install(EXPORT kth-c-api-version
#           FILE kth-c-api-versionTargets.cmake
#           DESTINATION ${_config_package_location})
# endif()

install(EXPORT kth-c-api
        FILE kth-c-apiTargets.cmake
        DESTINATION ${_config_package_location})

configure_file(kth-c-apiConfig.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfig.cmake"
        @ONLY)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfigVersion.cmake"
        DESTINATION ${_config_package_location})

        