# include(CMakeParseArguments)

# message( STATUS "--------------------------------------------"  )
# get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
# foreach( d ${DirDefs} )
#     message( STATUS "Found Define: " ${d} )
# endforeach()
# message( STATUS "DirDefs: " ${DirDefs} )
# message( STATUS "--------------------------------------------"  )

# message( STATUS "2 NO_CONAN_AT_ALL: " ${NO_CONAN_AT_ALL} )
# message( STATUS "CMAKE_CXX_COMPILER_ID: " ${CMAKE_CXX_COMPILER_ID} )
# message( STATUS "NOT_USE_CPP11_ABI: " ${NOT_USE_CPP11_ABI} )


# message( STATUS "CONAN_CXX_FLAGS: " ${CONAN_CXX_FLAGS} )
# message( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )


if (NOT NO_CONAN_AT_ALL)
    if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
        include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
        conan_basic_setup()

        remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
        remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            if (NOT NOT_USE_CPP11_ABI)
                add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
                message( STATUS "Bitprim: Using _GLIBCXX_USE_CXX11_ABI=1")
            else()
                add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
                message( STATUS "Bitprim: Using _GLIBCXX_USE_CXX11_ABI=0")
            endif()
            # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-macro-redefined")
            # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-builtin-macro-redefined")
        endif()
    else()
        message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
    endif()
endif()

# message( STATUS "CONAN_CXX_FLAGS: " ${CONAN_CXX_FLAGS} )
# message( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )

