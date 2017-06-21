cmake_minimum_required(VERSION 3.4)

# bitprim-node-cint
#==============================================================================
project(bitprim-node-cint
        VERSION 3.0.0
        LANGUAGES CXX C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++14 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================
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

# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Check dependencies.
#==============================================================================
# Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
#------------------------------------------------------------------------------
if (NOT ENABLE_SHARED)
  set(Boost_USE_STATIC_LIBS ON)
endif()


#------------------------------------------------------------------------------

#set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lwsock32" )
#set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lws2_32" )

#------------------------------------------------------------------------------

if (MSVC)
  find_package(
          Boost 1.56.0 REQUIRED
          COMPONENTS log log_setup unit_test_framework)
else()
  find_package(
          Boost 1.56.0 REQUIRED
          COMPONENTS unit_test_framework)
endif()



# Require bitprim-consensus of at least version 2.0.0 and output ${bitprim_consensus_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
if (WITH_CONSENSUS)
  if (NOT TARGET bitprim-consensus)
    find_package(bitprim-consensus 2.0.0 REQUIRED)
  endif()
endif()

# Implement --with-litecoin.
#------------------------------------------------------------------------------
option(WITH_LITECOIN "Compile with Litecoin support." OFF)
if (WITH_LITECOIN)
  add_definitions(-DLITECOIN)
endif()


# Require bitprim-node of at least version 3.0.0 and output ${bitprim_node_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
if (NOT TARGET bitprim-node)
  find_package(bitprim-node 3.0.0 REQUIRED)
endif()




# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

function(_add_c_compile_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_Flag}" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_Flag}" )
  endif()
endfunction()

function(_add_cxx_compile_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_Flag}" )
  endif()
endfunction()

function(_add_link_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${_Flag}" )
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${_Flag}" )
  endif()
endfunction()

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
function(_group_sources target sources_dir)
  file(GLOB_RECURSE _headers
          ${sources_dir}/include/*.h ${sources_dir}/include/*.hpp)
  target_sources(${target} PRIVATE ${_headers})

  get_target_property(sources ${target} SOURCES)
  foreach (source ${sources})
    get_filename_component(group ${source} ABSOLUTE)
    get_filename_component(group ${group} DIRECTORY)
    file(RELATIVE_PATH group "${sources_dir}" "${group}")
    if (group)
      if (MSVC)
        string(REPLACE "/" "\\" group "${group}")
      endif()
      source_group("${group}" FILES "${source}")
    endif()
  endforeach()

  set_target_properties(${target} PROPERTIES FOLDER "node")
endfunction()




# src/bitprim-node-cint.la => ${libdir}
#------------------------------------------------------------------------------
#set(MODE STATIC)
if (ENABLE_SHARED)
    set(MODE SHARED)
else()
    set(MODE STATIC)
endif()

add_library(bitprim-node-cint ${MODE}
        src/block.cpp
        src/compact_block.cpp
        src/executor.cpp
        src/executor_c.cpp
        src/header.cpp
        src/history_compact.cpp
        src/history_compact_list.cpp
        src/input.cpp
        src/merkle_block.cpp
        src/node.cpp
        src/output.cpp
        src/output_point.cpp
        src/parser.cpp
        src/payment_address.cpp
        src/script.cpp
        src/transaction.cpp)

# set_property(TARGET bitprim-node-cint PROPERTY POSITION_INDEPENDENT_CODE ON)


target_compile_definitions(bitprim-node-cint PUBLIC -Dbitprim_EXPORTS)

target_include_directories(bitprim-node-cint PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_definitions(bitprim-node-cint PUBLIC -DBCN_STATIC)
if (NOT MSVC)
  target_compile_definitions(bitprim-node-cint PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()


target_link_libraries(bitprim-node-cint PUBLIC bitprim-node)

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


#add_executable(test-console-twos
#        console/main.c)

add_executable(test_console
        console/main.cpp)

target_link_libraries(test_console bitprim-node-cint)

set_target_properties(
        test_console PROPERTIES
        FOLDER "node"
        OUTPUT_NAME test_console)




#==============================================================================

# # Tests
# #==============================================================================
# function(_add_tests target)
#   if (ENABLE_SHARED)
#     target_compile_definitions(${target} PRIVATE -DBOOST_TEST_DYN_LINK)
#   endif()
#   target_include_directories(${target} SYSTEM PUBLIC ${Boost_INCLUDE_DIR})
#   target_link_libraries(${target} PUBLIC ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
# 
#   foreach (_test_name ${ARGN})
#     add_test(
#             NAME test.node.${_test_name}
#             COMMAND ${target}
#             --run_test=${_test_name}
#             --show_progress=no
#             --detect_memory_leak=0
#             --report_level=no
#             --build_info=yes)
#   endforeach()
# endfunction()
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
install(TARGETS bitprim-node-cint
        EXPORT bitprim-node-cint
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)


set(_bitprim_headers
        # include_bitcoin_HEADERS =
        include/bitcoin/node.hpp
        # include_bitcoin_node_HEADERS =
        include/bitprim/nodecint/node.h
        include/bitprim/nodecint/executor_c.h
        include/bitprim/nodecint/executor.hpp
        include/bitprim/nodecint/parser.hpp
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
