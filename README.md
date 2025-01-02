## Intro
netcat is mostly used for reverse connection but it's limited to handling only one connection at a time. This utility offers a more convenient way to manage multiple sessions/clients using a single port/terminal, allowing you to easily manage and switch b/w session/clients.

## Quick Start
Download the latest version from the release section
```
$ ./tcphost <PORT>
```

## How to build
1: CMake
```
$ cd tcpHostCLI_linux && mkdir build && cd build
$ cmake -DTARGET_ARCH=x86 ../ && make    //  for 32-bit version
$ cmake -DTARGET_ARCH=x64 ../ && make    // for 64-bit version
```
2: Using g++
```
$ cd tcpHostCLI_linux && mkdir build
$ g++ -std=c++17 -pthread -I include/ -m32 src/*.cpp -o build/tcphost_x86    // for 32-bit version
$ g++ -std=c++17 -pthread -I include/ -m64 src/*.cpp -o build/tcphost_x64    // for 64-bit version
```

## Screenshots


