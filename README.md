# Qemu

This is brutal fork of qemu. 

# Building

See qemu [building dependencies](https://wiki.qemu.org/Hosts/Linux) and you can just run (for x86 support) :
```sh
mkdir -p build
cd build
../configure --target-list=x86_64-softmmu --enable-debug
make all -j$(nproc)
```

and you can run:

```sh
sudo make install
```
if you want this version of qemu installed.

# Changes

This fork add:

- dump-stackframe {x}:
   - allows to dump the stackframe at an address or using the RBP register (only for x86-64)
