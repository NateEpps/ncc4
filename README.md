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

When options are not present, ncc reads from standard input and
writes to standard output. ncc can be run interactively, but file
redirection is generally used for normal operation.
```

Links: [Order of operations](https://en.cppreference.com/w/c/language/operator_precedence)

## Version Planning

* **0.1** - General setup and parse a single-digit integer ✅
* **0.2** - Integer parsing, mathematical expressions ✅
    * Multi-digit integers ✅
    * Negative numbers ✅
    * Plus / minus ✅
    * Multiply / divide / modulus ✅
    * Parenthesis ✅
    * [🧪] Testing- Allow actual assembling of generated code! ✅
    * [🛠] Expression Generator ✅
    * [🧪][🛠] Integrate `expgen` and tests ✅
* **0.3** - General expressions, including function calls, and statements
    * New lightweight class "Parser" could be introduced here to support multiple statements
* **0.4** - Declaration and assignment (Types 1)
* **0.5** - `if` / `else`
* **0.6** - `while` / `do-while` / `for` 😎
* **0.7** - Functions ?
* **0.8** - Types 2
    * Types-parsing class?¿
* **0.9** - Preprocessor, comments?
* **1.0**

## Example

```
~$ echo "1 + 2 * 3 - 4" > input.c
~$ ./ncc < input.c > output.s
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
~$ ./ncc < input.c > output.s
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

## Acknowledgements

This project wouldn't exist without [Jack Crenshaw's compiler tutorial](https://compilers.iecc.com/crenshaw/).

`ncc` differs from Crenshaw's example `tiny` compiler, in that
* `ncc` is written in C++, `tiny` is written in Pascal
* `ncc` outputs x86 assembly, `tiny` outputs 68000
* `ncc`'s goal is to parse C code, `tiny` parses tutorial-specific "kiss" (keep it simple, stupid)

However, they both
* Use the [recursive descent](https://en.wikipedia.org/wiki/Recursive_descent_parser) algorithm
* Use a similar structure

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

_Part of an example run..._
```
~$ ./test 
./test v0.2

1) Test Case "ParseNumber"
Input:
>>> 5
Output:
>>> movq $5, %rax

2) Assembled Test Case "ParseNumber2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5
Output:
>>> 5
Cleaning up...

3) Test Case "ParseNumberWithExtra"
Input:
>>> 5a
Output:
>>> movq $5, %rax

4) Test Case "ParseNumberLeadingWs"
Input:
>>>      5
Output:
>>> movq $5, %rax

5) Error Case "ParseNumberError"
Input:
>>> Error
Error Output:
>>> ## expected operator [next = 'E']

...

Passed 29 / 29 tests

Expgen test...
==============

>>> expgen 5 0
5
>>> Running ncc...
>>> Assembling with gcc...
>>> Running and getting output...
>>> Result: 5
>>> Expected: 5
>>> PASS

>>> expgen 5 1
(-5 + 10)
>>> Running ncc...
>>> Assembling with gcc...
>>> Running and getting output...
>>> Result: 5
>>> Expected: 5
>>> PASS

...

>>> expgen 8 8
((((((((22 / 2) - (10 / 2)) - ((0 + 5) + (-8 + 8))) * (((12 / 2) / (12 - 10)) - ((25 / -5) + (13 - 6)))) * ((((70 / 2) - (3 + 6)) + ((1 * 9) - (-2 + 3))) / (((1 * 9) - (5 + 3)) * ((8 / 2) / (4 - 2))))) - (((((-8 + 9) * (1 / 1)) * ((1 * 4) / (-5 + 7))) - (((1 * 1) * (1 * 1)) * ((-3 + 4) / (1 * 1)))) * ((((20 / 2) / (4 - 2)) - ((1 * 3) + (-2 + 9))) + (((8 - 7) / (11 - 10)) * ((2 * 6) / (9 - 7)))))) + ((((((11 - 9) * (14 - 7)) + ((8 / 2) + (-2 + 8))) - (((2 * 5) / (4 / 2)) + ((1 * 3) - (-2 + 4)))) / ((((10 - 10) + (-8 + 10)) - ((16 / -4) + (-3 + 7))) - (((6 / 2) - (4 / 2)) * ((9 - 8) * (1 * 0))))) - (((((124 / 2) / (-2 + 4)) - ((2 * 7) / (4 / 2))) / (((7 - 6) * (8 / 2)) - ((-1 + 7) - (1 * 4)))) - ((((21 - 7) / (4 / 2)) - ((-6 + 7) * (2 + 7))) + (((16 + 5) - (20 / 2)) - ((24 / 2) / (4 / 2))))))) / (((((((1 * 2) * (18 / 2)) - ((-1 - 5) + (17 - 7))) - (((-6 + 8) * (2 * 4)) / ((1 * 2) + (1 * 0)))) - ((((4 - 3) * (1 * 1)) * ((24 / 2) / (2 + 0))) - (((9 - 8) * (4 / 2)) - ((7 - 6) / (1 / 1))))) * (((((1 * 7) + (1 * 3)) - ((1 / 1) * (-1 + 10))) * (((18 - 0) / (4 / 2)) - ((2 + 5) - (11 - 7)))) / ((((2 * 8) / (4 / 2)) / ((8 - 0) - (8 - 2))) / (((1 / 1) * (9 - 5)) / ((1 * -5) + (-2 + 9)))))) - ((((((64 / -8) + (3 + 6)) / ((-1 - 8) + (2 * 5))) * (((-8 + 9) * (1 * 17)) - ((21 - 6) - (17 - 10)))) - ((((2 - 1) * (1 * 1)) * ((4 + 3) - (-2 + 8))) * (((28 - 4) / (-4 + 6)) / ((19 - 9) - (16 / 2))))) - (((((1 * 1) * (1 * -12)) + ((3 * 5) - (8 + 0))) + (((26 - 6) - (4 + 4)) / ((2 + 0) - (1 * 0)))) + ((((12 - 1) - (2 * 5)) * ((1 * 1) * (1 * -2))) + (((-11 + 0) + (1 * 9)) + ((-8 + 5) + (-1 + 9))))))))
>>> Running ncc...
>>> Assembling with gcc...
>>> Running and getting output...
>>> Result: 8
>>> Expected: 8
>>> PASS

expgen test succeeded
```
