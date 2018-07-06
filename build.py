import copy
import os
import cpuid
import platform
from ci_utils import get_builder, handle_microarchs, copy_env_vars, filter_valid_exts

def xor(a, b):
    return (a and not b) or (not a and b)

if __name__ == "__main__":

    full_build = os.getenv('BITPRIM_FULL_BUILD', '0') == '1'
    # full_build = True

    builder, name = get_builder()
    builder.add_common_builds(shared_option_name="%s:shared" % name)
    filtered_builds = []

    for settings, options, env_vars, build_requires, reference in builder.items:


        if settings["build_type"] == "Release" \
                and (not "compiler.runtime" in settings or xor(options["%s:shared" % name] == True, settings["compiler.runtime"] == "MT")):

            copy_env_vars(env_vars)
                
            if os.getenv('BITPRIM_RUN_TESTS', 'false') == 'true':
                options["%s:with_tests" % name] = "True"
                marchs = ["x86-64"]
            else:
                if full_build:
                    # marchs = ["x86_64", ''.join(cpuid.cpu_microarchitecture()), "haswell", "skylake"]
                    marchs = filter_valid_exts(str(platform.system()), str(settings["compiler"]), float(str(settings["compiler.version"])), [''.join(cpuid.cpu_microarchitecture()), 'x86-64', 'sandybridge', 'ivybridge', 'haswell', 'skylake', 'skylake-avx512'])
                else:
                    marchs = ["x86-64"]

            options["*:currency"] = os.getenv('BITPRIM_CI_CURRENCY', '---')

            handle_microarchs("*:microarchitecture", marchs, filtered_builds, settings, options, env_vars, build_requires)

    builder.builds = filtered_builds
    builder.run()
