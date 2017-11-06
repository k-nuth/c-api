cmake_minimum_required(VERSION 3.4)

# bitprim-node-cint
#==============================================================================
project(bitprim-node-cint
        VERSION 3.0.0
        LANGUAGES CXX C)

if(USE_CPP11_ABI)
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
else()
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++14 standard.
#------------------------------------------------------------------------------
# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 11)
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
option(ENABLE_SHARED_NODE_CINT "" ON)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)

# Implement --with-remote-blockchain and declare WITH_REMOTE_BLOCKCHAIN.
#------------------------------------------------------------------------------
option(WITH_REMOTE_BLOCKCHAIN "Compile with remote bitprim-blockchain (aka. bitprim-blockchain-requester)." OFF)

# Implement --with-remote-database and declare WITH_REMOTE_DATABASE.
#------------------------------------------------------------------------------
option(WITH_REMOTE_DATABASE "Compile with remote bitprim-database (aka. bitprim-database-requester)." OFF)

# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)

# Implement --with-console and declare WITH_CONSOLE.
#------------------------------------------------------------------------------
option(WITH_CONSOLE "Compile console application." ON)
option(WITH_CONSOLE_NODE_CINT "Compile console application." ON)

# Implement --with-litecoin.
#------------------------------------------------------------------------------
option(WITH_LITECOIN "Compile with Litecoin support." OFF)



if (ENABLE_SHARED_NODE_CINT)
  set(ENABLE_SHARED ON)
endif()

# set(WITH_CONSOLE_NODE_CINT ON)

if (WITH_LITECOIN)
  add_definitions(-DLITECOIN)
endif()

# Conan infrastructure.
#==============================================================================
# Only if enabled
#------------------------------------------------------------------------------
if (NOT NO_CONAN_AT_ALL)
  if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
      include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
      conan_basic_setup()
  else()
      message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
  endif()
endif()


#------------------------------------------------------------------------------
# Check dependencies.
#==============================================================================
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
  ## Require bitprim-consensus of at least version 2.0.0 and output ${bitprim_consensus_CPPFLAGS/LIBS/PKG}.
  ##------------------------------------------------------------------------------
  #if (WITH_CONSENSUS)
  #  if (NOT TARGET bitprim-consensus)
  #    find_package(bitprim-consensus 2.0.0 REQUIRED)
  #  endif()
  #endif()

  # Require bitprim-node of at least version 3.0.0 and output ${bitprim_node_CPPFLAGS/LIBS/PKG}.
  #------------------------------------------------------------------------------
  if (NOT TARGET bitprim-node)
    find_package(bitprim-node 0.3.0 REQUIRED)
  endif()
endif()


# if (UNIX)
#   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake")
# elseif (WIN32)
#   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "cmake")
# endif()

# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)


# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(BitprimTools)


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
if (MSVC)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

# src/bitprim-node-cint.la => ${libdir}
#------------------------------------------------------------------------------
#set(MODE STATIC)
if (ENABLE_SHARED)
    set(MODE SHARED)
else()
    set(MODE STATIC)
endif()

set(_bitprim_sources
        src/executor.cpp
        src/executor_c.cpp

        src/parser.cpp
        src/binary.cpp
        src/chain/block.cpp
        src/chain/block_indexes.cpp
        src/chain/block_list.cpp
        src/chain/chain.cpp
        src/chain/compact_block.cpp
        src/chain/get_blocks.cpp
        src/chain/get_headers.cpp
        src/chain/hash_list.cpp
        src/chain/header.cpp
        src/chain/history_compact.cpp
        src/chain/history_compact_list.cpp
        src/chain/stealth_compact.cpp
        src/chain/stealth_compact_list.cpp
        src/chain/input.cpp
        src/chain/input_list.cpp
        src/chain/merkle_block.cpp
        src/chain/output.cpp
        src/chain/output_list.cpp
        src/chain/output_point.cpp
        src/chain/payment_address.cpp
        src/chain/point.cpp
        src/chain/point_list.cpp
        src/chain/script.cpp
        src/chain/transaction.cpp
        src/chain/transaction_list.cpp

        src/p2p/p2p.cpp

        src/wallet/wallet.cpp
        src/wallet/word_list.cpp
)


add_library(bitprim-node-cint ${MODE}
        ${_bitprim_sources}
        )




if (ENABLE_POSITION_INDEPENDENT_CODE) 
  set_property(TARGET bitprim-node-cint PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)

#set_target_properties(bitprim-node-cint PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_definitions(bitprim-node-cint PUBLIC -Dbitprim_EXPORTS)

