{
  "targets": [
    {
      "target_name": "bitprim",
      "sources": [ "bitprim_addon.cc" ],
      "include_dirs": ["/home/fernando/dev/bitprim/bitprim-node-cint/include"],
      "libraries": [ "-lbitprim-node-cint", "-L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug" ]
    }
  ]
}
