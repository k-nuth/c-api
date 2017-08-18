# Bitprim Node C Interface <a target="_blank" href="https://gitter.im/bitprim/Lobby">![Gitter Chat][badge.Gitter]</a>

*Bitcoin full node based on bitprim-node with a C Interface*

| **master(linux/osx)** | **conan-build-win(linux/osx)**   | **master(windows)**   | **conan-build-win(windows)** |
|:------:|:-:|:-:|:-:|
| [![Build Status](https://travis-ci.org/bitprim/bitprim-node-cint.svg)](https://travis-ci.org/bitprim/bitprim-node-cint)       | [![Build StatusB](https://travis-ci.org/bitprim/bitprim-node-cint.svg?branch=conan-build-win)](https://travis-ci.org/bitprim/bitprim-node-cint?branch=conan-build-win)  | [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-node-cint?svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-node-cint)  | [![Appveyor StatusB](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-node-cint?branch=conan-build-win&svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-node-cint?branch=conan-build-win)  |

<!-- Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core), [bitprim-database](https://github.com/bitprim/bitprim-database), [bitprim-blockchain](https://github.com/bitprim/bitprim-blockchain), [bitprim-consensus](https://github.com/bitprim/bitprim-consensus) (optional) and [bitprim-network](https://github.com/bitprim/bitprim-network) beforehand according to its build instructions.

```
$ git clone https://github.com/bitprim/bitprim-node-cint.git
$ cd bitprim-node-cint
$ mkdir build
$ cd build
$ cmake .. -DENABLE_TESTS=OFF -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11" 
$ make -j2
$ sudo make install
```

bitprim-node-cint is now installed in `/usr/local/`.

In version2 the `bitcoin-node` console app is for demonstration purposes only. See [bitprim-server](https://github.com/bitprim/bitprim-server) for release quality full node functionality. -->

[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
