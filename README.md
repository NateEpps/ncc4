# ncc4

Fourth time's the charm, right? 👽

```
~$ ./ncc --version
ncc v0.2
```
```
~$ ./ncc --help
ncc v0.2
Usage:
	./ncc [options OR see explanation]

 -h / --help            Bring up this help info
 -v / --version         Print version info
 --print-rax            Use PRINT_RAX scaffold. Defaults to MAIN
                        without this option.

When options are not present, ncc reads from standard input and
writes to standard output. ncc can be run interactively, but file
redirection is generally used for normal operation.
```

Links: [Order of operations](https://en.cppreference.com/w/c/language/operator_precedence)

## Version Planning

* **0.1** - General setup and parse a single-digit integer ✅
* **0.2** - Integer parsing, mathematical expressions ✅
* **0.3** - General expressions, including function calls, and statements ⚠️
    * [Scaffold] Scaffolding adjustments ✅
    * [Scanner] String literals ✅
    * [Scanner] Function call ⚠️
        * Function arguments ⚠️ _First draft_
        * Function call ✅
        * Nested function calls ❌ _Not yet_
            * _Note: don't forget to align the stack- 16 bytes?_
    * [Scanner] Assignment, sort of
        * Recognize non-function identifiers, some sort of stub
        * Assignment operator (_Remember to filter out rvalues_)
    * [NEW Parser] Statements
    * [🧪] Test refactor ✅ _see_ __Test Suite__ _section for more details_
        * Central class `ncc::test::TestController` ✅
        * Test fixture base class `ncc::test::Fixture` ✅
        * Iterate over a fixture with `ncc::test::FixtureIterator` ✅
        * `ncc::test::BasicFixture` ✅
        * `ncc::test::ErrorFixture` ✅
        * `ncc::test::FullPrintRaxFixture` ✅
        * `ncc::test::ExpgenFixture` ✅
        * `ncc::test::FullFixture` ✅
        * `ncc::test::FullMainFixture` ✅
        * Command-line interface ✅
    * [🧪] Test additions - _Added as needed_
* **0.4** - Declaration and assignment (Types 1)
* **0.5** - `if` / `else`
* **0.6** - `while` / `do-while` / `for` 😎
* **0.7** - Functions ?
* **0.8** - Types 2
    * Types-parsing class?¿
* **0.9** - Miscellaneous things, preprocessor, comments?
* **1.0**

## Examples

```
~$ cat input.c
printf("Hello, world!\n");
~$ ./ncc < input.c > output.s
~$ cat output.s
    .globl   _main
_main:
    pushq    %rbp
    movq     %rsp, %rbp
    subq     $16, %rsp

    leaq     S0(%rip), %rax
    movq     %rax, %rdi
    callq    _printf

    movq     $0, %rax
    addq     $16, %rsp
    popq     %rbp
    retq

S0:
    .asciz "Hello, world!\n"

~$ gcc output.s -o Output && ./Output
Hello, world!
```

```
~$ echo "1 + 2 * 3 - 4" > input.c
~$ ./ncc --print-rax < input.c > output.s
~$ cat output.s
    .globl   _main
_main:
    pushq    %rbp
    movq     %rsp, %rbp
    subq     $16, %rsp

    movq     $1, %rax
    pushq    %rax
    movq     $2, %rax
    pushq    %rax
    movq     $3, %rax
    popq     %r10
    imulq    %r10
    popq     %r10
    addq     %r10, %rax
    pushq    %rax
    movq     $4, %rax
    popq     %r10
    subq     %r10, %rax
    negq     %rax

    leaq     S0(%rip), %rdi
    movq     %rax, %rsi
    callq    _printf
    movq     $0, %rax
    addq     $16, %rsp
    popq     %rbp
    retq

S0:
    .asciz "%ld\n"

~$ gcc output.s -o Output && ./Output
3
```

## Expression Generator

```
~$ ./expgen --help
Usage:
    ./expgen (seed) (iterations)

~$ ./expgen 50 3
(((5 * 19) + (10 / 2)) / ((4 + 0) / (8 - 6)))
```

Given a _seed_ and a number of _iterations_, randomly generate a mathematical expression that evaluates to _seed_.

`expgen` in action:
```
~$ ./expgen 100 10 > input.c
~$ ./ncc --print-rax < input.c > output.s
~$ gcc output.s -o Output && ./Output
100
```
```
~$ cat input.c | wc -c
    6413
~$ cat output.s | wc -l
    5107
~$ cat ncc.log | wc -l
   11522
```

## Test Suite

```
~$ ./test --help
Usage:
      ./test [option, specific fixture, OR nothing]

  --list / -l          List all test fixtures
  --help / -h          Bring up this help info
  (Specific fixture)   Run just the named fixture
  (Nothing)            Run the full test suite
```
```
~$ ./test --list && ./test --list | wc -l
Basic
Error
FullPrintRax
Expgen
FullMain
       5
```

The test suite is comprised of various _fixtures_ (see `ncc::test::Fixture`), each fixture representing a type of test. Each fixture has associated test cases. Fixtures that run actual executables on hardware require C `system` function availability, fairly basic `gcc` functionality, and a sane shell. Currently developing on MacOS 12.5.1. May expand support to Linux in some form eventually-- see Github issue #20. See output from `./test --help` for command line interface info. May look into [CTest](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html) integration ⚠️.

### Fixtures

* `ncc::test::BasicFixture` ✅ - Run valid input through compiler and print generated assembly
* `ncc::test::ErrorFixture` ✅ - Run invalid input through compiler. Running valid code is an error.
* `ncc::test::FullPrintRaxFixture` ✅ - Run valid input through compiler with `--print-rax` option, create and run resulting executable on hardware, and check result.
* `ncc::test::ExpgenFixture` ✅ - Use `expgen` program to generate various mathematical expressions, and then test via `ncc::test::FullPrintRaxFixture`.
* `ncc::test::FullFixture` ✅ - Pseudo-fixture that runs basic file IO logic.
* `ncc::test::FullMainFixture` ✅ - Run valid input through compiler with `MAIN` scaffolding, create and run resulting executable on hardware, and check result.
* `ncc::test::FullScaffoldlessFixture` ⚠️ _Not yet needed_ - As the name implies, no scaffolding. This is a long way off, won't be needed until around **0.7**.

## Acknowledgements

This project wouldn't exist without [Jack Crenshaw's compiler tutorial](https://compilers.iecc.com/crenshaw/).

`ncc` differs from Crenshaw's example `tiny` compiler, in that
* `ncc` is written in C++, `tiny` is written in Pascal
* `ncc` outputs x86 assembly, `tiny` outputs 68000
* `ncc`'s goal is to parse C code, `tiny` parses tutorial-specific "kiss" (keep it simple, stupid)

However, they both
* Use the [recursive descent](https://en.wikipedia.org/wiki/Recursive_descent_parser) algorithm
* Use a similar structure
