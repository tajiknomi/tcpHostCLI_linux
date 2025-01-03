## What problem does it solve?
nc excels at reverse connections handling but couldn't handle multiple connections on single port/terminal. This tool offers a more convenient way to manage and switch between numerous sessions/clients using a single port and terminal.
This simplifies the handling of multiple connections.

## Quick Start
Download the latest version from the [release section](https://github.com/tajiknomi/tcpHostCLI_linux/releases)
```
$ ./tcphost <PORT>
```

## Example of usage
#### Show help menu
```
!
```
#### Show active session list
```
!list
```
#### If you want to switch b/w active sessions, e.g. switch to session 2
```
!2
```
#### Clear the terminal screen
```
!clear
```
#### Upgrade to tty
```
!tty py          // using python
!tty py3         // using python3
!tty perl        // using perl
```
#### Close the current session (i.e. disconnect from the current session/client)
```
!close
```
#### Quit the program
```
!quit
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



