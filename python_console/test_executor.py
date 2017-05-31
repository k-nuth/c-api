import sys
import bitprim

executor = bitprim.construct("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdin, sys.stdout, sys.stderr)
bitprim.initchain(executor)
bitprim.destruct(executor)