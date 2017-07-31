from conan.packager import ConanMultiPackager
import os

if __name__ == "__main__":
    builder = ConanMultiPackager(username="bitprim", channel="stable")
    builder.add_common_builds(shared_option_name="bitprim-node-cint:shared")
    builder.password = os.getenv("CONAN_PASSWORD")
    builder.run()
