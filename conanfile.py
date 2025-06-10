# Copyright (c) 2016-2024 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
from conan import ConanFile
from conan.tools.build.cppstd import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy
from kthbuild import KnuthConanFileV2, option_on_off

required_conan_version = ">=2.0"

class KnuthCAPIConan(KnuthConanFileV2):
    name = "c-api"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/c-api"
    description = "Bitcoin Full Node Library with C interface"
    settings = "os", "compiler", "build_type", "arch"
    package_type = "library"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "tests": [True, False],
        "console": [True, False],       #TODO(fernando): move to kthbuild
        "march_id": ["ANY"],
        "march_strategy": ["download_if_possible", "optimized", "download_or_fail"],
        "no_compilation": [True, False],
        "currency": ['BCH', 'BTC', 'LTC'],
        "verbose": [True, False],
        "mempool": [True, False],
        "db": ['dynamic'],
        "db_readonly": [True, False],
        "cxxflags": ["ANY"],
        "cflags": ["ANY"],
        "cmake_export_compile_commands": [True, False],
        "log": ["boost", "spdlog", "binlog"],
        "use_libmdbx": [True, False],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "tests": False,
        "console": False,
        "march_strategy": "download_if_possible",
        "no_compilation": False,
        "currency": "BCH",
        "verbose": False,
        "mempool": False,
        "db": "dynamic",
        "db_readonly": False,
        "cmake_export_compile_commands": False,
        "log": "spdlog",
        "use_libmdbx": False,
    }

    exports_sources = "src/*", "CMakeLists.txt", "ci_utils/cmake/*", "cmake/*", "knuthbuildinfo.cmake","include/*", "test/*", "console/*"

    def _is_legacy_db(self):
        return self.options.db == "legacy" or self.options.db == "legacy_full"

    @property
    def is_shared(self):
        # if self.settings.compiler == "Visual Studio" and self.msvc_mt_build:
        #     return False
        # else:
        #     return self.options.shared
        return self.options.shared

    def validate(self):
        KnuthConanFileV2.validate(self)
        if self.info.settings.compiler.cppstd:
            check_min_cppstd(self, "23")

    def requirements(self):
        if not self.options.no_compilation and self.settings.get_safe("compiler") is not None:
            self.requires("node/0.58.0", transitive_headers=True, transitive_libs=True)
            # if self.settings.os == "Emscripten":
            #     self.requires("domain/0.45.0", transitive_headers=True, transitive_libs=True)
            # else:
            #     self.requires("node/0.58.0", transitive_headers=True, transitive_libs=True)

    def build_requirements(self):
        if self.options.tests:
            self.test_requires("catch2/3.7.1")

    def config_options(self):
        KnuthConanFileV2.config_options(self)

    def configure(self):
        KnuthConanFileV2.configure(self)

        if self.options.no_compilation or (self.settings.compiler == None and self.settings.arch == 'x86_64' and self.settings.os in ('Linux', 'Windows', 'Macos')):
            self.settings.remove("compiler")
            self.settings.remove("build_type")

        self.options["*"].db_readonly = self.options.db_readonly
        self.output.info("Compiling with read-only DB: %s" % (self.options.db_readonly,))

        self.options["*"].mempool = self.options.mempool
        self.output.info("Compiling with mempool: %s" % (self.options.mempool,))

        #TODO(fernando): move to kthbuild
        self.options["*"].log = self.options.log
        self.output.info("Compiling with log: %s" % (self.options.log,))

        self.options["*"].use_libmdbx = self.options.use_libmdbx
        self.output.info("Compiling with use_libmdbx: %s" % (self.options.use_libmdbx,))


    def package_id(self):
        KnuthConanFileV2.package_id(self)

        self.info.options.console = "ANY"
        self.info.options.no_compilation = "ANY"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = self.cmake_toolchain_basis()
        # tc.variables["CMAKE_VERBOSE_MAKEFILE"] = True
        #TODO(fernando): check and compare "shared" logic with the one in kthbuild
        tc.variables["ENABLE_SHARED"] = option_on_off(self.is_shared)
        tc.variables["ENABLE_SHARED_CAPI"] = option_on_off(self.is_shared)
        # tc.variables["ENABLE_POSITION_INDEPENDENT_CODE"] = option_on_off(self.fPIC_enabled)

        tc.variables["WITH_CONSOLE"] = option_on_off(self.options.console)
        tc.variables["WITH_CONSOLE_CAPI"] = option_on_off(self.options.console)

        tc.variables["WITH_MEMPOOL"] = option_on_off(self.options.mempool)
        tc.variables["DB_READONLY_MODE"] = option_on_off(self.options.db_readonly)
        tc.variables["LOG_LIBRARY"] = self.options.log
        tc.variables["USE_LIBMDBX"] = option_on_off(self.options.use_libmdbx)
        tc.variables["CONAN_DISABLE_CHECK_COMPILER"] = option_on_off(True)

        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure()
        if not self.options.cmake_export_compile_commands:
            cmake.build()
            if self.options.tests:
                cmake.test()

    # def package(self):
    #     self.copy("*.h", dst="include", src="include")
    #     self.copy("*.hpp", dst="include", src="include")
    #     self.copy("*.ipp", dst="include", src="include")
    #     self.copy("*.lib", dst="lib", keep_path=False)
    #     self.copy("*.dll", dst="bin", keep_path=False)
    #     self.copy("*.dylib*", dst="lib", keep_path=False)
    #     self.copy("*.so", dst="lib", keep_path=False)
    #     self.copy("*.a", dst="lib", keep_path=False)

    def package(self):
        cmake = CMake(self)
        cmake.install()
        # rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        # rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        # rmdir(self, os.path.join(self.package_folder, "res"))
        # rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ["c-api"]

