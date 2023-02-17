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
    * [Scanner] Function call ⚠️ _In Progress_
        * Function arguments
        * Function call
        * Nested function calls (_Note: don't forget to align the stack- 16 bytes?_)
    * [Scanner] Assignment, sort of
        * Recognize non-function identifiers, some sort of stub
        * Assignment operator (_Remember to filter out rvalues_)
    * [NEW Parser] Statements
    * [🧪] Test adjustments / additions ⚠️ _In progress_
* **0.4** - Declaration and assignment (Types 1)
* **0.5** - `if` / `else`
* **0.6** - `while` / `do-while` / `for` 😎
* **0.7** - Functions ?
* **0.8** - Types 2
    * Types-parsing class?¿
* **0.9** - Miscellaneous things, preprocessor, comments?
* **1.0**

## Example

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

```
~$ ./test --help
./test v0.2
Usage:
        ./test [option]

 -h / --help           Bring up this help info
 -v / --version        Exit after printing version info
 --expgen              Run just the expgen test
 (no option)           Run the full test suite
```

The test suite consists of two parts, the first being a series of hard-coded strings given to the compiler, that fall into three categories:
* _Test cases_ are ran, and the output is shown, to manually confirm correctness
* _Error cases_ are expected to fail. _Not_ failing causes the error case to fail
* _Test cases with output_ are ran, assembled, and the resulting executable is run and output is compared against a hard-coded expected output.

The other piece of the test suite utilizes the `expgen` program to randomly generate mathematical expression input for the compiler.

## Acknowledgements

This project wouldn't exist without [Jack Crenshaw's compiler tutorial](https://compilers.iecc.com/crenshaw/).

`ncc` differs from Crenshaw's example `tiny` compiler, in that
* `ncc` is written in C++, `tiny` is written in Pascal
* `ncc` outputs x86 assembly, `tiny` outputs 68000
* `ncc`'s goal is to parse C code, `tiny` parses tutorial-specific "kiss" (keep it simple, stupid)

However, they both
* Use the [recursive descent](https://en.wikipedia.org/wiki/Recursive_descent_parser) algorithm
* Use a similar structure
