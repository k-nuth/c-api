# Executor

Defined in header `<bitprim/nodecint/executor_c.h>`

Controls the execution of a Bitprim crypto node.

## Construction

`executor_t executor_construct(char const* path, FILE* sout, FILE* serr);`

### Parameters:
- path: file path of the configuration file
- sout: output file stream of type `FILE*` where the node will print the logging information.
If sout is `NULL` the node will not print anything.
Typical use is to pass `stdout` defined in the standard header `<stdio.h>`.
- serr: error file stream of type `FILE*` where the node will print the logging information.
If sout is `NULL` the node will not print anything.
Typical use is to pass `stderr` defined in the standard header `<stdio.h>`.

### Return value:

An `executor_t` object that is capable to run a Bitprim crypto full-node.

### Notes:



`executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd);`


#if defined(_WIN32)

`executor_t executor_construct_handles(char const* path, void* sout, void* serr);`

#endif /* defined(_WIN32) */

### Destruction
`void executor_destruct(executor_t exec);`

`int executor_initchain(executor_t exec);`


`void executor_run(executor_t exec, void* ctx, run_handler_t handler);`


`void executor_init_and_run(executor_t exec, void* ctx, run_handler_t handler);`


`int executor_run_wait(executor_t exec);`


`int executor_init_and_run_wait(executor_t exec);`

`int executor_stop(executor_t exec);`

`int executor_stopped(executor_t exec);`

`chain_t executor_get_chain(executor_t exec);`

`p2p_t executor_get_p2p(executor_t exec);`

`char const* executor_version(void);`

`int executor_load_config_valid(executor_t exec);`
