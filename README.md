# brainfuck

Brainfuck interpreter written in C, with Windows and Android build guidance, optional fast clearing loops, numeric arithmetic shorthand, and execution telemetry for memory heatmaps.

This repository is maintained by [ERRORGITYT](https://github.com/ERRORGITYT), based on the upstream project [fabianishere/brainfuck](https://github.com/fabianishere/brainfuck).

## Usage

```text
brainfuck [-veh] file...
    -e, --eval       run code directly
    -v, --version    show version information
    -h, --help       show a help message
```

Run the interactive console by passing no arguments.

```sh
brainfuck examples/hello.bf
brainfuck --eval '++++++++[>++++++++<-]>+.+.'
cat examples/hello.bf | brainfuck
```

## Numeric shorthand

A decimal count may follow `+` or `-`. The parser treats the count as repeated arithmetic operations while preserving ordinary Brainfuck syntax:

```sh
brainfuck --eval '+1.+10.-3.'
```

The program outputs the cell values `1`, `11`, and `8`. `+` and `-` without a number continue to mean one increment or decrement. Counts are capped by the parser to avoid unbounded expansion from accidental input.

## C API

The library can be embedded in another C program. Read any telemetry before destroying the execution context:

```c
#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>

int main(void) {
    BrainfuckState *state = brainfuck_state();
    BrainfuckExecutionContext *context = brainfuck_context(BRAINFUCK_TAPE_SIZE);
    BrainfuckInstruction *instruction = brainfuck_parse_string(",+++++.");

    brainfuck_add(state, instruction);
    brainfuck_execute(state->root, context);

    /* The counters are valid until brainfuck_destroy_context(). */
    printf("cell 0 accesses: %llu\n",
           (unsigned long long) context->tape_accesses[0]);
    printf("total tape accesses: %llu\n",
           (unsigned long long) context->total_tape_accesses);

    brainfuck_destroy_context(context);
    brainfuck_destroy_state(state);
    return EXIT_SUCCESS;
}
```

During execution, `context->tape_accesses[i]` records how many executed instructions selected tape cell `i`, while `context->total_tape_accesses` records the aggregate count. These counters are intended for profilers, debuggers, and memory heatmaps.

## Examples

The [`examples/`](https://github.com/ERRORGITYT/brainfuck/tree/master/examples) directory contains Brainfuck programs. Original authors are credited where known.

## Getting the source

Clone the public repository with Git or GitHub CLI:

```sh
gh repo clone ERRORGITYT/brainfuck
# or
git clone https://github.com/ERRORGITYT/brainfuck.git
```

To inspect the upstream implementation and history, visit [fabianishere/brainfuck](https://github.com/fabianishere/brainfuck).

## Building and testing

The quickest local workflow is:

```sh
make
make test
```

To run an example:

```sh
make run FILE=examples/hello.bf
```

For a manual CMake build, Brainfuck requires CMake and a C compiler. The desktop CLI can use [libedit](http://thrysoee.dk/editline/), but the portable build below disables that optional dependency:

```sh
cmake -S . -B build -DBUILD_TESTING=ON -DENABLE_EDITLINE=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

### Windows

Use Visual Studio or MinGW with CMake. Editline is disabled automatically on Windows:

```powershell
cmake -S . -B build -A x64 -DENABLE_EDITLINE=OFF
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

The bundled `getopt` compatibility header is used when the platform does not provide `getopt`.

### Android

The interpreter core can be built with the Android NDK. The desktop CLI and editline console are disabled automatically for Android builds. See [`android/README.md`](https://github.com/ERRORGITYT/brainfuck/tree/master/android) for NDK and ABI guidance.

## Releases

Stable source releases are published on the [GitHub Releases page](https://github.com/ERRORGITYT/brainfuck/releases). The current consolidated release is [v2.8.0](https://github.com/ERRORGITYT/brainfuck/releases/tag/v2.8.0).

## License

The code is released under the [Apache License 2.0](LICENSE.txt).

## Contributors and repository history

Some contributors shown by GitHub are authors from the inherited upstream commit history. They are included for historical attribution and are not necessarily contributors to the changes made in this repository.

Fork-specific changes by ERRORGITYT include the quality-of-life improvements, Windows and Android support, numeric shorthand, fast loops, tape access counters, memory heatmap telemetry, and documentation updates.

For the upstream contributor history, see the [upstream repository](https://github.com/fabianishere/brainfuck) and its [contributors page](https://github.com/fabianishere/brainfuck/graphs/contributors). Contributions and pull requests to this public repository are welcome.

```text
Maintained by ERRORGITYT · upstream history preserved
```

<!--
  Note for maintainers: do not add a manually copied contributor list here.
  Git history and GitHub's contributors view are the source of truth.
-->
