brainfuck
[![Build Status](https://github.com/fabianishere/brainfuck/workflows/Build/badge.svg)](https://github.com/fabianishere/brainfuck/actions?query=workflow%3ABuild)
===========
Brainfuck interpreter written in C.

## Usage
    brainfuck [-veh] file...
	-e --eval	run code directly
	-v --version	show version information
	-h --help	show a help message.

The interactive console can be accessed by passing no arguments.    

Quick examples:
```sh
brainfuck examples/hello.bf
brainfuck --eval '++++++++[>++++++++<-]>+.+.'
cat examples/hello.bf | brainfuck
```

### Numeric shorthand
Cell and pointer operations accept a decimal count, which is expanded by the parser without changing classic Brainfuck syntax:

```sh
brainfuck --eval '+1.+10.-3.'
```

The example increments the first cell to `1`, then to `11`, then down to `8`. Plain `+`, `-`, `<`, and `>` remain fully compatible. Numeric shorthand is especially useful for readable experiments and generated programs.

We also provide a C api:

``` c
#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>
    
int main() {
	BrainfuckState *state = brainfuck_state();
	BrainfuckExecutionContext *context = brainfuck_context(BRAINFUCK_TAPE_SIZE);
	BrainfuckInstruction *instruction = brainfuck_parse_string(",+++++.");
 	brainfuck_add(state, instruction);
 	brainfuck_execute(state->root, context);
	brainfuck_destroy_context(context);
 	brainfuck_destroy_state(state);
	return EXIT_SUCCESS;
}
```

After execution, `context->tape_accesses[i]` contains the number of instruction-level accesses recorded for tape cell `i`, and `context->total_tape_accesses` contains the aggregate count. These counters are allocated with the execution context and are useful for profilers and memory heatmaps.

## Examples
The [examples/](/examples) directory contains a large amount of 
brainfuck example programs. We have tried to attribute the original
authors of these programs where possible.

## Getting the source
Download the source code by running the following code in your command prompt:
```sh
$ git clone https://github.com/fabianishere/brainfuck.git
```
or simply [grab](https://github.com/fabianishere/brainfuck/archive/master.zip) a copy of the source code as a Zip file.

## Building
The quickest way to build and test the project is with the included Makefile:
```sh
$ make
$ make test
```

The `run` target accepts a source file, for example `make run FILE=examples/hello.bf`.
For a manual CMake build, use the steps below.

### Windows
Use Visual Studio or MinGW with CMake:
```powershell
cmake -S . -B build -A x64 -DENABLE_EDITLINE=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```
The bundled `getopt` compatibility header is used automatically when the platform does not provide `getopt`.

### Android
The core library supports Android NDK builds. The CLI and editline console are optional; for Android applications, build the static library with `-DENABLE_CLI=OFF`. See [`android/README.md`](/android/README.md) for ABI-specific commands.

Create the build directory.
```sh
$ mkdir build
$ cd build
```
Brainfuck requires CMake and a C compiler (e.g. Clang or GCC) in order to run. It also depends on [libedit](http://thrysoee.dk/editline/), which is available in the main repositories of most Linux distributions (e.g. as [libedit-dev](https://packages.debian.org/stretch/libedit-dev) on Debian/Ubuntu) and comes with the macOS XCode command line tools. 
Then, simply create the Makefiles:
```sh
$ cmake ..
```
and finally, build it using the building system you chose (e.g. Make):
```sh
$ make
```

After the build has been finished, you may install the binaries to your local system (see [CMAKE\_INSTALL\_PREFIX](https://cmake.org/cmake/help/v3.0/variable/CMAKE_INSTALL_PREFIX.html) for information about the install prefix):
```sh
$ make install
```
Alternatively, you may run the interpreter directly without installation, for instance:
```sh
$ ./brainfuck ../examples/hello.bf
```

## License
The code is released under the Apache License version 2.0. See [LICENSE.txt](/LICENSE.txt).

## Contributors
	Fabian Mastenbroek https://github.com/fabianishere
	aliclubb https://github.com/aliclubb
	diekmann https://github.com/diekmann
	SevenBits https://github.com/SevenBits
	Alex Burka https://github.com/durka
	outis https://github.com/outis
	rien333 https://github.com/rien333
	boweiliu https://github.com/boweiliu
	Rotartsi https://github.com/ROTARTSI82
	Saket Upadhyay https://github.com/Saket-Upadhyay
	outis https://github.com/outis
	Jalmari91 https://github.com/Jalmari91
	Alok Singh https://github.com/alok
	Lasse Damsgaard Skaalum https://github.com/humleflue
