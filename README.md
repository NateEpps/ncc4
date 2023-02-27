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
    * [🧪] Test refactor ⚠️ _In progress_
        * Central class `ncc::test::System` ✅
        * Test fixture base class `ncc::test::Fixture` ✅
        * Iterate over a fixture with new `ncc::test::FixtureIterator` ✅ - _Keep an eye out for instability_
        * Fixtures ⚠️
            * `ncc::test::BasicFixture` ✅
            * `ncc::test::ErrorFixture` ✅
            * Will carry over:
                * `ncc::test::FullPrintRaxFixture` - Original `TEST_CASE_WITH_OUTPUT`'s
                * `ncc::test::ExpgenFixture` - `expgen` test will convert to this
            * New:
                * `ncc::test::FullMainFixture` - Newer `TEST_CASE_WITH_OUTPUT`'s
            * If needed:
                * `ncc::test::ExceptionFixture` - I don't think we'll need this
                * `ncc::test::TimeoutFixture` - I think I've covered these sorts of cases already, but if I can find anything...
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
_5107 lines of assembly... I'd hate to have to debug that!_

## Test Suite

_Major overhaul in progress. See_ **Version Planning** _for more info._

## Acknowledgements

This project wouldn't exist without [Jack Crenshaw's compiler tutorial](https://compilers.iecc.com/crenshaw/).

`ncc` differs from Crenshaw's example `tiny` compiler, in that
* `ncc` is written in C++, `tiny` is written in Pascal
* `ncc` outputs x86 assembly, `tiny` outputs 68000
* `ncc`'s goal is to parse C code, `tiny` parses tutorial-specific "kiss" (keep it simple, stupid)

However, they both
* Use the [recursive descent](https://en.wikipedia.org/wiki/Recursive_descent_parser) algorithm
* Use a similar structure
