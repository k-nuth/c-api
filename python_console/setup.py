# -------------------------------------------
# Ubuntu
# sudo apt-get install python-dev
# python setup.py build
# sudo python setup.py install
# export LD_LIBRARY_PATH=/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug:$LD_LIBRARY_PATH
# -------------------------------------------


from distutils.core import setup, Extension

# module1 = Extension('bitprim',
#                     sources = ['bitprimmodule.c'])
#
# module1 = Extension('demo',
#                     define_macros = [('MAJOR_VERSION', '1'),
#                                      ('MINOR_VERSION', '0')],
#                     include_dirs = ['/usr/local/include'],
#                     libraries = ['tcl83'],
#                     library_dirs = ['/usr/local/lib'],
#                     sources = ['demo.c'])

module1 = Extension('bitprim',
                    include_dirs = ['/home/fernando/dev/bitprim/bitprim-node-cint/include'],
                    libraries = ['bitprim-node-cint'],
                    library_dirs = ['/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug'],
                    sources = ['bitprimmodule.c'])



# setup (name = 'PackageName',
#        version = '1.0',
#        description = 'This is a demo package',
#        author = 'Martin v. Loewis',
#        author_email = 'martin@v.loewis.de',
#        url = 'https://docs.python.org/extending/building',
#        long_description = '''
# This is really just a demo package.
# ''',
#        ext_modules = [module1])


setup (name = 'Bitprim',
       version = '1.0',
       description = 'Bitprim Full-Node Bitcoin library',
       ext_modules = [module1])



#
# running build
# running build_ext
# building 'bitprim' extension
# x86_64-linux-gnu-gcc -pthread -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fno-strict-aliasing -Wdate-time -D_FORTIFY_SOURCE=2 -g -fdebug-prefix-map=/build/python2.7-ZZaKJ6/python2.7-2.7.13=. -fstack-protector-strong -Wformat -Werror=format-security -fPIC -I/home/fernando/dev/bitprim/bitprim-node-cint/include -I/usr/include/python2.7 -c bitprimmodule.c -o build/temp.linux-x86_64-2.7/bitprimmodule.o
# x86_64-linux-gnu-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-Bsymbolic-functions -Wl,-z,relro -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -Wdate-time -D_FORTIFY_SOURCE=2 -g -fdebug-prefix-map=/build/python2.7-ZZaKJ6/python2.7-2.7.13=. -fstack-protector-strong -Wformat -Werror=format-security -Wl,-Bsymbolic-functions -Wl,-z,relro -Wdate-time -D_FORTIFY_SOURCE=2 -g -fdebug-prefix-map=/build/python2.7-ZZaKJ6/python2.7-2.7.13=. -fstack-protector-strong -Wformat -Werror=format-security build/temp.linux-x86_64-2.7/bitprimmodule.o -L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug -lbitprim-node-cint -o build/lib.linux-x86_64-2.7/bitprim.so
# /usr/bin/ld: /home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug/libbitprim-node-cint.a(executor_c.cpp.o): relocation R_X86_64_PC32 against symbol `stderr@@GLIBC_2.2.5' can not be used when making a shared object; recompile with -fPIC
# /usr/bin/ld: final link failed: Bad value
# collect2: error: ld returned 1 exit status
# error: command 'x86_64-linux-gnu-gcc' failed with exit status 1
#
#

