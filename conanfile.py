from conans import ConanFile, CMake
# import os

class BitprimNodeCIntConan(ConanFile):
    name = "bitprim-node-cint"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/bitprim/bitprim-node-cint"
    description = "Bitcoin Full Node Library with C interface"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-node-cintConfig.cmake.in", "include/*", "test/*", "console/*"
    package_files = "build/lbitprim-node-cint.so"
    build_policy = "missing"

    requires = (("bitprim-conan-boost/1.64.0@bitprim/stable"),
                ("bitprim-node/0.1@bitprim/stable"))

    def build(self):
        cmake = CMake(self)
        # cmake.definitions["CMAKE_VERBOSE_MAKEFILE"] = "ON"
        cmake.configure(source_dir=self.conanfile_directory)
        cmake.build()

    def imports(self):
        print('def imports')
        self.copy("*.h", "", "include")
        self.copy("*.h", dst="/Users/fernando/fertest", src="include")
        self.copy("*.hpp", dst="/Users/fernando/fertest", src="include")
        self.copy("*.a", dst="/Users/fernando/fertest", src="include")

    def package(self):
        print('def package')
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
        self.cpp_info.libs = ["bitprim-node-cint"]
