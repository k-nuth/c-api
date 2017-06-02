// test.js

const bitprim = require('./bitprim.js');

bitprim.open("/home/fernando/exec/btc-mainnet.cfg", function (exec) {
    // exec.initchain()
    exec.run()
});


