// test.js
const bitprim = require('./build/Release/bitprim');

// ----------------------------------------------------

const executor = bitprim.construct("hola", process.stdin, process.stdout, process.stderr);
// bitprim.initchain(executor);
bitprim.run(executor);
bitprim.destruct(executor);

// addon.change_data(external_int_ptr);
// console.log(addon.receive_data(external_int_ptr));

// ----------------------------------------------------
