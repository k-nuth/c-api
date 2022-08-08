import copy
import os
import cpuid
import platform
from kthbuild import get_base_march_ids, get_builder, handle_microarchs, copy_env_vars, filter_marchs_tests

def xor(a, b):
    return (a and not b) or (not a and b)

if __name__ == "__main__":
    builder, name = get_builder(os.path.dirname(os.path.abspath(__file__)))
    builder.add_common_builds(shared_option_name="%s:shared" % name)

    filtered_builds = []
    march_ids = get_base_march_ids()
    for settings, options, env_vars, build_requires, reference in builder.items:

        if settings["build_type"] == "Release" \
                and (not "compiler.runtime" in settings or xor(options["%s:shared" % name] == True, settings["compiler.runtime"] == "MT")):

            print(settings["compiler"])
            print("compiler.libcxx" in settings)

            if settings["compiler"] == "gcc":
                # if settings.get_safe("compiler.libcxx") is None:
                # print("****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!")
                # print(settings["compiler.libcxx"])
                # print("****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!")

                settings["compiler.libcxx"] = "libstdc++11"

                print("****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!")
                print(settings["compiler.libcxx"])
                print("****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!****!!!!")


            copy_env_vars(env_vars)

            if os.getenv('KTH_RUN_TESTS', 'false') == 'true':
                options["%s:tests" % name] = "True"

            opts_bch = copy.deepcopy(options)
            # opts_btc = copy.deepcopy(options)

            opts_bch["%s:currency" % name] = "BCH"
            # opts_btc["%s:currency" % name] = "BTC"

            opts_bch_full = copy.deepcopy(opts_bch)
            opts_bch_full["%s:db" % name] = "full"

            # handle_microarchs("*:march_id", march_ids, filtered_builds, settings, opts_bch_full, env_vars, build_requires)
            # handle_microarchs("*:march_id", march_ids, filtered_builds, settings, opts_bch, env_vars, build_requires)
            # handle_microarchs("*:march_id", march_ids, filtered_builds, settings, opts_btc, env_vars, build_requires)
            # filter_marchs_tests(name, filtered_builds, ["%s:tests" % name], "*:march_id")

            handle_microarchs("%s:march_id" % name, march_ids, filtered_builds, settings, opts_bch_full, env_vars, build_requires)
            handle_microarchs("%s:march_id" % name, march_ids, filtered_builds, settings, opts_bch, env_vars, build_requires)
            # handle_microarchs("%s:march_id" % name, march_ids, filtered_builds, settings, opts_btc, env_vars, build_requires)
            filter_marchs_tests(name, filtered_builds, ["%s:tests" % name])

    builder.builds = filtered_builds
    builder.run()
