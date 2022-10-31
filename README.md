# ncc4

Four strikes, you're out, or something... 👽

```
$ ./ncc --version
ncc v0.1
```

This project wouldn't exist without [Jack Crenshaw's compiler tutorial](https://compilers.iecc.com/crenshaw/). Although the compiled language and target assembly language differ, I've applied a lot of the conceptual structure Crenshaw presents.

Links: [Order of operations](https://en.cppreference.com/w/c/language/operator_precedence)

## Version Planning

* **0.1** - General setup and parse a single-digit integer ✅
* **0.2** - Integer parsing, mathematical expressions ⚠️ _In Progress_
    * Multi-digit integers ✅
    * Negative numbers ✅
    * Plus / minus ✅
    * Multiply / divide / modulus ✅
    * Parenthesis
    * 🛠 Tool- Expression generator
    * 🧪 Testing- Allow actual assembling of generated code! ✅
* **0.3** - General expressions, including function calls, and statements
    * New lightweight class "Parser" could be introduced here to support statements
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

## Test Suite

```
~$ ./test 
./test v0.1

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

6) Test Case "ParseLongNumber"
Input:
>>> 90210
Output:
>>> movq $90210, %rax

7) Test Case "MixedChars"
Input:
>>> 123abc456
Output:
>>> movq $123, %rax

8) Test Case "NegativeInt"
Input:
>>> -5
Output:
>>> movq $-5, %rax

9) Test Case "NegativeInt2"
Input:
>>> -456
Output:
>>> movq $-456, %rax

10) Error Case "UnaryMinus"
Input:
>>> -
Error Output:
>>> ## expected number [next = '?']

11) Error Case "MinusSignExtra"
Input:
>>> -a
Error Output:
>>> ## expected number [next = 'a']

12) Assembled Test Case "Add"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 1+2
Output:
>>> 3
Cleaning up...

13) Test Case "UnaryPlus"
Input:
>>> +
Output:

14) Assembled Test Case "Add2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 123 + 456
Output:
>>> 579
Cleaning up...

15) Assembled Test Case "Sub"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5 - 4
Output:
>>> 1
Cleaning up...

16) Assembled Test Case "Sub2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 10 - 15
Output:
>>> -5
Cleaning up...

17) Assembled Test Case "AddAndSub"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 4 + 5 - 3
Output:
>>> 6
Cleaning up...

18) Assembled Test Case "Mult"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 2 * 4
Output:
>>> 8
Cleaning up...

19) Error Case "AddAdd"
Input:
>>> 2 + +
Error Output:
>>> movq $2, %rax
>>> pushq %rax
>>> ## expected non-operator [next = '?']

20) Assembled Test Case "OrderOfOps"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 3 * 2 + 2 * 2
Output:
>>> 10
Cleaning up...

21) Assembled Test Case "MultiMult"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5 * 4 * 3 * 2 * 1
Output:
>>> 120
Cleaning up...

22) Assembled Test Case "Divide"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 10 / 5
Output:
>>> 2
Cleaning up...

23) Assembled Test Case "NestedDiv"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 100 / 2 / 10 / 5
Output:
>>> 1
Cleaning up...

24) Assembled Test Case "Mod"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 12 % 5
Output:
>>> 2
Cleaning up...

25) Assembled Test Case "Mod2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 19 % 10 % 7
Output:
>>> 2
Cleaning up...

Passed 25 / 25 tests
```
