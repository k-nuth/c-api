import platform
from conan.packager import ConanMultiPackager
import os
import cpuid
import copy

def handle_microarchs(opt_name, microarchs, filtered_builds, settings, options, env_vars, build_requires):
    print(microarchs)
    microarchs = list(set(microarchs))
    print(microarchs)

    for ma in microarchs:
        opts_copy = copy.deepcopy(options)
        opts_copy[opt_name] = ma
        filtered_builds.append([settings, opts_copy, env_vars, build_requires])

def xor(a, b):
    return (a and not b) or (not a and b)

if __name__ == "__main__":
    builder = ConanMultiPackager(username="bitprim", channel="testing",
                                 remotes="https://api.bintray.com/conan/bitprim/bitprim",
                                 archs=["x86_64"])

    builder.add_common_builds(shared_option_name="bitprim-node-cint:shared")    
    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:

        # if settings["build_type"] == "Release" \
        #         and (not "compiler.runtime" in settings or not settings["compiler.runtime"] == "MT"):

        if settings["build_type"] == "Release" \
                and (not "compiler.runtime" in settings or xor(options["shared"] == True, settings["compiler.runtime"] == "MT")):

            env_vars["BITPRIM_BUILD_NUMBER"] = os.getenv('BITPRIM_BUILD_NUMBER', '-')
                
            if os.getenv('BITPRIM_RUN_TESTS', 'false') == 'true':
                options["bitprim-node-cint:with_tests"] = "True"

            marchs = ["x86_64", ''.join(cpuid.cpu_microarchitecture()), "haswell", "skylake"]
            handle_microarchs("bitprim-node-cint:microarchitecture", marchs, filtered_builds, settings, options, env_vars, build_requires)

            #filtered_builds.append([settings, options, env_vars, build_requires])

    builder.builds = filtered_builds
    builder.run()
