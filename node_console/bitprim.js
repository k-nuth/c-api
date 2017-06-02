// bitprim.js

const bitprim_native = require('./build/Release/bitprim');

function ExecutorResource (executor) {
    this.executor = executor;
}

ExecutorResource.prototype.run = function() {
    return bitprim_native.run(this.executor);
};

ExecutorResource.prototype.initchain = function() {
    return bitprim_native.initchain(this.executor);
};

function open(path, cb) {
    const executor_native = bitprim_native.construct(path, process.stdin, process.stdout, process.stderr);

    cb(new ExecutorResource(executor_native));

    bitprim_native.destruct(executor_native);
}

module.exports = {
    open: open
};