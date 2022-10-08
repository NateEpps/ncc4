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
    * Multiply / divide / modulus
    * Parenthesis
    * Tool- Expression generator
    * Testing- Allow actual assembling of generated code! ✅
* **0.3** - General expressions, including function calls
* **0.4** - Declaration and assignment
* **0.5** - `if`/`else`, maybe loops too
* ...
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

Passed 17 / 17 tests
```
