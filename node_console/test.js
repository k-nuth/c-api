// test.js

// Windows: Se necesita Python 2.7 y MSVC
//
// npm install -g node-gyp
//
// node-gyp configure
// node-gyp build
// node test.js


const bitprim = require('./bitprim.js');

bitprim.open("/home/fernando/exec/btc-mainnet.cfg", function (exec) {
    // console.log('open callback')
    // exec.initchain()
    exec.run_wait()
});


