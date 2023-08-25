# Console Calculator

My coursework on Data Structures and Algorithmes. 
Purpose of the coursework was to program console calculator capable of processing math expressions in the correct order, considering parentheses. 
Firstly, the program converts expression to the prefix one and prints it.
Then, calculates and prints the result.

Available operations:
- ``+`` Addition
- ``-`` Subtraction
- ``*`` Multiplication
- ``/`` Division
- ``()`` Parentheses
- ``^`` Exponentiation
- ``sqrt`` Extracting square root
- ``-`` Negatiation
- Trigonometric: ``sin``, ``cos``, ``tg``, ``ctg``
- Logarithms: ``log2`` binary, ``ln`` natural, ``log`` decimal

Calculator can replace ``pi`` and ``e`` constants.

The expression processing algorithm is based on the self-written [Stack](cw3/Stack.h) class and regular expressions.
[Unit tests](cw3_unittest/cw3_unittest.cpp) are provided.

### Examples

The 1st line is the input, the 2nd line is the prefix expression, the 3rd line is the result.

```
5 * 4 + 3 * 8 - 9 / 3
- + * 5 4 * 3 8 / 9 3
41
```

```
(cos(3 * pi) ^ 2 - sqrt(4)) / 2
/ - ^ cos * 3 3.141593 2 sqrt 4 2
-0.5
```

```
log2(2^5) - ln(e^4)
- log2 ^ 2 5 ln ^ 2.718282 4
1
```
