@echo off

echo %KTH_BRANCH%
Set KTH_BRANCH=master
echo %KTH_BRANCH%
​
if exist build mkdir build
cd build
conan remove --locks
REM conan install .. -s build_type=Debug --build=m4
conan install .. -s build_type=Debug -o db=full -s compiler.runtime=MDd --build=missing
​
cmake .. -G "Visual Studio 16 2019" -DCMAKE_VERBOSE_MAKEFILE=ON ^
                 -DUSE_CONAN=ON ^
                 -DCURRENCY=BCH ^
                 -DBINLOG=OFF ^
                 -DWITH_CONSOLE_CAPI=ON ^
                 -DDB_READONLY_MODE=OFF ^
                 -DENABLE_TESTS=OFF ^
                 -DWITH_TESTS=OFF ^
                 -DWITH_TOOLS=OFF ^
                 -DENABLE_ECMULT_STATIC_PRECOMPUTATION=OFF ^
                 -DDB_NEW=ON ^
                 -DDB_NEW_BLOCKS=ON ^
                 -DDB_NEW_FULL=ON ^
                 -DCMAKE_BUILD_TYPE=Debug
​
REM cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON -DWITH_CONSOLE_CAPI=OFF -DDB_READONLY_MODE=OFF -DDB_NEW=ON -DDB_NEW_BLOCKS=ON -DENABLE_TESTS=OFF -DWITH_TESTS=OFF -DWITH_TOOLS=OFF -DENABLE_ECMULT_STATIC_PRECOMPUTATION=OFF -DCMAKE_BUILD_TYPE=Debug
REM ninja -j4
cmake --build . -j 4