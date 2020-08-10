# CHAPTER 5: Pointers and Arrays

## 5.1 Pointers and Addresses

## 5.2 Pointers and Function Arguments

#### Exercise 5-1

As written, getint treats a `+` or `-` not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.

#### Exercise 5-2

Write `getfloat`, the floating-point analog of `getint`. What type does `getfloat` return as its function value?

## 5.3 Pointers and Arrays

## 5.4 Address Arithmetic

## 5.5 Character Pointers and Functions

#### Exercise 5-3

Write a pointer version of the function `strcat` that we showed in Chapter 2: `strcat(s,t)` copies the string `t` to the end of `s`.

#### Exercise 5-4

Write the function `strend(s,t)`, which returns 1 if the string `t` occurs at the end of the string `s`, and zero otherwise.

#### Exercise 5-5

Write versions of the library functions `strncpy`, `strncat`, and `strncmp`, which operate on at most the first `n` characters of their argument strings. For example, `strncpy(s,t,n)` copies at most `n` characters of `t` to `s`. Full descriptions are in Appendix B.

#### Exercise 5-6

Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include `getline` (Chapters 1 and 4), `atoi`, `itoa`, and their variants (Chapters 2, 3, and 4), `reverse` (Chapter 3), and `strindex` and `getop` (Chapter 4).

## 5.6 Pointer Arrays; Pointers to Pointers

#### Exercise 5-7

Rewrite `readlines` to store lines in an array supplied by `main`, rather than calling `alloc` to maintain storage. How much faster is the program?
