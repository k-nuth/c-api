# Copyright (c) 2016-2023 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 3.15)

project(c-api VERSION 0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_SHARED "" ON)
option(ENABLE_SHARED_CAPI "" ON)
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)
option(WITH_TESTS "Compile with unit tests." ON)
option(WITH_CONSOLE "Compile console application." ON)
option(WITH_CONSOLE_CAPI "Compile console application." ON)
option(USE_LIBMDBX "Uses libmdbx DB library." OFF)
option(WITH_MEMPOOL "Mempool enabled." OFF)
option(DB_READONLY_MODE "Readonly DB mode enabled." OFF)

option(GLOBAL_BUILD "" OFF)

if (WITH_MEMPOOL)
  message(STATUS "Knuth: Mempool enabled")
  add_definitions(-DKTH_WITH_MEMPOOL)
endif()

if (DB_READONLY_MODE)
  message(STATUS "Knuth: Readonly DB mode enabled")
  add_definitions(-DKTH_DB_READONLY)
endif()

if (ENABLE_SHARED_CAPI)
  set(ENABLE_SHARED ON)
endif()

if (USE_LIBMDBX)
  add_definitions(-DKTH_USE_LIBMDBX)
endif()

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


if (NOT GLOBAL_BUILD)
  find_package(node REQUIRED)
endif()


include(CheckCXXCompilerFlag)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)
include(KnuthTools)

if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)
_add_link_flag(-fstack-protector _has_stack_protector_flag)
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

if (MSVC)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

if (ENABLE_SHARED)
    set(MODE SHARED)
else()
    set(MODE STATIC)
endif()

set(kth_sources
        src/hash.cpp
        src/hash_list.cpp
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
        src/chain/double_spend_proof.cpp
        src/chain/double_spend_proof_spender.cpp
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

        # src/chain/token_data.cpp

        src/config/authority.cpp
        src/config/blockchain_settings.cpp
        src/config/checkpoint.cpp
        src/config/database_settings.cpp
        src/config/endpoint.cpp

        src/config/node_settings.cpp
        src/config/settings.cpp

        src/libconfig/libconfig.cpp

        src/node/settings.cpp



        src/wallet/ec_private.cpp
        src/wallet/ec_public.cpp
        src/wallet/elliptic_curve.cpp
        src/wallet/hd_public.cpp
        src/wallet/hd_private.cpp

        src/wallet/payment_address.cpp
        src/wallet/payment_address_list.cpp
        src/wallet/raw_output.cpp
        src/wallet/raw_output_list.cpp
        src/wallet/transaction_functions.cpp
        src/wallet/wallet.cpp
)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(kth_sources
    ${kth_sources}
    src/config/network_settings.cpp
    src/p2p/p2p.cpp
  )
endif()

set(kth_headers
  include/kth/capi/list_creator.h
  include/kth/capi/chain/block_list.h
  include/kth/capi/chain/mempool_transaction_list.h
  include/kth/capi/chain/compact_block.h
  include/kth/capi/chain/token_data.h
  include/kth/capi/chain/input.h
  include/kth/capi/chain/block_indexes.h
  include/kth/capi/chain/chain.h
  include/kth/capi/chain/chain_sync.h
  include/kth/capi/chain/chain_other.h
  include/kth/capi/chain/stealth_compact.h
  include/kth/capi/chain/history_compact_list.h
  include/kth/capi/chain/stealth_compact_list.h
  include/kth/capi/chain/output_point.h
  include/kth/capi/chain/point_list.h
  include/kth/capi/chain/header.h
  include/kth/capi/chain/chain_async.h
  include/kth/capi/chain/history_compact.h
  include/kth/capi/chain/transaction.h
  include/kth/capi/chain/output.h
  include/kth/capi/chain/output_list.h
  include/kth/capi/chain/get_blocks.h
  include/kth/capi/chain/double_spend_proof_spender.h
  include/kth/capi/chain/point.h
  include/kth/capi/chain/merkle_block.h
  include/kth/capi/chain/block.h
  include/kth/capi/chain/mempool_transaction.h
  include/kth/capi/chain/script.h
  include/kth/capi/chain/get_headers.h
  include/kth/capi/chain/double_spend_proof.h
  include/kth/capi/chain/transaction_list.h
  include/kth/capi/chain/input_list.h
  include/kth/capi/node/settings.h
  include/kth/capi/platform.h
  include/kth/capi/p2p/p2p.h
  include/kth/capi/node.h
  include/kth/capi/helpers.hpp
  include/kth/capi/libconfig/libconfig.h
  include/kth/capi/wallet/raw_output_list.h
  include/kth/capi/wallet/transaction_functions.h
  include/kth/capi/wallet/ec_public.h
  include/kth/capi/wallet/payment_address.h
  include/kth/capi/wallet/payment_address_list.h
  include/kth/capi/wallet/wallet.h
  include/kth/capi/wallet/raw_output.h
  include/kth/capi/primitives.h
  include/kth/capi/string_list.h
  include/kth/capi/hash_list.h
  include/kth/capi/type_conversions.h
  include/kth/capi/error.h
  include/kth/capi/doc_temp.md
  include/kth/capi/hash.h
  include/kth/capi/version.h
  include/kth/capi/visibility.h
  include/kth/capi/binary.h
  include/kth/capi/capi.h
  include/kth/capi/conversions.hpp
  include/kth/capi/config/blockchain_settings.h
  include/kth/capi/config/endpoint.h
  include/kth/capi/config/database_helpers.hpp

  include/kth/capi/config/authority_helpers.hpp
  include/kth/capi/config/settings.h
  include/kth/capi/config/authority.h
  include/kth/capi/config/checkpoint.h
  include/kth/capi/config/helpers.hpp
  include/kth/capi/config/settings_helper.hpp
  include/kth/capi/config/endpoint_helpers.hpp
  include/kth/capi/config/checkpoint_helpers.hpp
  include/kth/capi/config/database_settings.h
  include/kth/capi/config/blockchain_helpers.hpp
  include/kth/capi/config/node_settings.h
  include/kth/capi/config/node_helpers.hpp
  include/kth/capi.h
)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(kth_headers
    ${kth_headers}
    include/kth/capi/config/network_settings.h
    include/kth/capi/config/network_helpers.hpp

  )
