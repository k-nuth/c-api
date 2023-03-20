@echo off

echo %KTH_BRANCH%
Set KTH_BRANCH=master
echo %KTH_BRANCH%
​
if exist build_release mkdir build_release
cd build_release
conan remove --locks
REM conan install .. --build=m4
conan install .. -o db=full -o c-api:march_id=4fZKi37a595hP -s build_type=Release -s compiler.runtime=MD --build=missing
​
REM cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=ON^
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=ON^
                 -DUSE_CONAN=ON^
                 -DCURRENCY=BCH^
                 -DBINLOG=OFF^
                 -DWITH_CONSOLE_CAPI=ON^
                 -DDB_READONLY_MODE=OFF^
                 -DENABLE_TESTS=OFF^
                 -DWITH_TESTS=OFF^
                 -DWITH_TOOLS=OFF^
                 -DENABLE_ECMULT_STATIC_PRECOMPUTATION=OFF^
                 -DDB_NEW=ON^
                 -DDB_NEW_BLOCKS=ON^
                 -DDB_NEW_FULL=ON
                 
​
REM cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON -DWITH_CONSOLE_CAPI=OFF -DDB_READONLY_MODE=OFF -DDB_NEW=ON -DDB_NEW_BLOCKS=ON -DENABLE_TESTS=OFF -DWITH_TESTS=OFF -DWITH_TOOLS=OFF -DENABLE_ECMULT_STATIC_PRECOMPUTATION=OFF -DCMAKE_BUILD_TYPE=Release
ninja -j4
REM cmake --build . -j 8
