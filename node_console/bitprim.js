// bitprim.js

const bitprim_native = require('./build/Release/bitprim');

function ExecutorResource (executor) {
    this.executor = executor;
}

ExecutorResource.prototype.initchain = function() {
    return bitprim_native.initchain(this.executor);
};

// ExecutorResource.prototype.run = function() {
//     return bitprim_native.run(this.executor);
// };

ExecutorResource.prototype.run_wait = function() {
    return bitprim_native.run_wait(this.executor);
};



function open(path, cb) {

    console.log('before bitprim_native.construct')
    const executor_native = bitprim_native.construct(path, process.stdout, process.stderr);
    console.log('after bitprim_native.construct')

    cb(new ExecutorResource(executor_native));

    bitprim_native.destruct(executor_native);
}

module.exports = {
    open: open
};