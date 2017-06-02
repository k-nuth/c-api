import sys
import bitprim

# ------------------------------------------------------

class Executor:
    def __init__(self, path, sin, sout, serr):
        self.executor = bitprim.construct(path, sin, sout, serr)
        self.constructed = True
        self.running = False

    def destroy(self):
        print('destroy')

        if self.constructed:
            if self.running:
                self.stop()

            bitprim.destruct(self.executor)
            self.constructed = False

    def __del__(self):
        print('__del__')
        self.destroy()

    def run(self):
        ret = bitprim.run(self.executor)

        if ret:
            self.running = True

        return ret

    def stop(self):
        # precondition: self.running
        ret = bitprim.stop(self.executor)

        if ret:
            self.running = False

        return ret

    def init_chain(self):
        return bitprim.initchain(self.executor)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        print('__exit__')
        self.destroy()

# ------------------------------------------------------

# class ExecutorResource:
#     def __enter__(self):
#         class Executor:
#             ...
#         self.package_obj = Package()
#         return self.package_obj
#     def __exit__(self, exc_type, exc_value, traceback):
#         self.package_obj.cleanup()

# ------------------------------------------------------
# Main Test
# ------------------------------------------------------
# with Executor(1, 2, 3, 4) as exec:
#     exec.run()
#     exec.initchain()
# ------------------------------------------------------



# ------------------------------------------------------
# Main Real
# ------------------------------------------------------

with Executor("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdin, sys.stdout, sys.stderr) as executor:
    print("before run")
    # res = executor.initchain()
    res = executor.run()
    print("********************************* AFTER run *********************************")
    print(res)





# # ------------------------------------------------------
# # Main Real
# # ------------------------------------------------------
#
# executor = bitprim.construct("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdin, sys.stdout, sys.stderr)
#
# # res = bitprim.initchain(executor)
#
# print("before run")
#
# res = bitprim.run(executor)
#
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
# # print("********************************* AFTER run *********************************")
#
# print(res)
#
#
# bitprim.destruct(executor)