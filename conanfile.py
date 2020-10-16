# Copyright (c) 2016-2020 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
from conans import CMake
from kthbuild import option_on_off, march_conan_manip, pass_march_to_compiler
from kthbuild import KnuthConanFile

class KnuthCAPIConan(KnuthConanFile):
    def recipe_dir(self):
        return os.path.dirname(os.path.abspath(__file__))

    name = "c-api"
    # version = get_version()
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/c-api"
    description = "Bitcoin Full Node Library with C interface"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "tests": [True, False],
        "console": [True, False],       #TODO(fernando): move to kthbuild

        "microarchitecture": "ANY",
        "fix_march": [True, False],
        "march_id": "ANY",

        "no_compilation": [True, False],
        "currency": ['BCH', 'BTC', 'LTC'],
        "verbose": [True, False],
        "keoken": [True, False],
        "mempool": [True, False],

        "db": ['legacy', 'legacy_full', 'pruned', 'default', 'full'],
        "db_readonly": [True, False],

        "cxxflags": "ANY",
        "cflags": "ANY",
        "glibcxx_supports_cxx11_abi": "ANY",
        "cmake_export_compile_commands": [True, False],
        "log": ["boost", "spdlog", "binlog"],
        "use_libmdbx": [True, False],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "tests": False,
        "console": False,

        "microarchitecture": "_DUMMY_",
        "fix_march": False,
        "march_id": "_DUMMY_",

        "no_compilation": False,
        "currency": "BCH",
        "verbose": False,
        "keoken": False,
        "mempool": False,
        "db": "default",
        "db_readonly": False,

        "cxxflags": "_DUMMY_",
        "cflags": "_DUMMY_",
        "glibcxx_supports_cxx11_abi": "_DUMMY_",
        "cmake_export_compile_commands": False,
        "log": "spdlog",
        "use_libmdbx": False,
        
    }

    generators = "cmake"
    exports = "conan_*", "ci_utils/*"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "kth-c-apiConfig.cmake.in", "knuthbuildinfo.cmake","include/*", "test/*", "console/*"
    package_files = "build/lkth-c-api.so"
    build_policy = "missing"

    @property
    def is_shared(self):
        # if self.settings.compiler == "Visual Studio" and self.msvc_mt_build:
        #     return False
        # else:
        #     return self.options.shared
        return self.options.shared

    @property
    def is_keoken(self):
        return self.options.currency == "BCH" and self.options.get_safe("keoken")

    def requirements(self):
        if not self.options.no_compilation and self.settings.get_safe("compiler") is not None:
            self.requires("node/0.X@%s/%s" % (self.user, self.channel))

    def config_options(self):
        KnuthConanFile.config_options(self)

    def configure(self):
        KnuthConanFile.configure(self)

        if self.options.no_compilation or (self.settings.compiler == None and self.settings.arch == 'x86_64' and self.settings.os in ('Linux', 'Windows', 'Macos')):
            self.settings.remove("compiler")
            self.settings.remove("build_type")

        if self.options.keoken and self.options.currency != "BCH":
            self.output.warn("For the moment Keoken is only enabled for BCH. Building without Keoken support...")
            del self.options.keoken
        else:
            self.options["*"].keoken = self.options.keoken

        if self.is_keoken:
            if self.options.db == "pruned" or self.options.db == "default":
                self.output.warn("Keoken mode requires db=full and your configuration is db=%s, it has been changed automatically..." % (self.options.db,))
                self.options.db = "full"

        self.options["*"].keoken = self.is_keoken
        
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
        KnuthConanFile.package_id(self)

        self.info.options.console = "ANY"
        self.info.options.no_compilation = "ANY"

    def build(self):
        cmake = self.cmake_basis()

        #TODO(fernando): check and compare "shared" logic with the one in kthbuild
        cmake.definitions["ENABLE_SHARED"] = option_on_off(self.is_shared)
        cmake.definitions["ENABLE_SHARED_CAPI"] = option_on_off(self.is_shared)
        # cmake.definitions["ENABLE_POSITION_INDEPENDENT_CODE"] = option_on_off(self.fPIC_enabled)

        cmake.definitions["WITH_CONSOLE"] = option_on_off(self.options.console)
        cmake.definitions["WITH_CONSOLE_CAPI"] = option_on_off(self.options.console)

        cmake.definitions["WITH_KEOKEN"] = option_on_off(self.is_keoken)
        cmake.definitions["WITH_MEMPOOL"] = option_on_off(self.options.mempool)
        cmake.definitions["DB_READONLY_MODE"] = option_on_off(self.options.db_readonly)
        cmake.definitions["LOG_LIBRARY"] = self.options.log
        cmake.definitions["USE_LIBMDBX"] = option_on_off(self.options.use_libmdbx)

        cmake.configure(source_dir=self.source_folder)
        if not self.options.cmake_export_compile_commands:
            cmake.build()
            if self.options.tests:
                cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.ipp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs = ['include']

        if self.is_shared:
            self.cpp_info.libs = ["kth-c-api"]
        else:
            self.cpp_info.libs = ["kth-c-api", "kth-c-api-version"]