target_include_directories(bitprim-node-cint PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# target_compile_definitions(bitprim-node-cint PUBLIC -DBCN_STATIC)
if (NOT ENABLE_SHARED)
  target_compile_definitions(bitprim-node-cint PUBLIC -DBITPRIM_LIB_STATIC)
  # target_compile_definitions(bitprim-node-cint PUBLIC -DBCN_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)
# else()
  # target_compile_definitions(bitprim-node-cint PUBLIC -DBC_DLL)
endif()

#Note: Bitprim modules are Static, NodeCint Shared
target_compile_definitions(bitprim-node-cint PUBLIC -DBCN_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)



if (NOT MSVC)
  target_compile_definitions(bitprim-node-cint PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()

if (NOT USE_CONAN)
  target_link_libraries(bitprim-node-cint PUBLIC bitprim-node)
endif()

if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(bitprim-node-cint PUBLIC ${CONAN_LIBS})
endif()


if (USE_CONAN)
  if (MINGW)
    target_link_libraries(bitprim-node-cint PUBLIC ws2_32 wsock32) #TODO(fernando): manage with Conan
  endif()
endif()


# if (MSVC)
#   target_link_libraries(bitprim-node-cint PUBLIC ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})
# endif()
#if (MINGW)
#  target_link_libraries(bitprim-node-cint PUBLIC bitprim-node wsock32)
#else()
#    target_link_libraries(bitprim-node-cint PUBLIC bitprim-node)
#endif()


_group_sources(bitprim-node-cint "${CMAKE_CURRENT_LIST_DIR}")



# Console
#==============================================================================


if (WITH_CONSOLE_NODE_CINT)
  #add_executable(test-console-twos
  #        console/main.c)

  add_executable(test_console
          console/main.cpp)

  target_link_libraries(test_console bitprim-node-cint)

  set_target_properties(
          test_console PROPERTIES
          FOLDER "node"
          OUTPUT_NAME test_console)
endif()





#==============================================================================

# # Tests
# #==============================================================================
#
# if (WITH_TESTS)
#   enable_testing()
# endif()
# 
# # local: test/bitprim_node_cint_test
# #------------------------------------------------------------------------------
 if (WITH_TESTS)
   add_executable(queries
           test/queries.cpp)
   target_link_libraries(queries PUBLIC bitprim-node-cint)
   #_group_sources(queries "${CMAKE_CURRENT_LIST_DIR}/test")

   #_add_tests(bitprim_node_cint_test
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
#install(TARGETS bitprim-node-cint
#        EXPORT bitprim-node-cint
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#)


install(TARGETS bitprim-node-cint
        EXPORT bitprim-node-cint
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "lib"
        COMPONENT library
        )


set(_bitprim_headers
        bitprim/nodecint/convertions.hpp
        bitprim/nodecint/helpers.hpp
        bitprim/nodecint/executor_c.h
        bitprim/nodecint/primitives.h
        bitprim/nodecint/version.h
        bitprim/nodecint/visibility.h
        bitprim/nodecint/chain/block.h
        bitprim/nodecint/chain/block_indexes.h
        bitprim/nodecint/chain/block_list.h
        bitprim/nodecint/chain/chain.h
        bitprim/nodecint/chain/compact_block.h
        bitprim/nodecint/chain/get_blocks.h
        bitprim/nodecint/chain/get_headers.h
        bitprim/nodecint/chain/hash_list.h
        bitprim/nodecint/chain/header.h
        bitprim/nodecint/chain/history_compact.h
        bitprim/nodecint/chain/history_compact_list.h
        bitprim/nodecint/chain/stealth_compact.h
        bitprim/nodecint/chain/stealth_compact_list.h
        bitprim/nodecint/chain/input.h
        bitprim/nodecint/chain/input_list.h

        bitprim/nodecint/chain/merkle_block.h
        bitprim/nodecint/chain/output.h
        bitprim/nodecint/chain/output_list.h
        bitprim/nodecint/chain/output_point.h
        bitprim/nodecint/chain/payment_address.h
        bitprim/nodecint/chain/point.h
        bitprim/nodecint/chain/point_list.h
        bitprim/nodecint/chain/script.h
        bitprim/nodecint/chain/transaction.h
        bitprim/nodecint/chain/transaction_list.h

        bitprim/nodecint/p2p/p2p.h

        bitprim/nodecint/wallet/wallet.h
        bitprim/nodecint/wallet/word_list.h
        bitprim/nodecint/binary.h
)

foreach (_header ${_bitprim_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT bitprim-node-cint
        FILE "${CMAKE_CURRENT_BINARY_DIR}/bitprim-node-cintTargets.cmake")
export(PACKAGE bitprim-node-cint)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT bitprim-node-cint
        FILE bitprim-node-cintTargets.cmake
        DESTINATION ${_config_package_location})

configure_file(bitprim-node-cintConfig.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-node-cintConfig.cmake"
        @ONLY)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-node-cintConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-node-cintConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-node-cintConfigVersion.cmake"
        DESTINATION ${_config_package_location})
