<!-- <a target="_blank" href="http://semver.org">![Version][badge.version]</a> -->
<!-- <a target="_blank" href="https://cirrus-ci.com/github/k-nuth/c-api">![Build Status][badge.Cirrus]</a> -->

<img width="200px" src="https://raw.githubusercontent.com/k-nuth/misc/master/images/KTH-and-C.svg" />

# C API <a target="_blank" href="https://github.com/k-nuth/c-api/releases">![Github Releases][badge.release]</a> <a target="_blank" href="https://github.com/k-nuth/c-api/actions">![Build status][badge.GithubActions]</a> <a href="#">![C][badge.c]</a> <a target="_blank" href="https://t.me/knuth_cash">![Telegram][badge.telegram]</a> <a target="_blank" href="https://k-nuth.slack.com/">![Slack][badge.slack]</a>

> Bitcoin full node as a C Programming Language library

Knuth is a high performance implementation of the Bitcoin protocol focused on users requiring extra performance and flexibility, what makes it the best platform for wallets, exchanges, block explorers and miners.

## Getting started

Install and run Knuth is very easy:

1. Install and configure the Knuth build helper:
```
$ pip install kthbuild --user --upgrade

$ conan config install https://github.com/k-nuth/ci-utils/raw/master/conan/config2023.zip
```

2. Install the appropriate library:

```
$ conan install --requires=c-api/0.67.0 --update
```

### "Hello, Knuth!":
```c
// hello_knuth.c

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <kth/capi.h>

int main() {
    kth_node_t node = kth_node_construct("my_config_file", stdout, stderr);

    kth_node_initchain(node);
    kth_node_run_wait(node);
    kth_chain_t chain = kth_node_get_chain(node);

    uint64_t height;
    chain_get_last_height(chain, &height);

    printf("%" PRIu64 "\n", height);

    kth_node_destruct(node);
}
```

### Explanation:

```c
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
```

Includes C standard library stuff, like format conversion specifiers, fixed width integer types (`uint64_t`) and input/output features. (`stdout`, `stderr` and `printf())`.

```c
#include <kth/capi.h>
```
Gives access to Knuth C-API features.

```c
kth_node_t node = kth_node_construct("my_config_file", stdout, stderr);
```
Construct a Knuth _node_ object, which is necessary to run the node, interact with the blockchain, with the P2P peers and other components of the API.

`"my_config_file"` is the path to the configuration file; in the [config](https://github.com/k-nuth/config) repository you can find some example files.
If you pass an empty string (`""`), default configuration will be used.

`stdout` and `stderr` are pointers to the standard output and standard error streams. These are used to tell the Knuth node where to print the logs.
You can use any object of type `FILE*`. For example, you can make the Knuth node redirect the logs to a file.
If you pass null pointers (`NULL` or `0`), there will be no logging information.

```c
kth_node_initchain(node);
```

Initialize the filesystem database where the _blockchain_ will be stored.
You need to have enough disk space to store the blockchain.

This is equivalent to executing: `kth -i -c my_config_file`.

```c
kth_node_run_wait(node);
```

Run the node.
In this step, the connections and handshake with the peers will be established, and the initial process of downloading blocks will start. Once this stage has finished, the node will begin to receive transactions and blocks through the P2P network.

This is equivalent to executing: `kth -c my_config_file`.
```c
kth_chain_t chain = kth_node_get_chain(node);
```

Get access to the blockchain query interface (commands and queries).

```c
uint64_t height;
chain_get_last_height(chain, &height);

printf("%" PRIu64 "\n", height);
```

Ask the blockchain what is the height of the last downloaded block and print it in the standard output.

```c
kth_node_destruct(node);
```

Destroy the node object created earlier.
(We are in land of _The C Programming Language_, there is no automatic handling of resources here, you have to do it manually.)

### Build and run:

_Note: Here we are building the code using the GNU Compiler Collection (GCC) on Linux. You can use other compilers and operating systems as well. If you have any questions, you can [contact us here](info@kth.cash)._

To build and run the code example, first you have to create a tool file called `conanfile.txt` in orded to manage the dependencies of the code:

```sh
$ printf "[requires]\nc-api/0.67.0\n[options]\nc-api:shared=True\n[imports]\ninclude/kth, *.h -> ./include/kth\ninclude/kth, *.hpp -> ./include/kth\nlib, *.so -> ./lib\n" > conanfile.txt
```

Then, run the following command to bring the dependencies to the local directory:

```sh
$ conan install .
```

Now, you can build our code example:

```sh
$ gcc -Iinclude -c hello_knuth.c
$ gcc -Llib -o hello_knuth hello_knuth.o -lkth-c-api
```

...run it and enjoy the Knuth programmable APIs:

```sh
$ ./hello_knuth
```

For more more detailed instructions, please refer to our [documentation](https://kth.cash/docs/).

## Issues

Each of our modules has its own Github repository, but in case you want to create an issue, please do so in our [main repository](https://github.com/k-nuth/kth/issues).


<!-- Links -->
[badge.Travis]: https://travis-ci.org/k-nuth/c-api.svg?branch=master
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/github/k-nuth/c-api?svg=true&branch=master
[badge.Cirrus]: https://api.cirrus-ci.com/github/k-nuth/c-api.svg?branch=master
[badge.GithubActions]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Factions-badge.atrox.dev%2Fk-nuth%2Fc-api%2Fbadge&style=for-the-badge
[badge.version]: https://badge.fury.io/gh/k-nuth%2Fkth-c-api.svg
[badge.release]: https://img.shields.io/github/v/release/k-nuth/c-api?display_name=tag&style=for-the-badge&color=A8B9CC&logo=c
[badge.c]: https://img.shields.io/badge/C-23-blue.svg?logo=c&style=for-the-badge
[badge.telegram]: https://img.shields.io/badge/telegram-badge-blue.svg?logo=telegram&style=for-the-badge
[badge.slack]: https://img.shields.io/badge/slack-badge-orange.svg?logo=slack&style=for-the-badge

<!-- [badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg -->