endif()


add_library(${PROJECT_NAME} ${MODE} ${kth_sources} ${kth_headers})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)


if (ENABLE_POSITION_INDEPENDENT_CODE)
  set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DKTH_EXPORTS)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

if (NOT ENABLE_SHARED)
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DKTH_LIB_STATIC)
endif()

#Note: Knuth modules are Static, C-API Shared
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBCN_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)

if (NOT MSVC)
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC node::node)

if (MINGW)
  target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32 wsock32)
endif()

_group_sources(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}")


if (WITH_CONSOLE_CAPI)
    set(_test_console_sources
      # console/test_wallet.cpp
      # console/test_wallet.c
      # console/test_header_hash.cpp
      # console/main.cpp
      # console/main.c
      # console/print_headers.cpp
      # console/error_test.cpp
      # console/test_deadlock.cpp
      # console/config_test.cpp
      # console/platform_test.cpp
      # console/test_libconfig.cpp
      # console/main_744727.cpp
      # console/main_payment_addr_cash_aware.cpp
      # console/node_info.c
      console/get_block.c
    )

  add_executable(test_console ${_test_console_sources})

  target_link_libraries(test_console ${PROJECT_NAME})

  set_target_properties(
          test_console PROPERTIES
          FOLDER "node"
          OUTPUT_NAME test_console)
endif()

if (WITH_TESTS)
    enable_testing()
    find_package(Catch2 3 REQUIRED)

    add_executable(queries
      test/queries.cpp)
    target_link_libraries(queries PUBLIC ${PROJECT_NAME})
endif()




# Install
# ------------------------------------------------------------------------------

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Generate and install a CMake package configuration file
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)




# # Install
# #==============================================================================

# install(TARGETS kth-c-api
#         EXPORT kth-c-api
#         LIBRARY DESTINATION "lib"
#         ARCHIVE DESTINATION "lib"
#         RUNTIME DESTINATION "lib"
#         COMPONENT library
#         )




# foreach (_header ${kth_headers})
#   get_filename_component(_directory "${_header}" DIRECTORY)
#   install(FILES "include/${_header}" DESTINATION "include/${_directory}")
# endforeach()

# # Export
# #==============================================================================
# include(CMakePackageConfigHelpers)

# export(EXPORT kth-c-api
#         FILE "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiTargets.cmake")
# export(PACKAGE kth-c-api)

# if (UNIX)
#   set(_config_package_location "lib/cmake")
# elseif (WIN32)
#   set(_config_package_location "cmake")
# endif()

# install(EXPORT kth-c-api
#         FILE kth-c-apiTargets.cmake
#         DESTINATION ${_config_package_location})

# configure_file(kth-c-apiConfig.cmake.in
#         "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfig.cmake"
#         @ONLY)

# write_basic_package_version_file(
#         "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfigVersion.cmake"
#         VERSION ${PROJECT_VERSION}
#         COMPATIBILITY AnyNewerVersion)

# install(
#         FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfig.cmake"
#         "${CMAKE_CURRENT_BINARY_DIR}/kth-c-apiConfigVersion.cmake"
#         DESTINATION ${_config_package_location})

