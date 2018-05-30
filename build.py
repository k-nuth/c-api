from conan.packager import ConanMultiPackager
import cpuid
import os
import copy
import re
import platform


def get_content(path):
    with open(path, 'r') as f:
        return f.read()

def get_version():
    return get_content('conan_version')

def get_channel():
    return get_content('conan_channel')

def get_conan_vars():
    login_username = os.getenv("CONAN_LOGIN_USERNAME", "bitprim-bintray")
    username = os.getenv("CONAN_USERNAME", "bitprim")
    channel = os.getenv("CONAN_CHANNEL", get_channel())
    version = os.getenv("CONAN_VERSION", get_version())
    return login_username, username, channel, version

def get_value_from_recipe(search_string, recipe="conanfile.py"):
    with open(recipe, "r") as conanfile:
        contents = conanfile.read()
        result = re.search(search_string, contents)
    return result

def get_name_from_recipe():
    return get_value_from_recipe(r'''name\s*=\s*["'](\S*)["']''').groups()[0]

def get_user_repository(username, repository_name):
    # https://api.bintray.com/conan/bitprim/bitprim
    return "https://api.bintray.com/conan/{0}/{1}".format(username.lower(), repository_name)

def get_conan_upload(username):
    repository_name = os.getenv("BIPRIM_BINTRAY_REPOSITORY", "bitprim")
    return os.getenv("CONAN_UPLOAD", get_user_repository(username, repository_name))

def get_conan_remotes(username):
    # While redundant, this moves upload remote to position 0.
    remotes = [get_conan_upload(username)]

    # # Add bincrafters repository for other users, e.g. if the package would
    # # require other packages from the bincrafters repo.
    # bincrafters_user = "bincrafters"
    # if username != bincrafters_user:
    #     remotes.append(get_conan_upload(bincrafters_user))
    return remotes

def get_os():
    return platform.system().replace("Darwin", "Macos")

def get_archs():
    return ["x86_64"]
    # archs = os.getenv("CONAN_ARCHS", None)
    # if get_os() == "Macos" and archs is None:
    #     return ["x86_64"]
    # return split_colon_env("CONAN_ARCHS") if archs else None


def get_builder(args=None):
    name = get_name_from_recipe()
    login_username, username, channel, version = get_conan_vars()
    reference = "{0}/{1}".format(name, version)
    upload = get_conan_upload(username)
    remotes = os.getenv("CONAN_REMOTES", get_conan_remotes(username))

    # upload_when_stable = get_upload_when_stable()
    # stable_branch_pattern = os.getenv("CONAN_STABLE_BRANCH_PATTERN", "stable/*")

    archs = get_archs()
    builder = ConanMultiPackager(
        args=args,
        username=username,
        login_username=login_username,
        channel=channel,
        reference=reference,
        upload=upload,
        remotes=remotes,
        archs=archs,
        # upload_only_when_stable=upload_when_stable,
        # stable_branch_pattern=stable_branch_pattern
        )

    return builder, name


def handle_microarchs(opt_name, microarchs, filtered_builds, settings, options, env_vars, build_requires):
    # print(microarchs)
    microarchs = list(set(microarchs))
    # print(microarchs)

    for ma in microarchs:
        opts_copy = copy.deepcopy(options)
        opts_copy[opt_name] = ma
        filtered_builds.append([settings, opts_copy, env_vars, build_requires])

def xor(a, b):
    return (a and not b) or (not a and b)


if __name__ == "__main__":
    builder, name = get_builder()
    builder.add_common_builds(shared_option_name="%s:shared" % name)    
    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:

        if settings["build_type"] == "Release" \
                and (not "compiler.runtime" in settings or xor(options["%s:shared" % name] == True, settings["compiler.runtime"] == "MT")):

            env_vars["BITPRIM_BUILD_NUMBER"] = os.getenv('BITPRIM_BUILD_NUMBER', '-')
                
            if os.getenv('BITPRIM_RUN_TESTS', 'false') == 'true':
                options["%s:with_tests" % name] = "True"

            options["*:currency"] = os.getenv('BITPRIM_CI_CURRENCY', 'BCH')

            marchs = ["x86_64", ''.join(cpuid.cpu_microarchitecture()), "haswell", "skylake"]
            handle_microarchs("*:microarchitecture", marchs, filtered_builds, settings, options, env_vars, build_requires)

    builder.builds = filtered_builds
    builder.run()



# if __name__ == "__main__":
#     # builder = ConanMultiPackager(username="bitprim", channel="testing",
#     #                              remotes="https://api.bintray.com/conan/bitprim/bitprim",
#     #                              archs=["x86_64"])

#     builder, name = get_builder()
#     builder.add_common_builds(shared_option_name="%s:shared" % name)    
#     filtered_builds = []
#     for settings, options, env_vars, build_requires in builder.builds:

#         # if settings["build_type"] == "Release" \
#         #         and (not "compiler.runtime" in settings or not settings["compiler.runtime"] == "MT"):

#         if settings["build_type"] == "Release" \
#                 and (not "compiler.runtime" in settings or xor(options["%s:shared" % name] == True, settings["compiler.runtime"] == "MT")):

#             env_vars["BITPRIM_BUILD_NUMBER"] = os.getenv('BITPRIM_BUILD_NUMBER', '-')
                
#             if os.getenv('BITPRIM_RUN_TESTS', 'false') == 'true':
#                 options["%s:with_tests" % name] = "True"

#             opts_bch = copy.deepcopy(options)
#             opts_btc = copy.deepcopy(options)
#             # opts_ltc = copy.deepcopy(options)

#             opts_bch["*:currency"] = "BCH"
#             opts_btc["*:currency"] = "BTC"
#             # opts_ltc["*:currency"] = "LTC"

#             marchs = ["x86_64", ''.join(cpuid.cpu_microarchitecture()), "haswell", "skylake"]
#             handle_microarchs("*:microarchitecture", marchs, filtered_builds, settings, opts_bch, env_vars, build_requires)
#             handle_microarchs("*:microarchitecture", marchs, filtered_builds, settings, opts_btc, env_vars, build_requires)
#             # handle_microarchs("*:microarchitecture", marchs, filtered_builds, settings, opts_ltc, env_vars, build_requires)

#             #filtered_builds.append([settings, options, env_vars, build_requires])

#     builder.builds = filtered_builds
#     builder.run()
