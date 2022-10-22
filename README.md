# ncc4

Four strikes, you're out, or something... 👽

```
$ ./ncc --version
ncc v0.1
```

## Version Planning

Links: [Order of operations](https://en.cppreference.com/w/c/language/operator_precedence)

* **0.1** - General setup and parse a single-digit integer ✅
* **0.2** - Integer parsing and mathematical expressions ⚠️ _In Progress_
    * Multi-digit integers ✅
    * Negative numbers ✅
    * Plus / minus ✅
    * Multiply ✅ / divide / modulus
    * Parenthesis
    * Tool- Expression generator ❗️
    * Testing- Allow actual assembling of generated code! ✅
* **0.3** - General expressions, including function calls
* **0.4** - Declaration and assignment (Types 1)
* **0.5** - `if`/`else`
    * Involve a new class at this point? `ncc::Scanner` will be handling expressions and declaration/assignment already. Something along the lines of "Parser", higher level then Scanner but member of `ncc::Controller`
* **0.6** - `while`/`do-while`/`for` 😎
* **0.7** - Functions ?
* **0.8** - Types 2
    * Types-parsing class?¿
* **0.9** - Preprocessor, comments?
* **1.0**

## Test Suite

```
~$ ./test 
./test v0.1

Test Case "ParseNumber"
Input:
>>> 5
Output:
>>> movq $5, %rax

Assembled Test Case "ParseNumber2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5
Output:
>>> 5
Cleaning up...

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
Error Output:
>>> ## expected operator [next = 'E']

Test Case "ParseLongNumber"
Input:
>>> 90210
Output:
>>> movq $90210, %rax

Test Case "MixedChars"
Input:
>>> 123abc456
Output:
>>> movq $123, %rax

Test Case "NegativeInt"
Input:
>>> -5
Output:
>>> movq $-5, %rax

Test Case "NegativeInt2"
Input:
>>> -456
Output:
>>> movq $-456, %rax

Error Case "MinusSign"
Input:
>>> -
Error Output:
>>> ## expected number [next = '?']

Error Case "MinusSignExtra"
Input:
>>> -a
Error Output:
>>> ## expected number [next = 'a']

Test Case "JustPlus"
Input:
>>> +
Output:

Assembled Test Case "Add"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 1+2
Output:
>>> 3
Cleaning up...

Assembled Test Case "Add2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 123 + 456
Output:
>>> 579
Cleaning up...

Assembled Test Case "Sub"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5 - 4
Output:
>>> 1
Cleaning up...

Assembled Test Case "Sub2"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 10 - 15
Output:
>>> -5
Cleaning up...

Assembled Test Case "AddAndSub"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 4 + 5 - 3
Output:
>>> 6
Cleaning up...

Assembled Test Case "Mult"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 2 * 4
Output:
>>> 8
Cleaning up...

Error Case "AddAdd"
Input:
>>> 2 + +
Error Output:
>>> movq $2, %rax
>>> pushq %rax
>>> ## expected NOT operator [next = '?']

Assembled Test Case "OrderOfOps"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 3 * 2 + 2 * 2
Output:
>>> 10
Cleaning up...

Error Case "Divide"
Input:
>>> 9 / 3
Error Output:
>>> movq $9, %rax
>>> pushq %rax
>>> ## division stub

Error Case "Mod"
Input:
>>> 12 % 5
Error Output:
>>> movq $12, %rax
>>> pushq %rax
>>> ## modulus stub

Assembled Test Case "MultiMult"
Compiling...
Assembling... [gcc tmp.s -o Tmp]
Running... [./Tmp > tmp_output.txt]
Input:
>>> 5 * 4 * 3 * 2 * 1
Output:
>>> 120
Cleaning up...

Passed 23 / 23 tests
```
