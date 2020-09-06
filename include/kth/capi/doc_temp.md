# Node

Defined in header `<kth/capi/node.h>`

Controls the execution of a Knuth crypto node.

## Construction

`kth_node_t kth_node_construct(char const* path, FILE* sout, FILE* serr);`

### Parameters:
- path: file path of the configuration file
- sout: output file stream of type `FILE*` where the node will print the logging information.
If sout is `NULL` the node will not print anything.
Typical use is to pass `stdout` defined in the standard header `<stdio.h>`.
- serr: error file stream of type `FILE*` where the node will print the logging information.
If sout is `NULL` the node will not print anything.
Typical use is to pass `stderr` defined in the standard header `<stdio.h>`.

### Return value:

An `kth_node_t` object that is capable to run a Knuth crypto full-node.

### Notes:



`kth_node_t kth_node_construct_fd(char const* path, int sout_fd, int serr_fd);`


#if defined(_WIN32)

`kth_node_t kth_node_construct_handles(char const* path, void* sout, void* serr);`

#endif /* defined(_WIN32) */

### Destruction
`void kth_node_destruct(kth_node_t exec);`

`int kth_node_initchain(kth_node_t exec);`


`void kth_node_run(kth_node_t exec, void* ctx, kth_run_handler_t handler);`


`void kth_node_init_and_run(kth_node_t exec, void* ctx, kth_run_handler_t handler);`


`int kth_node_run_wait(kth_node_t exec);`


`int kth_node_init_and_run_wait(kth_node_t exec);`

`int kth_node_stop(kth_node_t exec);`

`int kth_node_stopped(kth_node_t exec);`

`kth_chain_t kth_node_get_chain(kth_node_t exec);`

`kth_p2p_t kth_node_get_p2p(kth_node_t exec);`

`char const* kth_node_version(void);`
