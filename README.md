# ncc4

Four strikes, you're out, or something... 👽

```
$ ./ncc --version
ncc v0.0
```

## Version Planning

* **0.1** - General setup and parse a single-digit integer ⚠️ _In Progress_
    * CMake ✅
    * Git[hub] ✅
    * Doxygen ✅
    * Parse a single-digit number ✅
    * IO logging ✅
    * Test setup ✅
* **0.2** - Integer parsing and mathematical expressions
* **0.3** - General expressions, including function calls
* **0.4** - Declaration and assignment
* **0.5** - `if`/`else`, maybe loops too
* ...
* **1.0**

## Test Suite

Particularly proud of this 😁

```
~$ ./test 
./test v0.0

Test Case "ParseNumber"
Input:
>>> 5
Output:
>>> movq $5, %rax

Test Case "ParseNumberWithExtra"
Input:
>>> 5a
Output:
>>> movq $5, %rax

Test Case "ParseNumberLeadingWs"
Input:
>>>      5
Output:
>>> movq $5, %rax

Error Case "ParseNumberError"
Input:
>>> Error
Error Message:
>>> expected number [current = 69 (ascii)]

Test Case "ParseLongNumber"
Input:
>>> 90210
Output:
>>> movq $9, %rax

Passed 5 / 5 tests
```

## IO Logging

```
~$ echo "4" > input.c
~$ ./ncc < input.c 
    .globl   _main
_main:
    pushq    %rbp
    movq     %rsp, %rbp
    subq     $16, %rsp

    movq     $4, %rax

    leaq     S0(%rip), %rdi
    movq     %rax, %rsi
    callq    _printf
    movq     $0, %rax
    addq     $16, %rsp
    popq     %rbp
    retq
S0:
    .asciz "%ld\n"

~$ cat ncc.log 
void ncc::io::init(std::istream &, std::os...: Initialized
                         char ncc::io::read(): Read '4' from input
     ncc::Scanner::Scanner(ncc::Controller *): Scanner initialized, current = 52 (ascii)
             void ncc::io::write(std::string): Writing instruction ".globl _main"
               void ncc::io::put(std::string): Writing "_main:(newline)"
             void ncc::io::write(std::string): Writing instruction "pushq %rbp"
             void ncc::io::write(std::string): Writing instruction "movq %rsp, %rbp"
             void ncc::io::write(std::string): Writing instruction "subq $16, %rsp"
               void ncc::io::put(std::string): Writing "(newline)"
                         char ncc::io::read(): Read '(newline)' from input
                         char ncc::io::read(): Read '(EOF)' from input
             void ncc::io::write(std::string): Writing instruction "movq $4, %rax"
               void ncc::io::put(std::string): Writing "(newline)"
             void ncc::io::write(std::string): Writing instruction "leaq S0(%rip), %rdi"
             void ncc::io::write(std::string): Writing instruction "movq %rax, %rsi"
             void ncc::io::write(std::string): Writing instruction "callq _printf"
             void ncc::io::write(std::string): Writing instruction "movq $0, %rax"
             void ncc::io::write(std::string): Writing instruction "addq $16, %rsp"
             void ncc::io::write(std::string): Writing instruction "popq %rbp"
             void ncc::io::write(std::string): Writing instruction "retq"
               void ncc::io::put(std::string): Writing "S0:(newline)    .asciz "%ld\n"(newline)"
                 int main(int, const char **): Exiting successfully

```
