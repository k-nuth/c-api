# Knuth C-API <a target="_blank" href="http://semver.org">![Version][badge.version]</a> <a target="_blank" href="https://travis-ci.org/k-nuth/node-cint">![Travis status][badge.Travis]</a> [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/k-nuth/node-cint?svg=true&branch=master)](https://ci.appveyor.com/projects/k-nuth/node-cint) <a target="_blank" href="https://gitter.im/kth/Lobby">![Gitter Chat][badge.Gitter]</a>

> Multi-Cryptocurrency _C Programming Language_ API.

*Knuth C-API* is a library written in the _C Programming Language_ which exposes an API that allows you to programmatically access all of the *Knuth* node features:
  * Wallet
  * Mining
  * Full blockchain
  * Routing

Knuth C-API supports the following cryptocurrencies:
  * [Bitcoin Cash](https://www.bitcoincash.org/)
  * [Bitcoin](https://bitcoin.org/)
  * [Litecoin](https://litecoin.org/)
  
  The main purpose of this API is to serve as a building block for higher level APIs, because most high level languages can interface most easily with C. Therefore, this C API is functional, but we encourage using the others built on top of it (such as kth-py, kth-cs and kth-go).

## Installation Requirements

- 64-bit machine.
- [Conan](https://www.conan.io/) package manager, version 1.1.0 or newer. See [Conan Installation](http://docs.conan.io/en/latest/installation.html#install-with-pip-recommended).

## Installation Procedure

The *Knuth* libraries can be installed on Linux, macOS, FreeBSD, Windows and others. These binaries are pre-built for the most usual operating system/compiler combinations and hosted in an online repository. If there are no pre-built binaries for your platform, a build from source will be attempted.

So, for any platform, an installation can be performed in 2 simple steps:

1. Configure the Conan remote
```
conan remote add kth https://api.bintray.com/conan/k-nuth/kth
```

2. Install the appropriate library

```
# For Bitcoin Cash
conan install kth-node-cint/0.X@kth/stable -o currency=BCH 
# ... or (BCH is the default crypto)
conan install kth-node-cint/0.X@kth/stable 

# For Bitcoin Legacy
conan install kth-node-cint/0.X@kth/stable -o currency=BTC

# For Litecoin
conan install kth-node-cint/0.X@kth/stable -o currency=LTC
```

## Building from source Requirements

In case there are no pre-built binaries for your platform, it is necessary to build from source code. In such a scenario, the following requirements must be added to the previous ones:

- C++11 Conforming Compiler.
- [CMake](https://cmake.org/) building tool, version 3.4 or newer.

## How to use it

### "Hello, Blockchain!" example:
```c
// hello_blockchain.c

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <kth/capi.h>

int main() {
    executor_t exec = executor_construct("my_config_file", stdout, stderr);

    executor_initchain(exec);
    executor_run_wait(exec);
    chain_t chain = executor_get_chain(exec);

    uint64_t height;
    chain_get_last_height(chain, &height);

    printf("%" PRIu64 "\n", height);

    executor_destruct(exec);
}
```

### Explanation:

```c
#include <inttypes.h>
```

Includes C standard library format conversion specifier to output an unsigned decimal integer value of type `uint64_t`.

```c
#include <stdint.h>
```

Includes C standard library fixed width integer types: `uint64_t`.


```c
#include <stdio.h>
```

Includes C standard library input/output features: `stdout`, `stderr` and `printf()`.

```c
#include <kth/capi.h>
```

Needed to use the Knuth C-API features.

```c
executor_t exec = executor_construct("my_config_file", stdout, stderr);
```
Construct a Knuth _Executor_ object, which is necessary to run the node, interact with the blockchain, with the P2P peers and other components of the API.  

`"my_config_file"` is the path to the configuration file; in the [kth-config](https://github.com/k-nuth/config) repository you can find some example files.  
If you pass an empty string (`""`), default configuration will be used.

`stdout` and `stderr` are pointers to the standard output and standard error streams. These are used to tell the Knuth node where to print the logs.   
You can use any object of type `FILE*`. For example, you can make the Knuth node redirect the logs to a file.  
If you pass null pointers (`NULL` or `0`), there will be no logging information.

```c
executor_initchain(exec);
```

Initialize the filesystem database where the Blockchain will be stored.  
You need to have enough disk space to store the full Blockchain.

This is equivalent to executing: `bn -i -c my_config_file`.

```c
executor_run_wait(exec);
```

Run the node.  
In this step, the connections and handshake with the peers will be established, and the initial process of downloading blocks will start. Once this stage has finished, the node will begin to receive transactions and blocks through the P2P network.

This is equivalent to executing: `bn -c my_config_file`.
```c
chain_t chain = executor_get_chain(exec);
```

Get access to the Blockchain query interface (commands and queries).

```c
uint64_t height;
chain_get_last_height(chain, &height);

printf("%" PRIu64 "\n", height);
```

Ask the Blockchain what is the height of the last downloaded block and print it in the standard output.

```c
executor_destruct(exec);
```

Destroy the Executor object created earlier.  
This is the _C Programming Language_, there is no automatic handling of resources here, you have to do it manually.

### Build and run:

_Note: Here we are building the code using the GNU Compiler Collection (GCC) on Linux. You can use other compilers and operating systems as well. If you have any questions, you can [contact us here](https://gitter.im/kth/contact)._

To build and run the code example, first you have to create a tool file called `conanfile.txt` in orded to manage the dependencies of the code:

```sh
printf "[requires]\nkth-node-cint/0.X@kth/stable\n[options]\nkth-node-cint:shared=True\n[imports]\ninclude/kth, *.h -> ./include/kth\ninclude/kth, *.hpp -> ./include/kth\nlib, *.so -> ./lib\n" > conanfile.txt
```

Then, run the following command to bring the dependencies to the local directory:

```sh
conan install .
```

Now, you can build our code example:

```sh
gcc -Iinclude -c hello_blockchain.c
gcc -Llib -o hello_blockchain hello_blockchain.o -lkth-node-cint
```

...run it and enjoy the Knuth programmable APIs:

```sh
./hello_blockchain
```


## Advanced Installation

Knuth is a high performance node, so we have some options and pre-built packages tuned for several platforms.
Specifically, you can choose your computer _microarchitecture_ to download a pre-build executable compiled to take advantage of the instructions available in your processor. For example:

```
# For Haswell microarchitecture and Bitcoin Cash currency
conan install kth-node-cint/0.X@kth/stable -o currency=BCH -o microarchitecture=haswell 
```
So, you can manually choose the appropriate microarchitecture, some examples are: _x86_64_, _haswell_, _ivybridge_, _sandybridge_, _bulldozer_, ...  
By default, if you do not specify any, the building system will select a base microarchitecture corresponding to your _Instruction Set Architecture_ (ISA). For example, for _Intel 80x86_, the x86_64 microarchitecture will be selected.

### Automatic Microarchitecture selection

Our build system has the ability to automatically detect the microarchitecture of your processor. To do this, first, you have to install our _pip_ package called [cpuid](https://pypi.python.org/pypi/cpuid). Our build system detects if this package is installed and in such case, makes use of it to detect the best possible executable for your processor.

```
pip install cpuid
conan install kth-node-cint/0.X@kth/stable 
```


<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/github/k-nuth/node-cint?svg=true&branch=dev
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/k-nuth/node-cint.svg?branch=master
[badge.version]: https://badge.fury.io/gh/kth%2Fkth-node-cint.svg
